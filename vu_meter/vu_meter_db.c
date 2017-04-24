/* Volume Unit meter (VU meter) 
 * 
 * 96Boards examples
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <signal.h>

#include <alsa/asoundlib.h>

#define BUFF_SIZE 320 * 2

static int running = 1;

void sig_handler(int signum)
{
	if (signum == SIGINT) {
		printf("closing the signal capture...\n");
		running = 0;
	}
}

short get_rms(short *buffer)
{
	long rms_val, i;

	for (i = 0; i < BUFF_SIZE; i++) {
		rms_val += buffer[i] * buffer[i];
	}

	rms_val = rms_val / BUFF_SIZE;
	
	return sqrt(rms_val);
}

void print_progress(double progress) 
{
    int barWidth = 100, i;
    int pos =  progress;

    printf("%c",'[');

    for (i = 0; i < barWidth; ++i) 
    {
        if (i < pos) {
            printf("%c",'=');
        }
        else if (i == pos) {
            printf("%c",'>');
        }
        else {
            printf("%c",' ');
        }
    }

    printf("] %f%% \r",(progress));
    fflush(stdout);
}

int main(int argc, char *argv[])
{
	int ret;
	int channels = 2;
	short val;
	short buffer[BUFF_SIZE];
	double log_val;
	char *device;
	int old_range = 30, new_range = 100;
	snd_pcm_uframes_t frames = 320;
	unsigned int rate = 44100;
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_t *capture_handle;
	snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

	printf("\n##### Volume Unit Meter #####\n\n");
	if (argc < 2) {
		device = "default";
		printf("Using the default source...\n");
	} else {
		device = argv[1];
		printf("Using the source: %s\n", device);
	}

	/* Open the PCM source in capture mode */
	if ((ret = snd_pcm_open(&capture_handle, device, SND_PCM_STREAM_CAPTURE, 0)) < 0) {
		fprintf(stderr, "Unable to open pcm device: %s\n", snd_strerror(ret));
		return -1;
	}

	/* Allocate hardware parameters object */
	snd_pcm_hw_params_alloca(&hw_params);

	/* Initialize with default values */
	ret = snd_pcm_hw_params_any(capture_handle, hw_params);
	if (ret < 0)
		return ret;

	/* Set interleaved mode */
	snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);

	/* Set the sample format */
	snd_pcm_hw_params_set_format(capture_handle, hw_params, format);
	
	/* Set the sampling rate */
	snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, 0);

	/* Set period size */
	snd_pcm_hw_params_set_period_size(capture_handle, hw_params, frames, 0);

	/* Set the channel type (Stereo) */
	snd_pcm_hw_params_set_channels(capture_handle, hw_params, channels);

	/* Write the configuration to driver */
	if ((ret = snd_pcm_hw_params (capture_handle, hw_params)) < 0) {
		fprintf(stderr, "Unable to write configuration to driver: %s\n", snd_strerror(ret));
		return -1;
	}

	if ((ret = snd_pcm_prepare (capture_handle)) < 0) {
		fprintf (stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror (ret));
		return -1;
	}

	signal(SIGINT, sig_handler);

	printf("starting signal capture from source...\n");

	while(running) {
		/* Start audio capture */
		if ((ret = snd_pcm_readi(capture_handle, buffer, frames)) < 0) {
			fprintf (stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror (ret));
			exit (1);
		}
	
		val = get_rms(buffer);

		/* dB = 20 * log10(v) */
		log_val = (20 * log10(val));

		/* Scale the range to (0 - 100) */
		print_progress((((log_val - 60) * new_range) / old_range));
	}

	/* Close the interface */
	snd_pcm_close(capture_handle);

	return 0;
}
