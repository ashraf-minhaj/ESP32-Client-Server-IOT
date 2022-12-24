/*
 * ESP32 wifi Mother Server for roject: Decentralized Fire Security Alarm
 * via Server-Client relationship.
 * 
 * author: ashraf minhaj
 * mail  : ashraf_minhaj@yahoo.com
*/


#include <WiFi.h>


const char* ssid = "SASIMISI";
const char* password = "ditamna007";

// define light pins
int light1 = 23;
int light2 = 22;


// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);


void setup() {
  Serial.begin(115200);
  delay(10);


  // prepare GPIO2
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  
  digitalWrite(light1, 0);
  digitalWrite(light2, 0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");


  // Start the server
  server.begin();
  Serial.println("Server started");


  // Print the IP address
  Serial.println(WiFi.localIP());
}


void loop() {
  // state vars
  int val1 = 3;
  int val2 = 3;
  
  // Check if a client has connected
  WiFiClient client = server.available();

  // Match the request
  if (client) {
    
    // Wait until the client sends some data
    Serial.println("new client");
    while (!client.available()) {
      delay(1);
      }


  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("/light/1/0") != -1) {
    val1 = 0;
    }
    else if (req.indexOf("/light/1/1") != -1) {
      val1 = 1;
      }
      else if (req.indexOf("/light/2/0") != -1) {
        val2 = 0;
        }
        else if (req.indexOf("/light/2/1") != -1) {
          val2 = 1;
          }
          else {
            Serial.println("invalid request");
            client.stop();
            return;
            }
  }

  if (val1 == 1) {
    digitalWrite(light1, HIGH);
  }
  if (val1 == 0) {
   digitalWrite(light1, LOW);
   delay(100);
  } 
  if (val2 == 1) {
    digitalWrite(light2, HIGH);
  }
  if (val2 == 0) {
    digitalWrite(light2, LOW);
  }

  if (val2 == 3) {
    digitalWrite(light1, HIGH);
    delay(100);
  }
  if (val2 == 3) {
    digitalWrite(light2, HIGH);
    delay(100);
  }
  
}
