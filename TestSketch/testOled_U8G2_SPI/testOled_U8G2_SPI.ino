/*
    TTGO T8 V1.8
    TEST OLED SPI HARDWARE
    hardware: Board ESP32-MP OLED 256x64 Display
    Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/) 
*/

#include <U8g2lib.h>

/**** Display OLED 4 way Hardware SPI  *****/
//#define DISPLAY_MOSI   23   // default SPI pin  
//#define DISPLAY_CLK    18   // default SPI pin  
#define DISPLAY_DC      0     // DC     
#define DISPLAY_CS      2     // CS           
#define DISPLAY_RESET   5     // RES 

// OK costruttore per OLED DISPLAY SPI (2,42" 128x64 SSD1309 SPI 2420A V1.1 FUTURA 3085-OLED242W)
//U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ DISPLAY_CS, /* dc=*/ DISPLAY_DC, /* reset=*/ DISPLAY_RESET); 

// OK costruttore per OLED DISPLAY SPI (2,08" 256x64 SH1122 SPI HM25664A208W02 FUTURA 2846-SPIOLED208)
U8G2_SH1122_256X64_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ DISPLAY_CS, /* dc=*/ DISPLAY_DC, /* reset=*/ DISPLAY_RESET);


/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
*/

// 'select20', 20x20px
const unsigned char select20 [] = {
  0x00, 0x06, 0x00, 0x00, 0x0f, 0x00, 0x80, 0x1f, 0x00, 0xc0, 0x3f, 0x00, 0xe0, 0x7f, 0x00, 0xf0, 
  0xff, 0x00, 0xf8, 0xff, 0x01, 0xfc, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x03, 0xf8, 0xff, 0x01, 0xf0, 0xff, 0x00, 0xe0, 0x7f, 0x00, 
  0xc0, 0x3f, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x06, 0x00
};

// 'repeatall20', 20x20px
const unsigned char repeatall20 [] PROGMEM = {
  0x00, 0x08, 0x00, 0x00, 0x18, 0x00, 0x00, 0x38, 0x00, 0x00, 0x78, 0x00, 0xfc, 0xff, 0x03, 0xfe, 
  0xff, 0x07, 0x07, 0x78, 0x0e, 0x03, 0x38, 0x0c, 0x03, 0x18, 0x0c, 0x03, 0x08, 0x0c, 0x03, 0x01, 
  0x0c, 0x83, 0x01, 0x0c, 0xc3, 0x01, 0x0c, 0xe7, 0x01, 0x0e, 0xfe, 0xff, 0x07, 0xfc, 0xff, 0x03, 
  0xe0, 0x01, 0x00, 0xc0, 0x01, 0x00, 0x80, 0x01, 0x00, 0x00, 0x01, 0x00
};


void setup(void) 
{
  u8g2.begin();
}

void loop() 
{
    u8g2.clearBuffer();
    u8g2.setFontPosCenter();  //centrato in verticale  
    u8g2.setFont(u8g2_font_fur20_tf);
    u8g2.setCursor(0, 32);      
    u8g2.print("Hello ");
    
    // icone di sistema come caratteri
    u8g2.setFont(u8g2_font_open_iconic_all_2x_t);  
    u8g2.drawUTF8( 60, 32, "\u00C1"); //chiave C1 HEX
    u8g2.drawGlyph(80,32, 242);  //repeat all
    u8g2.drawGlyph(100,32, 245); //freccia su e giu
    u8g2.drawGlyph(120,32, 154); //freccia su e giu
    u8g2.drawGlyph(140,32, 243); //random
    u8g2.drawGlyph(160,32, 204); //repeat
        
    //draw icons    
     u8g2.drawXBM( 180, 32, 20, 20, select20);    
     u8g2.drawXBMP( 200, 32, 20, 20, repeatall20);      
     u8g2.sendBuffer();
       
    for(;;) ;
}
