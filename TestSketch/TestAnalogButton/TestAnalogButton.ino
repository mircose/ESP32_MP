// TEST ANALOG BUTTON

// Hardware ESP32_MP

// Arduino ADKeyboard Futura (Scheda a pulsanti SKU: 3085-BUTTONBOARD)
// OK analog keypad MIA 4 pulsanti ESP32-MP_PCB_PB_12X12X4_SF
// const int KeypadMap[] = {0, 850, 1967, 2945};   //cortocircuitando R9 100ohm
// const int KeypadMap[] = {100, 927, 1886, 2785}; //con R9 100ohm non funziona bene!
// SICCOME LA LIBRERIA ANALOGMULTIBUTTON DA ERRORE IN FASE DI BOOT SONO PASSATO A QUESTA
// E (131) gpio: gpio_set_level(226): GPIO output gpio_num error

//https://github.com/Makuna/AnalogKeypad

#include <AnalogKeypad.h>

// see the AnalogKeypad_CreateConfig.ino sketch example on how to create this table

// const int KeypadMap[] = {0, 430, 1200, 1925, 2900}; //5 button ADKeyboard Futura
// const int KeypadMap[] = {0, 850, 1967, 2945}; //4 button ESP32-MP_PCB_PB_12X12X4_SF con R9=0ohm

const int KeypadMap[] = {0, 474, 1234, 2002, 2958}; //5 button ESP32-MP_PCB_PB_12X12X5_SFXL

const uint16_t KeypadHoldTimeMs = 2000;
const uint8_t KeypadAnalogPin = A7;

AnalogKeypad keypad(KeypadAnalogPin, KeypadMap, countof(KeypadMap), KeypadHoldTimeMs);

// the button event callback
// this will be called when buttons are pressed and released
void ButtonHandler(const ButtonParam& param)
{
/*
  if (param.button==0 && param.state==ButtonState_Click)  //pulsante zero rilasciato
    Serial.println("Btn 0 Click");

  if (param.button==0 && param.state==ButtonState_Hold)  //pulsante zero long click (scaduto il tempo KeypadHoldTimeMs) ButtonState_Click NON si verifica
    Serial.println("Btn 0 Long");
*/  
  Serial.print("P=");
  Serial.print(param.button); //quale pulsante è premuto
  Serial.print(" ");
  Serial.println(param.state);
 
/*  
  switch (param.state)  //quale azione è stata compiuta sul pulsante, click equivale rilascio
  {
    case ButtonState_Up:
    Serial.print("Up");
    break;
    
    case ButtonState_Down:
    Serial.print("Down");
    break;
    
    case ButtonState_Click:
    Serial.print("Click");
    break;
    
    case ButtonState_DoubleClick:
    Serial.print("Double Click");
    break;
    
    case ButtonState_Hold:
    Serial.print("Hold");
    break;
   
  }
  
  Serial.println();
  */
}

void setup() 
{
    Serial.begin(115200);
    Serial.println("Initialized");
}

void loop() {
  
  keypad.loop(ButtonHandler);

  // simulate other work happening
  // it also should avoid long delays so loop above can be called
  // at least every 10-20ms
  delay(10);
}
