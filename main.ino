// Pin connections
const int trigPin = 9;   // Trig pin of HC-SR04 connected to digital pin 9
const int echoPin = 10;  // Echo pin of HC-SR04 connected to digital pin 10

// Variables
long duration;    // Time taken for the pulse to return
float distance;   // Calculated distance in centimeters
unsigned long timeNow; // Time since start in ms
unsigned long countedTime = 0.0;

void setup() {
  Serial.begin(9600);          // Start serial communication
  pinMode(trigPin, OUTPUT);    // Trig is an output
  pinMode(echoPin, INPUT);     // Echo is an input
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10 µs pulse to trigger the sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance (speed of sound = 343 m/s)
  distance = duration * 0.034 / 2;  // Convert to cm

  // Print the result to Serial Monitor

  if(distance < 6)
  {
    
    unsigned long timeNow = millis(); // Time since start in ms
    Serial.println("");
    Serial.println("START OPTION");
    //Serial.print("Counted now: ");
   // Serial.println(countedTime);
   // Serial.print("Time now: ");
   // Serial.println(timeNow);
    Serial.print("Time took: ");
    Serial.println((timeNow-countedTime)/1000);
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    Serial.print("Velocity: ");
    Serial.println( (8*3.14*2) / ((timeNow-countedTime)/1000));





    countedTime = timeNow;
  //  Serial.print("Counted now: ");
  //  Serial.println(countedTime);
  //  Serial.print("Time now: ");
  //  Serial.println(timeNow);
    //unsigned long timeNow = millis();


  }

  delay(500);  // Wait half a second between measurements
}
