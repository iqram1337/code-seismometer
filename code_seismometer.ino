#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,2,16);
int logic_state = 0;
int led_kuning = 13;
int v_sensor = 7;

boolean ls_status;
boolean v_sensor_status;

float x,y,z;

void setup()
{
  pinMode(logic_state, INPUT);
  pinMode(led_kuning, OUTPUT);
  pinMode(v_sensor, INPUT);

  lcd.init(); 
  lcd.backlight();
  Serial.begin(9600);
  lcd.setCursor(2, 0);
  lcd.print("[SEISMOMETER]");

  lcd.setCursor(3, 1);
  lcd.print("[SEDERHANA]");
  delay(300);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Loading...");
  delay(300);

}

void loop()
{
  x = ((analogRead(A2)*2.0)/1024.0)-1; 
  y = ((analogRead(A1)*2.0)/1024.0)-1; 
  z = ((analogRead(A0)*2.0)/1024.0)-1;
  
  v_sensor_status = digitalRead(v_sensor);
  ls_status = digitalRead(logic_state);
  
  if (ls_status == 1)
  {
    digitalWrite(led_kuning, HIGH);
    lcd.clear();
    
    lcd.setCursor(0, 1);
    lcd.print(x);
    lcd.setCursor(0,0);
    lcd.print("x");
    
    lcd.setCursor(6, 1);
    lcd.print(y);
    lcd.setCursor(6,0);
    lcd.print("y");
    
    lcd.setCursor(12, 1);
    lcd.print(z);
    lcd.setCursor(12,0);
    lcd.print("z");
    delay(100);
  }
  else if (ls_status == 0)
  {
  digitalWrite(led_kuning, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kondisi");
  lcd.setCursor(0, 1);
  lcd.print("[AMAN]");
  delay(300);
  }
}
