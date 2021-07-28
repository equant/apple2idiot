EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "apple2idiot"
Date "2021-07-27"
Rev "0.0.1"
Comp "Nathanial Hendler"
Comment1 "MIT license; see LICENSE file"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_02x25_Counter_Clockwise J1
U 1 1 5E339C7A
P 2000 3300
F 0 "J1" H 2050 4717 50  0000 C CNN
F 1 "CARD EDGE" H 2050 4626 50  0000 C CNN
F 2 "pub:AppleIIBus" H 2000 3300 50  0001 C CNN
F 3 "~" H 2000 3300 50  0001 C CNN
	1    2000 3300
	1    0    0    -1  
$EndComp
Text Label 1750 2100 2    50   ~ 0
~IOSEL
Text Label 1750 2200 2    50   ~ 0
A0
Text Label 1750 2300 2    50   ~ 0
A1
Text Label 1750 2400 2    50   ~ 0
A2
Text Label 1750 2500 2    50   ~ 0
A3
Text Label 1750 2600 2    50   ~ 0
A4
Text Label 1750 2700 2    50   ~ 0
A5
Text Label 1750 2800 2    50   ~ 0
A6
Text Label 1750 2900 2    50   ~ 0
A7
Text Label 1750 3000 2    50   ~ 0
A8
Text Label 1750 3100 2    50   ~ 0
A9
Text Label 1750 3200 2    50   ~ 0
A10
Text Label 1750 3300 2    50   ~ 0
A11
Text Label 1750 3400 2    50   ~ 0
A12
Text Label 1750 3500 2    50   ~ 0
A13
Text Label 1750 3600 2    50   ~ 0
A14
Text Label 1750 3700 2    50   ~ 0
A15
Text Label 1750 3800 2    50   ~ 0
R~W
Text Label 1750 3900 2    50   ~ 0
SYNC
Text Label 1750 4000 2    50   ~ 0
~IOSTRB
Text Label 1750 4100 2    50   ~ 0
RDY
Text Label 1750 4200 2    50   ~ 0
~DMA
Text Label 1750 4300 2    50   ~ 0
INTOUT
Text Label 1750 4400 2    50   ~ 0
DMAOUT
Text Label 1750 4500 2    50   ~ 0
+5V
Text Label 2350 4500 0    50   ~ 0
GND
Text Label 2350 4400 0    50   ~ 0
DMAIN
Text Label 2350 4300 0    50   ~ 0
INTIN
Text Label 2350 4200 0    50   ~ 0
~NMI
Text Label 2350 4100 0    50   ~ 0
~IRQ
Text Label 2350 4000 0    50   ~ 0
~RES
Text Label 2350 3900 0    50   ~ 0
~INH
Text Label 2350 3800 0    50   ~ 0
-12V
Text Label 2350 3700 0    50   ~ 0
-5V
Text Label 2350 3500 0    50   ~ 0
7M
Text Label 2350 3400 0    50   ~ 0
Q3
Text Label 2350 3300 0    50   ~ 0
PHI1
Text Label 2350 3200 0    50   ~ 0
USER1
Text Label 2350 3100 0    50   ~ 0
PHI0
Text Label 2350 3000 0    50   ~ 0
~DEVSEL
Text Label 2350 2100 0    50   ~ 0
+12V
Text Label 2350 2200 0    50   ~ 0
D0
Text Label 2350 2300 0    50   ~ 0
D1
Text Label 2350 2400 0    50   ~ 0
D2
Text Label 2350 2500 0    50   ~ 0
D3
Text Label 2350 2600 0    50   ~ 0
D4
Text Label 2350 2700 0    50   ~ 0
D5
Text Label 2350 2800 0    50   ~ 0
D6
Text Label 2350 2900 0    50   ~ 0
D7
Wire Wire Line
	2300 2100 2800 2100
Wire Wire Line
	2300 3100 2800 3100
Wire Wire Line
	2300 3200 2800 3200
Wire Wire Line
	2300 3300 2800 3300
Wire Wire Line
	2300 3400 2800 3400
Wire Wire Line
	2300 3500 2800 3500
Wire Wire Line
	2300 3600 2800 3600
Wire Wire Line
	2300 3700 2800 3700
Wire Wire Line
	2300 3800 2800 3800
Wire Wire Line
	2300 3900 2800 3900
Wire Wire Line
	2300 4000 2800 4000
Wire Wire Line
	2300 4100 2800 4100
Wire Wire Line
	2300 4200 2800 4200
Wire Wire Line
	2300 4300 2800 4300
Wire Wire Line
	2300 4400 2800 4400
Text Label 2350 3600 0    50   ~ 0
COLORREF
Wire Wire Line
	1800 2100 1300 2100
Wire Wire Line
	1800 3000 1300 3000
Wire Wire Line
	1800 3100 1300 3100
Wire Wire Line
	1800 3200 1300 3200
Wire Wire Line
	1800 3300 1300 3300
Wire Wire Line
	1800 3400 1300 3400
Wire Wire Line
	1800 3500 1300 3500
Wire Wire Line
	1800 3600 1300 3600
Wire Wire Line
	1800 3700 1300 3700
Wire Wire Line
	1800 3900 1300 3900
Wire Wire Line
	1800 4000 1300 4000
Wire Wire Line
	1800 4100 1300 4100
Wire Wire Line
	1800 4200 1300 4200
Wire Wire Line
	1800 4300 1300 4300
Wire Wire Line
	1800 4400 1300 4400
$Comp
L RF_Module:ESP32-WROOM-32 U2
U 1 1 6102A0B5
P 9750 2350
F 0 "U2" H 10200 1000 50  0000 C CNN
F 1 "ESP32-WROOM-32" H 9350 3700 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 9750 850 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf" H 9450 2400 50  0001 C CNN
	1    9750 2350
	-1   0    0    1   
$EndComp
$Comp
L Device:C C1
U 1 1 6103513B
P 1000 5850
F 0 "C1" H 1115 5896 50  0000 L CNN
F 1 "C" H 1115 5805 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D8.0mm_W2.5mm_P5.00mm" H 1038 5700 50  0001 C CNN
F 3 "~" H 1000 5850 50  0001 C CNN
	1    1000 5850
	1    0    0    -1  
$EndComp
Entry Wire Line
	3050 2200 3150 2300
Entry Wire Line
	3050 2300 3150 2400
Entry Wire Line
	3050 2400 3150 2500
Entry Wire Line
	3050 2500 3150 2600
Entry Wire Line
	3050 2600 3150 2700
Entry Wire Line
	3050 2700 3150 2800
Entry Wire Line
	3050 2800 3150 2900
Entry Wire Line
	3050 2900 3150 3000
Entry Wire Line
	4800 2750 4900 2850
Entry Wire Line
	4800 2850 4900 2950
Entry Wire Line
	4800 2950 4900 3050
Entry Wire Line
	4800 3050 4900 3150
Entry Wire Line
	4800 3150 4900 3250
Entry Wire Line
	4800 3250 4900 3350
Entry Wire Line
	4800 3350 4900 3450
Entry Wire Line
	4800 3450 4900 3550
Wire Wire Line
	4900 2850 5100 2850
Wire Wire Line
	4900 2950 5100 2950
Wire Wire Line
	4900 3050 5100 3050
Wire Wire Line
	4900 3150 5100 3150
Wire Wire Line
	4900 3250 5100 3250
Wire Wire Line
	4900 3350 5100 3350
Wire Wire Line
	5100 3450 4900 3450
Wire Wire Line
	4900 3550 5100 3550
Wire Wire Line
	2300 2200 3050 2200
Wire Wire Line
	2300 2300 3050 2300
Wire Wire Line
	2300 2400 3050 2400
Wire Wire Line
	2300 2500 3050 2500
Wire Wire Line
	2300 2600 3050 2600
Wire Wire Line
	2300 2700 3050 2700
Wire Wire Line
	2300 2800 3050 2800
Wire Wire Line
	2300 2900 3050 2900
Text Label 2950 2200 0    50   ~ 0
D0
Text Label 2950 2300 0    50   ~ 0
D1
Text Label 2950 2400 0    50   ~ 0
D2
Text Label 2950 2500 0    50   ~ 0
D3
Text Label 2950 2600 0    50   ~ 0
D4
Text Label 2950 2700 0    50   ~ 0
D5
Text Label 2950 2800 0    50   ~ 0
D6
Text Label 2950 2900 0    50   ~ 0
D7
Text Label 4900 2850 0    50   ~ 0
D0
Text Label 4900 2950 0    50   ~ 0
D1
Text Label 4900 3050 0    50   ~ 0
D2
Text Label 4900 3150 0    50   ~ 0
D3
Text Label 4900 3250 0    50   ~ 0
D4
Text Label 4900 3350 0    50   ~ 0
D5
Text Label 4900 3450 0    50   ~ 0
D6
Text Label 4900 3550 0    50   ~ 0
D7
Wire Bus Line
	3150 3000 4250 3000
Wire Bus Line
	4250 3000 4250 2750
Wire Wire Line
	3050 3000 3050 3100
Wire Wire Line
	4400 3100 4400 1150
Wire Wire Line
	2300 3000 3050 3000
Text GLabel 5000 1450 0    50   Input ~ 0
GND
Wire Wire Line
	5100 1450 5000 1450
Text GLabel 2950 4500 2    50   Input ~ 0
GND
Wire Wire Line
	2300 4500 2950 4500
Entry Wire Line
	900  2100 1000 2200
Entry Wire Line
	900  2200 1000 2300
Entry Wire Line
	900  2300 1000 2400
Entry Wire Line
	900  2400 1000 2500
Entry Wire Line
	4650 1750 4750 1850
Entry Wire Line
	4650 1850 4750 1950
Entry Wire Line
	4650 1650 4750 1750
Entry Wire Line
	4650 1550 4750 1650
$Comp
L Memory_RAM:IDT7132 U1
U 1 1 6102DC5C
P 6000 2350
F 0 "U1" H 5450 3800 50  0000 C CNN
F 1 "IDT7132" H 6450 900 50  0000 C CNN
F 2 "Package_DIP:DIP-48_W15.24mm_Socket_LongPads" H 6000 2350 50  0001 C CNN
F 3 "" H 6000 2350 50  0001 C CNN
	1    6000 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 1650 5100 1650
Wire Wire Line
	4750 1750 5100 1750
Wire Wire Line
	4750 1850 5100 1850
Wire Wire Line
	4750 1950 5100 1950
Wire Wire Line
	3050 3100 4400 3100
Wire Wire Line
	1000 2200 1800 2200
Wire Wire Line
	1000 2300 1800 2300
Wire Wire Line
	1000 2400 1800 2400
Wire Wire Line
	1000 2500 1800 2500
Text Label 1000 2200 0    50   ~ 0
A0
Text Label 1000 2300 0    50   ~ 0
A1
Text Label 1000 2400 0    50   ~ 0
A2
Text Label 1000 2500 0    50   ~ 0
A3
Text Label 4750 1650 0    50   ~ 0
A0
Text Label 4750 1750 0    50   ~ 0
A1
Text Label 4750 1850 0    50   ~ 0
A2
Text Label 4750 1950 0    50   ~ 0
A3
Text GLabel 10500 1100 3    50   Input ~ 0
GND
Wire Wire Line
	650  3800 650  1250
Wire Wire Line
	650  3800 1800 3800
Text GLabel 1000 6000 3    50   Input ~ 0
GND
Text GLabel 1150 4500 0    50   Input ~ 0
+5V
Wire Wire Line
	1150 4500 1800 4500
Text GLabel 1000 5700 1    50   Input ~ 0
+5V
Wire Wire Line
	9750 950  10500 950 
Wire Wire Line
	10500 950  10500 1100
Wire Wire Line
	650  1250 5100 1250
Wire Bus Line
	900  1550 4650 1550
Wire Bus Line
	4250 2750 4800 2750
Wire Wire Line
	4400 1150 5100 1150
Entry Wire Line
	4650 1950 4750 2050
Entry Wire Line
	4650 2050 4750 2150
Entry Wire Line
	4650 2150 4750 2250
Entry Wire Line
	4650 2250 4750 2350
Wire Wire Line
	4750 2050 5100 2050
Wire Wire Line
	4750 2250 5100 2250
Wire Wire Line
	4750 2150 5100 2150
Wire Wire Line
	4750 2350 5100 2350
Wire Wire Line
	1000 2600 1800 2600
Entry Wire Line
	900  2500 1000 2600
Entry Wire Line
	900  2600 1000 2700
Entry Wire Line
	900  2700 1000 2800
Entry Wire Line
	900  2800 1000 2900
Wire Wire Line
	1000 2700 1800 2700
Wire Wire Line
	1000 2800 1800 2800
Wire Wire Line
	1000 2900 1800 2900
Text GLabel 5000 2550 0    50   Input ~ 0
GND
Wire Wire Line
	5100 2550 5000 2550
Text GLabel 5000 2650 0    50   Input ~ 0
GND
Wire Wire Line
	5100 2650 5000 2650
Text Label 1000 2600 0    50   ~ 0
A4
Text Label 1000 2700 0    50   ~ 0
A5
Text Label 1000 2800 0    50   ~ 0
A6
Text Label 1000 2900 0    50   ~ 0
A7
Text Label 4750 2050 0    50   ~ 0
A4
Text Label 4750 2150 0    50   ~ 0
A5
Text Label 4750 2250 0    50   ~ 0
A6
Text Label 4750 2350 0    50   ~ 0
A7
Text GLabel 5000 2450 0    50   Input ~ 0
GND
Wire Wire Line
	5100 2450 5000 2450
Entry Wire Line
	7150 2850 7250 2950
Entry Wire Line
	7150 2950 7250 3050
Entry Wire Line
	7150 3050 7250 3150
Entry Wire Line
	7150 3150 7250 3250
Entry Wire Line
	7150 3250 7250 3350
Entry Wire Line
	7150 3350 7250 3450
Entry Wire Line
	7150 3450 7250 3550
Entry Wire Line
	7150 3550 7250 3650
Entry Wire Line
	9050 2750 9150 2850
Entry Wire Line
	9050 2850 9150 2950
Entry Wire Line
	9050 2550 9150 2650
Entry Wire Line
	9050 2650 9150 2750
Entry Wire Line
	9050 2150 9150 2250
Entry Wire Line
	9050 2250 9150 2350
Entry Wire Line
	9050 1950 9150 2050
Entry Wire Line
	9050 2050 9150 2150
Wire Wire Line
	9050 1950 8800 1950
Wire Wire Line
	9050 2050 8800 2050
Wire Wire Line
	9050 2150 8800 2150
Wire Wire Line
	9050 2250 8800 2250
Wire Wire Line
	9050 2550 8800 2550
Wire Wire Line
	9050 2650 8800 2650
Wire Wire Line
	9050 2750 8800 2750
Wire Bus Line
	7250 2950 8000 2950
Wire Bus Line
	8000 2950 8000 2850
Wire Wire Line
	6900 2850 7150 2850
Wire Wire Line
	6900 2950 7150 2950
Wire Wire Line
	6900 3550 7150 3550
Wire Wire Line
	6900 3450 7150 3450
Wire Wire Line
	6900 3350 7150 3350
Wire Wire Line
	6900 3250 7150 3250
Wire Wire Line
	6900 3150 7150 3150
Wire Wire Line
	6900 3050 7150 3050
Text Label 7000 2850 0    50   ~ 0
D0R
Text Label 7000 2950 0    50   ~ 0
D1R
Text Label 7000 3050 0    50   ~ 0
D2R
Text Label 7000 3150 0    50   ~ 0
D3R
Text Label 7000 3250 0    50   ~ 0
D4R
Text Label 7000 3350 0    50   ~ 0
D5R
Text Label 7000 3450 0    50   ~ 0
D6R
Text Label 7000 3550 0    50   ~ 0
D7R
Wire Bus Line
	8800 2850 8800 1950
Wire Bus Line
	8000 2850 8800 2850
Wire Wire Line
	9050 2850 8800 2850
Text Label 8850 2850 0    50   ~ 0
D0R
Text Label 8850 2750 0    50   ~ 0
D1R
Text Label 8850 2650 0    50   ~ 0
D2R
Text Label 8850 2550 0    50   ~ 0
D3R
Text Label 8850 2250 0    50   ~ 0
D4R
Text Label 8850 2150 0    50   ~ 0
D5R
Text Label 8850 2050 0    50   ~ 0
D6R
Text Label 8850 1950 0    50   ~ 0
D7R
Wire Wire Line
	9100 1950 9150 1950
Wire Wire Line
	6900 1750 8100 1750
Wire Wire Line
	8100 1750 8100 1850
Wire Wire Line
	8100 1850 9150 1850
Wire Wire Line
	6900 1850 8050 1850
Wire Wire Line
	8050 1850 8050 1900
Wire Wire Line
	8050 1900 8550 1900
Wire Wire Line
	8550 1900 8550 1750
Wire Wire Line
	8550 1750 9150 1750
Wire Wire Line
	6900 1650 8150 1650
Wire Wire Line
	8150 1650 8150 1800
Wire Wire Line
	8150 1800 9050 1800
Wire Wire Line
	9050 1800 9050 1900
Wire Wire Line
	9050 1900 9100 1900
Wire Wire Line
	9100 1900 9100 1950
Wire Wire Line
	6900 1950 8500 1950
Wire Wire Line
	8500 1950 8500 1650
Wire Wire Line
	8500 1650 9150 1650
Wire Wire Line
	6900 1250 7900 1250
Wire Wire Line
	7900 1250 7900 3050
Wire Wire Line
	7900 3050 9150 3050
Wire Wire Line
	5100 1350 4950 1350
Wire Wire Line
	4950 1350 4950 800 
Wire Wire Line
	7850 3150 9150 3150
Wire Wire Line
	8950 800  8950 1250
Wire Wire Line
	8950 1250 9150 1250
Wire Wire Line
	4950 800  8950 800 
Wire Wire Line
	6900 1350 9150 1350
Wire Wire Line
	1300 2100 1300 700 
Wire Wire Line
	1300 700  8900 700 
Wire Wire Line
	8900 700  8900 1450
Wire Wire Line
	8900 1450 9150 1450
Wire Wire Line
	7850 2050 6900 2050
Wire Wire Line
	7850 2050 7850 3150
Text GLabel 7000 1450 2    50   Input ~ 0
GND
Wire Wire Line
	6900 1450 7000 1450
Text GLabel 7000 1150 2    50   Input ~ 0
GND
Wire Wire Line
	6900 1150 7000 1150
Wire Bus Line
	3150 2300 3150 3000
Wire Bus Line
	4800 2750 4800 3450
Wire Bus Line
	4650 1550 4650 2250
Wire Bus Line
	7250 2950 7250 3650
Wire Bus Line
	900  1550 900  2800
$EndSCHEMATC
