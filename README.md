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
https://vds.mrcheat.ga/dl/pcl.zip Windows

https://vds.mrcheat.ga/dl/pcl.apk Android APK

https://vds.mrcheat.ga/dl/pcl.aab Android App Bundle

# Setting up

- Get a N channel mosfet and an arduino board
- Connect Gate to 9(by default it is, you can change it in sketch later), Drain to GND of your led string, and Source to ground of an power supply of string. LED string's VCC is connected to the external power supply. Arduino gets power from computer. 
- If you did not understand, here is the schematic:
- ![http://wiki.amperka.ru/%D0%BA%D0%BE%D0%BD%D1%81%D0%BF%D0%B5%D0%BA%D1%82-arduino:%D0%BF%D0%BE%D0%BB%D0%B5%D0%B2%D0%BE%D0%B9-%D1%82%D1%80%D0%B0%D0%BD%D0%B7%D0%B8%D1%81%D1%82%D0%BE%D1%80](https://github.com/MrCheatEugene/PCL/blob/images/image_two.png?raw=true)
- Then, download [latest](https://github.com/MrCheatEugene/PCL/releases/latest/ProbablyCoolLights.ino) 
- and [upload](https://google.com/search?q=how%20to20upload%20sketch%20using%20arduino%20IDE) it using arduino IDE!
- If board isn't on port COM4 go to Device Manager and change it!
- ![Changing serial port guide](https://github.com/MrCheatEugene/PCL/blob/images/image_three.png?raw=true)
- Done! Now you can flex to your freinds in Discord and show what cool thing *that you made*(well, that's half true) and *totally not downloaded* from Github!
- Note.For phone app to work, you need to open Windows app first!

# Can't upload firmware!

If not uploading with error ```avrdude: ser_open(): can't open device "\\.\COM4":Device is busy```(or for other languages ```�������� � �������```, and no this is not encoding error)
or any other:
- Reconnect your arduino
- Close Arduino lights control software
- Reboot your PC 
- Change serial port in arduino IDE to board's port(after uploading - change it to COM4 if it isn't in Device manager for software to work)

# Mosfet is hot/heating up!

## Mosfet is slightly hot, but everything works 
Add a heatsink to your mosfet, and also check

- Can your mosfet handle that voltage&current?
- Can wires handle that power(in watts)?

### Why?
- Mosfet may die
- Wires may heat up too much and melt. Trust me, that smell is awful. If you hate people who smoke and wires have melted and you have that small in whole house - Well, congratulations! You have just ruined yours(and people who are in house) lungs! 

## Mosfet is hot and nothing works!
Unplug everything IMMEDEATLY. RIGHT NOW.

Congratulations, you've succesfully failed building project!

Now go get another N channel mosfet that CAN handle your application's voltage&current(check datasheet for that) and connect it to the board as it's on the scheme. 

All mosfets have different pinout, so go find a datasheet for yours and connect it as it's on the scheme!

# Serial port for developers

You can also control system trough serial port! 

By default, it runs on 9600 baud.

Print "help" for getting list of commands!

All commands return true/input value.

# Webserver for developers

You can send a command like in serial port to
http://ip_address_or_domain_of_the_station_that_runs_windows_software:24000/command_from_HELP_list_from_serial_port

It does not give any response, so,Chrome, for example,will show you slow loading animation.

Example: http://192.168.0.76:24000/turn_on_smooth

# Price

Price of components:

- LED string that runs on 3 AAs that is 4.5 volts that can be powered from 5V of USB 2.0 = ~3$ = ~200 russian roubles(prices may be different)
- N channel Mosfet = less than 1$ = less than 50 russian roubles = can be desoldered from some old broken tech
- Arduino Nano/Uno = from 5 to 25$ = from 300 to 1500 russian roubles
- Soldering iron = Ask your dad or dad's freind = optional
