#include <Wire.h>
#include "RTClib.h"
#include "LedControl.h"
LedControl lc = LedControl(7,6,5,1);
 
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

int jam, menit, detik;
int satuanjam, satuanmenit, puluhanjam, puluhanmenit, puluhandetik, satuandetik;
 
void setup() {
 
Serial.begin(9600);
   if (! rtc.begin()) {
    Serial.println("RTC tidak ditemukan");
    while (1);
  }
  
  if (! rtc.isrunning()) {
    Serial.println("RTC tidak jalan!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
   
  // Initialize the MAX7219 device 
  lc.shutdown(0,false); // Enable display 
  lc.setIntensity(0,8); // Set brightness level (0 is min, 15 is max) 
  lc.clearDisplay(0); // Clear display register 
  } 
  void loop() 
  { 
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
  jam = now.hour();
  menit = now.minute();
  detik = now.second();
  
  satuanjam = jam % 10;
  puluhanjam = jam / 10;
      
  satuanmenit = menit % 10;
  puluhanmenit = menit / 10;
      
  satuandetik = detik % 10;
  puluhandetik = detik / 10;
 
    lc.setDigit(0,3,puluhanjam,false); 
    lc.setDigit(0,2,satuanjam,true); 
    lc.setDigit(0,1,puluhanmenit,false);  
    lc.setDigit(0,0,satuanmenit,false); 
    delay(1000);
} 
