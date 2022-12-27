#include "Arduino.h"
#include "Data_Storage.h"

#define FORMAT_SPIFFS_IF_FAILED true

DataStorage Data_S;

void setup(){
    Serial.begin(115200);
    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    
    Data_S.listDir(SPIFFS, "/", 0);
    Data_S.writeFile(SPIFFS, "/hello.txt", "Hello ");
    Data_S.appendFile(SPIFFS, "/hello.txt", "World! 002\r\n");
    Data_S.readFile(SPIFFS, "/hello.txt");
    Data_S.renameFile(SPIFFS, "/hello.txt", "/foo.txt");
    Data_S.readFile(SPIFFS, "/foo.txt");
    Data_S.deleteFile(SPIFFS, "/foo.txt");
    Data_S.testFileIO(SPIFFS, "/test.txt");
    Data_S.deleteFile(SPIFFS, "/test.txt");
    Serial.println( "Test complete" );
}

void loop(){

}