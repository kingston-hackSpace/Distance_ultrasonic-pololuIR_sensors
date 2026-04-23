// Example Arduino program for reading the Pololu Distance Sensor with Pulse Width Output, 300cm Max

const uint8_t sensorPin = 2;
 
void setup(){
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
}
 
void loop(){
  int16_t timeout = pulseIn(sensorPin, HIGH);
 
  if (timeout == 0){
    Serial.println("timeout"); // pulseIn() did not detect the start of a pulse within 1 second.
  }
  else if (timeout > 1850){
    Serial.println("OUT OF RANGE"); // No detection.
  }  else {
    // Valid pulse width reading. Convert pulse width in microseconds to distance in millimeters.
    int16_t distance_mm = (timeout - 1000) * 4;
 
    if (distance_mm < 0) {     // Limit minimum distance to 0.
      distance_mm = 0; 
    } 

    float distance_cm = distance_mm / 10.0; // convert to cm
  
    Serial.print(distance_mm);
    Serial.print(" mm");

    Serial.print(" | ");

    Serial.print(distance_cm);
    Serial.println(" cm");

    delay(50);
  }
}
