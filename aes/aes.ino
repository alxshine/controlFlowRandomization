#include "tinyAES.h"

#define OUTPIN 7
uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
uint8_t data[] = "0123456789012345"; //16 chars == 16 bytes
uint8_t buf[16];
uint8_t buf2[16];

void setup() {
  // put your setup code here, to run once:
  pinMode(OUTPIN, OUTPUT);
  Serial.setTimeout(10000); 
  Serial.begin(115200);
}

uint8_t plaintext[16];

void loop() {
  // put your main code here, to run repeatedly:
  Serial.readBytesUntil('\n', plaintext, 16);

  Serial.println("Plaintext:");
  for(int i = 0; i<16; i++)
      Serial.print(plaintext[i]);
  Serial.println();
      
  digitalWrite(OUTPIN,HIGH);
  Serial.println("Starting encryption");
  AES128_ECB_encrypt(plaintext, key, buf);
  Serial.println("Encrypted");
  digitalWrite(OUTPIN, LOW);
  AES128_ECB_decrypt(buf, key, buf2);
  Serial.println("Decrypted");
  int same = !(memcmp(buf2, plaintext, 16));
  if(same)
    Serial.println("SUCCESS!");
  else
    Serial.println("FAILURE!");
  //delay(500);
}
