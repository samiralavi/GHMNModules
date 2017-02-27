#include <UIPEthernet.h>
#include <ModbusIP.h>
#include <Modbus.h>
#include <avr/wdt.h>

const int PINMUX1 = 7;
const int PINMUX2 = 6;
const int PINMUX3 = 5;

//Modbus Registers Offsets (0-9999)
const int DI1 = 4001;
const int DI2 = 4002;
const int DI3 = 4003;
const int DI4 = 4004;
const int DI5 = 4005;
const int DI6 = 4006;
const int DI7 = 4007;
const int DI8 = 4008;

const int DIPIN = 8;

const int COIL1 = 4009;
const int COIL2 = 4010;
const int COIL3 = 4011;
const int COIL4 = 4012;
const int COIL5 = 4013;
const int COIL6 = 4014;
const int COIL7 = 4015;
const int COIL8 = 4016;
const int COIL9 = 4017;
const int COIL10 = 4018;

const int PINCOIL1 = A0;
const int PINCOIL2 = A1;
const int PINCOIL3 = A2;
const int PINCOIL4 = A3;
const int PINCOIL5 = A4;
const int PINCOIL6 = A5;
const int PINCOIL7 = 4;
const int PINCOIL8 = 3;
const int PINCOIL9 = 1;
const int PINCOIL10 = 0;

//ModbusIP object
ModbusIP mb;

void setup() {
  wdt_enable(WDTO_2S);
  // The media access control (ethernet hardware) address for the shield
  byte mac[] = { 0xB4, 0x68, 0xA8, 0x72, 0x4B, 0x3F};

  //Config Modbus IP
  mb.config(mac);

  //Set MUX pins output
  pinMode(PINMUX1, OUTPUT);
  pinMode(PINMUX2, OUTPUT);
  pinMode(PINMUX3, OUTPUT);

  //Set coil pins output
  pinMode(PINCOIL1, OUTPUT);
  pinMode(PINCOIL2, OUTPUT);
  pinMode(PINCOIL3, OUTPUT);
  pinMode(PINCOIL4, OUTPUT);
  pinMode(PINCOIL5, OUTPUT);
  pinMode(PINCOIL6, OUTPUT);
  pinMode(PINCOIL7, OUTPUT);
  pinMode(PINCOIL8, OUTPUT);
  pinMode(PINCOIL9, OUTPUT);
  pinMode(PINCOIL10, OUTPUT);
  //Set DI pin input
  pinMode(DIPIN, INPUT);

  // Add Digital Input registers - Use addIsts() for digital inputs
  mb.addIsts(DI1, false);
  mb.addIsts(DI2, false);
  mb.addIsts(DI3, false);
  mb.addIsts(DI4, false);
  mb.addIsts(DI5, false);
  mb.addIsts(DI6, false);
  mb.addIsts(DI7, false);
  mb.addIsts(DI8, false);

  // Add coils to mb - Use addCoil() for digital outputs
  mb.addCoil(COIL1, false);
  mb.addCoil(COIL2, false);
  mb.addCoil(COIL3, false);
  mb.addCoil(COIL4, false);
  mb.addCoil(COIL5, false);
  mb.addCoil(COIL6, false);
  mb.addCoil(COIL7, false);
  mb.addCoil(COIL8, false);
  mb.addCoil(COIL9, false);
  mb.addCoil(COIL10, false);


}

void loop() {
  wdt_reset();
  //  Ethernet.maintain();
  //Call once inside loop() - all magic here
  mb.task();

  //Attach coils registers to pins
  digitalWrite(PINCOIL1, mb.Coil(COIL1));
  digitalWrite(PINCOIL2, mb.Coil(COIL2));
  digitalWrite(PINCOIL3, mb.Coil(COIL3));
  digitalWrite(PINCOIL4, mb.Coil(COIL4));
  digitalWrite(PINCOIL5, mb.Coil(COIL5));
  digitalWrite(PINCOIL6, mb.Coil(COIL6));
  digitalWrite(PINCOIL7, mb.Coil(COIL7));
  digitalWrite(PINCOIL8, mb.Coil(COIL8));
  digitalWrite(PINCOIL9, mb.Coil(COIL9));
  digitalWrite(PINCOIL10, mb.Coil(COIL10));

  //Attach digital input registers to pins
  digitalWrite(PINMUX3, LOW);
  digitalWrite(PINMUX2, LOW);
  digitalWrite(PINMUX1, LOW);
  delay(1);
  mb.Ists(DI4, digitalRead(DIPIN));

  digitalWrite(PINMUX3, HIGH);
  digitalWrite(PINMUX2, LOW);
  digitalWrite(PINMUX1, LOW);
  delay(1);
  mb.Ists(DI2, digitalRead(DIPIN));

  digitalWrite(PINMUX3, LOW);
  digitalWrite(PINMUX2, HIGH);
  digitalWrite(PINMUX1, LOW);
  delay(1);
  mb.Ists(DI1, digitalRead(DIPIN));

  digitalWrite(PINMUX3, HIGH);
  digitalWrite(PINMUX2, HIGH);
  digitalWrite(PINMUX1, LOW);
  delay(1);
  mb.Ists(DI3, digitalRead(DIPIN));

  digitalWrite(PINMUX3, LOW);
  digitalWrite(PINMUX2, LOW);
  digitalWrite(PINMUX1, HIGH);
  delay(1);
  mb.Ists(DI5, digitalRead(DIPIN));

  digitalWrite(PINMUX3, HIGH);
  digitalWrite(PINMUX2, LOW);
  digitalWrite(PINMUX1, HIGH);
  delay(1);
  mb.Ists(DI8, digitalRead(DIPIN));

  digitalWrite(PINMUX3, LOW);
  digitalWrite(PINMUX2, HIGH);
  digitalWrite(PINMUX1, HIGH);
  delay(1);
  mb.Ists(DI7, digitalRead(DIPIN));

  digitalWrite(PINMUX3, HIGH);
  digitalWrite(PINMUX2, HIGH);
  digitalWrite(PINMUX1, HIGH);
  delay(1);
  mb.Ists(DI6, digitalRead(DIPIN));
}
