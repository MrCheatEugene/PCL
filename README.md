# PCL
Probably Cool Lights will transfrom your LED string or any other things to a masterpiece with remote access from phone and computer!



![Windows app](https://github.com/MrCheatEugene/PCL/blob/images/image_one.png?raw=true)
# How it works?
Under your table is hidden Arduino board with mosfet, that controls LED string or something else(THAT WORKS ON DC, if you will connect AC, say goodbye to your mosfet,arduino,PC and maybe that thing). Arduino does not do anything with the string itself, it controls the mosfet.

Computer, that is also a webserver, connects to arduino by Serial port at speed of 9600 baud and sends commands to it.

Phone just sends requests to webserver. Also, webserver uses port 24000 rather than classical 80/8080.

And boom, simple, easy, and it works!(at least for people who have one color LED string or led string whiout controller. and if it runs on DC).

# Donate

Making projects like that one is hard, and if you want to support me, so I can do better things

go to https://donationalerts.com/r/mrcheatt

# Download
http://vds.mrcheat.ga/dl/pcl.zip Windows

http://vds.mrcheat.ga/dl/pcl.apk Android APK

http://vds.mrcheat.ga/dl/pcl.aab Android App Bundle

# Setting up

- Get a N channel mosfet and an arduino board
- Connect Gate to 9(by default it is, you can change it in sketch later), Drain to GND of your led string, and Source to ground of an power supply of string. LED string's VCC is connected to the external power supply. Arduino gets power from computer. 
- If you did not understand, here is the schematic:
- ![Windows app](https://github.com/MrCheatEugene/PCL/blob/images/image_two.png?raw=true) Original: http://wiki.amperka.ru/%D0%BA%D0%BE%D0%BD%D1%81%D0%BF%D0%B5%D0%BA%D1%82-arduino:%D0%BF%D0%BE%D0%BB%D0%B5%D0%B2%D0%BE%D0%B9-%D1%82%D1%80%D0%B0%D0%BD%D0%B7%D0%B8%D1%81%D1%82%D0%BE%D1%80
