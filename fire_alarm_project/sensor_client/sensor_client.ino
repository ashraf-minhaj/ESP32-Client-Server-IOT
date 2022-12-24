#include <WiFi.h>
#include <HTTPClient.h>

String server_ip = "http://192.168.0.109";

const char* ssid = "";
const char* password =  "";

int buttonPin     = 23;     
int sensorPin     = 22;

int buttonState   = 0; 
int sensorState   = 0;


void send_req(String stat){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;   
  
   http.begin(server_ip + "/light/2/" + stat);  //Specify destination for HTTP request
  
   int httpResponseCode = http.GET();   //Send the actual GET request
  
   if(httpResponseCode>0){
    String response = http.getString();                       //Get the response to the request
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  
   }
   else{
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
   }
   http.end();  //Free resources
   }
   else{
    Serial.println("Error in WiFi connection");   
    }
}


void setup() {
  
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
  
}
  
void loop() {
   buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if ((digitalRead(buttonPin) == HIGH) || (digitalRead(sensorPin) == LOW)) {
    Serial.println("We enter here");
    // turn LED on:
    send_req("1");
  } 
//if (digitalRead(buttonPin) == HIGH) {
//    Serial.println("We enter here");
//    // turn LED on:
//    send_req("1");
//  }
//  else {
//    send_req("0");
//  }
}
