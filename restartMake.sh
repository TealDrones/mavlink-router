#!/bin/bash
source /usr/local/rb3-oecore-x86_64/environment-setup-aarch64-oe-linux 
if make -j16; then
	scp dcm root@drone:~/code/distro/dcm
	echo "Success +++++++++++++++++++++++++"
else
	echo "Build Fail ----------------------"
fi


