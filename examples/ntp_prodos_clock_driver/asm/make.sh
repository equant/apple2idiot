~/bin/Merlin32_v1.0/Linux64/Merlin32 -V . BELL.S
mv BELL BELL#068000
cadius ADDFILE ntp_clock_dev-prodos.po /NTPCLOCKDEV/ BELL#068000
mame apple2e -skip_gameinfo -window -nomax -flop1 ntp_clock_dev-prodos.po
