#include "tinyAES.h"

#define TEST

#define OUTPIN 7
uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
uint8_t buf[16];
uint8_t buf2[16];
uint8_t plaintext[17];

void setup() {
    // put your setup code here, to run once:
    pinMode(OUTPIN, OUTPUT);
    Serial.setTimeout(100000);
    Serial.begin(115200);
    srand(micros());
}

void loop() {
#ifdef TEST
    //generate random plaintext
    for(uint8_t i=0; i<16; i++)
        plaintext[i] = (uint8_t) rand();
    plaintext[16] = 0;

    digitalWrite(OUTPIN,HIGH);
    Serial.println("Starting encryption");
    unsigned long time = micros();
    AES128_ECB_encrypt(plaintext, key, buf);
    time = micros() - time;
    Serial.println("Encrypted");
    digitalWrite(OUTPIN, LOW);
    Serial.println("Starting decryption");
    AES128_ECB_decrypt(buf, key, buf2);
    Serial.println("Decrypted");
    int same = !(memcmp(buf2, plaintext, 16));
    if(same)
        Serial.println("SUCCESS!");
    else
        Serial.println("FAILURE!");
    Serial.print("Time taken: ");
    Serial.print(time);
    Serial.println("microseconds");
    Serial.println();
    delay(500);
#else
    // put your main code here, to run repeatedly:
    Serial.readBytesUntil('\n', plaintext, 17);

    for(int i = 0; i<16; i++)
    {
        Serial.write(plaintext[i]);
    }
    //Serial.println();


    digitalWrite(OUTPIN,HIGH);
    //Serial.println("Starting encryption");
    AES128_ECB_encrypt(plaintext, key, buf);
    //Serial.println("Encrypted");
    digitalWrite(OUTPIN, LOW);
    AES128_ECB_decrypt(buf, key, buf2);
#endif
}
