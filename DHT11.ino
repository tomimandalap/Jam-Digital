#include "DHT.h"
#include "LedControl.h"
//(DIN,SCK,LOAD)
LedControl lc = LedControl(7,6,5,1);

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();

  // Initialize the MAX7219 device 
  lc.shutdown(0,false); // Enable display 
  lc.setIntensity(0,8); // Set brightness level (0 is min, 15 is max) 
  lc.clearDisplay(0); // Clear display register
  
}

void loop() 
{
  // Wait a few seconds between measurements.
  delay(1000);

  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  Kelvin= t+273;
  
  Serial.print("Temperature: ");
  Serial.print(Kelvin);
  Serial.print(" K ");

  int suhu = kelvin;
  int satuan = int (suhu%10);
  int puluhan = int (suhu/10)%10;
  int ratusan = int suhu/100)%10;
  int ribuan = int (suhu/1000)%10;
  
    //lc.setDigit(0,3,ribuan,false); 
    lc.setDigit(0,2,ratusan,true); 
    lc.setDigit(0,1,puluhan,false);  
    lc.setDigit(0,0,satuan,false); 
    
}
