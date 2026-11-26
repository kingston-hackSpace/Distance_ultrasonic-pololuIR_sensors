// Count objects using a Pololu Distance Sensor
// The LED turns on while an object is close, and the counter goes up by 1
// each time a NEW object comes closer than the threshold.

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

void setup(){
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(LED_pin, OUTPUT);
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
      Serial.print("Count: ");
      Serial.println(counter);
      objectDetected = true; // now true, therefore, stop counting
    }

  }else{
    digitalWrite(LED_pin, LOW); // LED off
    objectDetected = false;     // object has gone, ready to count the next one
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