/*******************************************
* function:get the id of RFID key
* RFID   Uno r3
* VCC    3.3V
* RST    2
* GND    GND
* MISO   3
* MOSI   4
* SCK    5
* NSS    6
* IRQ    7
****************************************/


#include"rfid1.h"
RFID1 rfid;//create a variable type of RFID1

uchar serNumCard1[5]; // array to store your ID
uchar serNumCard2[5]; // array to store your ID
uchar serNumCard3[5]; // array to store your ID
uchar serNumCard4[5]; // array to store your ID

#define RST 10
#define MOSI 11
#define SCK 12
#define SDA 13
#define IRQ 9

#define MISO_1 2 //dogs 
#define MISO_2 3 //satan
#define MISO_3 4 //whore boy
#define MISO_4 5 //loose lips sink ships

#define LED_1 A0 
#define LED_2 A1
#define LED_3 A2
#define LED_4 A3

uchar card1[4] = {
  0xEC,
  0x9A,
  0x10,
  0xCF
};

uchar card2[4] = {
  0x7C,
  0x9E,
  0x06,
  0xCF
};

uchar card3[4] = {
  0xA3,
  0x86,
  0xDF,
  0x20
};

uchar card4[4] = {
  0xD1,
  0x7A,
  0x71,
  0x1A
};

void setup()
{
  Serial.begin(9600); //initialize the serial
  delay(100);//delay 1s
}

void loop()
{
  GetCardId(0, serNumCard1);
  GetCardId(1, serNumCard2);
  GetCardId(2, serNumCard3);
  GetCardId(3, serNumCard4);
  
  HandleCard(serNumCard1, card1, LED_1); //long dog
  HandleCard(serNumCard2, card2, LED_2);
  HandleCard(serNumCard3, card3, LED_3); //
  HandleCard(serNumCard4, card4, LED_4);
}

void HandleCard(uchar* serNum, uchar* card, int ledPin) {
  if (IsCorrectCard(serNum, card)) {
    analogWrite(ledPin, 255);
  } else {
    analogWrite(ledPin, 0);
  }
}

bool IsCorrectCard(uchar* serNum, uchar* card) {
  return memcmp(serNum, card, 4) == 0;
}

// rename this to GetCardId and have it return a string (return empty string if no card)
void GetCardId(int i, uchar* serNum){
  if(i==0){
    rfid.begin(IRQ, SCK, MOSI, MISO_1, SDA, RST);
  }
  if(i==1){
    rfid.begin(IRQ, SCK, MOSI, MISO_2, SDA, RST);
  }
  if(i==2){
    rfid.begin(IRQ, SCK, MOSI, MISO_3, SDA, RST);
  }
  if(i==3){
    rfid.begin(IRQ, SCK, MOSI, MISO_4, SDA, RST);
  }
  delay(100);
  rfid.init();
  uchar status;
  uchar str[MAX_LEN];
  // Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK)
  {
     memset(serNum, 0, 5);
     return;
  }
  // Show card type
  //Prevent conflict, return the 4 bytes Serial number of the card
  status = rfid.anticoll(str);
  if (status == MI_OK)
  {
    memcpy(serNum, str, 5);
  }
  delay(100);
  rfid.halt(); //command the card into sleep mode 
}
