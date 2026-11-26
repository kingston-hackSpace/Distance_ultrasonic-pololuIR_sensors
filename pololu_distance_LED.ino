// Turn on an LED using a Pololu PIR Distance Sensor

//Pins
int sensorPin = 2;
int LED_pin = 13;

//distance variables
int distance_mm; 
int timeout;
int threshold = 50;

void setup(){
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(LED_pin, OUTPUT);
}
 
void loop(){
  timeout = pulseIn(sensorPin, HIGH);
  sensorDebugg();
 
  //print sensor data
  Serial.print(distance_mm);
  Serial.println(" mm");

  if (distance_mm < threshold){
    digitalWrite(LED_pin, HIGH); // LED on
    }else{
      digitalWrite(LED_pin, LOW); // LED off
    }

  delay(50);
  
}

void sensorDebugg(){
  if (timeout == 0){
    Serial.println("timeout"); // pulseIn() did not detect the start of a pulse within 1 second.
  }
  else if (timeout > 1850){
    Serial.println("OUT OF RANGE"); // No detection.
  }  else {
    // Valid pulse width reading. Convert pulse width in microseconds to distance in millimeters.
    distance_mm = (timeout - 1000) * 4;
 
    if (distance_mm < 0) {     // Limit minimum distance to 0.
      distance_mm = 0; 
    } 
  }

}
