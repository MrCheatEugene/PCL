import controlP5.*;
import processing.serial.*;
import processing.net.*;
import java.net.URLDecoder;
String command;
Serial myPort;
ControlP5 cp5;
Button on_btn;
Button off_btn;
Button on_s_btn;
Button off_s_btn;
Button blink_btn;
Button fast_blink_btn;
Button fast_turn_on_smooth;
Button fast_turn_off_smooth;
Button repeatBlink;
Button raveMode;
Button randomModes;
boolean doCallFunc=true;
boolean repeatBlinkinn=false;
boolean repeatParty=false;
boolean randomMode=false;
Client c;
Server s;
void setup(){
  size(700,300);
  noStroke();
    s = new Server(this, 24000); // Start a simple server on a port

  cp5 = new ControlP5(this);
  on_btn=cp5.addButton("Turn on")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(25,25)
     .setSize(200,50)
     ;
       off_btn=cp5.addButton("Turn off")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(250,25)
     .setSize(200,50)
     ;
       on_s_btn=cp5.addButton("Turn on softly")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(475,25)
     .setSize(200,50)
     ;
          off_s_btn=cp5.addButton("Turn off softly")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(25,80)
     .setSize(200,50)
     ;
               blink_btn=cp5.addButton("Blink")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(250,80)
     .setSize(200,50)
     ;    
                    fast_blink_btn=cp5.addButton("Blink fastly")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(475,80)
     .setSize(200,50)
     ;   
                         fast_turn_on_smooth=cp5.addButton("Turn on smooth&fastly")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(25,135)
     .setSize(300,50)
     ;                           fast_turn_off_smooth=cp5.addButton("Turn off smooth&fastly")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(375,135)
     .setSize(300,50)
     ;  
                   repeatBlink=cp5.addButton("Blink continously")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(25,190)
     .setSize(300,50)
     ;  
                        raveMode=cp5.addButton("PARTY")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(350,190)
     .setSize(100,50)
     ;                          randomModes=cp5.addButton("Random")
     .setValue(0)
.setFont(createFont("Arial",20))
     .setPosition(475,190)
     .setSize(150,50)
     ;  
     myPort = new Serial(this, "COM4", 9600);
}
int timesCalled=0;

void draw(){
 if( on_btn.isPressed()== true){
sendCommand("turn_on");
 }
  if( off_btn.isPressed()== true){
sendCommand("turn_off");
 }
  if( on_s_btn.isPressed()== true){
sendCommand("turn_on_smooth");
 }
  if( off_s_btn.isPressed()== true){
sendCommand("turn_off_smooth");
 }
   if( blink_btn.isPressed()== true){
sendCommand("blink");
 }
    if( fast_blink_btn.isPressed()== true){
sendCommand("blink_fast");
 }
    if( fast_turn_on_smooth.isPressed()== true){
sendCommand("turn_on_smooth_fast");
 }
    if( fast_turn_off_smooth.isPressed()== true){
sendCommand("turn_off_smooth_fast");
 }   
 if( repeatBlink.isPressed()== true){  
   repeatBlinkinn=!repeatBlinkinn;
 } if( raveMode.isPressed()== true){  
   repeatParty=!repeatParty;
 }if( randomModes.isPressed()== true){  
   randomMode=!randomMode;
 }
 if (repeatBlinkinn ==true){
      repeatBlink.setLabel("Press any key to stop");
 sendCommand("blink");
    delay(2500);   
}
 if (repeatParty ==true){
    raveMode.setLabel("PR KEY");
 sendCommand("blink_fast");
    delay(1000);
}
 if (randomMode ==true){
   String modes[]={"turn_on","turn_off","turn_on_smooth","turn_off_smooth","turn_on_smooth_fast","turn_off_smooth_fast","blink_fast","blink"};
    randomModes.setLabel("PRESSANYKEY");
 sendCommand(modes[round(random(0,modes.length-1))]);
    delay(1000);
}
  c = s.available();
  if (c != null) {
    command=c.readString().split("\n")[0].split(" HTTP/1.1")[0].split("/")[1];
     sendCommand(command);

}
}private String decode(String value) {
    return URLDecoder.decode(value);
}
void keyPressed() {
   if (repeatBlinkinn ==true){
           repeatBlink.setLabel("Blink continously");
  repeatBlinkinn =false;
}
   if (repeatParty ==true){
           raveMode.setLabel("PARTY");
  repeatParty =false;
}
  if (randomMode ==true){
           randomModes.setLabel("Random");
  randomMode =false;
}

}

void sendCommand(String cmd){
 println(decode(cmd));
    myPort.write(decode(cmd));              // send an H to indicate mouse is over square
    delay(200);
}
