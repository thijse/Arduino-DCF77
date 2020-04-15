/*
 * InternalClockSync.ino 
 * example code illustrating time synced from a DCF77 receiver
 * Thijs Elenbaas, 2012-2017
 * This example code is in the public domain.
 
  This example shows how to fetch a DCF77 time and synchronize
  the internal clock. In order for this example to give clear output,
  make sure that you disable logging  from the DCF library. You can 
  do this by commenting out   #define VERBOSE_DEBUG 1   in Utils.cpp. 
  
  NOTE: If you used a package manager to download the DCF77 library, 
  make sure have also fetched these libraries:

 * RTCZero | or the appropiate library for your RTC
  
 */

#define DCF77_USE_RTC // define before #include "DCF77.h"; 
                      // it "enables" RTC and "disables" TimeLib
#include "DCF77.h"
#include <RTCZero.h>

#define DCF_PIN 12                 // Connection pin to DCF 77 device
#define DCF_OnRisingFlank false    // false: DCF device signal inverted
#define DCF_EnableInputPullup true // true: connection pin input pullup enabled
#define DCF_CompareToUTC true      // true: library compares to UTC instead of localtime
#define DCF_INTERRUPT digitalPinToInterrupt(DCF_PIN)  // Interrupt number associated with pin
#ifdef SERIAL_PORT_MONITOR
#define Serial SERIAL_PORT_MONITOR
#endif

RTCZero rtc;
DCF77 DCF = DCF77(DCF_PIN, DCF_INTERRUPT, DCF_OnRisingFlank, DCF_EnableInputPullup, DCF_CompareToUTC);


void setup() {
  Serial.begin(9600);
  rtc.begin(); // initialize RTC
  DCF.Start();
  DCF.setCallbackFunctionRTC(RTC_Callback_Wrapper); // change in RTC_Callback_Wrapper, not here
  Serial.println("Waiting for DCF77 time ... ");
  Serial.println("It will take at least 2 minutes until a first update can be processed.");
}

void loop() {
  time_t DCFtime = DCF.getUTCTime(); // Check if new DCF77 time is available
  if (DCFtime!=0)
  {
    if (DCFtime != rtc.getEpoch()) {
      Serial.println("Time is updated");
      rtc.setEpoch(DCFtime);
    } else {
      Serial.println("0 delta");
    }
  }	

  digitalClockDisplay();  
  delay(1000);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(rtc.getHours());
  printDigits(rtc.getHours());
  printDigits(rtc.getSeconds());
  Serial.print(" ");
  Serial.print(rtc.getDay());
  Serial.print(" ");
  Serial.print(rtc.getMonth());
  Serial.print(" ");
  Serial.print(rtc.getYear()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

time_t RTC_Callback_Wrapper()
{
    // change rtc.getEpoch() to the apporpiate function for your RTC
    return rtc.getEpoch();
}
