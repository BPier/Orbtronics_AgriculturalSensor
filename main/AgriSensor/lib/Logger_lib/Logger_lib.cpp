#include <Arduino.h>
#include <Logger_lib.h>
#include <Data_Storage.h>


Logger_lib::Logger_lib()
{

}

void Logger_lib::setup()
{
 
}

// 0-Fatal	
//    One or more key business functionalities are not working and the whole system doesn’t fulfill the business functionalities.
// 1-Error	
//    One or more functionalities are not working, preventing some functionalities from working correctly.
// 2-Warn	
//    Unexpected behavior happened inside the application, but it is continuing its work and the key business features are operating as expected.
// 3-Info	
//    An event happened, the event is purely informative and can be ignored during normal operations.
// 4-Debug	
//    A log level used for events considered to be useful during software debugging when more granular information is needed.
// 5-Trace	
//    A log level describing events showing step by step execution of your code that can be ignored during the standard operation, but may be useful during extended debugging sessions.
void logEvent(int level, char* EventDescription)
{

}


