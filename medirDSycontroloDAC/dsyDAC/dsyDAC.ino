#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>

#define ONE_WIRE_BUS 2    //conectar DS a pin 2
#define voltsIn A0

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress tempSIPM = {0x28, 0xAF, 0x33, 0x84, 0x03, 0x00, 0x00, 0x9F};  //si no la conozco usar programa para ver direccion

Adafruit_MCP4725 dac; // constructor
 
int analogPin = A0;     // potentiometer wiper (middle terminal) connected to analog pin 3
float tempC;
//float incomingByte = 0.0;
int adcValueRead = 0 ;
float voltageRead = 0.0;

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  sensors.setResolution(tempSIPM, 12);
  dac.begin(0x62); // The I2C Address:
  Serial.setTimeout(10000000);   //para evitar que aparezc el extra zero
 }

void printTemperature(DeviceAddress deviceAddress)
{
  tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    Serial.print(" Temperatura actual: ");
    Serial.print(tempC);
    Serial.print("\n\r");
   }
}

void envioValorDAC(float incomingByte)
{
   int bytentrada = (int) incomingByte;
   Serial.print("byte entrada:");
   Serial.print(bytentrada);
   Serial.print("\n");
   dac.setVoltage(bytentrada, false); 
   adcValueRead = analogRead(voltsIn);
   voltageRead = (adcValueRead * 5.0 )/ 1024.0;
   Serial.print("\tArduino ADC Value: ");
   Serial.print(adcValueRead);
     
   Serial.print("\tArduino Voltage: ");      
   Serial.println(voltageRead,3);  

}


void loop(void)
{
  sensors.requestTemperatures();
  printTemperature(tempSIPM);
  envioValorDAC(tempC);
  
  delay(2000);
  
 
} 
