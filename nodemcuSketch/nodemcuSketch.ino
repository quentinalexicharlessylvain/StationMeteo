// DHT11 sensor
#include <dht.h>

// Sigfox communication
#include <SoftwareSerial.h>
#include <SigFox.h>


dht DHT;

// pin out of DHT11 module goes to D4 pin on the Nodemcu
#define DHT11_PIN D4

// pin for Sigfox module
#define RxNodePin 13
#define TxNodePin 15

// Setup UART Communication with 
SoftwareSerial Sigfox =  SoftwareSerial(RxNodePin, TxNodePin);

// 12 bytes message buffer
uint8_t sigfoxMsg[12];

// variables to store temperature and humidity
int T;
int H;

void acquireDHT(){
  // acquire temperature and humidity from the DHT11 module and cast the data into integer
  // Humidity Range: 20-90% RH
  // Humidity Accuracy: ±5% RH
  // Temperature Range: 0-50 °C
  // Temperature Accuracy: ±2% °C
  int chk = DHT.read11(DHT11_PIN);
  if(chk>=0){
    T = (int) DHT.temperature;
    H = (int) DHT.humidity;
  }
}


void setup()
{
  pinMode(RxNodePin, INPUT);
  pinMode(TxNodePin, OUTPUT);
  // setup serial connection with 115200 baud rate
  Serial.begin(115200);
  Sigfox.begin(9600);

  Serial.println("\nSigfox parameters :");
  Serial.print("Device ID: " + getID()); 
  Serial.print("Device PAC Number: " + getPAC());
}

void loop()
{
  acquireDHT();
    
  Serial.println(T);
  Serial.println(H);
  
  sendMessage(T+"/"+H);
  delay(1000*30);
  
}


void sendMessage(String sigfoxMsg) {
  //Sigfox.print("AT$SF=");
  SigFox.begin();
  SigFox.beginPacket();
  SigFox.print(sigfoxMsg);
  SigFox.endPacket();
  

  Sigfox.print("\r");

}




// Get device ID
String getID () {
  String deviceId = "";
  char sigfoxBuffer;

  // Send AT$I=10 to WISOL to GET ID number
  Sigfox.print("AT$I=10\r");

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

  // Send AT$I=11 to WISOL to GET PAC number
  Sigfox.print("AT$I=11\r");
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
