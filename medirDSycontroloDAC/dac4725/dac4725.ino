#include <Wire.h>
#include <Adafruit_MCP4725.h>

#define voltsIn A0
uint32_t dac_value = 0;
  int adcValueRead = 0 ;
  float voltageRead = 0.0;
  int incomingByte = 0;
  int flag = 0;

Adafruit_MCP4725 dac; // constructor

void setup(void) {
  Serial.begin(9600);
  dac.begin(0x62); // The I2C Address: Run the I2C Scanner if you're not sure  
  Serial.print("introduzca valor DAC:\n");
   delay(500);
  Serial.setTimeout(10000000);  
}

void loop(void) {

   if(incomingByte != '\n' && incomingByte != '\r')
   {     
      if (Serial.available() > 0){
        delay(500);
        incomingByte = Serial.parseInt(); //read int or parseFloat for ..float...
        
          
        Serial.println(incomingByte, DEC);          // otro formato, BIN o HEX

        dac.setVoltage(incomingByte, false);   //, true or false to save value in memmory
      
        adcValueRead = analogRead(voltsIn);
        voltageRead = (adcValueRead * 5.0 )/ 1024.0;
      
        Serial.print("\tArduino ADC Value: ");
        Serial.print(adcValueRead);
      
        Serial.print("\tArduino Voltage: ");      
        Serial.println(voltageRead,3);  

        delay(1000);
        Serial.print("introduzca valor DAC:\n"); 
        delay(500);
      }

   }
     
}
