# Dronecode Camera Manager

[![Build Status](https://travis-ci.org/Dronecode/camera-manager.svg?branch=master)](https://travis-ci.org/intel/camera-streaming-daemon)
<a href="https://scan.coverity.com/projects/01org-camera-streaming-daemon">
  <img alt="Coverity Scan Build Status"
       src="https://scan.coverity.com/projects/12056/badge.svg"/>
</a>

The [Dronecode Camera Manager](https://camera-manager.dronecode.org/en/) (DCM) is an extensible Linux camera server for interfacing cameras with the Dronecode platform. 

It provides a [MAVLink Camera Protocol](https://mavlink.io/en/protocol/camera.html) compatible API for video and image capture etc., and an RTSP service for advertising and sharing video streams. The server can connect to and manage multiple cameras, and has been designed so that it can be extended to support new camera types and protocols when needed. 

> **Tip** The DCM is the easiest way for Camera OEMs to interface with the Dronecode platform. Many cameras will just work "out of the box". At most OEMs will need to implement a camera integration layer.

Full instructions for [building](https://camera-manager.dronecode.org/en/getting_started/), [using](https://camera-manager.dronecode.org/en/guide/overview.html), [extending](https://camera-manager.dronecode.org/en/guide/extending.html) and [contributing](https://camera-manager.dronecode.org/en/contribute/) to the camera manager can be found in the [guide](https://camera-manager.dronecode.org/en/).

# Camera Manual 
# PI Setup - this is done
u/p:pi/All4TealDrones!

## Installation - done
```bash
sudo apt-get update
sudo apt install -y screen android-tools-adb android-tools-fastboot
```

## ADB Configuration on PI - done
```bash
sudo usermod -aG plugdev $LOGNAME
echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="05c6", ATTR{idProduct}=="901d", MODE="0666"' >> /etc/udev/rules.d/50-usb-perms.conf
sudo udevadm control --reload-rules
```
# 845HDK operation instructions

## starts the root console

u/p:root/oelinux123
from the pi
```bash
# screen /dev/ttyUSB0 115200
```
this will get you to the login screen

## check adb
from the pi

```bash
# adb devices
List of devices attached
(no serial number)	device
```

## FastBoot
from the pi

```bash
# fastboot
fastboot: usage: no command
```

# 845 with good privelage

```bash
adb shell mount -o rw,remount /
adb shell setenforce 0
```

# Hal3Test Tool 
from the 845
## visible
```bash
# hal3_test
CAM0>> A:id=0,gsize=1280x720,gformat=yuv420,gnode=/dev/video4
# hal3 snapshot still
CAM0>> s:1
# hal3 video record
CAM0>> V:id=0,gsize=1280x720,gformat=yuv420,gnode=/dev/video4,vsize=1920x1080,ssize=1920x1080,sformat=jpeg,fpsrange=30-30,codectype=0,bitrate=16
# stop record
CAM0>> G:id=0,gsize=1280x720,gformat=yuv420,gnode=/dev/video4
```

### visible gst still
from the 845
```bash
gst-launch-1.0 v4l2src device=/dev/video4 num-buffers=1 ! 'video/x-raw,width=1920,height=1088' ! jpegenc ! filesink location=test.jpg
```

### visible gst video
from the 845
```bash
# gst-launch-1.0 -e v4l2src device=/dev/video4 ! videoparse width=1280 height=768 format=nv12 framerate=30 !  \ 
omxh264enc control-rate=constant target-bitrate=2000000 ! \
'video/x-h264,streamformat=(string)byte-stream,profile=main' ! \
h264parse ! filesink location=P1.h264
```

## IR Camera

this has been fixed in the MK1, and will be in the next release

### IR Initialize

see ticket https://tech.intrinsyc.com/issues/2116


### IR Test Still
```bash
gst-launch-1.0 v4l2src device=/dev/video2 num-buffers=1 ! 'video/x-raw,width=640,height=512' ! jpegenc ! filesink location=/data/misc/camera/IRStill.jpg
```

### IR Test Video
```bash
gst-launch-1.0 v4l2src device=/dev/video2 num-buffers=300 ! 'video/x-raw,width=640,height=512' ! \
omxh264enc control-rate=constant target-bitrate=2000000 ! \
'video/x-h264,streamformat=(string)byte-stream,profile=main' ! \
h264parse ! filesink location=P1.h264
```



### IR Stream
```bash
gst-launch-1.0 v4l2src device=/dev/video2 ! 'video/x-raw,width=640,height=512' ! queue ! videoflip video-direction=180 ! omxh264enc control-rate=constant target-bitrate=1000000 ! video/x-h264,profile=main ! rtph264pay pt=96 ! udpsink host=192.168.168.200 port=5600

```

### visible gst video hal3_test

```bash
hal3_test
A:id=0,gsize=1280x720,gformat=yuv420,gnode=/dev/video4
```

in seperate terminal setup for gstream
```bash
gst-launch-1.0 v4l2src device=/dev/video4 ! videoparse width=1280 height=768 format=nv12 framerate=30 ! queue ! videoflip video-direction=180 ! omxh264enc control-rate=constant target-bitrate=2000000 ! video/x-h264,profile=main ! rtph264pay pt=96 ! udpsink host=192.168.168.200 port=5601
```

### UDP Stream playback on destination without ground control
```bash
gst-launch-1.0 -vc udpsrc port=5600 ! application/x-rtp, payload=96 ! rtph264depay ! omxh264dec ! videoscale ! videorate ! videoconvert ! autovideosink
```

### 
dronecode camera service
```bash
systemctl stop dronecode-camera-manager.service
systemctl start dronecode-camera-manager.service
systemctl reset dronecode-camera-manager.service
systemctl disable dronecode-camera-manager.service
systemctl enable dronecode-camera-manager.service
```

### Bring Up Gimbal
```bash
cd /home/root/tealflasher/
echo 1 > /sys/kernel/debug/regulator/hadron_pwr_5p0/enable 
./set-gpio.sh 32 1
./set-gpio.sh 32 0
```

configuration is at:
