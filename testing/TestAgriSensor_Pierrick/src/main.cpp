#include "Arduino.h"
#include "Data_Storage.h"
#include <RTCLIB.h>
#include <SPI.h>


DataStorage Data_S;

void setup(){
    Serial.begin(115200);
    Data_S.setup();
    Data_S.deleteFile(SPIFFS,"/2022-12_data.csv");
    // Data_S.listDir(SPIFFS, "/", 0);
    // Data_S.writeFile(SPIFFS, "/hello.txt", "Hello ");
    // Data_S.appendFile(SPIFFS, "/text.txt", "And Happy Holidays !\r\n");
    // Data_S.readFile(SPIFFS, "/hello.txt");
    // Data_S.renameFile(SPIFFS, "/hello.txt", "/foo.txt");
    // Data_S.readFile(SPIFFS, "/data.json");
    // Data_S.deleteFile(SPIFFS, "/foo.txt");
    // Data_S.testFileIO(SPIFFS, "/test.txt");
    // Data_S.deleteFile(SPIFFS, "/test.txt");
    // Serial.println( "Test complete" );
    // File file = SPIFFS.open("/text.txt");
    // if(!file){
    //     Serial.println("Failed to open file for reading");
    //     return;
    // }
    
    // Serial.println("File Contents:");
    // while(file.available()){
    //     Serial.write(file.read());
    // }
    // file.close();
}

void loop(){
    Data_S.writedata(7.45,34,27.76);
    Data_S.readFile(SPIFFS, "/2022-12_data.csv");
    delay(6000);

}