# PCL
Probably Cool Lights will transfrom your LED string or any other things to a masterpiece with remote access from phone and computer!
# How it works?
Under your table is hidden Arduino board with mosfet, that controls LED string or something else(THAT WORKS ON DC, if you will connect AC, say goodbye to your mosfet,arduino,PC and maybe that thing). Arduino does not do anything with the string itself, it controls the mosfet.

Computer, that is also a webserver, connects to arduino by Serial port at speed of 9600 baud and sends commands to it.

Phone just sends requests to webserver. Also, webserver uses port 24000 rather than classical 80/8080.

And boom, simple, easy, and it works!(at least for people who have one color LED string or led string whiout controller. and if it runs on DC).

# Donate

Making projects like that one is hard, and if you want to support me, so I can do better things

go to https://donationalerts.com/r/mrcheatt

# App for PC
