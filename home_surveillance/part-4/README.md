# Part 4 - Setting up your Amazon Web Service (AWS) Cloud Service

Set up streaming of data from Dragonboard to AWS S3 bucket. AWS account and S3 needs to be configured
prior executing the script.

### Hardware requirements and Setup

* Dragonboard410C
* USB Webcam

Connect USB webcam and other I/O devices (Monitor, Keyboard etc...) to Dragonboard.

### Software Dependencies
 
Installed the dependencies mentioned in [Part-2](../part-2) along with the following:

``` shell
$ sudo easy_install boto3
```
### Create S3 bucket:
 
1. Go to https://aws.amazon.com/ and select Sign in to console 
2. Login to AWS using your Email and password (You’ll be redirected to console if you are already logged in)
3. Select S3 from Storage. S3 console will get opened.
4. Click on Create bucket button
5. Enter Bucket name and Region in the opened window (Bucket name should be unique across all existing bucket names in S3). 6. Click Next
7. If you want to customize your bucket, modify the properties otherwise keep on hitting Next until you find Create bucket button.
8. In the final window, you should see the Bucket name, region, properties and permissions. Under permissions the instance of the login account should get displayed. Then, click Create bucket.
9. The created bucket would get listed in the AWS S3 console.
 
### Set Object policy:
 
Select the created bucket and click Permissions tab on top
Then select Bucket policy and paste the following policy in the text field

```shell 	
{
  "Id": "Policy1495783674300",
  "Version": "2012-10-17",
  "Statement": [
    {
      "Sid": "Stmt1495783672125",
      "Action": "s3:*",
      "Effect": "Allow",
      "Resource": "arn:aws:s3:::homesurveillance",
      "Principal": "*"
    }
  ]
}
```
Replace ‘homesurveillance’ with your bucket name in the above policy and click Save.
Policy is essential for creating/modifying objects in the bucket. The above shown policy is just for demonstration purpose as it allows all AWS users to gain full access to the created bucket.
 
### Setup Boto SDK
 
Boto is the Python SDK offered by AWS for accessing services such as S3 and EC2. Boto should be installed using the command given under Software Dependencies section. Before using Boto, it needs to be configured with IAM. Obtain the AWS key Id and secret key by following the instructions given in below link:
 
https://aws.amazon.com/premiumsupport/knowledge-center/create-access-key/
 
After getting the ID and secret key, now we can configure Boto to use AWS. Paste the following content in ~/.aws/credentials hosted on Dragonboard410C.

 ```shell
	[default]
	aws_access_key_id = YOUR_ACCESS_KEY
	aws_secret_access_key = YOUR_SECRET_KEY
 ```
Replace AWS IAM key appropriately and set default region as same as what was given during AWS account creation in ~/.aws/config

 ```shell
	[default]
	region=us-east-1
 ```
Now Boto has been configured with IAM credentials.

### Stream data to S3 bucket

``` shell
$ git clone https://github.com/96boards/projects.git
$ cd projects/home-surveillance/part-4
```
Place the trained dataset and haarcascade_frontalface_default.xml to this directory

``` shell
$ cp -r ../part-2/trainer ../part-2/haarcascade_frontalface_default.xml ./
$ mkdir captured
$ sudo python streamface.py
```
[Link to Blog](http://www.96boards.org/blog/part-4-home-surveillance-project-96boards/)
