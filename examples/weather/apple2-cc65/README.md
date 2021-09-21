# Apple2 Internet Weather Client Example

This is the C code to compile the software that runs on an Apple2 and makes use
of the Apple2idiot card to display the weather for a given city.


## How I use this

This is how I compile, make a disk and then stage the disk for transfer to my //c using ADTPro.

```
make
make TARGETS=apple2 dsk
cp weather.dsk ~/bin/ADTPro-2.1.0/disks/
```
