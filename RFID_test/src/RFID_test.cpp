/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/IoTPa/Documents/Particle/RFID_test/src/RFID_test.ino"
/*
 * Project RFID_test
 * Description:
 * Author:
 * Date:
 */

#include "MFRC522.h"

void setup();
void loop();
#line 10 "c:/Users/IoTPa/Documents/Particle/RFID_test/src/RFID_test.ino"
#define SS_PIN SS
#define RST_PIN D2

MFRC522 mfrc522(SS_PIN, RST_PIN);        // Create MFRC522 instance.

void setup() {
  Serial.begin(9600);        // Initialize serial communications with the PC
	mfrc522.setSPIConfig();

	mfrc522.PCD_Init();        // Init MFRC522 card
  Serial.println("Scan a MIFARE Classic PICC to demonstrate Value Blocks.");
}

void loop() {
        
        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        Serial.println("Preparing Key");
        MFRC522::MIFARE_Key key;
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) {
                Serial.println("No card");
                return;
        }

        // Select one of the cards
        Serial.println("Select card");
        if ( ! mfrc522.PICC_ReadCardSerial()) {
                return;
        }
        // Now a card is selected. The UID and SAK is in mfrc522.uid.
        
        // Dump UID
        Serial.print("Card UID:");
        delay(10000);
        for (byte i = 0; i < mfrc522.uid.size; i++) {
                Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                Serial.print(mfrc522.uid.uidByte[i], HEX);
        } 
        Serial.println();

        // Dump PICC type
        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
        Serial.print("PICC type: ");
        Serial.println(mfrc522.PICC_GetTypeName(piccType));
        if (        piccType != MFRC522::PICC_TYPE_MIFARE_MINI 
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_1K
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
                //Serial.println("This sample only works with MIFARE Classic cards.");
                return;
        }
               
        // In this sample we use the second sector (ie block 4-7). the first sector is = 0
        // scegliere settore di lettura da 0 = primo settore 
        byte sector         = 1;
        // block sector 0-3(sector0) 4-7(sector1) 8-11(sector2)
        // blocchi di scrittura da 0-3(sector0) 4-7(sector1) 8-11(sector2)
        byte valueBlockA    = 4;
        byte valueBlockB    = 5;
        byte valueBlockC    = 6;
        byte trailerBlock   = 7;
        byte status;
        // Authenticate using key A.
        // avvio l'autentificazione A
        //Serial.println("Authenticating using key A...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
                Serial.print("PCD_Authenticate() failed: ");
                Serial.println(mfrc522.GetStatusCodeName(status));
                return;
        }
        // Authenticate using key B.
        // avvio l'autentificazione B
        //Serial.println("Authenticating again using key B...");
        status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
        if (status != MFRC522::STATUS_OK) {
                Serial.print("PCD_Authenticate() failed: ");
                Serial.println(mfrc522.GetStatusCodeName(status));
                return;
        }
        
        // Writing new value block A
        // Scrivo i valori per il settore A
        Serial.println("Writing new value block A(4) : the first of the sector TWO ");
                byte value1Block[] = { 1,2,3,4,  5,6,7,8, 9,10,255,12,  13,14,15,16,   valueBlockA,~valueBlockA,valueBlockA,~valueBlockA };
                status = mfrc522.MIFARE_Write(valueBlockA, value1Block, 16);
                if (status != MFRC522::STATUS_OK) {
                        Serial.print("MIFARE_Write() failed: ");
                        Serial.println(mfrc522.GetStatusCodeName(status));
                }
        /*
        
        // Writing new value block B
        // Scrivo i valori per il settore B
        Serial.println("Writing new value block B");
                byte value2Block[] = { 255,255,255,255,  0,0,0,0, 0,0,0,0,  255,255,255,255,   valueBlockB,~valueBlockB,valueBlockB,~valueBlockB };
                status = mfrc522.MIFARE_Write(valueBlockB, value2Block, 16);
                if (status != MFRC522::STATUS_OK) {
                        Serial.print("MIFARE_Write() failed: ");
                        Serial.println(mfrc522.GetStatusCodeName(status));
                }
        
        // Writing new value block D
        // Scrivo i valori per il settore C
        Serial.println("Writing new value block C");
                byte value3Block[] = { 255,255,255,255,  0,0,0,0, 0,0,0,0,  255,255,255,255,   valueBlockC,~valueBlockC,valueBlockC,~valueBlockC };
                status = mfrc522.MIFARE_Write(valueBlockC, value3Block, 16);
                if (status != MFRC522::STATUS_OK) {
                        Serial.print("MIFARE_Write() failed: ");
                        Serial.println(mfrc522.GetStatusCodeName(status));
                }
                
        */
        
        
        Serial.println("Read block A(4) : the first of the sector TWO");        
        byte buffer[18];
        byte size = sizeof(buffer);
        // change this: valueBlockA , for read anather block
        // cambiate valueBlockA per leggere un altro blocco
        status = mfrc522.MIFARE_Read(valueBlockA, buffer, &size);
        Serial.print("Settore : 0 Valore :");
        Serial.println(buffer[0]);
        Serial.print("Settore : 1 Valore :");
        Serial.println(buffer[1]);
        Serial.print("Settore : 2 Valore :");
        Serial.println(buffer[2]);
        Serial.print("Settore : 3 Valore :");
        Serial.println(buffer[3]);
        Serial.print("Settore : 4 Valore :");
        Serial.println(buffer[4]);
        Serial.print("Settore : 5 Valore :");
        Serial.println(buffer[5]);
        Serial.print("Settore : 6 Valore :");
        Serial.println(buffer[6]);
        Serial.print("Settore : 7 Valore :");
        Serial.println(buffer[7]);
        Serial.print("Settore : 8 Valore :");
        Serial.println(buffer[8]);
        Serial.print("Settore : 9 Valore :");
        Serial.println(buffer[9]);
        Serial.print("Settore :10 Valore :");
        Serial.println(buffer[10]);
        Serial.print("Settore :11 Valore :");
        Serial.println(buffer[11]);
        Serial.print("Settore :12 Valore :");
        Serial.println(buffer[12]);
        Serial.print("Settore :13 Valore :");
        Serial.println(buffer[13]);
        Serial.print("Settore :14 Valore :");
        Serial.println(buffer[14]);
        Serial.print("Settore :15 Valore :");
        Serial.println(buffer[15]);
        
        
        
        //byte value1Block[] = { 1,2,3,4,  5,6,7,8, 9,10,255,12,  13,14,15,16,   valueBlockA,~valueBlockA,valueBlockA,~valueBlockA };
        if ( 
        buffer[0]  == 1   &&
        buffer[1]  == 2   && 
        buffer[2]  == 3   && 
        buffer[3]  == 4   &&
        buffer[4]  == 5   &&
        buffer[5]  == 6   &&
        buffer[6]  == 7   &&
        buffer[7]  == 8   &&
        buffer[8]  == 9   &&
        buffer[9]  == 10  &&
        buffer[10] == 255 &&
        buffer[11] == 12  &&
        buffer[12] == 13  &&
        buffer[13] == 14  &&
        buffer[14] == 15  &&
        buffer[15] == 16 
        ){
        
        // sel a scrittura è uguale alla lettura allora e stato un successo !!   
        Serial.println("Read block A(4) : the first of the sector TWO : success");  
        Serial.println(":-)");  
          
        }else{
        
         //  scrittura Fallita
        Serial.println("Read block A(4) : the first of the sector TWO : no match - write don't work fine ");
        Serial.println(":-( ");  
        
        }
        
        
        // risponde successo
        //Serial.println(mfrc522.GetStatusCodeName(status));
        
        // Dump the result
        //mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
        
        // Halt PICC
        mfrc522.PICC_HaltA();

        // Stop encryption on PCD
        mfrc522.PCD_StopCrypto1();
        
        
}