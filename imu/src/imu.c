/*
 * Title: IMU-MPU6050 interfacing with 96Boards CE
 * Author: Manivannan Sadhasivam
 * Copyright (c) 2017 Linaro Ltd.
 * All rights reserved.
 ********************************
 * 
 * I2C0 --> MPU6050
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <endian.h>
#include <math.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "mraa/i2c.h"

#define I2C_BUS 0
#define UNIX_PATH_MAX 108

/* register definitions */
#define MPU6050_ADDR 0x68
#define MPU6050_REG_PWR_MGMT_1 0x6b
#define MPU6050_REG_SMPRT_DIV 0x19
#define MPU6050_REG_RAW_ACCEL_X 0x3b
#define MPU6050_REG_RAW_ACCEL_Y 0x3d
#define MPU6050_REG_RAW_ACCEL_Z 0x3f
#define MPU6050_REG_RAW_GYRO_X 0x43
#define MPU6050_REG_RAW_GYRO_Y 0x45
#define MPU6050_REG_RAW_GYRO_Z 0x47
#define MPU6050_REG_CONFIG 0x1a
#define MPU6050_REG_GYRO_CONFIG 0x1b
#define MPU6050_REG_ACCEL_CONFIG 0x1c

/* bit definitions */
#define MPU6050_WAKEUP 0x00
#define MPU6050_RESET 0x80
#define MPU6050_SLEEP (1 << 6)
#define MPU6050_PLL_GYRO_X (1 << 1)
#define MPU6050_TEMP_DIS (1 << 3)
#define MPU6050_SRATE 0x00
#define MPU6050_FILTER_20HZ (1 << 4)
#define MPU6050_GYRO_FS_250 0x00
#define MPU6050_ACCEL_FS_2 0x00

/* accelerometer scale factor for (+/-)2g */
#define MPU6050_ACCEL_SCALE 16384.0

/* gyroscope scale factor for (+/-)250/s */
#define MPU6050_GYRO_SCALE 131.0

volatile sig_atomic_t flag = 1;
int socket_fd, conn_fd, ret;
struct sockaddr_un address;

void sig_handler(int signum)
{
	flag = 0;
}

float dist(int16_t a, int16_t b)
{
	  return sqrt((a*a) + (b*b));
}

float y_rotation(int16_t x, int16_t y, int16_t z)
{
	float radians;

	radians = atan2(x, dist(y, z));

	return -(radians * (180.0 / M_PI));
}

float x_rotation(int16_t x, int16_t y, int16_t z)
{
	float radians;

	radians = atan2(y, dist(x, z));
	
	return (radians * (180.0 / M_PI));
}

int16_t i2c_read_word(mraa_i2c_context dev, uint8_t command)
{
	return be16toh(mraa_i2c_read_word_data(dev, command));
}

int main(void) 
{
	mraa_result_t status = MRAA_SUCCESS;
	socklen_t addr_len;
    	struct sigaction action;
	uint8_t data;
	int16_t accel_data[3];
	int16_t gyro_data[3];
	int16_t accel_offset[3];
	int16_t gyro_offset[3];
	float x_rot, y_rot;
	float angle_x = 0;
	float angle_y = 0;
	char buffer_x[20], buffer_y[20];
	char accel[50];

    	memset(&action, 0, sizeof(struct sigaction));
    	action.sa_handler = sig_handler;
    	sigaction(SIGTERM, &action, NULL);

	/* create a socket */
	socket_fd = socket(AF_UNIX, SOCK_STREAM,0);
	if (socket_fd < 0) {
		printf("socket creation failed\n");
		return -1;
	}

	memset(&address, 0, sizeof(struct sockaddr_un));

	address.sun_family = AF_UNIX;
	snprintf(address.sun_path, UNIX_PATH_MAX, "/tmp/socket");

	/* bind the socket to /tmp/socket */
	if (bind(socket_fd, (struct sockaddr *)&address, sizeof(struct sockaddr_un)) != 0) {
		printf("bind failed\n");
		goto err_exit;
	}

	/* listen for connections */
	if (listen(socket_fd, 5) != 0) {
		printf("listen failed\n");
		goto err_exit;
	}

	mraa_i2c_context i2c = mraa_i2c_init(I2C_BUS);
	if (i2c == NULL)
		goto err_exit;

    	status = mraa_i2c_address(i2c, MPU6050_ADDR);
    	if (status != MRAA_SUCCESS)
        	goto err_exit;

	/* reset the sensor */
	status = mraa_i2c_write_byte_data(i2c, MPU6050_RESET, MPU6050_REG_PWR_MGMT_1);
	if (status != MRAA_SUCCESS)
		goto err_exit;

	usleep(50000);

	/* configure power management regsiter */
	ret = mraa_i2c_read_byte_data(i2c, MPU6050_REG_PWR_MGMT_1);
	if (ret == -1)
		goto err_exit;
	
	data = ret;
	data |= (MPU6050_PLL_GYRO_X | MPU6050_TEMP_DIS);
        data &=	~(MPU6050_SLEEP);

	status = mraa_i2c_write_byte_data(i2c, data, MPU6050_REG_PWR_MGMT_1);
    	if (status != MRAA_SUCCESS)
        	goto err_exit;
	
	usleep(50000);

	/* 
	 * set 1KHz sample rate 
	 * sample rate = (gyro_rate / (1 + SMPRT_DIV)) = 1 / (0+1) = 1 KHz
	 */
	status = mraa_i2c_write_byte_data(i2c, MPU6050_SRATE, MPU6050_REG_SMPRT_DIV);
	if (status != MRAA_SUCCESS)
		goto err_exit;

        status = mraa_i2c_write_byte_data(i2c, MPU6050_FILTER_20HZ, MPU6050_REG_CONFIG);
	if (status != MRAA_SUCCESS)
		goto err_exit;

	/* set 250/s full scale range */
        status = mraa_i2c_write_byte_data(i2c, MPU6050_GYRO_FS_250, MPU6050_REG_GYRO_CONFIG);
	if (status != MRAA_SUCCESS)
		goto err_exit;

	/* set 2g full scale range */
        status = mraa_i2c_write_byte_data(i2c, MPU6050_ACCEL_FS_2, MPU6050_REG_ACCEL_CONFIG);
	if (status != MRAA_SUCCESS)
		goto err_exit;

	usleep(20000);

	/* read accel data for calculating offset */
	accel_offset[0] = i2c_read_word(i2c, MPU6050_REG_RAW_ACCEL_X) / MPU6050_ACCEL_SCALE;
	accel_offset[1] = i2c_read_word(i2c, MPU6050_REG_RAW_ACCEL_Y) / MPU6050_ACCEL_SCALE;
	accel_offset[2] = i2c_read_word(i2c, MPU6050_REG_RAW_ACCEL_Z) / MPU6050_ACCEL_SCALE;

        /* read gyro data for calculating offset */
        gyro_offset[0] = i2c_read_word(i2c, MPU6050_REG_RAW_GYRO_X) / MPU6050_GYRO_SCALE;
        gyro_offset[1] = i2c_read_word(i2c, MPU6050_REG_RAW_GYRO_Y) / MPU6050_GYRO_SCALE;

	/* wait until connection with client (blocking) */
	while((conn_fd = accept(socket_fd, (struct sockaddr *)&address, &addr_len)) <= -1);

	while(flag) {
		/* read raw accel data */
		accel_data[0] = i2c_read_word(i2c, MPU6050_REG_RAW_ACCEL_X) / MPU6050_ACCEL_SCALE;
		accel_data[1] = i2c_read_word(i2c, MPU6050_REG_RAW_ACCEL_Y) / MPU6050_ACCEL_SCALE;
		accel_data[2] = i2c_read_word(i2c, MPU6050_REG_RAW_ACCEL_Z) / MPU6050_ACCEL_SCALE;
	
		/* read raw gyro data */
		gyro_data[0] = i2c_read_word(i2c, MPU6050_REG_RAW_GYRO_X) / MPU6050_GYRO_SCALE;
		gyro_data[1] = i2c_read_word(i2c, MPU6050_REG_RAW_GYRO_Y) / MPU6050_GYRO_SCALE;			 
		gyro_data[2] = i2c_read_word(i2c, MPU6050_REG_RAW_GYRO_Z) / MPU6050_GYRO_SCALE;

		accel_data[0] -= accel_offset[0];
		accel_data[1] -= accel_offset[1];
		accel_data[2] -= accel_offset[2];

		gyro_data[0] -= gyro_offset[0];
		gyro_data[1] -= gyro_offset[1];

		/* calculate x and y axes rotation */
	        x_rot = x_rotation(accel_data[0], accel_data[1], accel_data[2]);
		y_rot = y_rotation(accel_data[0], accel_data[1], accel_data[2]);

		/* implement complementary filter for sensor fusion */
		angle_x = (0.98)*(angle_x + (gyro_data[0] * 0.02)) + (0.02 * x_rot);
		angle_y = (0.98)*(angle_y + (gyro_data[1] * 0.02)) + (0.02 * y_rot);
		
		memset(accel, 0, sizeof(accel));

		sprintf(buffer_x, "%f", angle_x);
		sprintf(buffer_y, "%f", angle_y);
		strcat(accel, buffer_x);
		strcat(accel, " ");
		strcat(accel, buffer_y);
		strcat(accel, "\n");

		/* send data to client */
		ret = write(conn_fd, accel, 50);
		if (ret < 0) {
			printf("server write error\n");
			goto err_exit;
		}

		usleep(20000);
	}

	close(conn_fd);
	close(socket_fd);
	unlink(address.sun_path);
	
	return 0;
err_exit:
        close(conn_fd);
        close(socket_fd);
        unlink(address.sun_path);

	return -1;
}
