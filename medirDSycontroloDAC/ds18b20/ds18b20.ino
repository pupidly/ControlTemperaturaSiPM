#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// Assign the unique addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

DeviceAddress tempSIPM = {0x28, 0xAF, 0x33, 0x84, 0x03, 0x00, 0x00, 0x9F};
 
//DeviceAddress outsideThermometer = { 0x28, 0x6B, 0xDF, 0xDF, 0x02, 0x00, 0x00, 0xC0 };
//DeviceAddress dogHouseThermometer = { 0x28, 0x59, 0xBE, 0xDF, 0x02, 0x00, 0x00, 0x9F };

int analogPin = A0;     // potentiometer wiper (middle terminal) connected to analog pin 3
                       // outside leads to ground and +5V
int val = 0;           // variable to store the value read


void setup(void)
{
  // start serial port
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  // set the resolution to 12 bit 
  sensors.setResolution(tempSIPM, 12);
  
}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    Serial.print("C: ");
    Serial.print(tempC);
    Serial.print(" F: ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
  }
}

void loop(void)
{
  delay(2000);
  Serial.print("Getting temperatures...\n\r");
  sensors.requestTemperatures();
 
  Serial.print("La temperatura es: ");
  printTemperature(tempSIPM);
  Serial.print("\n\r");
  val = analogRead(analogPin); 
  float voltage= val * (5.0 / 1023.0);     // ADC de 10 bits, maximo 5V
  Serial.println(val);
  Serial.print("\n\r");
  
  Serial.println(voltage); 
  Serial.print("\n\r");
  
  //Serial.print("Outside temperature is: ");
  //printTemperature(outsideThermometer);
  //Serial.print("\n\r");
  //Serial.print("Dog House temperature is: ");
  //printTemperature(dogHouseThermometer);
  //Serial.print("\n\r\n\r");
} 
