const int trigPin = 9;
const int echoPin = 10;

float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  digitalWrite(trigPin, LOW); // Make sure trigger is off at setup
}

void loop() {
  // Send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time (with simple timeout)
  unsigned long duration = pulseIn(echoPin, HIGH, 30000); // measures the echo pulse duration in microseconds

  if (duration == 0) {
      Serial.println("Out of range");
    } else {
      distance = (duration * 0.0343) / 2; // converts echo time to distance in cm
  
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
    }
  
    delay(100);
}
