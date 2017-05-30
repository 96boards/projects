# vu_meter

Volume Unit meter (VU meter) is an application used to monitor the intensity of sound using ALSA programming interface
for linux. There are two variants of this application:

1. Using dB (decibels)
2. Using FFT (Fast Fourier Transform)

## Using dB:

Here, the intensity of sound is calculated by computing RMS value of sampled audio signal and converting to dB. The
implementation is straight forward and simple.

Link to blog: http://www.96boards.org/blog/96boards-vu-meter-part-1/

### Hardware required:

1. [HiKey development board](http://www.96boards.org/product/hikey/)
2. USB mic

### Package dependencies:

1. ALSA library

### Building and Running:

``` shell
$ git clone https://github.com/96boards/projects.git
$ cd projects
$ cd vu_meter
$ make
$ ./bin plughw:U0x46d0x825
```

Replace the Sound card info according to your device

### Conclusion:

Running the executable causes progress bar to move according to the sound intensity.

## Using FFT:

Under development
