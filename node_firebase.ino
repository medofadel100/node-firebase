/*
 * receive data from android using UART protocol
 * Send Data To FireBase Realtime Data Base
 * board management > esp8266 > v2.4 
 * library  > FirebaseArduino 
 * FirebaseArduino > src > edit FirebaseHttpClient.h > line 43 static const char kFirebaseFingerprint[] =
 *  new data >>>> "CF:6C:F8:33:A3:FB:42:4A:49:0A:E7:72:24:53:1A:11:A2:C1:34:0D"
 *
 *library  > ArduinoJson > v 5.13.5
 */
String x;

#include<SoftwareSerial.h>
SoftwareSerial SUART( D1, D2); //SRX=Dpin-D2; STX-DPin-D1

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>



// Fire Base Host Auth
#define FIREBASE_HOST "**********"
#define FIREBASE_AUTH "********" //Change line with your WiFi router name and password
// WiFi setting 
#define WIFI_SSID "*************" 
#define WIFI_PASSWORD "************"


void setup() {
  // Open serial communications and wait for port to open:
  
  Serial.begin(9600); //enable Serial Monitor
  SUART.begin(115200); //enable SUART Port
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 pinMode(2, OUTPUT);
 digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
//test For Stat transfer data with FireBase 
 Firebase.setString("RX", "Start");
  
}

void loop() { // run over and over
  
  int n = SUART.available(); //n != 0 means a character has arrived
  if (n != 0)
  {
    //  received data
    String x = SUART.readString();  //read character
  delay(500);
    Serial.println(x);      //show character on Serial Monitor
    //Firebase.setString(head , data);
    Firebase.setString("RX", x);
  }
   

  
  // handle error
  if (Firebase.failed()) {
  Serial.print("setting /number failed:");
  Serial.println(Firebase.error());
  return;
  }
  delay(1000);

//  if (Serial.available()) {
//    //Serial.write(Serial.read());
//    x=Serial.read();
//    //Serial.print(x);
//  }
}
