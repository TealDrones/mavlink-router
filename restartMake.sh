#!/bin/bash
source /usr/local/rb3-oecore-x86_64/environment-setup-aarch64-oe-linux 
if make -j16; then
	scp dcm pi@dmz.tealdrones.com:/home/pi/code/distro/dcm.x.x.x
	cp dcm ../distro/dcm.x.x.x
	echo "Success +++++++++++++++++++++++++"
else
	echo "Build Fail ----------------------"
fi


