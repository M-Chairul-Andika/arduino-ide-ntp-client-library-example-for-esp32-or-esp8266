#if defined(ESP32) 
#include <WiFi.h>  //if you are using esp32 this function will be executed
#elif defined(ESP8266)
#include <ESP8266WiFi.h> //if you are using esp8266 this function will be executed
#endif


/************************************************************************/
//I use the ntp client library by Fabrice Weinbeg version 3.2.1
#include <NTPClient.h> 
#include <WiFiUdp.h>
WiFiUDP ntpUDP;


/************************************************************************/
NTPClient timeClient(ntpUDP, "id.pool.ntp.org", 25200, 60000);
/*
 * NTPClient timeClient(ntpUDP, "change ntp server, link below", change, 60000);
 * look for the name of the ntp server you want,
 * because I'm in Indonesia, I use id.pool.ntp.org
 * https://www.ntppool.org/en/
 * 
 * don't forget to change the epoch
 * I'm in North Sumatra, Indonesia with UTC +07 = 25200
 * https://www.epochconverter.com/timezones
 * for the last do not change, let 60000.
*/


byte last_second, second_, minute_, hour_, day_, month_;
int year_;

String weekDays[7]= {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};  //adjust to your language
String months[12]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; //adjust to your language


//const char *ssid     = "your wifi name"; //change
//const char *password = "your wifi password"; //change
const char *ssid     = "Beli_paket"; //change
const char *password = "belilahjanganminta"; //change


void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 timeClient.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  int currentYear = ptm->tm_year+1900;
  String cYear = String(currentYear).substring(2,4); //takes 2 characters out of 4 characters

  String hours_minutes_seconds = timeClient.getFormattedTime();
  String hour_minute = hours_minutes_seconds.substring(0,5); //takes 5 characters from the front.
  String mount_with_letters = months[currentMonth-1];
  String day_with_letter = weekDays[timeClient.getDay()];
  

  //Variation
  String combination_date = String(monthDay) + "-" + String(currentMonth) + "-" + String(cYear);
  String day_and_hour = String(day_with_letter)+ " " + String(hours_minutes_seconds);
  String all = String(monthDay)+ "-" + String(currentMonth) + "-" + String(currentYear) + " " + String(hours_minutes_seconds);
  String all2 = String(day_with_letter) + " " + String(monthDay)+ "-" + String(mount_with_letters) + "-" + String(cYear) + " " + String(hours_minutes_seconds);

  
  Serial.print("day with letter : "); 
  Serial.println(day_with_letter);  
  Serial.print("Month : "); 
  Serial.println(mount_with_letters);   
  Serial.print("Year Split: "); 
  Serial.println(cYear);  
  Serial.print("Year : "); 
  Serial.println(currentYear); 
  Serial.print("Time : "); 
  Serial.println(hour_minute); 
  Serial.print("Hour Min Sec: "); 
  Serial.println(hours_minutes_seconds); 
  Serial.print("Date : "); 
  Serial.println(combination_date);

  
  Serial.println(""); 
  Serial.println("======Variation======"); 
  Serial.print("day & hour : "); 
  Serial.println(day_and_hour); 
  Serial.print("date 1: "); 
  Serial.println(all); 
  Serial.print("date 2: "); 
  Serial.println(all2); 

  Serial.println("========================="); 
  Serial.println(""); 
  Serial.println(""); 
  Serial.println(""); 
  
  delay(1000); //delay 1 detik
}
