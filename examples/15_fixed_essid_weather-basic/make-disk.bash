diskname='15_fixed_essid_weather-cc65.dsk'

echo "-------------------------"
echo "Files on disk image (before):"
java -jar ~/bin/AppleCommander.jar -l $diskname

for f in *.BAS
do                                                                              
    echo "-------------------------"
    echo Removing file: $f
    java -jar ~/bin/AppleCommander.jar -d $diskname $f
    echo Adding file: $f
    java -jar ~/bin/AppleCommander.jar -bas $diskname $f < $f
done

echo "-------------------------"
echo "Files on disk image (after):"
java -jar ~/bin/AppleCommander.jar -l $diskname
