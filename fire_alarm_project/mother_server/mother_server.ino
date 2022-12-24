/*
 * ESP32 wifi Server to control multiple loads controlled by other esp32s
 * via Server-Client relationship.
 * 
 * ip/light/1/0 - light 1 off
 * ip/light/1/1- light 1 on
 * 
 * ip/light/2/0 - light 2 off
 * ip/light/2/1 - light 2 on
 * 
 * author: ashraf minhaj
 * mail  : ashraf_minhaj@yahoo.com
*/


#include <WiFi.h>


const char* ssid = "";
const char* password = "";

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
  int val1 = 0;
  int val2 = 0;
  
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


  // Set GPIO according to the requests
//  digitalWrite(light1, val1);
//  digitalWrite(light2, val2);

  if (val1 == 1) {
    digitalWrite(light1, HIGH);
  }
  if (val1 != 1) {
   digitalWrite(light1, LOW);
  } 
  if (val2 == 1) {
    digitalWrite(light2, HIGH);
  }
  if (val2 != 1) {
    digitalWrite(light2, LOW);
  }

  Serial.println("Client disonnected");


  // The client will actually be disconnected
  // when the function returns and 'client' object is detroyed
}
