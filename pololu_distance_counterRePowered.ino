// Count objects using a Pololu Distance Sensor (pulse width output)
// The LED turns on while an object is close, and the counter goes up by 1
// each time a NEW object comes closer than the threshold.
// The count is saved in EEPROM, so it is remembered after unplugging.

#include <EEPROM.h> // library for the Arduino's permanent memory

//Pins
int sensorPin = 2;
int LED_pin = 13;

//distance variables
int distance_mm;
int timeout;
int threshold = 50;

//counter variables
int counter = 0;
bool objectDetected = false; // remembers if an object was there last time
int counterAddress = 0;      // where in the EEPROM we save the counter

void setup(){
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(LED_pin, OUTPUT);

  // read the last saved count from EEPROM
  EEPROM.get(counterAddress, counter);

  // a brand new (empty) EEPROM gives -1, so start from 0 in that case
  if (counter < 0){
    counter = 0;
  }

  Serial.print("Starting count: ");
  Serial.println(counter);
}

void loop(){
  timeout = pulseIn(sensorPin, HIGH);
  sensorDebugg();

  //print sensor data
  //Serial.print(distance_mm);
  //Serial.println(" mm");

  if (distance_mm < threshold){
    digitalWrite(LED_pin, HIGH); // LED on

    // only count if the object is NEW (it wasn't there last time)
    if (objectDetected == false){
      counter = counter + 1;
      EEPROM.put(counterAddress, counter); // save the new count
      Serial.print("Count: ");
      Serial.println(counter);
      objectDetected = true;
    }

  }else{
    digitalWrite(LED_pin, LOW); // LED off
    objectDetected = false;     // object has gone, ready to count the next one
  }

  // type r in the Serial Monitor and press Enter to reset the count to 0
  if (Serial.available() > 0){
    char letter = Serial.read();
    if (letter == 'r'){
      counter = 0;
      EEPROM.put(counterAddress, counter);
      Serial.println("Counter reset to 0");
    }
  }

  delay(50);
}

void sensorDebugg(){
  if (timeout == 0){
    Serial.println("timeout"); // pulseIn() did not detect the start of a pulse within 1 second.
    distance_mm = 9999;        // treat as "nothing there"
  }
  else if (timeout > 1850){
    Serial.println("OUT OF RANGE"); // No detection.
    distance_mm = 9999;             // treat as "nothing there"
  } else {
    // Valid pulse width reading. Convert pulse width in microseconds to distance in millimeters.
    distance_mm = (timeout - 1000) * 4;

    if (distance_mm < 0) {     // Limit minimum distance to 0.
      distance_mm = 0;
    }
  }
}