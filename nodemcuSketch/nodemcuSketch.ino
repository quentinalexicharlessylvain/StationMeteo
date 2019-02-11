#include <dht.h>

dht DHT;

// pin out of DHT11 module goes to D4 pin on the Nodemcu
#define DHT11_PIN D4

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
  T = (int) DHT.temperature;
  H = (int) DHT.humidity;
  }


void setup()
{
  // setup serial connection with 115200 baud rate
  Serial.begin(115200);
}

void loop()
{
  acquireDHT();
    
  Serial.println(T);
  Serial.println(H);
  delay(1000);
  
}
