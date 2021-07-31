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
Wire Wire Line
	3050 3000 3050 3100
Wire Wire Line
	2300 3000 3050 3000
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
Text GLabel 9950 1850 2    50   Input ~ 0
GND
Wire Wire Line
	650  3800 650  1250
Wire Wire Line
	650  3800 1800 3800
Text GLabel 1000 6000 3    50   Input ~ 0
GND
Text GLabel 1000 5700 1    50   Input ~ 0
+5V
Wire Wire Line
	9800 1850 9950 1850
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
Text Label 1000 2600 0    50   ~ 0
A4
Text Label 1000 2700 0    50   ~ 0
A5
Text Label 1000 2800 0    50   ~ 0
A6
Text Label 1000 2900 0    50   ~ 0
A7
$Comp
L ESP32-DEV_KIT:ESP32-DEVKITC-32D U2
U 1 1 613EE5FC
P 9000 2750
F 0 "U2" H 9000 3917 50  0000 C CNN
F 1 "ESP32-DEVKITC-32D" H 9000 3826 50  0000 C CNN
F 2 "ESPDEVKIT:MODULE_ESP32-DEVKITC-32D" H 9000 2750 50  0001 L BNN
F 3 "" H 9000 2750 50  0001 L BNN
F 4 "4" H 9000 2750 50  0001 L BNN "PARTREV"
F 5 "Espressif Systems" H 9000 2750 50  0001 L BNN "MANUFACTURER"
	1    9000 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1150 6150 1150
Text GLabel 6150 1150 2    50   Input ~ 0
GND
Wire Wire Line
	6050 1450 6150 1450
Text GLabel 6150 1450 2    50   Input ~ 0
GND
Wire Wire Line
	4250 1350 4100 1350
Wire Wire Line
	4250 2450 4150 2450
Text GLabel 4150 2450 0    50   Input ~ 0
GND
Text Label 3900 2350 0    50   ~ 0
A7
Text Label 3900 2250 0    50   ~ 0
A6
Text Label 3900 2150 0    50   ~ 0
A5
Text Label 3900 2050 0    50   ~ 0
A4
Wire Wire Line
	4250 2650 4150 2650
Text GLabel 4150 2650 0    50   Input ~ 0
GND
Wire Wire Line
	4250 2550 4150 2550
Text GLabel 4150 2550 0    50   Input ~ 0
GND
Wire Wire Line
	3900 2350 4250 2350
Wire Wire Line
	3900 2150 4250 2150
Wire Wire Line
	3900 2250 4250 2250
Wire Wire Line
	3900 2050 4250 2050
Entry Wire Line
	3800 2250 3900 2350
Entry Wire Line
	3800 2150 3900 2250
Entry Wire Line
	3800 2050 3900 2150
Entry Wire Line
	3800 1950 3900 2050
Wire Wire Line
	3550 1150 4250 1150
Wire Bus Line
	3400 2750 3950 2750
Text Label 3900 1950 0    50   ~ 0
A3
Text Label 3900 1850 0    50   ~ 0
A2
Text Label 3900 1750 0    50   ~ 0
A1
Text Label 3900 1650 0    50   ~ 0
A0
Wire Wire Line
	3900 1950 4250 1950
Wire Wire Line
	3900 1850 4250 1850
Wire Wire Line
	3900 1750 4250 1750
Wire Wire Line
	3900 1650 4250 1650
$Comp
L Memory_RAM:IDT7132 U1
U 1 1 6102DC5C
P 5150 2350
F 0 "U1" H 4600 3800 50  0000 C CNN
F 1 "IDT7132" H 5600 900 50  0000 C CNN
F 2 "Package_DIP:DIP-48_W15.24mm_Socket_LongPads" H 5150 2350 50  0001 C CNN
F 3 "" H 5150 2350 50  0001 C CNN
	1    5150 2350
	1    0    0    -1  
$EndComp
Entry Wire Line
	3800 1550 3900 1650
Entry Wire Line
	3800 1650 3900 1750
Entry Wire Line
	3800 1850 3900 1950
Entry Wire Line
	3800 1750 3900 1850
Wire Wire Line
	4250 1450 4150 1450
Text GLabel 4150 1450 0    50   Input ~ 0
GND
Wire Wire Line
	3550 3100 3550 1150
Text Label 4050 3550 0    50   ~ 0
D7
Text Label 4050 3450 0    50   ~ 0
D6
Text Label 4050 3350 0    50   ~ 0
D5
Text Label 4050 3250 0    50   ~ 0
D4
Text Label 4050 3150 0    50   ~ 0
D3
Text Label 4050 3050 0    50   ~ 0
D2
Text Label 4050 2950 0    50   ~ 0
D1
Text Label 4050 2850 0    50   ~ 0
D0
Wire Wire Line
	4050 3550 4250 3550
Wire Wire Line
	4250 3450 4050 3450
Wire Wire Line
	4050 3350 4250 3350
Wire Wire Line
	4050 3250 4250 3250
Wire Wire Line
	4050 3150 4250 3150
Wire Wire Line
	4050 3050 4250 3050
Wire Wire Line
	4050 2950 4250 2950
Wire Wire Line
	4050 2850 4250 2850
Entry Wire Line
	3950 3450 4050 3550
Entry Wire Line
	3950 3350 4050 3450
Entry Wire Line
	3950 3250 4050 3350
Entry Wire Line
	3950 3150 4050 3250
Entry Wire Line
	3950 3050 4050 3150
Entry Wire Line
	3950 2950 4050 3050
Entry Wire Line
	3950 2850 4050 2950
Entry Wire Line
	3950 2750 4050 2850
Wire Wire Line
	650  1250 4250 1250
Wire Wire Line
	3050 3100 3550 3100
Wire Bus Line
	3150 3000 3400 3000
Wire Bus Line
	3400 2750 3400 3000
Wire Bus Line
	900  1550 3800 1550
Wire Wire Line
	1150 4500 1300 4500
Text GLabel 1150 4500 0    50   Input ~ 0
+5V
Text Label 1750 4500 2    50   ~ 0
+5V
Text GLabel 8050 3650 0    50   Input ~ 0
+5V
Wire Wire Line
	8050 3650 8200 3650
Wire Wire Line
	6050 3550 7100 3550
Wire Wire Line
	7100 3550 7100 3050
Wire Wire Line
	7100 3050 8200 3050
Wire Wire Line
	6050 3450 7200 3450
Wire Wire Line
	7200 3450 7200 3250
Wire Wire Line
	7000 3350 7000 2950
Wire Wire Line
	7000 2950 8200 2950
Wire Wire Line
	6050 3350 7000 3350
Wire Wire Line
	6050 3250 6150 3250
Wire Wire Line
	6150 3250 6150 3850
Wire Wire Line
	6150 3850 10050 3850
Wire Wire Line
	10050 3850 10050 3350
Wire Wire Line
	10050 3350 9800 3350
Wire Wire Line
	6050 3150 6250 3150
Wire Wire Line
	6250 3150 6250 3950
Wire Wire Line
	6250 3950 10150 3950
Wire Wire Line
	10150 3950 10150 2650
Wire Wire Line
	10150 2650 9800 2650
Wire Wire Line
	6050 3050 6350 3050
Wire Wire Line
	6350 3050 6350 4050
Wire Wire Line
	6350 4050 10250 4050
Wire Wire Line
	10250 4050 10250 2550
Wire Wire Line
	10250 2550 9800 2550
Wire Wire Line
	6050 2950 6450 2950
Wire Wire Line
	6450 2950 6450 4150
Wire Wire Line
	6450 4150 10350 4150
Wire Wire Line
	10350 4150 10350 2350
Wire Wire Line
	10350 2350 9800 2350
Text GLabel 9950 2450 2    50   Input ~ 0
GND
Wire Wire Line
	9800 2450 9950 2450
Wire Wire Line
	6050 2850 6550 2850
Wire Wire Line
	6550 2850 6550 4250
Wire Wire Line
	6550 4250 10450 4250
Wire Wire Line
	10450 4250 10450 2050
Wire Wire Line
	10450 2050 9800 2050
Wire Wire Line
	6050 1650 8050 1650
Wire Wire Line
	8050 1650 8050 1450
Wire Wire Line
	8050 1450 10250 1450
Wire Wire Line
	10250 1450 10250 1950
Wire Wire Line
	10250 1950 9800 1950
Wire Wire Line
	6050 1750 7050 1750
Wire Wire Line
	7050 1750 7050 2650
Wire Wire Line
	7050 2650 8200 2650
Wire Wire Line
	6050 1850 6950 1850
Wire Wire Line
	6950 1850 6950 2750
Wire Wire Line
	6950 2750 8200 2750
Wire Wire Line
	6050 1950 6850 1950
Wire Wire Line
	6850 1950 6850 2850
Wire Wire Line
	6850 2850 8200 2850
Wire Wire Line
	4100 850  7300 850 
Wire Wire Line
	7300 850  7300 2350
Wire Wire Line
	7300 2350 8200 2350
Wire Wire Line
	4100 850  4100 1350
Wire Wire Line
	1300 750  7400 750 
Wire Wire Line
	7400 750  7400 2250
Wire Wire Line
	7400 2250 8200 2250
Wire Wire Line
	1300 750  1300 2100
Wire Wire Line
	6050 2050 7150 2050
Wire Wire Line
	6050 2150 6750 2150
Wire Wire Line
	6750 2150 6750 2550
Wire Wire Line
	6750 2550 8200 2550
Wire Wire Line
	7150 2050 7150 2450
Wire Wire Line
	7150 2450 8200 2450
Wire Wire Line
	6050 1250 10550 1250
Wire Wire Line
	10550 1250 10550 2750
Wire Wire Line
	10550 2750 9800 2750
Wire Wire Line
	8200 3150 8050 3150
Text GLabel 8050 3150 0    50   Input ~ 0
GND
Wire Wire Line
	7200 3250 8200 3250
Text GLabel 1150 4700 0    50   Input ~ 0
VCC
Wire Wire Line
	1150 4700 1300 4700
Wire Wire Line
	1300 4700 1300 4500
Wire Bus Line
	3150 2300 3150 3000
Wire Bus Line
	3800 1550 3800 2250
Wire Bus Line
	3950 2750 3950 3450
Wire Bus Line
	900  1550 900  2800
Connection ~ 1300 4500
Wire Wire Line
	1300 4500 1800 4500
$EndSCHEMATC
