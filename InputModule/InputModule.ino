#include <UIPEthernet.h>
#include <Modbus.h>
#include <ModbusIP.h>
#include <avr/wdt.h>

const int PINMUX1 = 7;
const int PINMUX2 = 6;
const int PINMUX3 = 5;

//Modbus Registers Offsets (0-9999)
const int DI1 = 4001;
const int DI2 = 4002;
const int DI3 = 4003;
const int DI4 = 4004;

const int DIPIN = 8;

const int PT1 = 4009;
const int PT2 = 4010;
const int PT3 = 4011;
const int PT4 = 4012;
const int PT5 = 4013;
const int PT6 = 4014;
const int PT7 = 4015;
const int PT8 = 4016;
const int PT9 = 4017;
const int PT10 = 4018;

const int CurrentSensor1 = 4019;
const int CurrentSensor2 = 4020;
const int CurrentSensor3 = 4021;

//ModbusIP object
ModbusIP mb;

void setup() {

  wdt_enable(WDTO_2S);
  analogReference(EXTERNAL);
  // The media access control (ethernet hardware) address for the shield
  byte mac[] = { 0xB4, 0x68, 0xA8, 0x7B, 0x6F, 0x27};
  //  byte ip[] = { 192, 168, 137, 10 };

  //Config Modbus IP
  mb.config(mac);

  //Set MUX pins output
  pinMode(PINMUX1, OUTPUT);
  pinMode(PINMUX2, OUTPUT);
  pinMode(PINMUX3, OUTPUT);

  //Set DI pin input
  pinMode(DIPIN, INPUT);

  // Add Digital Input registers - Use addIsts() for digital inputs
  mb.addIsts(DI1, false);
  mb.addIsts(DI2, false);
  mb.addIsts(DI3, false);
  mb.addIsts(DI4, false);
  //  mb.addIsts(DI5,false);
  //  mb.addIsts(DI6,false);

  // Add analog registers - Use addIreg() for analog Inputs
  mb.addIreg(PT1);
  mb.addIreg(PT2);
  mb.addIreg(PT3);
  mb.addIreg(PT4);
  mb.addIreg(PT5);
  mb.addIreg(PT6);
  mb.addIreg(PT7);
  mb.addIreg(PT8);
  mb.addIreg(PT9);
  mb.addIreg(PT10);

  mb.addIreg(CurrentSensor1);
  mb.addIreg(CurrentSensor2);
  mb.addIreg(CurrentSensor3);


}
void loop() {
  wdt_reset();
  //Ethernet.maintain();
  //Call once inside loop() - all magic here
  mb.task();

  //Attach digital input registers to pins
  digitalWrite(PINMUX1, LOW);
  digitalWrite(PINMUX2, LOW);
  digitalWrite(PINMUX3, LOW);

  mb.task();

  mb.Ists(DI1, digitalRead(DIPIN));
  mb.Ireg(PT2, analogRead(A0));

  digitalWrite(PINMUX1, HIGH);
  digitalWrite(PINMUX2, LOW);
  digitalWrite(PINMUX3, LOW);

  mb.task();

  mb.Ists(DI4, digitalRead(DIPIN));
  mb.Ireg(PT3, analogRead(A0));

  digitalWrite(PINMUX1, LOW);
  digitalWrite(PINMUX2, HIGH);
  digitalWrite(PINMUX3, LOW);

  mb.task();
  //  mb.Ists(DI5, digitalRead(DIPIN));
  mb.Ireg(PT4, analogRead(A0));

  digitalWrite(PINMUX1, HIGH);
  digitalWrite(PINMUX2, HIGH);
  digitalWrite(PINMUX3, LOW);

  mb.task();
  //  mb.Ists(DI6, digitalRead(DIPIN));
  mb.Ireg(PT1, analogRead(A0));

  digitalWrite(PINMUX1, LOW);
  digitalWrite(PINMUX2, LOW);
  digitalWrite(PINMUX3, HIGH);

  mb.task();

  mb.Ists(DI2, digitalRead(DIPIN));
  mb.Ireg(PT8, analogRead(A0));

  digitalWrite(PINMUX1, HIGH);
  digitalWrite(PINMUX2, LOW);
  digitalWrite(PINMUX3, HIGH);

  mb.task();

  mb.Ists(DI3, digitalRead(DIPIN));
  mb.Ireg(PT5, analogRead(A0));


  digitalWrite(PINMUX1, LOW);
  digitalWrite(PINMUX2, HIGH);
  digitalWrite(PINMUX3, HIGH);

  mb.task();

  mb.Ireg(PT7, analogRead(A0));

  digitalWrite(PINMUX1, HIGH);
  digitalWrite(PINMUX2, HIGH);
  digitalWrite(PINMUX3, HIGH);

  mb.task();

  mb.Ireg(PT6, analogRead(A0));

  mb.task();

  mb.Ireg(PT9, analogRead(A2));

  mb.task();

  mb.Ireg(PT10, analogRead(A1));

  mb.Ireg(CurrentSensor1, analogRead(A3));

  mb.task();

  mb.Ireg(CurrentSensor2, analogRead(A4));

  mb.task();

  mb.Ireg(CurrentSensor3, analogRead(A5));
}
