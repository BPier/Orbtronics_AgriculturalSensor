#ifndef Data_Storage_h
#define Data_Storage_h

#include "Arduino.h"
#include "Time_lib.h"
#include "FS.h"
#include "SPIFFS.h"


class DataStorage
{
  public:
    DataStorage();
    void setup();
    void read();
    char* writedata(float pH, float Moisture, float Temp);
    void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
    void readFile(fs::FS &fs, const char * path);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    void appendFile(fs::FS &fs, const char * path, const char * message);
    void renameFile(fs::FS &fs, const char * path1, const char * path2);
    void deleteFile(fs::FS &fs, const char * path);
    void testFileIO(fs::FS &fs, const char * path);
    void sendFileBT(fs::FS &fs, const char * path);
  private:
    int _pin;
};

#endif