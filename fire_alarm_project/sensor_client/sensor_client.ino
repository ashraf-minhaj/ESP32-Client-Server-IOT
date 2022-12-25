#include <WiFi.h>
#include <HTTPClient.h>

String server_ip = "http://192.168.0.100";

const char* ssid = "";
const char* password =  "";

int buttonPin     = 23;     
int sensorPin     = 22;
int ledPin        = 21;

int ledState      = LOW;
long interval     = 900;                 // interval at which to blink (milliseconds)

unsigned long previousMillis = 0;        // will store last time LED was updated


void send_req(String stat){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;   
  
   http.begin(server_ip + "/light/1/" + stat);  //Specify destination for HTTP request
  
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

void blink() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    Serial.println(ledState);
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    }
}

void setup() {
  pinMode(ledPin, OUTPUT);
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
//   buttonState = digitalRead(buttonPin);
//  Serial.println(buttonState);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if ((digitalRead(buttonPin) == HIGH) || (digitalRead(sensorPin) == LOW)) {
    Serial.println("GAS Leaked/Fire");
    blink();
    // turn LED on:
    send_req("1");
  } 
  else {
    send_req("0");
    digitalWrite(ledPin, LOW);
  }
  delay(10);
}
