source /usr/local/rb3-oecore-x86_64/environment-setup-aarch64-oe-linux
make clean
python ./modules/mavlink/pymavlink/tools/mavgen.py -o include/mavlink --lang C --wire-protocol 2.0 modules/mavlink/message_definitions/v1.0/ardupilotmega.xml
if make -j10; then
    cp mavlink-routerd ~/code/distro
    echo "+++++++++++++ Success "
else
    echo "------------- Fail "
fi
