// Include the R-series Logic Engine API
#include <wlogic32.h>

// Initialise the WLogicEngine API
WLogicEngine WLogicEngine(&Serial,9600); // Serial (Stream Port, baud rate)
//WLogicEngine WLogicEngine(16,17,9600); // Serial (RX Pin, TX Pin, baud rate)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Begin Setup
  WLogicEngine.begin(); // Refresh Speed (Default:125 ms)
}

unsigned long Wait = millis();
void loop() {
  // put your main code here, to run repeatedly:

  // If 30 Seconds have passed
  if (millis() > Wait) {
    // Set All Lights to Rainbow for 15 Seconds
    WLogicEngine.Rainbow(0, 15);


    // Reset Timer    
    Wait = millis() + 30000;
  }
}