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

SoftwareSerial Sigfox =  SoftwareSerial(RxNodePin, TxNodePin);  // Setup UART Communication with 
uint8_t sigfoxMsg[12];        // 12 bytes message buffer

int T;                        // variables to store temperature and humidity
int H;

String IDSigfox;
String PACSigfox; 


void setup(){
  pinMode(RxNodePin, INPUT);
  pinMode(TxNodePin, OUTPUT);
  
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
  acquireDHT();
    
  Serial.println(T);
  Serial.println(H);
  
  sendDataSigfox(T, H);
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
void sendDataSigfox(int T, int H) {
  //Sigfox.print("AT$SF=");
  Sigfox.print(T + "/" + H);
  Sigfox.print("\r");
  delay(1000*30);     // delay to be in the low
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
  
  for(int i=0;i<=20;i++){
    server.handleClient();
    delay(1000*2);
  }
  // Close the access point
  WiFi.softAPdisconnect (true);
}
