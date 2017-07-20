# vu_meter

Volume Unit meter (VU meter) is an application used to monitor the intensity of sound using ALSA programming interface
for linux. There are two variants of this application:

1. Using dB (decibels)
2. Using FFT (Fast Fourier Transform)

# Table of Contents
- [1) Using dB](#1-using-db)
- [2) Hardware Requirements](#2-hardware-requirements)
- [3) Package Dependencies](#3-package-dependencies)
- [4) Building and running](#4-building-and-running)
- [5) Conclusion](#5-conclusion)

# 1. Using dB:

Here, the intensity of sound is calculated by computing RMS value of sampled audio signal and converting to dB. The
implementation is straight forward and simple.

Link to blog: http://www.96boards.org/blog/96boards-vu-meter-part-1/

# 2. Hardware requirements:

1. [HiKey development board](http://www.96boards.org/product/hikey/)
2. [USB mic](https://www.adafruit.com/product/3367?gclid=Cj0KCQjwhrzLBRC3ARIsAPmhsnV7xmpPhkGgkUXuj0vmOFLwUCjxhiF1lbgvio7QglCJQwX9oMOCBvMaAs3YEALw_wcB)

# 3. Package Dependencies

1. ALSA library
```
$ sudo apt-get install libasound2
```

# 4. Building and Running:

``` shell
$ git clone https://github.com/96boards/projects.git
$ cd projects
$ cd vu_meter
$ make
$ ./bin plughw:U0x46d0x825
```

Replace the Sound card info according to your device

# 5. Conclusion:

Running the executable causes progress bar to move according to the sound intensity.

## Using FFT:

Under development
