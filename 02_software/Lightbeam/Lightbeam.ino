//----------------------
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Sodaq_DS3231.h>


const int chipSelect = 4;
File datei;

int Empfaenger = A0;
int LEDpin = 8;
int WARNpin = 9;
int Wert;

void setup() {
  pinMode(LEDpin, OUTPUT);
  pinMode(WARNpin, OUTPUT);
  pinMode(Empfaenger, INPUT);

  SD.begin(chipSelect);
  rtc.begin();
  //DateTime dt(__DATE__, __TIME__); // First enable this line, upload the sketch, then comment it out and upload it again
  //rtc.setDateTime(dt); // First enable this line, upload the sketch, then comment it out and upload it again
  pinMode(SS, OUTPUT);

  datei = SD.open("batbox.log", O_CREAT | O_APPEND | O_WRITE);

{ if (!datei) {

      digitalWrite(WARNpin, HIGH);
      delay(100);
      digitalWrite(WARNpin, LOW);
      delay(500);
      digitalWrite(WARNpin, HIGH);
      delay(100);
      digitalWrite(WARNpin, LOW);
      delay(500);
      digitalWrite(WARNpin, HIGH);
      delay(100);
      digitalWrite(WARNpin, LOW);
      delay(500);
      digitalWrite(WARNpin, HIGH);
      delay(100);
      digitalWrite(WARNpin, LOW);
      delay(500);
      digitalWrite(WARNpin, HIGH);
      delay(100);
      digitalWrite(WARNpin, LOW);
      delay(500);
      digitalWrite(WARNpin, HIGH);
      delay(100);
      digitalWrite(WARNpin, LOW);
      delay(500);
      digitalWrite(WARNpin, HIGH);
      delay(100);
      digitalWrite(WARNpin, LOW);
      delay(500);
      digitalWrite(WARNpin, HIGH);
      delay(100);
      digitalWrite(WARNpin, LOW);


      delay(1000);
    }
    else {

      digitalWrite(LEDpin, HIGH);
      delay(500);
      digitalWrite(LEDpin, LOW);
      delay(500);
      digitalWrite(LEDpin, HIGH);
      delay(500);
      digitalWrite(LEDpin, LOW);
      delay(500);
      digitalWrite(LEDpin, HIGH);
      delay(500);
      digitalWrite(LEDpin, LOW);
      delay(500);
      digitalWrite(LEDpin, HIGH);
      delay(500);
      digitalWrite(LEDpin, LOW);

      delay(1000);
    }
  }

  datei.close();


  datei = SD.open("batbox.log", O_CREAT | O_APPEND | O_WRITE);
  datei.println("Date,Time,Light_Beam,Others");
  uhrzeit_SD();
  datei.print(",,");
  datei.println("started");
  datei.close();

}


void uhrzeit_SD()
{
  DateTime now = rtc.now();

  if (now.date() < 10) datei.print("0");
  datei.print(now.date());
  datei.print('.');
  if (now.month() < 10) datei.print("0");
  datei.print(now.month());
  datei.print('.');
  datei.print(now.year());
  datei.print(',');
  if (now.hour() < 10) datei.print("0");
  datei.print(now.hour());
  datei.print(":");
  if (now.minute() < 10) datei.print("0");
  datei.print(now.minute());
  datei.print(":");
  if (now.second() < 10) datei.print("0");
  datei.print(now.second());
}


void loop() {
  Wert = analogRead(Empfaenger);
  if (Wert > 60)
  {
    digitalWrite(LEDpin, HIGH);
    analogWrite(WARNpin, 10);

    datei = SD.open("batbox.log", O_CREAT | O_APPEND | O_WRITE);
    uhrzeit_SD();
    datei.print(",");
    datei.print("interruption");
    datei.println(",");

    datei.close();
  }
  else
  {
    digitalWrite(LEDpin, LOW);
    digitalWrite(WARNpin, LOW);
  }
}
