#define ENA   16          // Enable/speed motors Right        
#define ENB   14          // Enable/speed motors Left         
#define IN_1  5          // L298N in1 motors Rightx          
#define IN_2  4          // L298N in2 motors Right           
#define IN_3  0           // L298N in3 motors Left            
#define IN_4  2           // L298N in4 motors Left            
#define Lamp  12          // Lamp control pin

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             // String to store app command state.
int speedCar = 900;         // Default speed: 400 - 1023.
int speed_Coeff = 8;         // Default speed coefficient

const char* ssid = "KOMINFO";
const char* pass = "Admin1234";

ESP8266WebServer server(80);

void setup() {
  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);  
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT); 
  pinMode(Lamp, OUTPUT);  // Initialize Lamp pin
  
  Serial.begin(115200);

  // WiFi setup
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  // Start the server
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
}

void goAhead() { 
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goBack() { 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goRight() { 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goAheadRight() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goAheadLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar / speed_Coeff);
}

void goBackRight() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar / speed_Coeff);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goBackLeft() {
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar / speed_Coeff);
}

void stopRobot() {  
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, 0);
}

void lamp(int onOff) {
  if (onOff == 1) {
    digitalWrite(Lamp, HIGH);  // Turn lamp on
  } else {
    digitalWrite(Lamp, LOW);   // Turn lamp off
  }
}

void loop() {
  server.handleClient();
  
  command = server.arg("State");
  
  // Movement and lamp control
  if (command == "F") goAhead();
  else if (command == "B") goBack();
  else if (command == "L") goLeft();
  else if (command == "R") goRight();
  else if (command == "I") goAheadRight();
  else if (command == "G") goAheadLeft();
  else if (command == "J") goBackRight();
  else if (command == "H") goBackLeft();
  
  // Speed adjustment with coefficient
  else if (command == "0") { speedCar = 75; speed_Coeff = 3; }
  else if (command == "1") { speedCar = 115; speed_Coeff = 4; }
  else if (command == "2") { speedCar = 125; speed_Coeff = 4; }
  else if (command == "3") { speedCar = 150; speed_Coeff = 5; }
  else if (command == "4") { speedCar = 220; speed_Coeff = 5; }
  else if (command == "5") { speedCar = 350; speed_Coeff = 6; }
  else if (command == "6") { speedCar = 450; speed_Coeff = 6; }
  else if (command == "7") { speedCar = 520; speed_Coeff = 7; }
  else if (command == "8") { speedCar = 890; speed_Coeff = 7; }
  else if (command == "9") { speedCar = 960; speed_Coeff = 8; }
  else if (command == "q") { speedCar = 1023; speed_Coeff = 9; }
  
  // Stop and lamp control
  else if (command == "S") stopRobot();
  else if (command == "W") lamp(1);  // Turn lamp on
  else if (command == "w") lamp(0);  // Turn lamp off
}

void HTTP_handleRoot(void) {
  if (server.hasArg("State")) {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}