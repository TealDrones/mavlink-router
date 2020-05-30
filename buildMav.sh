source /usr/local/rb3-oecore-x86_64/environment-setup-aarch64-oe-linux
./configure CFLAGS='-g -O2' CXXFLAGS='-g -O2' --sysconfdir=/etc --localstatedir=/var --libdir=/usr/lib          --with-rootprefix=       --with-rootlibdir=/lib 
./autogen.sh && ./configure CFLAGS='-g -O2' \
        --sysconfdir=/etc --localstatedir=/var --libdir=/usr/lib64 \
    --prefix=/usr
make clean
python ./modules/mavlink/pymavlink/tools/mavgen.py -o include/mavlink --lang C --wire-protocol 2.0 modules/mavlink/message_definitions/v1.0/ardupilotmega.xml
if make -j10; then
    scp mavlink-routerd root@drone:~/code/distro/
    echo "+++++++++++++ Success "
else
    echo "------------- Fail "
fi
