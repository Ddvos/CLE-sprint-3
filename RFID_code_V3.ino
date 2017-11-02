
#include <SPI.h>
#include <MFRC522.h>  // library voor de RFID
 
#define SS_PIN 10 // declaratie pinnnen
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int i = 0; //punten per juist antwoord
boolean e1Combo =false; // dit is de eerste combinatie als hij gemaakt is niet meer bij tellen
boolean e2Combo =false; // dit is de tweede combinatie als hij gemaakt is niet meer bij tellen
boolean e3Combo =false; // dit is de derde combinatie als hij gemaakt is niet meer bij tellen

boolean e4Combo =false; // enzo...
boolean e5Combo =false; 
boolean e6Combo =false; 

boolean e7Combo =false; 
boolean e8Combo =false; 
boolean e9Combo =false; 


int greenLedPin = 4;  // ledje als de juiste combinatie is gemaakt
int redLedPin = 3;   // ledje als er geen of een foute combinatie is gemaakt
 
int servoMotor = 8; // dit is de pin die naar de 2de Arduino gaat (Arduino 2 laat de servo draaien)

int knop1 = A0; // input knoppen
int knop2 = A1;
int knop3 = A2;
int knop4 = A3;
int knop5 = 7;
int knop6 = 6;

int val1 = 0;  // beginwaarde knoppen
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;



String dierenKaart1 = "64 2D E5 20";  // nummer van kaarten (RFID UID)
String dierenKaart2 = "C4 52 F9 20";
String dierenKaart3 = "64 FA EF 20";


////////////////////////setup/////////////////////////////////
 
void setup() 
{
  Serial.begin(9600);  
  SPI.begin();      
  Serial.println("leg een kaart op de reader...");
  mfrc522.PCD_Init();  
  Serial.println();

  pinMode(greenLedPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);
  pinMode(knop1,INPUT);
  pinMode(servoMotor,OUTPUT);

 
 beginScherm(); // in deze functie toont hij het beginscherm, het welkoms woord.
 
}

////////////////////loop//////////////////////////////////
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) // controleerd voor nieuwe kaarten
  {
    Serial.println("No card");    // geen nieuwe kaarten gevonden
    digitalWrite(greenLedPin,LOW);
    digitalWrite(redLedPin,LOW);
    digitalWrite(blueLedPin,LOW); 
    return;
  }

  else{

                 //// met de onderstaande for loop toont hij de UID van de kaart//////////
            Serial.print("UID tag :");
            String content= "";
            byte letter;
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            {
               Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
               Serial.print(mfrc522.uid.uidByte[i], HEX);
               content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
               content.concat(String(mfrc522.uid.uidByte[i], HEX));
            }
          
            //// kijkt of er een bekende kaart word gelezen en opend bijbehorende functie///
            Serial.println();
            Serial.print("Message : ");
            content.toUpperCase();
            if (content.substring(1) == dierenKaart1)//kaart 1//
            {
                Serial.println("dierenKaart1");
                lcd.clear(); 
                lcd.print("Kaart 1");
                kaart1(); // gaat naar de functie van de eerste kaart
            }
            else if (content.substring(1) == dierenKaart2)// kaart 2
            {
              Serial.println("dierenKaart2");
              lcd.clear(); 
              lcd.print("Kaart 2"); 
              kaart2(); // gaat naar de functie van de tweede kaart  
            }
             else if (content.substring(1) == dierenKaart3)// kaart 3
            {
              Serial.println("dierenKaart3");
              lcd.clear(); 
              lcd.print("Kaart 3");
              kaart3(); // gaat naar de functie van de derde kaart    
            }  
    }

    // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) // hier leest hij de kaart uit
  {
    return;
  }

    
    
} // einde loop 


/*/////////////////////////////////////////////////////////////
                        functie beginscherm   
////////////////////////////////////////////////////////////*/

int beginScherm(){  // dit is het welkom scherm
  lcd.begin();
  lcd.backlight();
  lcd.print("     Welkom");
  delay(2000);
}


/*/////////////////////////////////////////////////////////////
                        kaart 1  
////////////////////////////////////////////////////////////*/

int kaart1(){

    val1 = digitalRead(knop1);
    val2 = digitalRead(knop2);
    val3 = digitalRead(knop3);
    val4 = digitalRead(knop4);
    val5 = digitalRead(knop5);
    val6 = digitalRead(knop6);
  
      
    if(val1 == HIGH && val2 == HIGH){ // dit zijn de combinaties die je moet maken om punten te krijgen 
      
       digitalWrite(greenLedPin,HIGH);
       digitalWrite(servoMotor,HIGH);
       digitalWrite(redLedPin,LOW);

       if(e1Combo ==false){ // als de eerste combinatie is gemaakt telt hij een punt op. en zorgt dat je niet nog een keer de zelfde combinatie kan maken
       i=i+2;
       e1Combo = true;
       }
    }
    else if (val3 == HIGH && val4 == HIGH){ //2de combinatie
       digitalWrite(greenLedPin,HIGH);
       digitalWrite(servoMotor,HIGH);
       digitalWrite(redLedPin,LOW);

       if(e2Combo ==false){
       i=i+2;
       e2Combo = true;
       }
      }

    else if (val5 == HIGH && val6 == HIGH) { //3de combinatie
       digitalWrite(greenLedPin,HIGH);
       digitalWrite(servoMotor,HIGH);
       digitalWrite(redLedPin,LOW);

         if(e3Combo ==false){ // 
       i=i+2;
       e3Combo = true;
       }
      }
    
    else{digitalWrite(redLedPin,HIGH); // nu wordt er geen juist antwoord gegeven
         digitalWrite(greenLedPin,LOW);
         digitalWrite(servoMotor,LOW);
        
    } 
       lcd.setCursor(0,1); // met deze code toont hij de totale score op het scherm
       lcd.print("score ");
       lcd.print(i);
       
}

/*/////////////////////////////////////////////////////////////
                        kaart 2  
////////////////////////////////////////////////////////////*/

int kaart2(){

    val1 = digitalRead(knop1);
    val2 = digitalRead(knop2);
    val3 = digitalRead(knop3);
    val4 = digitalRead(knop4);
    val5 = digitalRead(knop5);
    val6 = digitalRead(knop6);
  
      
      if(val1 == HIGH && val3 == HIGH){ // dit zijn de combinaties die je moet maken om punten te krijgen 
      
       digitalWrite(greenLedPin,HIGH);
       digitalWrite(servoMotor,HIGH);
       digitalWrite(redLedPin,LOW);

       if(e4Combo ==false){ // als de eerste combinatie is gemaakt telt hij een punt op. en zorgt dat je niet nog een keer de zelfde combinatie kan maken
       i=i+2;
       e4Combo = true;
       }
    }
   else if (val6 == HIGH && val4 == HIGH){ //2de combinatie
       digitalWrite(greenLedPin,HIGH);
       digitalWrite(servoMotor,HIGH);
       digitalWrite(redLedPin,LOW);

       if(e5Combo ==false){
       i=i+2;
       e5Combo = true;
       }
      }

   else if (val5 == HIGH && val2 == HIGH) { //3de combinatie
       digitalWrite(greenLedPin,HIGH);
       digitalWrite(servoMotor,HIGH);
       digitalWrite(redLedPin,LOW);

         if(e6Combo ==false){ // 
       i=i+2;
       e6Combo = true;
       }
      }
    
    else{digitalWrite(redLedPin,HIGH);  // nu wordt er geen juist antwoord gegeven
         digitalWrite(servoMotor,LOW);
         digitalWrite(greenLedPin,LOW);
        
    } 
       lcd.setCursor(0,1); // met deze code toont hij de totale score op het scherm
       lcd.print("score ");
       lcd.print(i);


}

/*/////////////////////////////////////////////////////////////
                        kaart 3  
////////////////////////////////////////////////////////////*/

int kaart3(){


}


