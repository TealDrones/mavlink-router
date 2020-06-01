source /usr/local/rb3-oecore-x86_64/environment-setup-aarch64-oe-linux
./autogen.sh
./configure CFLAGS='-g -O2' \
    --sysconfdir=/etc \
    --localstatedir=/var \
    --libdir=/usr/lib64 \
    --prefix=/usr \
    --host=aarch64
make clean
python ./modules/mavlink/pymavlink/tools/mavgen.py -o include/mavlink --lang C --wire-protocol 2.0 modules/mavlink/message_definitions/v1.0/ardupilotmega.xml
if make -j10; then
    echo "+++++++++++++ Success "
    scp mavlink-routerd pi@dmz.tealdrones.com:~/code/distro/
    exit 0
else
    echo "------------- Fail "
    exit 1
fi
