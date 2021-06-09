#include <LiquidCrystal.h>
#include <Servo.h>

#define buzzer 6
#define relay 5
#define acclerometer1 A4
#define acclerometer2 A5

int inclination1, inclination2;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

Servo servo;
int pos = 0;

void setup()
{
    pinMode(buzzer, OUTPUT);
    pinMode(relay, OUTPUT);
    
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, HIGH);

    lcd.begin(16, 2);
    servo.attach(7);
    servo.write(pos);
    
    Serial.begin(9600);
}

void loop()
{
    inclination1 = analogRead(acclerometer1);
    inclination2 = analogRead(acclerometer2);

    if(abs(inclination1 - inclination2) > 200)
    {
        digitalWrite(buzzer, HIGH);
        digitalWrite(relay, LOW);

        lcd.clear();
        delay(300);
        lcd.setCursor(0, 0);
        lcd.print("Earquake alert");
        
        door();
        message();
    }
    else
    {
        digitalWrite(buzzer,LOW);
        digitalWrite(relay, HIGH);

        lcd.setCursor(0, 0);
        lcd.print("Have a great day");
    }
}

void door() {
  if(pos < 180) {
    for(pos = 0; pos <= 180; pos++){
      servo.write(pos);
    }
  }
}

void message()
{
    Serial.print("EARTHQUAKE ALERT!");
    Serial.write(0xd);
    Serial.print("TAKE SAFETY MEASURES!");
    Serial.write(0xd);
    Serial.write(0xd);
    delay(1000);
}
