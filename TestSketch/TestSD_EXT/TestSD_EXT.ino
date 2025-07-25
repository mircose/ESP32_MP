/*
  ESP32_MP TTGO T8 V1.8 TEST SD Card
  use EXTERNAL SD card reader HARDWARE SPI
*/

/***** SD Card Pins (SPI) *****/

#define SD_CS      4
#define SPI_MOSI  23
#define SPI_MISO  19
#define SPI_SCK   18



/* for use SD in BUS HSPI instead of VSPI
// configure this instance to use the 
// 2nd SPI bus called "HSPI" instead
// of the first, default bus "VSPI"
SPIClass sdSPI(HSPI);
// initialized the alternate SPI port and pin mappings
sdSPI.begin(SDM_CLK,SDM_MISO,SDM_MOSI,SDM_CS); //CLK,MISO,MOSI,CS

// initialize SD
if(!SD.begin(SDM_CS,sdSPI)){
    Serial.println(F("MicroSD Card Mount Failed"));
    return -1;
}
*/
 
 
#include <FS.h>
#include <SD.h>
#include <SPI.h>

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}


void setup(){
    Serial.begin(115200);
    delay(100);
    Serial.println("\n\nTEST EXTERNAL SD");

    const byte pinSDEnable   = 12;    
    pinMode(pinSDEnable, OUTPUT);
    digitalWrite(pinSDEnable, HIGH);      
    delay(1000);

    //use default SPI pins
    if(!SD.begin(SD_CS)){
        Serial.println("Card Mount Failed");
        return;
    }

    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
    delay(1000);
    listDir(SD, "/", 0);
}

void loop(){
  delay(100);
}
