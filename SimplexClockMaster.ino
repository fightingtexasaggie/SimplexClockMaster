#include <TimeLib.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <TinyGPS.h>

int relayPin = 6;
int syncLed = 13;

TinyGPS gps;

tmElements_t tm;
void setup() {

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor

  pinMode(relayPin, OUTPUT);
  pinMode(syncLed, OUTPUT);
  
  digitalWrite(relayPin, LOW);
  digitalWrite(syncLed, LOW); 
    
  setSyncProvider(syncClock); 
  setSyncInterval(900); 
 
  Alarm.alarmRepeat(0 ,57, 54, ShortAlarm);
  Alarm.alarmRepeat(1 ,57, 54, ShortAlarm);
  Alarm.alarmRepeat(2, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(3, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(4, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(5, 57, 54, LongAlarm);
  Alarm.alarmRepeat(6, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(7, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(8, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(9, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(10, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(11, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(12, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(13, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(14, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(15, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(16, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(17, 57, 54, LongAlarm);
  Alarm.alarmRepeat(18, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(19, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(20, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(21, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(22, 57, 54, ShortAlarm);
  Alarm.alarmRepeat(23, 57, 54, ShortAlarm);
}

void loop() {
  digitalClockDisplay();
  Alarm.delay(1000); // check every second for possible event.
}

time_t syncClock() {
  if (RTC.read(tm)) {
    digitalWrite(syncLed, HIGH);
    Serial.println("Good Sync!");
    return makeTime(tm);
  } else {
    digitalWrite(syncLed, LOW);
    return 0;
  }
}

void ShortAlarm() {
  Serial.println("Relay On:");
  digitalClockDisplay();
  digitalWrite(relayPin, HIGH);
  Alarm.delay(8000);
  Serial.println("Relay Off\n");
  digitalWrite(relayPin, LOW); 
  digitalClockDisplay();
}

void LongAlarm() {
  Serial.println("Relay On:");
  digitalClockDisplay();
  digitalWrite(relayPin, HIGH);
  Alarm.delay(14000);
  Serial.println("Relay Off\n");
  digitalWrite(relayPin, LOW); 
  digitalClockDisplay();
}
void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(timeStatus());
  Serial.print(' ');
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

