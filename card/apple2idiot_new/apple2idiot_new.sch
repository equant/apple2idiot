EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr B 17000 11000
encoding utf-8
Sheet 1 1
Title "Apple2Idiot"
Date "2021-08-06"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 "Nathanial Hendler"
$EndDescr
$Comp
L kicad-library:AppleIIBus J1
U 1 1 61291E51
P 3400 6800
F 0 "J1" H 3950 8300 50  0000 C CNN
F 1 "AppleIIBus" H 3800 5300 50  0000 C CNN
F 2 "kicad-library:AppleIIBus" H 3400 6800 50  0001 C CNN
F 3 "" H 3400 6800 50  0001 C CNN
	1    3400 6800
	1    0    0    -1  
$EndComp
$Comp
L ESP32-DEV_KIT:ESP32-DEVKITC-32D U2
U 1 1 612B5485
P 13000 5550
F 0 "U2" H 13500 6600 50  0000 C CNN
F 1 "ESP32-DEVKITC-32D" H 13200 4500 50  0000 C CNN
F 2 "ESPDEVKIT:MODULE_ESP32-DEVKITC-32D" H 13000 5550 50  0001 L BNN
F 3 "" H 13000 5550 50  0001 L BNN
F 4 "4" H 13000 5550 50  0001 L BNN "PARTREV"
F 5 "Espressif Systems" H 13000 5550 50  0001 L BNN "MANUFACTURER"
	1    13000 5550
	1    0    0    -1  
$EndComp
Text GLabel 11850 7000 3    50   Input ~ 0
VCC
Text GLabel 3250 5200 1    50   Input ~ 0
VCC
Text GLabel 14050 4650 2    50   Input ~ 0
GND
Text GLabel 14050 5250 2    50   Input ~ 0
GND
Text GLabel 3400 8500 3    50   Input ~ 0
GND
Wire Wire Line
	3400 8350 3400 8500
Wire Wire Line
	13800 4650 14050 4650
Wire Wire Line
	13800 5250 14050 5250
Entry Wire Line
	2400 6100 2500 6200
Entry Wire Line
	2400 6000 2500 6100
Entry Wire Line
	2400 5900 2500 6000
Entry Wire Line
	2400 5800 2500 5900
Entry Wire Line
	2400 5700 2500 5800
Entry Wire Line
	2400 5600 2500 5700
Entry Wire Line
	2400 5500 2500 5600
Entry Wire Line
	2400 5400 2500 5500
Wire Wire Line
	2500 5500 2700 5500
Wire Wire Line
	2500 5600 2700 5600
Wire Wire Line
	2500 5700 2700 5700
Wire Wire Line
	2500 5800 2700 5800
Wire Wire Line
	2500 5900 2700 5900
Wire Wire Line
	2500 6000 2700 6000
Wire Wire Line
	2500 6100 2700 6100
Wire Wire Line
	2500 6200 2700 6200
Entry Wire Line
	7300 5850 7400 5950
Entry Wire Line
	7300 5750 7400 5850
Entry Wire Line
	7300 5650 7400 5750
Entry Wire Line
	7300 5550 7400 5650
Entry Wire Line
	7300 5450 7400 5550
Entry Wire Line
	7300 5350 7400 5450
Entry Wire Line
	7300 5250 7400 5350
Entry Wire Line
	7300 5150 7400 5250
Wire Wire Line
	7400 5250 7600 5250
Wire Wire Line
	7400 5350 7600 5350
Wire Wire Line
	7400 5450 7600 5450
Wire Wire Line
	7400 5550 7600 5550
Wire Wire Line
	7400 5650 7600 5650
Wire Wire Line
	7400 5750 7600 5750
Wire Wire Line
	7400 5850 7600 5850
Wire Wire Line
	7400 5950 7600 5950
Entry Wire Line
	4250 6250 4350 6350
Entry Wire Line
	4250 6150 4350 6250
Entry Wire Line
	4250 6050 4350 6150
Entry Wire Line
	4250 5950 4350 6050
Entry Wire Line
	4250 5850 4350 5950
Entry Wire Line
	4250 5750 4350 5850
Entry Wire Line
	4250 5650 4350 5750
Entry Wire Line
	4250 5550 4350 5650
Entry Wire Line
	9600 5350 9700 5450
Entry Wire Line
	9600 5450 9700 5550
Entry Wire Line
	9600 5250 9700 5350
Entry Wire Line
	11200 5750 11300 5850
Entry Wire Line
	11200 5950 11300 6050
Entry Wire Line
	11200 5650 11300 5750
Wire Wire Line
	9600 5250 9400 5250
Wire Wire Line
	9600 5350 9400 5350
Wire Wire Line
	9600 5450 9400 5450
Text GLabel 11950 5950 0    50   Input ~ 0
GND
Wire Wire Line
	11950 5950 12200 5950
Wire Wire Line
	11300 6050 12200 6050
Wire Wire Line
	11300 5850 12200 5850
Entry Wire Line
	9600 5550 9700 5650
Wire Wire Line
	9600 5550 9400 5550
Entry Wire Line
	14550 6150 14650 6250
Entry Wire Line
	14550 5750 14650 5850
Entry Wire Line
	14550 5650 14650 5750
Entry Wire Line
	14550 5450 14650 5550
Entry Wire Line
	14550 5350 14650 5450
Wire Wire Line
	13800 6150 14550 6150
Wire Wire Line
	13800 5750 14550 5750
Wire Wire Line
	13800 5650 14550 5650
Wire Wire Line
	13800 5450 14550 5450
Wire Wire Line
	13800 5350 14550 5350
Entry Wire Line
	9600 6550 9700 6650
Entry Wire Line
	9600 6650 9700 6750
Wire Wire Line
	9600 6550 9400 6550
Wire Wire Line
	9600 6650 9400 6650
Entry Wire Line
	9600 6850 9700 6950
Entry Wire Line
	9600 6950 9700 7050
Entry Wire Line
	9600 6750 9700 6850
Wire Wire Line
	9600 6750 9400 6750
Wire Wire Line
	9600 6850 9400 6850
Wire Wire Line
	9600 6950 9400 6950
Entry Wire Line
	9600 7150 9700 7250
Entry Wire Line
	9600 7050 9700 7150
Wire Wire Line
	9600 7050 9400 7050
Wire Wire Line
	9600 7150 9400 7150
Entry Wire Line
	7400 6950 7300 6850
Entry Wire Line
	7300 6750 7400 6850
Entry Wire Line
	7300 6650 7400 6750
Entry Wire Line
	7300 6550 7400 6650
Wire Wire Line
	7400 6550 7600 6550
Wire Wire Line
	7400 6650 7600 6650
Wire Wire Line
	7400 6750 7600 6750
Wire Wire Line
	7400 6850 7600 6850
Wire Wire Line
	7400 6950 7600 6950
Entry Wire Line
	7400 7050 7300 6950
Wire Wire Line
	7400 7050 7600 7050
Entry Wire Line
	7400 7150 7300 7050
Wire Wire Line
	7400 7150 7600 7150
Wire Bus Line
	11200 7550 9700 7550
Wire Bus Line
	11200 7550 14650 7550
Connection ~ 11200 7550
Text GLabel 9650 4750 2    50   Input ~ 0
GND
Wire Wire Line
	9400 4750 9650 4750
Text GLabel 9650 4850 2    50   Input ~ 0
RWR
Wire Wire Line
	9400 4850 9650 4850
Text GLabel 14050 5550 2    50   Input ~ 0
RWR
Wire Wire Line
	13800 5550 14050 5550
Entry Wire Line
	14550 5150 14650 5250
Wire Wire Line
	13800 5150 14550 5150
Entry Wire Line
	14550 4850 14650 4950
Wire Wire Line
	13800 4850 14550 4850
Entry Wire Line
	14550 4750 14650 4850
Wire Wire Line
	13800 4750 14550 4750
Wire Wire Line
	11300 5750 12200 5750
Entry Wire Line
	11200 5350 11300 5450
Wire Wire Line
	11300 5450 12200 5450
Wire Bus Line
	9700 5350 11200 5350
Wire Bus Line
	11200 5350 11200 4100
Wire Bus Line
	11200 4100 14650 4100
Wire Wire Line
	3250 5250 3250 5200
Wire Wire Line
	4100 5550 4250 5550
Wire Wire Line
	4100 5650 4250 5650
Wire Wire Line
	4100 5750 4250 5750
Wire Wire Line
	4100 5850 4250 5850
Wire Wire Line
	4100 5950 4250 5950
Wire Wire Line
	4100 6050 4250 6050
Wire Wire Line
	4100 6150 4250 6150
Wire Wire Line
	4100 6250 4250 6250
Wire Wire Line
	2700 7200 2100 7200
Wire Wire Line
	7600 4950 7450 4950
Wire Wire Line
	8050 4200 9900 4200
Wire Wire Line
	9900 4200 9900 4950
Wire Wire Line
	9900 4950 9400 4950
Wire Wire Line
	12200 5150 11950 5150
Wire Wire Line
	2700 7500 1950 7500
Wire Wire Line
	1950 7500 1950 4850
Text Label 2500 5500 0    50   ~ 0
A0
Text Label 2500 5600 0    50   ~ 0
A1
Text Label 2500 5700 0    50   ~ 0
A2
Text Label 2500 5800 0    50   ~ 0
A3
Text Label 2500 5900 0    50   ~ 0
A4
Text Label 2500 6000 0    50   ~ 0
A5
Text Label 2500 6100 0    50   ~ 0
A6
Text Label 2500 6200 0    50   ~ 0
A7
Text Label 4150 5550 0    50   ~ 0
D0
Text Label 4150 5650 0    50   ~ 0
D1
Text Label 4150 5750 0    50   ~ 0
D2
Text Label 4150 5850 0    50   ~ 0
D3
Text Label 4150 5950 0    50   ~ 0
D4
Text Label 4150 6050 0    50   ~ 0
D5
Text Label 4150 6150 0    50   ~ 0
D6
Text Label 4150 6250 0    50   ~ 0
D7
Text Label 7400 6550 0    50   ~ 0
D1
Text Label 7400 6650 0    50   ~ 0
D2
Text Label 7400 6750 0    50   ~ 0
D3
Text Label 7400 6850 0    50   ~ 0
D4
Text Label 7400 6950 0    50   ~ 0
D5
Text Label 7400 7050 0    50   ~ 0
D6
Text Label 7400 7150 0    50   ~ 0
D7
Text Label 7400 5250 0    50   ~ 0
A0
Text Label 7400 5350 0    50   ~ 0
A1
Text Label 7400 5450 0    50   ~ 0
A2
Text Label 7400 5550 0    50   ~ 0
A3
Text Label 7400 5650 0    50   ~ 0
A4
Text Label 7400 5750 0    50   ~ 0
A5
Text Label 7400 5850 0    50   ~ 0
A6
Text Label 7400 5950 0    50   ~ 0
A7
Text Label 9450 5250 0    50   ~ 0
AR0
Text Label 9450 5350 0    50   ~ 0
AR1
Text Label 9450 5450 0    50   ~ 0
AR2
Text Label 9450 5550 0    50   ~ 0
AR3
Text Label 14350 5150 0    50   ~ 0
AR0
Text Label 14350 4850 0    50   ~ 0
AR1
Text Label 14350 4750 0    50   ~ 0
AR2
Text Label 11400 5450 0    50   ~ 0
AR3
Text Label 9400 6550 0    50   ~ 0
DR1
Text Label 9400 6650 0    50   ~ 0
DR2
Text Label 9400 6750 0    50   ~ 0
DR3
Text Label 9400 6850 0    50   ~ 0
DR4
Text Label 9400 6950 0    50   ~ 0
DR5
Text Label 9400 7050 0    50   ~ 0
DR6
Text Label 9400 7150 0    50   ~ 0
DR7
Text Label 11350 5850 0    50   ~ 0
DR0
Text Label 11350 6050 0    50   ~ 0
DR1
Text Label 11350 5750 0    50   ~ 0
DR2
Text Label 14350 6150 0    50   ~ 0
DR3
Text Label 14350 5750 0    50   ~ 0
DR4
Text Label 14350 5650 0    50   ~ 0
DR5
Text Label 14350 5450 0    50   ~ 0
DR6
Text Label 14350 5350 0    50   ~ 0
DR7
Wire Wire Line
	1950 4850 7600 4850
Wire Wire Line
	7200 3800 7200 4750
Wire Wire Line
	7200 4750 7600 4750
Wire Wire Line
	9650 5650 9650 5700
Wire Wire Line
	9650 5700 9750 5700
Wire Wire Line
	9750 5700 9750 5650
Wire Wire Line
	9400 5650 9650 5650
Wire Wire Line
	10800 5650 10800 5550
Wire Wire Line
	10800 5550 12200 5550
Wire Wire Line
	10850 5750 10850 5600
Wire Wire Line
	10850 5600 12000 5600
Wire Wire Line
	12000 5600 12000 5650
Wire Wire Line
	12000 5650 12200 5650
Wire Wire Line
	10900 5850 10900 5250
Wire Wire Line
	10900 5250 12200 5250
Wire Wire Line
	11000 5950 11000 5300
Wire Wire Line
	11000 5300 12050 5300
Wire Wire Line
	12050 5300 12050 5350
Wire Wire Line
	12050 5350 12200 5350
Wire Wire Line
	12000 5050 12000 2500
Wire Wire Line
	12000 2500 12250 2500
Wire Wire Line
	12000 5050 12200 5050
Wire Wire Line
	11950 5150 11950 2600
Wire Wire Line
	11950 2600 12250 2600
Wire Wire Line
	12200 4850 12100 4850
Wire Wire Line
	12100 4850 12100 3100
Wire Wire Line
	12200 4950 12050 4950
Wire Wire Line
	12050 4950 12050 2700
Wire Wire Line
	12050 2700 12250 2700
Wire Wire Line
	13800 6050 16050 6050
Wire Wire Line
	16050 6050 16050 2100
Wire Wire Line
	16050 2100 12750 2100
Wire Wire Line
	13800 5950 15950 5950
Wire Wire Line
	15950 5950 15950 2200
Wire Wire Line
	15950 2200 12750 2200
Wire Wire Line
	14550 5850 14550 5900
Wire Wire Line
	14800 5900 14800 5850
Wire Wire Line
	14800 5850 15850 5850
Wire Wire Line
	15850 5850 15850 2300
Wire Wire Line
	15850 2300 12750 2300
Wire Wire Line
	13800 5850 14550 5850
Wire Wire Line
	14550 5900 14800 5900
Wire Wire Line
	13800 5050 14550 5050
Wire Wire Line
	14550 5050 14550 5100
Wire Wire Line
	14550 5100 15750 5100
Wire Wire Line
	15750 2400 12750 2400
Wire Wire Line
	15750 2400 15750 5100
Wire Wire Line
	13800 4950 14550 4950
Wire Wire Line
	14550 4950 14550 5000
Wire Wire Line
	14550 5000 15650 5000
Wire Wire Line
	15650 2500 12750 2500
Wire Wire Line
	15650 2500 15650 5000
$Comp
L Connector_Generic:Conn_02x02_Odd_Even J4
U 1 1 61709865
P 8400 2800
F 0 "J4" H 8450 3017 50  0000 C CNN
F 1 "Conn_02x02_Odd_Even" H 8450 2926 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x02_P2.54mm_Vertical" H 8400 2800 50  0001 C CNN
F 3 "~" H 8400 2800 50  0001 C CNN
	1    8400 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 4950 7450 2800
Wire Wire Line
	7450 2800 8200 2800
Wire Wire Line
	8050 2900 8200 2900
Wire Wire Line
	8050 2900 8050 4200
Wire Wire Line
	8700 2800 11600 2800
Wire Wire Line
	11600 2800 11600 5050
Wire Wire Line
	11600 5050 12000 5050
Connection ~ 12000 5050
Wire Wire Line
	8700 2900 11500 2900
Wire Wire Line
	11500 2900 11500 5150
Wire Wire Line
	11500 5150 11950 5150
Connection ~ 11950 5150
$Comp
L Device:C C1
U 1 1 6174221E
P 5250 8150
F 0 "C1" H 5365 8196 50  0000 L CNN
F 1 "C" H 5365 8105 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L4.6mm_W2.0mm_P2.50mm_MKS02_FKP02" H 5288 8000 50  0001 C CNN
F 3 "~" H 5250 8150 50  0001 C CNN
	1    5250 8150
	1    0    0    -1  
$EndComp
Text GLabel 5250 8400 3    50   Input ~ 0
GND
Text GLabel 5250 7900 1    50   Input ~ 0
VCC
Wire Wire Line
	5250 7900 5250 8000
Wire Wire Line
	5250 8300 5250 8400
Wire Bus Line
	2400 4950 7300 4950
Wire Wire Line
	2100 2300 5100 2300
Wire Wire Line
	5100 2300 5100 1850
Wire Wire Line
	8050 2900 5300 2900
Wire Wire Line
	5300 2900 5300 1850
Connection ~ 8050 2900
Wire Wire Line
	7450 2800 5200 2800
Wire Wire Line
	5200 2800 5200 1850
Connection ~ 7450 2800
Text GLabel 7550 5050 0    50   Input ~ 0
GND
Wire Wire Line
	7550 5050 7600 5050
Text GLabel 9450 5050 2    50   Input ~ 0
GND
Wire Wire Line
	9450 5050 9400 5050
Text GLabel 9450 6050 2    50   Input ~ 0
GND
Wire Wire Line
	9450 6050 9400 6050
Text GLabel 9450 6150 2    50   Input ~ 0
GND
Wire Wire Line
	9450 6150 9400 6150
Wire Wire Line
	9450 6250 9400 6250
Text GLabel 9450 6250 2    50   Input ~ 0
GND
Text Label 9400 6450 0    50   ~ 0
DR0
Text Label 7400 6450 0    50   ~ 0
D0
Wire Bus Line
	4350 6350 7300 6350
Wire Wire Line
	7400 6450 7600 6450
Entry Wire Line
	7300 6350 7400 6450
Entry Wire Line
	7300 6450 7400 6550
Wire Wire Line
	9600 6450 9400 6450
Entry Wire Line
	9600 6450 9700 6550
$Comp
L Memory_RAM:IDT7132 U1
U 1 1 61296796
P 8500 5950
F 0 "U1" H 9050 7400 50  0000 C CNN
F 1 "IDT7132" H 8950 4500 50  0000 C CNN
F 2 "Package_DIP:DIP-48_W15.24mm_LongPads" H 8500 5950 50  0001 C CNN
F 3 "" H 8500 5950 50  0001 C CNN
	1    8500 5950
	1    0    0    -1  
$EndComp
NoConn ~ 4100 6450
NoConn ~ 4100 6550
NoConn ~ 4100 6650
NoConn ~ 4100 6750
NoConn ~ 4100 6950
NoConn ~ 4100 7050
NoConn ~ 4100 7150
NoConn ~ 4100 7350
NoConn ~ 4100 7450
NoConn ~ 4100 7550
NoConn ~ 4100 7650
NoConn ~ 4100 7850
NoConn ~ 4100 8050
NoConn ~ 2700 8100
NoConn ~ 2700 7900
NoConn ~ 2700 7800
NoConn ~ 2700 7700
NoConn ~ 2700 6600
NoConn ~ 2700 6700
NoConn ~ 2700 6800
NoConn ~ 2700 6900
NoConn ~ 2700 7000
NoConn ~ 3350 5250
NoConn ~ 3450 5250
NoConn ~ 3550 5250
NoConn ~ 12200 6150
NoConn ~ 12200 6250
NoConn ~ 12200 6350
NoConn ~ 13800 6250
NoConn ~ 13800 6350
NoConn ~ 13800 6450
NoConn ~ 12200 4650
NoConn ~ 12200 4750
Text Label 12050 5550 0    50   ~ 0
IO26
Text Label 12050 5650 0    50   ~ 0
IO27
Text Label 12050 5350 0    50   ~ 0
IO33
Text Label 12050 5450 0    50   ~ 0
IO25
Text Label 12050 5050 0    50   ~ 0
IO34
Text Label 12050 5150 0    50   ~ 0
IO35
Text Label 12050 5250 0    50   ~ 0
IO32
Text Label 12100 4850 0    50   ~ 0
SENVP
Text Label 12100 4950 0    50   ~ 0
SENVN
Text Label 13800 4950 0    50   ~ 0
TX
Text Label 13800 5050 0    50   ~ 0
RX
Text Label 13850 5850 0    50   ~ 0
IO4
Text Label 13850 5950 0    50   ~ 0
IO0
Text Label 13850 6050 0    50   ~ 0
IO2
Text Label 9400 5650 0    50   ~ 0
AR4
Text Label 9400 5750 0    50   ~ 0
AR5
Text Label 9400 5850 0    50   ~ 0
AR6
Text Label 9400 5950 0    50   ~ 0
AR7
Text Label 7500 4950 0    50   ~ 0
BSYL
Text Label 9350 4950 0    50   ~ 0
BSYR
Text Label 2250 7200 0    50   ~ 0
IOSEL
Text Label 2250 7500 0    50   ~ 0
RW
Text GLabel 7550 6050 0    50   Input ~ 0
GND
Wire Wire Line
	7550 6050 7600 6050
Text GLabel 7550 6150 0    50   Input ~ 0
GND
Wire Wire Line
	7550 6150 7600 6150
Text GLabel 7550 6250 0    50   Input ~ 0
GND
Wire Wire Line
	7550 6250 7600 6250
Wire Wire Line
	9750 5650 10800 5650
Wire Wire Line
	9400 5750 10850 5750
Wire Wire Line
	9400 5850 10900 5850
Wire Wire Line
	9400 5950 11000 5950
Text Label 3450 3800 0    50   ~ 0
CEL
Text Label 2250 7400 0    50   ~ 0
DEVSEL
Wire Wire Line
	3250 3800 7200 3800
Wire Wire Line
	2700 7400 1850 7400
Wire Wire Line
	1850 7400 1850 2100
Wire Wire Line
	1850 2100 5000 2100
Wire Wire Line
	5000 2100 5000 1850
Wire Wire Line
	2700 7300 1700 7300
Wire Wire Line
	1700 7300 1700 2500
Wire Wire Line
	1700 2500 5400 2500
Wire Wire Line
	5400 2500 5400 1850
$Comp
L Connector_Generic:Conn_02x01 J2
U 1 1 613AE9B4
P 2950 3800
F 0 "J2" H 3000 4017 50  0000 C CNN
F 1 "Conn_02x01" H 3000 3926 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 2950 3800 50  0001 C CNN
F 3 "~" H 2950 3800 50  0001 C CNN
	1    2950 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2300 2100 3800
Wire Wire Line
	2750 3800 2100 3800
Connection ~ 2100 3800
Wire Wire Line
	2100 3800 2100 7200
$Comp
L Connector_Generic:Conn_01x05 J3
U 1 1 613E8185
P 5200 1650
F 0 "J3" V 5164 1362 50  0000 R CNN
F 1 "Conn_01x05" V 5073 1362 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 5200 1650 50  0001 C CNN
F 3 "~" H 5200 1650 50  0001 C CNN
	1    5200 1650
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J5
U 1 1 6140E262
P 12450 2400
F 0 "J5" H 12500 2917 50  0000 C CNN
F 1 "Conn_02x08_Odd_Even" H 12500 2826 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x08_P2.54mm_Vertical" H 12450 2400 50  0001 C CNN
F 3 "~" H 12450 2400 50  0001 C CNN
	1    12450 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	12100 3100 13250 3100
Wire Wire Line
	13250 3100 13250 2600
Wire Wire Line
	13250 2600 12750 2600
Wire Wire Line
	12250 2100 12000 2100
Text GLabel 12000 2100 0    50   Input ~ 0
GND
Wire Wire Line
	12250 2200 12000 2200
Text GLabel 12000 2200 0    50   Input ~ 0
GND
Wire Wire Line
	12250 2300 12000 2300
Text GLabel 12000 2300 0    50   Input ~ 0
GND
Wire Wire Line
	12250 2400 12000 2400
Text GLabel 12000 2400 0    50   Input ~ 0
GND
Text GLabel 12850 2700 2    50   Input ~ 0
VCC
Wire Wire Line
	12850 2700 12750 2700
Text GLabel 12850 2800 2    50   Input ~ 0
VCC
Wire Wire Line
	12850 2800 12750 2800
Text GLabel 12350 3000 2    50   Input ~ 0
VCC
Wire Wire Line
	12350 3000 12250 3000
Wire Wire Line
	12250 2800 12250 3000
$Comp
L Device:D D1
U 1 1 614F5A8B
P 11850 6750
F 0 "D1" V 11804 6830 50  0000 L CNN
F 1 "D" V 11895 6830 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 11850 6750 50  0001 C CNN
F 3 "~" H 11850 6750 50  0001 C CNN
	1    11850 6750
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 6152E0F0
P 5600 8150
F 0 "C2" H 5715 8196 50  0000 L CNN
F 1 "C" H 5715 8105 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L4.6mm_W2.0mm_P2.50mm_MKS02_FKP02" H 5638 8000 50  0001 C CNN
F 3 "~" H 5600 8150 50  0001 C CNN
	1    5600 8150
	1    0    0    -1  
$EndComp
Text GLabel 5600 8400 3    50   Input ~ 0
GND
Text GLabel 5600 7900 1    50   Input ~ 0
VCC
Wire Wire Line
	5600 7900 5600 8000
Wire Wire Line
	5600 8300 5600 8400
Wire Wire Line
	12200 6450 12150 6450
Wire Wire Line
	12150 6900 12150 7000
Text GLabel 12150 7000 3    50   Input ~ 0
GND
$Comp
L Device:C C3
U 1 1 61585748
P 12150 6750
F 0 "C3" H 12265 6796 50  0000 L CNN
F 1 "C" H 12265 6705 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L4.6mm_W2.0mm_P2.50mm_MKS02_FKP02" H 12188 6600 50  0001 C CNN
F 3 "~" H 12150 6750 50  0001 C CNN
	1    12150 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	12150 6450 12150 6600
Connection ~ 12150 6450
Wire Wire Line
	12150 6450 11850 6450
Wire Wire Line
	11850 6450 11850 6600
Wire Wire Line
	11850 6900 11850 7000
Wire Bus Line
	9700 5350 9700 5650
Wire Bus Line
	11200 5650 11200 7550
Wire Bus Line
	14650 4100 14650 5250
Wire Bus Line
	4350 5650 4350 6350
Wire Bus Line
	14650 5450 14650 7550
Wire Bus Line
	7300 6350 7300 7050
Wire Bus Line
	9700 6550 9700 7550
Wire Bus Line
	7300 4950 7300 5850
Wire Bus Line
	2400 4950 2400 6100
$EndSCHEMATC
