#include <Firebase.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
//#include <FirebaseESP8266.h>

//#include <SoftwareSerial>
//#include <ESP8266WiFi.h>

// Set these to run example.
#define FIREBASE_HOST "sustainable-farm-ad936-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "jTPdp3E8r7MUb56UFQidhYzaLhXPWrkNqMePjoYZ"
#define WIFI_SSID "KLEOS-20002992"
#define WIFI_PASSWORD "12212992"

void setup() {
  Serial.begin(115200);

  

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
//  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.setString("temp","4");

}

String values,sensor_data;


void loop() {

  Firebase.setString("hh", "dgfth");

 bool Sr =false;
 
  while(Serial.available()){
    
        //get sensor data from serial put in sensor_data
        sensor_data=Serial.readString(); 
        Sr=true;    
        
    }
  
delay(1000);

  if(Sr==true){  
    
  values=sensor_data;
  
  //get comma indexes from values variable
  int fristCommaIndex = values.indexOf(',');
  int secondCommaIndex = values.indexOf(',', fristCommaIndex+1);
  int thirdCommaIndex = values.indexOf(',', secondCommaIndex + 1);
  int fourthCommaIndex = values.indexOf(',', thirdCommaIndex+1);
  int fifthCommaIndex = values.indexOf(',', fifthCommaIndex+1);
//  
//  //get sensors data from values variable by  spliting by commas and put in to variables  
  String temperature_value = values.substring(0, fristCommaIndex);
  String humidity_value = values.substring(fristCommaIndex+1, secondCommaIndex);
  String water_value = values.substring(secondCommaIndex, thirdCommaIndex);
  String soil_value = values.substring(thirdCommaIndex, fourthCommaIndex);
  String light_value = values.substring(fourthCommaIndex + 1);
//
  Firebase.setString("temp","4");
   delay(10);
  Firebase.setString("humidity",humidity_value);
   delay(10);
  Firebase.setString("water",water_value);
  delay(10);
  Firebase.setString("moisture", soil_value);
  delay(10);
  Firebase.setString("Light", light_value);
  
//
  delay(10);
 //Firebase.setString("isaac", "working");
    
  //store previous sensors data as string in firebase
  
//  Firebase.pushString("previous_ultrasonic_value",ultrasonic_value);
//   delay(10);
//  Firebase.pushString("previous_IR_sensor1_value",IR_sensor1_value);
//   delay(10);
//  Firebase.pushString("previous_IR_sensor2_value",IR_sensor2_value);
  
  
  delay(1000);
  
  if (Firebase.failed()) {  
      Serial.println(Firebase.error());
  }

// Serial.println("Hello from ESP");
  
}
}
