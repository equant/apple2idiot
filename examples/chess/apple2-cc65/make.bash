cc65 -g -Oi -t apple2 weather.c
cc65 -g -Oi -t apple2 inputline.c 
cc65 -g -Oi -t apple2 menu.c 
cc65 -g -Oi -t apple2 screen.c 
ca65 -g weather.s 
ca65 -g inputline.s 
ca65 -g menu.s 
ca65 -g screen.s 
ld65 -o weather -t apple2 weather.o inputline.o menu.o screen.o apple2.lib

#cl65 -t apple2 weather.c -o weather
#cl65 -c -Oirs -t apple2 weather.c -o weather
java -jar ~/bin/AppleCommander.jar -d hello.dsk weather
java -jar ~/bin/AppleCommander.jar -as hello.dsk weather bin < weather
java -jar ~/bin/AppleCommander.jar -l hello.dsk
java -jar ~/bin/AppleCommander.jar -as ~/bin/ADTPro-2.1.0/disks/dev.dsk weather bin < weather.apple2 
