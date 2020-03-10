#!/bin/bash
pushd camera-manager
git pull
git submodule update --init --recursive
source /usr/local/rb3-oecore-x86_64/environment-setup-aarch64-oe-linux 
./autogen.sh
./configure CFLAGS='-g -O2' CXXFLAGS='-g -O2' --sysconfdir=/etc --localstatedir=/var --libdir=/usr/lib --with-rootprefix= --with-rootlibdir=/lib --host=aarch64-oe-linux --enable-mavlink
if make; then
	scp dcm pi@dmz.tealdrones.com:/home/pi/code/distro/dcm.x.x.x
	echo "Success +++++++++++++++++++++++++"
else
	echo "Build Fail ----------------------"
fi
cd tools/export_v4l2_param_xml
make
popd
