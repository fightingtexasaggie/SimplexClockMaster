#include <TimeLib.h>
#include <TimeAlarms.h>
#include <TinyGPS++.h>

#define SerialGPS Serial

int relayPin = 6;
int syncLed = 13;

TinyGPSPlus gps;

tmElements_t tm;

// Offset hours from gps time (UTC)
const int offset = -6;   

void setup() {
  
  SerialGPS.begin(9600);
  delay(5000);

  pinMode(relayPin, OUTPUT);
  pinMode(syncLed, OUTPUT);
  
  digitalWrite(relayPin, LOW);
  digitalWrite(syncLed, LOW); 
    
  setSyncProvider(syncClock); 
  setSyncInterval(900); 
 
 // Remember to set number of alarms to at least 24 in TimeAlarms.h before building.
 // The default is 6, and will cause silent failures if not set high enough.
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
  Alarm.delay(1000); // check every second for possible event.
}

time_t syncClock() {
  unsigned long age;
  int Year;
  byte Month, Day, Hour, Minute, Second;
  
  for (int trial = 0; trial < 25; trial++) {
    // For one second we parse GPS data and report some key values
    for (unsigned long start = millis(); millis() - start < 1000;) {
      while (SerialGPS.available()) {
        int c = SerialGPS.read();
        if (gps.encode(c)) {
          tm.Second = gps.time.second();
          tm.Minute = gps.time.minute();
          tm.Hour = gps.time.hour();
          tm.Day = gps.date.day();
          tm.Month = gps.date.month();
          tm.Year = gps.date.year()+30;
          digitalWrite(syncLed, HIGH);
          return makeTime(tm);
        }
      }
    }
  }  
  digitalWrite(syncLed, LOW);
  return 0;
}

void ShortAlarm() {
  if (timeStatus() == 2) {
    digitalWrite(relayPin, HIGH);
    Alarm.delay(8000);
    digitalWrite(relayPin, LOW); 
  }
}

void LongAlarm() {
  if (timeStatus() == 2) {
    digitalWrite(relayPin, HIGH);
    Alarm.delay(14000);
    digitalWrite(relayPin, LOW); 
  }
}

