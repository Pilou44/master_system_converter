

# Master System Converter
## About the project
The purpose of this project is to create a Master System Converter that allows to play Master System games on Sega Megadrive / Genesis.
It is based on work done by [Raphaël Assenat](https://www.raphnet.net/) that can be found [here](https://www.raphnet.net/electronique/sms_to_smd/index.php).
PCB are developped using EasyEDA.
Code is Arduino IDE file.
## Description
Master System Converter (Power Base converter in USA) is a product that has been sold by Sega and allows to play Master System games on Sega Megadrive / Genesis. Low cost version have been sold by other companies like Datel. Main difference between these versions is that some games that start on official Sega product doesn't on other converters. It comes from the fact that some games need a stack initialization to start. Some of this games that needs stack initialization are Shinobi, R-Type, Aztec Adventure and Sydney Hunter.
The purpose of this projetct is to create a converter that initialize this stack in order to be compatible with all the games that are supported by the official Sega converter.
To achieve that, it integrates an Arduino Nano.

## Components

 - 1 Arduino Nano or compatible (I've tested Elegoo and AZ-Delivery versions). Reset button has to be removed to fit into cartridge shell. USB port can be removed too once software has been flashed. It's better not to use old bootloader.
 - 2 resistors 1.5 kΩ
 - 1 resistor 56 kΩ
 - 1 push button 6 x 6 mm of at least 9.5 mm height (can be found [here](https://www.gotronic.fr/art-bp-subminiature-krs0643-4266.htm))
 - 1 Master System port (can be found [here](https://fr.aliexpress.com/item/32818469880.html?spm=a2g0o.order_list.0.0.7e7a5e5bNEJM4c&gatewayAdapt=glo2fra)). Pins have to be bend. 
 - 1 Megadrive / Genesis cartridge shell (can be found [here](https://fr.aliexpress.com/item/4000124389632.html?spm=a2g0o.order_list.0.0.7e7a5e5bNEJM4c&gatewayAdapt=glo2fra)) Holes must be drilled to let pause button go through and USB port if not removed.

## History
### First prototype
Developped from Raphaël Assenat gerber file, it has no stack initialization. I've used it to test my Master System games on my Megadrive.

<center>
<img src="https://github.com/Pilou44/master_system_converter/blob/main/docs/v0_front.jpg?raw=true" width="200"/> <img src="https://github.com/Pilou44/master_system_converter/blob/main/docs/v0_back.jpg?raw=true" width="200"/>
</center>

### V1.0
First PCB home made, with Arduino Nano. From PCB to working version, several patches have been applied: 
 - Using D11 and D12 instead of D0 and D1 (that are used by Arduino for Rx and Tx)
 - Usin 5V instead of VIN for alimentation.

However, this version works without Arduino to launch games that don't need stack initialization.

<center>
<img src="https://github.com/Pilou44/master_system_converter/blob/main/docs/v1.0_front.jpg?raw=true" width="200"/> <img src="https://github.com/Pilou44/master_system_converter/blob/main/docs/v1.0_back.jpg?raw=true" width="200"/>
</center>

### V1.1
This is previous version with patches integrated. It is first deployable version.

<center>
<img src="https://github.com/Pilou44/master_system_converter/blob/main/docs/v1.1_front.jpg?raw=true" width="200"/> <img src="https://github.com/Pilou44/master_system_converter/blob/main/docs/v1.1_back.jpg?raw=true" width="200"/>
</center>

### V2.0
This version is based on V1.1 with different pinout to simplify code.
### V2.1
Same as V2.0, but tracks has been moved on PCB to be farer from holes.

<center>
<img src="https://github.com/Pilou44/master_system_converter/blob/main/docs/v2.0_front.jpg?raw=true" width="200"/> <img src="https://github.com/Pilou44/master_system_converter/blob/main/docs/v2.0_back.jpg?raw=true" width="200"/>
</center>

### V2.1
Same as V2.0, but tracks has been moved on PCB to be farer from holes.
