#include "Arduino.h"
#include "Data_Storage.h"
#include "Time_lib.h"
#include "FS.h"
#include "SPIFFS.h"

#define FORMAT_SPIFFS_IF_FAILED true

/* You only need to format SPIFFS the first time you run a
   test or else use the SPIFFS plugin to create a partition
   https://github.com/me-no-dev/arduino-esp32fs-plugin */

DataStorage::DataStorage()
{
  // pinMode(pin, INPUT);
  // _pin = pin;
  return;
}

void DataStorage::setup()
{
    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    Serial.println("[INFO] : The data module is ready to be used ");
}


void DataStorage::read()
{

}

void DataStorage::writedata(float pH, float Moisture, float Temp)
{
  
    static char time[30];
    Timelib Time_l;
    String Formated_time;
    static char Formated_TimeChar[50];
    static char Formated_text[255];
    // unsigned long TimeMillis = 0;
    // TimeMillis = Time_l.GetTime();
    Formated_time = Time_l.FormatTime();
    Formated_time.toCharArray(Formated_TimeChar,50);

    char FileName[20] = "/2022-12_data.csv";
    // snprintf(Formated_text,
    //     255,
    //     PSTR("{\"Time\":\"%s\",\"pH\":%.2f,\"Moisture\":%.1f,\"Temp\":%.2f}\r\n"),
    //     Formated_time,
    //     pH,
    //     Moisture,
    //     Temp
    // );
    snprintf(Formated_text,
        255,
        PSTR("{\"Time\":\"%s\",\"pH\":%.2f,\"Moisture\":%.1f,\"Temp\":%.2f}\r\n"),
        Formated_TimeChar,
        pH,
        Moisture,
        Temp
    );
    appendFile(SPIFFS, FileName, Formated_text);
    Serial.print("[DATA] : The following data is stored in the file ");
    Serial.print(FileName);
    Serial.print(" : ");
    Serial.println(Formated_text);

}

void DataStorage::listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("[INFO] Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
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
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void DataStorage::readFile(fs::FS &fs, const char * path){
    Serial.printf("[INFO] Reading file: %s\r\n", path);

    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }

    // Serial.println("- read from file:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void DataStorage::writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
}

void DataStorage::appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("[INFO] Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("   - failed to open file for appending");
        return;
    }
    if(file.print(message)){
        // Serial.println("- message appended");
    } else {
        Serial.println("   - append failed");
    }
    file.close();
}

void DataStorage::renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\r\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("   - file renamed");
    } else {
        Serial.println("   - rename failed");
    }
}

void DataStorage::deleteFile(fs::FS &fs, const char * path){
    Serial.printf("[INFO] Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("   - file deleted");
    } else {
        Serial.println("   - delete failed");
    }
}

void DataStorage::testFileIO(fs::FS &fs, const char * path){
    Serial.printf("Testing file I/O with %s\r\n", path);

    static uint8_t buf[512];
    size_t len = 0;
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }

    size_t i;
    Serial.print("- writing" );
    uint32_t start = millis();
    for(i=0; i<2048; i++){
        if ((i & 0x001F) == 0x001F){
          Serial.print(".");
        }
        file.write(buf, 512);
    }
    Serial.println("");
    uint32_t end = millis() - start;
    Serial.printf(" - %u bytes written in %u ms\r\n", 2048 * 512, end);
    file.close();

    file = fs.open(path);
    start = millis();
    end = start;
    i = 0;
    if(file && !file.isDirectory()){
        len = file.size();
        size_t flen = len;
        start = millis();
        Serial.print("- reading" );
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            if ((i++ & 0x001F) == 0x001F){
              Serial.print(".");
            }
            len -= toRead;
        }
        Serial.println("");
        end = millis() - start;
        Serial.printf("- %u bytes read in %u ms\r\n", flen, end);
        file.close();
    } else {
        Serial.println("- failed to open file for reading");
    }
}