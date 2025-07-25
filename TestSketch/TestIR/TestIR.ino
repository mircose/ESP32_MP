// TEST IR
// Hardware ESP32_MP

#include "src/IRremote/IRremote.h"
#define    IR_PIN        15

void setup() 
{
  Serial.begin(115200);
  delay(100);
  Serial.println("Test IR");
  IrReceiver.begin(IR_PIN);}

void loop() 
{
    handleIR();
    delay(10);
}

void handleIR()
{
  if (IrReceiver.decode()) 
  {
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)
    {
     IrReceiver.resume(); // // Enable receiving of the next value
     return;     
    }

    int code = IrReceiver.decodedIRData.command;
    Serial.print("IR code: "); Serial.println(code); 
    IrReceiver.resume(); // // Enable receiving of the next value 
  }    
}  
