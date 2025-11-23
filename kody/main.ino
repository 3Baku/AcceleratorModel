#include <WiFi.h>
#include "wifipass.h"
#include <WebServer.h>
#include "webpage.h"
WebServer server(80);

const short numberOfMeasurements = 100;
const float onOffAspectRatio = 0.8;  //how much of calibrated V is considered open circuit
const float radius = 6.5; //in cm
const float mass = 2.74; //in grams
const float circumference = 2*radius*3.1415;
const int laserPin = D9; 
const int photoPin = D2;

bool calibration = 1;
bool showPlot = 0;
//states define 0 as being no barrier/closed circuit
bool currentState = 0;
bool lastState = 0;

unsigned short velocityIndex = 0;
unsigned long currentMillis = 0;
unsigned long duration = 0;
unsigned long duration_tmp = 0;
float velocity = 0.0;
unsigned long lastChangeTime = 0;
float calibratedVoltages = 0;
bool isEvenReading = 0; //used, because two measurenments per one circle

float velocityArray[numberOfMeasurements] = {0.0};
unsigned long durationArray[numberOfMeasurements] = {0}; 

// --- JSON GENERATORS ---

// Simple Array for first plot [v1, v2, v3]
String get_array_string() {
  String json = "[";
  for (int i = 0; i < velocityIndex; i++) {
    json += String(velocityArray[i]);
    if (i < velocityIndex - 1) json += ",";
  }
  json += "]";
  return json; 
}

// V,t object Array for plot 2: [{x:0, y:10}, {x:50, y:12}]
String get_xy_data_string() {
  String json = "[";
  for (int i = 0; i < velocityIndex; i++) {
    json += "{x:";
    json += String(durationArray[i]);
    json += ",y:";
    json += String(velocityArray[i]);
    json += "}";
    if (i < velocityIndex - 1) json += ",";
  }
  json += "]";
  return json;
}

float get_average_voltage(int pin, int numOfMeasurements) {
  long totalValue = 0;
  for (int i = 0; i < numOfMeasurements; i++) {
    totalValue += analogRead(pin);
  }
  return ((float)totalValue / numOfMeasurements) * (3.3 / 4095.0);
}

void calibrate_sensor(){
  calibratedVoltages = get_average_voltage(photoPin, 10);
  Serial.print("--- CALIBRATION DONE: ");
  Serial.println(calibratedVoltages);
}

unsigned long calculate_duration(){
  currentMillis = millis();    
  duration_tmp = currentMillis - lastChangeTime;
  return duration_tmp;
}

float calculate_velocity(){
  if(duration == 0) return 0; 
  return circumference/(duration/1000.0);
}


float calc_avg_velocity(){
  float sum = 0;
  if (velocityIndex == 0) return 0.0;
  
  for(int i = 0; i < velocityIndex; i++) {
    sum += velocityArray[i];
  }
  return sum / velocityIndex;
}

float calc_avg_ekin(float avgVel){
  return 0.05 * mass * avgVel * avgVel;
}

void setup() {
  Serial.begin(115200);
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH); 
  pinMode(photoPin, INPUT);
  connect_to_Wifi();
  server_setup();
}

void loop() {
  server.handleClient();

  if(calibration == 1) {
    calibrate_sensor();
    calibration = 0;   
    currentState = 0;
    velocityIndex = 0;
    for(int i=0; i<numberOfMeasurements; i++) {
       velocityArray[i] = 0; 
       durationArray[i] = 0;
    }
  }
  
  float voltage = get_average_voltage(photoPin, 5);
  
  // Open circuit
  if(voltage * onOffAspectRatio > calibratedVoltages){
    lastState = currentState;
    currentState = 1;
  } else {
    lastState = currentState;
    currentState = 0;
  }

  if(!lastState && currentState){
    if (velocityIndex < numberOfMeasurements) {

      if(isEvenReading){
        duration = calculate_duration();
        lastChangeTime = currentMillis;
        isEvenReading = 0;
      }
      else{
        duration += calculate_duration();
        lastChangeTime = currentMillis;
        
        unsigned long prevTime = (velocityIndex == 0) ? 0 : durationArray[velocityIndex-1];
        durationArray[velocityIndex] = prevTime + duration;
        
        velocityArray[velocityIndex] = calculate_velocity();
        Serial.println("New velocity saved");
        velocityIndex++;
        isEvenReading = 1;
      }
      
    } else {
        // Serial.println("Memory Full!"); 
    }
    lastState = currentState;
  }
  
}