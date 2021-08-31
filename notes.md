## Debugging board 08/28/2021

What the ESP thinks is address 0x00 (0xC200) is 0xC2FF,49919 to the Apple.
AND the data from the ESP is 192 and the apple sees 3, so the endian is backwards
for the data and logic levels for the address are flipped.

## Needed changes to board

DONE: Add a GND and +5V breakout.
Fix DEVSEL address in silkscreen docs.
DONE: Unconnect addresses above A7.
DONE: Add diode to +5V.


## Thanks

Renee
flux
c2t

## Ordered:

* 5PCS IDT7132SA100P IDT7132SA DIP-48 HIGH-SPEED 2K x 8 DUAL-PORT STATIC RAM 
* STM32F411 "BlackPill" Development Board

## Misc

* https://pastebin.com/raw/1kR0vbRA

## ESP32 Interupt Issues

* ESP32 Thread I started: https://esp32.com/viewtopic.php?f=12&t=21855
	* " Consider 74ls373 to latch the value to be processed by software."
	* It might also be worth trying ESP32's assembly high-level interrupts. I've never used them personally, but they can allegedly give interrupt latencies that are significantly lower than the ~2us for regular ESP32 C interrupts.
		* See: https://esp32.com/viewtopic.php?t=422
		* See: https://docs.espressif.com/projects/esp ... rupts.html
	* components/esp_system/port/soc/esp32/dport_panic_highint_hdl.S

## Python binar/hex/dec manipulation

```
In [11]: format(10, '016b')
Out[11]: '0000000000001010'

bin(10)
```


## Jumper and Breakout pins

* Input (to ESP32) only
    ~IOSEL  (from Apple2)
    ~BSYL   (from Apple2 side of IDT7132)
    ~BSYR   (from ESP32 side of IDT7132)


+ Apple II Pins to header
    + IOSEL
    + DEVSEL
    + IOSTROBE
+ IDT7132S Pins to header
    + BSYL
    + BSYR
+ ESP32 Pins to header
    + GPIO 0
    + GPIO 1    (TX)
    + GPIO 2
    + GPIO 3    (RX)
    + GPIO 4
    + GPIO 26
    + GPIO 27
    + GPIO 32
    + GPIO 33
    + GPIO 34   (input only) No pullup, needs resistor?
    + GPIO 35   (input only) No pullup, needs resistor?
    + SENSOR_VP (input only) No pullup, needs resistor?
    + SENSOR_VN (input only) No pullup, needs resistor?
