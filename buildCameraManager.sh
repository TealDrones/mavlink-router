#!/bin/bash
rm -Rf camera-manager
git clone git@github.com:TealDrones/camera-manager.git
pushd camera-manager
git submodule update --init --recursive
git fetch --tags
source /usr/local/rb3-oecore-x86_64/environment-setup-aarch64-oe-linux 
./autogen.sh
./configure CFLAGS='-g -O2' CXXFLAGS='-g -O2' --sysconfdir=/etc --localstatedir=/var --libdir=/usr/lib --with-rootprefix= --with-rootlibdir=/lib --host=aarch64-oe-linux --enable-mavlink
ver=$(git rev-parse --abbrev-ref HEAD)
make
scp dcm pi@dmz.tealdrones.com:/home/pi/code/distro/dcm.${ver}
#cd tools/export_v4l2_param_xml
#make
popd
