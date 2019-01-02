
#include <OneWire.h> 
#include <DallasTemperature.h>

  //Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;
//int resolution = 12;

  // Setup a oneWire instance to communicate with any OneWire devices  
  // (not just Maxim/Dallas temperature ICs) 


void setup() {
 Serial.begin(9600); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
 // Start up the library 
 sensors.begin(); 

 Serial.print("Device 0 Address: ");
 Serial.print(insideThermometer);
  Serial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 9);
 
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC); 
  Serial.println();

}

void loop() {
  
//Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures();
  //Serial.println("DONE"); 
  Serial.print("Temperature is: "); 
 Serial.print(sensors.getTempCByIndex(0)); 
 Serial.print("\n ");
 delay(5000);
}
