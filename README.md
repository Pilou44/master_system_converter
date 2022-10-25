
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
## History
### First prototype
Developped from Raphaël Assenat gerber file, it has no stack initialization. I've used it to test my Master System games on my Megadrive.
### V1.0
First PCB home made, with Arduino Nano. From PCB to working version, several patches have been applied: 
 - Using D11 and D12 instead of D0 and D1 (that are used by Arduino for Rx and Tx)
 - Usin 5V instead of VIN for alimentation.
### V1.1
This is previous version with patches integrated. It should be first deployable version. Software optimizations are to be developped on this version.
### V2.0
This version is based on V1.1 with different pinout to simplify code.

