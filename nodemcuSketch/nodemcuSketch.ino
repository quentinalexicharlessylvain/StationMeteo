#include <dht.h>              // DHT11 sensor
#include <SoftwareSerial.h>   // Sigfox communication by antena

#include <ESP8266WiFi.h>      // WiFi access point
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// Set the ssid of the setup page
#ifndef APSSID
#define APSSID "WeatherStation"
#endif

const char *ssid = APSSID;
ESP8266WebServer server(80);


dht DHT;

#define DHT11_PIN D4          // pin out of DHT11 module goes to D4 pin on the Nodemcu

#define RxNodePin 13          // pin for Sigfox module
#define TxNodePin 15

#define webButton D3          // webButton to open and close setup page
#define webLED D2             // ON if page available

SoftwareSerial Sigfox =  SoftwareSerial(RxNodePin, TxNodePin);  // Setup UART Communication with 
uint8_t sigfoxMsg[12];        // 12 bytes message buffer

int T;                        // variables to store temperature and humidity
int H;

String IDSigfox;
String PACSigfox; 


void setup(){
  pinMode(RxNodePin, INPUT);
  pinMode(TxNodePin, OUTPUT);

  pinMode(webButton, INPUT);
  pinMode(webLED, OUTPUT);
  
  Serial.begin(115200);
  Sigfox.begin(9600);
  
  Serial.println("\nSigfox parameters :");
  IDSigfox = getID();
  Serial.print("Device ID: " + IDSigfox); 
  PACSigfox = getPAC();
  Serial.print("Device PAC Number: " + PACSigfox);

  Serial.print("The setup page is available at 192.168.4.1 in a web browser");
  
  webSetupPage();
}

void loop(){

  while(digitalRead(webButton)==LOW){
    acquireDHT();

    Serial.print("Temperature: ");
    Serial.println(T);
    Serial.print("Humidity: ");
    Serial.println(H);
  
    msgSigfox(T, H);
  }
  webSetupPage();
}





/* acquire temperature and humidity 
 * from the DHT11 module 
 * and cast the data into integer 
 */
void acquireDHT(){
  /* Humidity Range: 20-90% RH
   * Humidity Accuracy: ±5% RH
   * Temperature Range: 0-50 °C
   * Temperature Accuracy: ±2% °C
   */
  int chk = DHT.read11(DHT11_PIN);
  if(chk>=0){
    T = (int) DHT.temperature;
    H = (int) DHT.humidity;
  }
}


// Send data to Sigfox 
void msgSigfox(int T, int H) {
  String temperature = (String)T;
  String humidity = (String)H;

  if(T<10){
    sigfoxMsg[0] = 0x00;
    sigfoxMsg[1] = temperature[0];
  }
  else{
    sigfoxMsg[0] = uint8_t(temperature[0]);
    sigfoxMsg[1] = uint8_t(temperature[1]);
  }


   if(H<10){
    sigfoxMsg[2] = 0x00;
    sigfoxMsg[3] = humidity[0];
  }
  else{
    sigfoxMsg[2] = uint8_t(humidity[0]);
    sigfoxMsg[3] = uint8_t(humidity[1]);
  }

  sendDataSigfox(sigfoxMsg, 4);
}


String sendDataSigfox(uint8_t sigfoxMsg[], int bufferSize) {
  String status = "";
  char sigfoxBuffer;

  // Send AT$SF=xx to WISOL to send XX (payload data of size 1 to 12 bytes)
  Sigfox.print("AT$SF=");
  for(int i= 0;i<bufferSize;i++){
    if (sigfoxMsg[i]<0x10) {
      Sigfox.print("0");
    }
    Sigfox.print(String(sigfoxMsg[i], HEX));
  }

  Sigfox.print("\r");

  while (!Sigfox.available()){
     delay(10);
  }

  while(Sigfox.available()){
    sigfoxBuffer = (char)Sigfox.read();
    status += sigfoxBuffer;
    delay(10);
  }

  return status;
}



// Get Sigfox informations

// Get device ID
String getID () {
  String deviceId = "";
  char sigfoxBuffer;

  Sigfox.print("AT$I=10\r");    // Send AT$I=10 to WISOL to GET ID number

  while (!Sigfox.available()){
     delay(10);
  }
  
  while(Sigfox.available()){
    sigfoxBuffer = Sigfox.read();
    deviceId += sigfoxBuffer;
    delay(10);
  }
  return deviceId;
}


// Get PAC number
String getPAC (){
  String pacNumber = "";
  char sigfoxBuffer;

  Sigfox.print("AT$I=11\r");    // Send AT$I=11 to WISOL to GET PAC number
  while (!Sigfox.available()){
     delay(10);
  }
  while(Sigfox.available()){
    sigfoxBuffer = Sigfox.read();
    pacNumber += sigfoxBuffer;
    delay(10);
  }
  return pacNumber;
}




// setup page

void handleRoot() {
  // setup page
  String page = "<h1>Welcome on our Weather station setup page !</h1></BR><h4>ID : "+String(IDSigfox)+"</h4></BR><h4>PAC : "+String(PACSigfox)+"</h4>";
  server.send(200, "text/html", page);
}
// Create the access point, show the setup page for 40s and then delete it 
void webSetupPage(){
  WiFi.softAP(ssid);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("setup page started");
  digitalWrite(webLED, HIGH);
  delay(1000*5);
  
  while(digitalRead(webButton) == LOW){
    server.handleClient();
    delay(100);
  }
  
  // Close the access point
  WiFi.softAPdisconnect (true);
  Serial.println("setup page closed");
  digitalWrite(webLED, LOW);
}
