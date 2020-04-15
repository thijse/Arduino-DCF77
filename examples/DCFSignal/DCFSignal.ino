/*
 * DCFSignal.ino - DCF77 debug Example
 * Thijs Elenbaas, 2012-2017
 * This example code is in the public domain.
 
  This simple example shows the raw signal coming from the DCF decoder.
  
  Pulse-to-Pulse is approximately 1000 ms and pulse with is approx 100ms or 200ms
  The axis underestimates the elapsed time slightly, because a single loop takes a bit
  longer than 10ms.
  
  NOTE: If you used a package manager to download the DCF77 library, 
  make sure have also fetched these libraries:

 * Time 

*/

#define BLINKPIN LED_BUILTIN
#define DCF77PIN 2
#ifdef SERIAL_PORT_MONITOR
#define Serial SERIAL_PORT_MONITOR
#endif

int prevSensorValue=0;
  
void setup() {
  Serial.begin(9600);
  pinMode(DCF77PIN, INPUT);
  pinMode(13, OUTPUT);
  Serial.println("0ms       100ms     200ms     300ms     400ms     500ms     600ms     700ms     800ms     900ms     1000ms    1100ms    1200ms");
}

void loop() {
  int sensorValue = digitalRead(DCF77PIN);
  if (sensorValue==1 && prevSensorValue==0) { Serial.println("");   }
  digitalWrite(BLINKPIN, sensorValue);
  Serial.print(sensorValue);   
  prevSensorValue = sensorValue;
  delay(10);
}



