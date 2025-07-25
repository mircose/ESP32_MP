// TEST ENCODER
// ESP32_MP

#include "src/Button2/Button2.h"

/***** Encoder pins *****/
const byte pinEncA     = 36; //Data (Rpullup inclusa in encoder breakout)
const byte pinEncB     = 39; //CLK  (Rpullup inclusa in encoder breakout)
const byte pinEncPB    = 34; //PB   (Rpullup inclusa in encoder breakout)
volatile int encCount = 0;
volatile byte encState = 0;
//ESP32Encoder encoder;
Button2 EncPB;
bool disableEncPB=0;

void setup() 
{
   Serial.begin(115200);
   delay(100);
   Serial.println("Test Encoder");
   initEncoder();                  // Initialize encoder

}

void loop() 
{
    EncPB.loop();          // digital button service (Button2 lib)
    encService();

    /***** ENCODER SERVICE CW ROTATION *****/
    if (encCount > 0) //CW rotation INCREMENT
    {
       encCount = 0;
       Serial.println("+");
    }

    /***** ENCODER SERVICE CCW ROTATION *****/
    if (encCount < 0) //CCW rotation DECREMENT
    {
       encCount = 0;       
       Serial.println("-");   
    }
    
    delay(10);
}

// ENCODER BUTTON LONG PRESS EVENT 
void longClickDetected(Button2& btn) 
{
  Serial.println("Long click");        
}

// ENCODER BUTTON CLICK EVENT    
void released(Button2& btn) 
{
  Serial.println("Press Knob");
}

// Initialize Encoder Push Button 
void initEncoder()
{
    pinMode(pinEncA, INPUT);  // PULL UP già nella breakout board, add 100nF Capacitor
    pinMode(pinEncB, INPUT);    

    #define DEBOUNCE_MS 50
    #define LONGCLICK_MS 2000
    #define DOUBLECLICK_MS 3000
  
    EncPB.begin(pinEncPB);
    //EncPB.setPressedHandler(pressed);    
    EncPB.setReleasedHandler(released);  

    EncPB.setLongClickTime(LONGCLICK_MS);   
    EncPB.setLongClickDetectedHandler(longClickDetected); //quando è passato il tempo prastabilito mantenendo premuto il pulsante
    EncPB.setLongClickDetectedRetriggerable(false); //???    
}

// Run repeatedly Encoder Knob 
void encService()
{
  bool CHA = digitalRead(pinEncA);
  bool CHB = digitalRead(pinEncB);  
  switch (encState) {
    case 0:
      if (CHA==0 && CHB==1) encState=1;
      if (CHA==1 && CHB==0) encState=4;
      break;
    case 1:
      if (CHA==1 && CHB==1) encState=0;
      if (CHA==0 && CHB==0) encState=2;
      break;
    case 2:
      if (CHA==1 && CHB==0) encState=3;  
      if (CHA==0 && CHB==1) encState=1;    
      break;
    case 3:
      if (CHA==1 && CHB==1) { encState=0;  encCount++; }
      if (CHA==0 && CHB==0) encState=2;    
      break;      
    case 4:
      if (CHA==1 && CHB==1) encState=0;
      if (CHA==0 && CHB==0) encState=5;
      break;  
    case 5:
      if (CHA==0 && CHB==1) encState=6;
      if (CHA==1 && CHB==0) encState=4;
      break;   
    case 6:  
      if (CHA==1 && CHB==1) { encState=0;  encCount--; }
      if (CHA==0 && CHB==0) encState=5;    
      break;                
  }    
}
