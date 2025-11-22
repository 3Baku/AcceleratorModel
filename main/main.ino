/*
XIAO C3 reading of time between laser-photoresistor key opening. 
getAverageVoltage - function to average a number of measurements for accurate resault
setup - function to turn on the laser and photoresistors management

*/
#include <WiFi.h>
#include "wifipass.h"
#include <WebServer.h>
#include "webpage.h"
WebServer server(80);

const short numberOfMeasurements = 100;
const float onOffAspectRatio = 0.5; //how much of calibrated V is considered open circuit
const float radius = 5; //in cm
const float mass = 1; //in grams
const float circumference = 2*radius*3.1415;
const int laserPin = D9; // IO19
const int photoPin = D2; // IO2

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
unsigned long durationArray[numberOfMeasurements] = {0.0};
float avgVelocity = 0.0;

String get_array_string() {
  String json = "[";
  
  for (int i = 0; i < numberOfMeasurements; i++) {
    json += String(velocityArray[i]);
    if (i < numberOfMeasurements-1) 
        json += ",";
  }
  
  json += "]";
  return json; // Returns: "[12.1,10.5,0.0,...]"
}

float get_average_voltage(int pin, int numOfMeasurements) {
  long totalValue = 0;
  for (int i = 0; i < numOfMeasurements; i++) {
    totalValue += analogRead(pin);
  }
  return ((float)totalValue / numOfMeasurements) * (3.3 / 4095.0);
}


void calibrate_sensor(){
  calibratedVoltages =  get_average_voltage(photoPin, 10);
  Serial.print("--- CALIBRATION DONE, Baseline: ");
  Serial.println(calibratedVoltages);
}

unsigned long calculate_duration(){
  currentMillis = millis();    
  duration_tmp = currentMillis - lastChangeTime;
  Serial.print("Time ON: ");
  Serial.print(duration_tmp);
  Serial.println(" ms");
  return duration_tmp;
}

float calculate_velocity(){
  return circumference/(duration/1000.0);
}
float calc_avg_velocity(){
  float avgVelocity = 0;
  static unsigned short i = 0;
  while((i < numberOfMeasurements) & ((velocityArray[i] != 0.0) & (velocityArray[i+1] != 0.0))) {
    avgVelocity += velocityArray[i];
    i++;
  }
  return avgVelocity/i;
}
float calc_avg_ekin(avgVelocity){
  return avgVelocity*avgVelocity*mass / 2;
}


void setup() {
  Serial.begin(115200);
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH); // Laser ON for calibration
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

  }
  
  float voltage = get_average_voltage(photoPin, 5);
  
  //opened circuit
  if(voltage * onOffAspectRatio> calibratedVoltages){
    lastState = currentState; currentState = 1;}
  else{
    lastState = currentState;currentState = 0;}
 //   Serial.println("my state is");
  //  Serial.println(voltage);
   // Serial.println("Being % of calibrated");
   // Serial.println(calibratedVoltages/voltage);

  if(!lastState & currentState){
    if (velocityIndex < numberOfMeasurements) {


      if(isEvenReading){
        //velocity = calculate_velocity();
        duration = calculate_duration();
        lastChangeTime = currentMillis;
        isEvenReading = 0;
      }
      else{
        duration += calculate_duration();
        lastChangeTime = currentMillis;
        durationArray[velocityIndex] = (velocityIndex == 0) ? duration : (durationArray[velocityIndex-1] + duration);
        velocityArray[velocityIndex] = calculate_velocity();
        Serial.println("A new velocity has been saved");
        velocityIndex++;
        isEvenReading = 1;
      }
      
    } else {
        Serial.println("Memory Full!"); velocityIndex = 0;
    }
    lastState = currentState;
  //  currentState = 0;
  }


  delay(1); 
}