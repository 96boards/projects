# Game Emulator

This project is aimed at running different game emulators on CE 96Boards.


# Table of Contents

- [1) Hardware](#1-hardware)
   - [1.1) Hardware requirements](#11-hardware-requirements)
   - [1.2) Hardware setup](#12-hardware-setup)
- [2) Software](#2-software)   
   - [2.1) Operating System](#21-operating-system)
   - [2.2) Package dependencies](#22-package-dependencies)
- [3) RetroArch](#3-retroarch)
   - [3.1) Emulator Installation](#31-emulator-installation)
   - [3.2) Core Installation](#32-core-installation)
   - [3.2) Game Execution](#33-game-execution)
- [4) RetroPie](#4-retropie)
   - [4.1) Installation](#41-installation)


***

# 1) Hardware

## 1.1 Hardware requirements

- [Dragonboard 410c](http://www.96boards.org/product/dragonboard410c/)
- [96Boards Compliant Power Supply](http://www.96boards.org/product/power/)

## 1.2 Hardware setup

- DragonBoard 410 is powered off
- Connect I/O devices (Monitor, Keyboard, etc...)
- Power on your DragonBoard 410c with 96Boards compliant power supply

# 2) Software

## 2.1 Operating System

- [Linaro Debian based OS (latest)](https://github.com/96boards/documentation/blob/master/ConsumerEdition/DragonBoard-410c/Downloads/Debian.md)

## 2.2 Package Dependencies

```shell
$ sudo apt-get update
$ sudo apt-get dist-upgrade

> Note: HiKey: Some packages might get corrupted by this, so run the following commmand to resolve.
$ sudo apt-get -f install

$ sudo apt-get install -y libsdl1.2-dev libsdl2-dev libboost-system-dev libboost-filesystem-dev \
libboost-date-time-dev libfreeimage-dev libfreetype6-dev libeigen3-dev libcurl4-openssl-dev libasound2-dev \
libgl1-mesa-dev cmake build-essential git pkg-config ffmpeg libavdevice-dev
```
# 3) RetroArch

#### Turn ON SWAP partition:

Use swapfile to prevent DragonBoard from running out of RAM. Follow the instructions [here](https://github.com/96boards/documentation/blob/master/ConsumerEdition/guides/sd_swapspace.md) for allocating swap space in SD card.

## 3.1 Emulator Installation

#### Clone the Emulator source

```shell
$ git clone git://github.com/libretro/RetroArch.git
```
#### Building and Installing the Emulator

```shell
$ cd RetroArch
$ ./configure
$ make -j 2
$ sudo make install
```
## 3.2 Core Installation

#### Clone the core source

All of the supported cores for RetroArch is available [here](https://github.com/libretro/). You can use any of them. For instance, follow the below instructions to clone and build ***snes*** core.

```shell
$ git clone https://github.com/libretro/snes9x2010.git
```
#### Building the core

```shell
$ cd snes9x2010 
$ make -f Makefile.libretro
```
After building, the core ***snes9x2010_libretro.so*** will get generated

## 3.3 Game Execution

Run the Emulator with compiled core and ROM.

```shell
retroarch -L snes9x2010_libretro.so <path_to_rom>
```
> Note: Replace <path_to_rom> with the path of appropriate ROM. Instructions for downloading ROM is not provided here.

# 4) RetroPie

## 4.1 Installation

#### Clone the source

```shell
$ git clone -b 96Boards https://github.com/Mani-Sadhasivam/RetroPie-Setup.git
```
#### Building the source

```shell
$ cd RetroPie-Setup
```
This script will install emulation station, RetroArch and few cores.

```shell
$ sudo ./retropie_setup.sh
```

Select **yes** to Copyright agreement and select **Basic install** from the opened dialog. After the installation has finished successfully, exit the dialog.

## 4.2 Game Execution

Place the downloaded ROMs into the appropriate core directory under ***/home/linaro/RetroPie/roms/***

Execute the following command and configure the keypad then select games by choosing the emulator in main window.

```shell
$ emulationstation
```

For more info please visit the official RetroPie Wiki [here](https://github.com/retropie/retropie-setup/wiki/First-Installation)
