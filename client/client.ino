#include <WiFi.h>
#include <HTTPClient.h>
  
const char* ssid = "wifi name";
const char* password =  "password";

server_ip = "http://192.168.."
  
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
  
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;   
  
   http.begin(server_ip.concat("/light/1/1"));  //Specify destination for HTTP request
  
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
  
  delay(10000);  //Send a request every 10 seconds
  
}
