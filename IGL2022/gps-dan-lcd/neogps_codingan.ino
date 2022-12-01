#include <TinyGPS++.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

int chipselect = 10;
int count = 1; 
String namafile = "file.txt";
File file;

LiquidCrystal_I2C lcd(0x27, 20, 4);

TinyGPSPlus gps;
void getgps(TinyGPSPlus &gps);

void setup() {
  pinMode(chipselect, OUTPUT);
  Serial.begin(9600);
  lcd.begin(20,4);
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("Inisialisasi GPS...");
  delay(5000);
  lcd.clear();
  
}

void getgps(TinyGPSPlus &gps)
{
  if (gps.location.isValid() and gps.date.isValid() and gps.time.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);

    lcd.setCursor(0,0);
    lcd.print("Iqram 12320021");
    lcd.setCursor(0,1);
    lcd.print(gps.date.day());
    lcd.print("/");
    lcd.print(gps.date.month());
    lcd.print("/");
    lcd.print(gps.date.year());
    lcd.print("--");
    lcd.print(gps.time.hour()+7);
    lcd.print(":");
    lcd.print(gps.time.minute());
    lcd.print(":");
    lcd.print(gps.time.second());

    lcd.setCursor(0,2);
    lcd.print("lat: ");
    lcd.print(gps.location.lat(), 6);
    lcd.setCursor(0,3);
    lcd.print("long: ");
    lcd.print(gps.location.lng(), 6);
    
  file = SD.open(namafile, FILE_WRITE);
  if (file)
   {
    file.println("");
    file.print(count);
    file.print(gps.location.lat());
    file.print("|");
    file.print(gps.location.lat()); 
    file.close();

    Serial.println(" | Data Tersimpan"); 
    if(count>19) count=0;
   }
  }
  else
  {
    Serial.println("Location: Not Available");
  }
}

void loop() {
  byte a;
  if (Serial.available() > 0)
  {
    a = Serial.read();
    if (gps.encode(a))
    {
      getgps(gps);
    }
  }
}
