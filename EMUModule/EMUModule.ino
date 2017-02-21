#include <UIPEthernet.h>
#include <Modbus.h>
#include <ModbusIP.h>

//Modbus Registers Offsets (0-9999)

const int VT1 = 4009;
const int VT2 = 4010;
const int VT3 = 4011;
const int CT1 = 4012;
const int CT2 = 4013;
const int CT3 = 4014;

//ModbusIP object
ModbusIP mb;

int getVPP(int analogpin)
{
  float result;

  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here

  uint32_t start_time = millis();
  while ((millis() - start_time) < 20) //sample for 1 Sec
  {
    readValue = analogRead(analogpin);
    // see if you have a new maxValue
    if (readValue > maxValue)
    {
      /*record the maximum sensor value*/
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      /*record the maximum sensor value*/
      minValue = readValue;
    }
  }

  // Subtract min from max
  result = (maxValue - minValue);

  return result;
}

void setup() {

//  analogReference(INTERNAL);
  // The media access control (ethernet hardware) address for the shield
  byte mac[] = { 0xB4, 0x68, 0xA8, 0x43, 0x35, 0x54 };
  //  byte ip[] = { 192, 168, 137, 10 };

  //Config Modbus IP
  mb.config(mac);

  // Add analog registers - Use addIreg() for analog Inputs
  mb.addIreg(CT1);
  mb.addIreg(CT2);
  mb.addIreg(CT3);

  mb.addIreg(VT1);
  mb.addIreg(VT2);
  mb.addIreg(VT3);
  
}

int Voltage = 0;
int Current = 0;
int VRMS = 0;
int AmpsRMS = 0;

void loop() {
  //  Ethernet.maintain();
  //Call once inside loop() - all magic here
  mb.task();

  Current = getVPP(A0);
  AmpsRMS = (Current) /2 * 0.707;
  mb.Ireg(CT1, AmpsRMS);

//  mb.task();

  Current = getVPP(A1);
  AmpsRMS = (Current) /2 * 0.707;
  mb.Ireg(CT2, AmpsRMS);

//  mb.task();

  Current = getVPP(A2);
  AmpsRMS = (Current) /2 * 0.707;
  mb.Ireg(CT3, AmpsRMS);

//  mb.task();

  Voltage = getVPP(A3);
  VRMS = (Voltage) * 0.707;
  mb.Ireg(VT1, VRMS);

//  mb.task();

  Voltage = getVPP(A4);
  VRMS = (Voltage) * 0.707;
  mb.Ireg(VT2, VRMS);

//  mb.task();

  Voltage = getVPP(A5);
  VRMS = (Voltage) * 0.707;
  mb.Ireg(VT3, VRMS);
}
