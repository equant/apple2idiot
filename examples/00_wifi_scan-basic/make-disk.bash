diskname='00_wifi_scan-basic.dsk'
files_to_add=CSCANWIFI.BAS,SCANWIFI.BAS,SHOWIP.BAS

for f in ${files_to_add//,/ };                                                      
do                                                                              
    echo "-------------------------"
    echo Removing file: $f
    java -jar ~/bin/AppleCommander.jar -d $diskname $f
    echo Adding file: $f
    java -jar ~/bin/AppleCommander.jar -bas $diskname $f < $f
done

#java -jar ~/bin/AppleCommander.jar -l diskname
#java -jar ~/bin/AppleCommander.jar -as ~/bin/ADTPro-2.1.0/disks/dev.dsk weather bin < weather.apple2 
