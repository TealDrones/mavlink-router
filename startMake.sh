#!/bin/bash
source /usr/local/rb3-oecore-x86_64/environment-setup-aarch64-oe-linux 
./autogen.sh
./configure CFLAGS='-g -O2' CXXFLAGS='-g -O2' --sysconfdir=/etc --localstatedir=/var --libdir=/usr/lib --with-rootprefix= --with-rootlibdir=/lib --host=aarch64-oe-linux --enable-mavlink
if make -j8; then
	scp dcm pi@dmz.tealdrones.com:/home/pi/code/distro/dcm.x.x.x
	scp teal.conf pi@dmz.tealdrones.com:/home/pi/code/distro/teal.conf.x.x.x
	cp dcm ../distro/dcm.0.0.9
	cp teal.conf ../distro/teal.conf.0.0.9

	echo "Success +++++++++++++++++++++++++"
else
	echo "Build Fail ----------------------"
fi
cd tools/export_v4l2_param_xml
make

