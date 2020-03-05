 #include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;
int pWm=200;
int m1d=26, m2d=28, m3d=30, m4d=32;
int m1p=13, m2p=12, m3p=8, m4p=7;
int ptA=34,ptB=6;
int pkA=36,pkB=5;

void setup(){
 Serial.begin(57600);

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  pinMode(26,OUTPUT),pinMode(28,OUTPUT),pinMode(30,OUTPUT),pinMode(32,OUTPUT),pinMode(13,OUTPUT),pinMode(12,OUTPUT),pinMode(8,OUTPUT),pinMode(7,OUTPUT),pinMode(34,OUTPUT),pinMode(6,OUTPUT),pinMode(36,OUTPUT),pinMode(5,OUTPUT);
 
 error = ps2x.config_gamepad(53,10,11,51, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
  Serial.println("holding L1 or R1 will print out the analog stick values.");
  Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
  
}

void loop(){
   /* You must Read Gamepad to get new values
   Read GamePad and set vibration values
   ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-pWm)
   if you don't enable the rumble, use ps2x.read_gamepad(); with no values
   
   you should call this at least once a second
   */
   
   
   
 if(error == 1) //skip loop if no controller found
  return; 
  
 if(type == 2){ //Guitar Hero Controller
   /*
   ps2x.read_gamepad();          //read controller 
   
   if(ps2x.ButtonPressed(GREEN_FRET))
     Serial.println("Green Fret Pressed");
   if(ps2x.ButtonPressed(RED_FRET))
     Serial.println("Red Fret Pressed");
   if(ps2x.ButtonPressed(YELLOW_FRET))
     Serial.println("Yellow Fret Pressed");
   if(ps2x.ButtonPressed(BLUE_FRET))
     Serial.println("Blue Fret Pressed");
   if(ps2x.ButtonPressed(ORANGE_FRET))
     Serial.println("Orange Fret Pressed");
     

    if(ps2x.ButtonPressed(STAR_POWER))
     Serial.println("Star Power Command");
    
    if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
     Serial.println("Up Strum");
    if(ps2x.Button(DOWN_STRUM))
     Serial.println("DOWN Strum");
  
 
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");

    
    if(ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE
    {
        Serial.print("Wammy Bar Position:");
        Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
    } */
 }

 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
       
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   
  
    
      vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                              //how hard you press the blue (X) button    
    
    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
     
       
         
        if(ps2x.Button(PSB_L3))
         Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
         Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         Serial.println("R2 pressed");
        if(ps2x.Button(PSB_GREEN))
         Serial.println("Triangle pressed");
         
    }   
         
    
    if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
         Serial.println("Circle just pressed");
         
    if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
         Serial.println("Square just released");     
    
    if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
         Serial.println("X just changed");    
    
    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); 
    } 

    float x=ps2x.Analog(PSS_LX);
    float y=ps2x.Analog(PSS_LY);
    
    if(x==123 && y<123 && ps2x.Button(PSB_L1))  //forward movement
    {
      digitalWrite(m1d,1);
      digitalWrite(m2d,0);
      digitalWrite(m3d,1);
      digitalWrite(m4d,0);
  
      analogWrite(m1p,pWm);
      analogWrite(m2p,pWm);
      analogWrite(m3p,pWm);
      analogWrite(m4p,pWm);

    } 

    if(x==123 && y>123 && ps2x.Button(PSB_L1))  //backward movement
    {
      digitalWrite(m1d,0);
      digitalWrite(m2d,1);
      digitalWrite(m3d,0);
      digitalWrite(m4d,1);
  
      analogWrite(m1p,pWm);
      analogWrite(m2p,pWm);
      analogWrite(m3p,pWm);
      analogWrite(m4p,pWm);

    }

    if(y==123 && x>123 && ps2x.Button(PSB_L1)) //right movement
    {
      digitalWrite(m1d,0);
      digitalWrite(m2d,1);
      digitalWrite(m3d,1);
      digitalWrite(m4d,0);
  
      analogWrite(m1p,pWm);
      analogWrite(m2p,pWm);
      analogWrite(m3p,pWm);
      analogWrite(m4p,pWm);

    }

    if(y==123 && x<123 && ps2x.Button(PSB_L1))  //left movement
    {
      digitalWrite(m1d,1);
      digitalWrite(m2d,0);
      digitalWrite(m3d,0);
      digitalWrite(m4d,1);
  
      analogWrite(m1p,pWm);
      analogWrite(m2p,pWm);
      analogWrite(m3p,pWm);
      analogWrite(m4p,pWm);

    }

     if(y<123 && x>123 && ps2x.Button(PSB_L1))  //diagonal quadrant 1 movement
    {
      digitalWrite(m1d,0);
      digitalWrite(m3d,1);
      
  
      analogWrite(m1p,pWm);
      analogWrite(m2p,0);
      analogWrite(m3p,pWm);
      analogWrite(m4p,0);

    }

    if(y<123 && x<123 && ps2x.Button(PSB_L1))  //diagonal quadrant 2 movement
    {
      digitalWrite(m2d,0);
      digitalWrite(m4d,1);
      
  
      analogWrite(m1p,0);
      analogWrite(m2p,pWm);
      analogWrite(m3p,0);
      analogWrite(m4p,pWm);

    }

    if(y>123 && x<123 && ps2x.Button(PSB_L1))  //diagonal quadrant 3 movement
    {
      digitalWrite(m1d,1);
      digitalWrite(m3d,0);
      
  
      analogWrite(m1p,pWm);
      analogWrite(m2p,0);
      analogWrite(m3p,pWm);
      analogWrite(m4p,0);

    }

    if(y>123 && x>123 && ps2x.Button(PSB_L1))  //diagonal quadrant 4 movement
    {
      digitalWrite(m2d,1);
      digitalWrite(m4d,0);
      
  
      analogWrite(m1p,0);ū
      analogWrite(m2p,pWm);
      analogWrite(m3p,0);
      analogWrite(m4p,pWm);

    }

    if(y<5&& ps2x.Button(PSB_L2))  //forward movement
    {
      digitalWrite(m1d,1);
      digitalWrite(m2d,1);
      digitalWrite(m3d,1);
      digitalWrite(m4d,1);
  
      analogWrite(m1p,pWm);
      analogWrite(m2p,230);
      analogWrite(m3p,pWm);
      analogWrite(m4p,pWm-40);

    }

    if(y>250 && ps2x.Button(PSB_L2))  //backward movement
    {
      digitalWrite(m1d,0);
      digitalWrite(m2d,0);
      digitalWrite(m3d,0);
      digitalWrite(m4d,0);
  
      analogWrite(m1p,pWm);
      analogWrite(m2p,pWm);
      analogWrite(m3p,pWm);
      analogWrite(m4p,pWm);

    }

    if(x>250&& ps2x.Button(PSB_L2)) //right movement
    {
      digitalWrite(m1d,1);
      digitalWrite(m2d,0);
      digitalWrite(m3d,0);
      digitalWrite(m4d,1);
  
      analogWrite(m1p,pWm);
      analogWrite(m2p,pWm);
      analogWrite(m3p,pWm);
      analogWrite(m4p,pWm);

    }

    if(x<5&& ps2x.Button(PSB_L2))  //left movement
    {
      digitalWrite(m1d,0);
      digitalWrite(m2d,1);
      digitalWrite(m3d,1);
      digitalWrite(m4d,0);  
      analogWrite(m1p,pWm);
      analogWrite(m2p,pWm);
      analogWrite(m3p,pWm);
      analogWrite(m4p,pWm);

    }

     if(y<2 && x>253 && ps2x.Button(PSB_L2))  //diagonal quadrant 1 movement
    {
      digitalWrite(m1d,1);
      digitalWrite(m4d,1);
      analogWrite(m1p,pWm);
      analogWrite(m2p,0);
      analogWrite(m4p,pWm);
      analogWrite(m3p,0);

    }

    if(y<2&&x<2&&ps2x.Button(PSB_L2))  //diagonal quadrant 2 movement
    {
      digitalWrite(m2d,1);
      digitalWrite(m3d,1);
      analogWrite(m1p,0);
      analogWrite(m2p,pWm);
      analogWrite(m4p,0);
      analogWrite(m3p,pWm);

    }

    if(y>253&&x<2&&ps2x.Button(PSB_L2))  //diagonal quadrant 3 movement
    {
      digitalWrite(m1d,0);
      digitalWrite(m4d,0);
      analogWrite(m1p,pWm);
      analogWrite(m2p,0);
      analogWrite(m4p,pWm);
      analogWrite(m3p,0);

    }

    if(y>253&&x>253&&ps2x.Button(PSB_L2))  //diagonal quadrant 4 movement
    {
      digitalWrite(m2d,0);
      digitalWrite(m3d,0);
      analogWrite(m1p,0);
      analogWrite(m2p,pWm);
      analogWrite(m4p,0);
      analogWrite(m3p,pWm);

    }

    float x1=ps2x.Analog(PSS_RX);
    float y1=ps2x.Analog(PSS_RY);

    if( x1>132 && ps2x.Button(PSB_L2))    // right rotation

    { 
      digitalWrite(m1d,1);
      digitalWrite(m2d,0);
      digitalWrite(m3d,1);
      digitalWrite(m4d,0);
      analogWrite(m1p,x1/3);
      analogWrite(m2p,x1/3);
      analogWrite(m3p,x1/3);
      analogWrite(m4p,x1/3);

    }

    if( x1<110 && ps2x.Button(PSB_L2))     //left rotation

    { 
      digitalWrite(m1d,0);
      digitalWrite(m2d,1);
      digitalWrite(m3d,0);
      digitalWrite(m4d,1);
      analogWrite(m1p,(255-x1)/3);
      analogWrite(m2p,(255-x1)/3);
      analogWrite(m3p,(255-x1)/3);
      analogWrite(m4p,(255-x1)/3);

    }

    if(ps2x.Button(PSB_PAD_LEFT)) {               //trying pneumatic release
      digitalWrite(ptA,HIGH);
      digitalWrite(ptB,LOW);
     }

    if(ps2x.Button(PSB_PAD_RIGHT)) {               //trying pneumatic back
      digitalWrite(ptA,LOW);
      digitalWrite(ptB,LOW);
     }
    if(ps2x.Button(PSB_PAD_LEFT)) {               //KICK
      digitalWrite(pkA,HIGH);
      digitalWrite(pkB,LOW);
     }

    if(ps2x.Button(PSB_PAD_RIGHT)) {               //KICK BACK
      digitalWrite(pkA,LOW);
      digitalWrite(pkB,LOW);
     }  
      else if(x1>110&&x1<133&&x<240&&x>10&&y>10&&y<240)
     {
      analogWrite(m1p,0);
      analogWrite(m2p,0);
      analogWrite(m3p,0);
      analogWrite(m4p,0);
     }
      else if(ps2x.ButtonReleased(PSB_L2)){
      analogWrite(m1p,0);
      analogWrite(m2p,0);
      analogWrite(m3p,0);
      analogWrite(m4p,0);
     } 
 }
 delay(50);
 }
 
 

     
