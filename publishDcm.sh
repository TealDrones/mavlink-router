ssh mhunter@nebula "./buildit.sh"
adb shell "systemctl stop dcm"
sleep 5
adb push dcm /usr/bin/dcm
adb shell "systemctl start dcm"

