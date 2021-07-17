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
