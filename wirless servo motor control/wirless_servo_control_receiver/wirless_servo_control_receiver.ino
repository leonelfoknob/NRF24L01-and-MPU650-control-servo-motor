/*titremer cihazı receiver
 * 3.3v and gnd use 10 nanofarad condansator and if you want change ce and cns pin
 * NRF24L01  PNA/LNA Arduino uno and Arduino nano connection pin
     ----------------
GND |GND         VCC | 3.3V        
7   |CE          CNS | 8    ---------   
13  |SCK         MOSI| 11      ANTEN  |
12  |MISO        IRQ |      ---------
     ----------------

* NRF24L01 Arduino uno and Arduino nano connection pin
     ----------------
GND |GND         VCC | 3.3V        
7   |CE          CNS | 8    ---  
13  |SCK         MOSI| 11     | ANTEN
12  |MISO        IRQ |      ---
     ----------------
*/
//alıcı 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo sero_Y;
Servo sero_X;

int initial_X = 100;
int initial_Y = 45;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int data[2];//table to receive data
int angX,angY;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  //servo initialisation
    sero_Y.attach(3);
    sero_X.attach(5);
    sero_Y.write(initial_X);
    sero_X.write(initial_Y);
}
void loop() {
  if (radio.available()) {
    radio.read(data, sizeof(data));

   angX = data[0];
   angY = data[1];
   sero_Y.write(angY);
   sero_X.write(angX);
   
   Serial.print("Received --> ");Serial.print("angX : ");Serial.print(angX);Serial.print("angY : ");Serial.println(angY);
   delay(20);
  }
}
