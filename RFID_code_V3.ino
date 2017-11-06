/*

Deze code heb ik geschreven voor Sprint 3. In deze sprint heb ik met mijn team de Dierendoos gemaakt.

Door de omschrijving hieronder zal de werking van de code een stuk duidelijker worden.

Werking Dierendoos:
Om De Dierendoos aan te zetten hoef je hem alleen aan te sluiten op een usb poort hij zal dan automatisch opstarten. 
Onder het Welkom scherm zitten 6 knoppen waar je een dierenplaat overheen kan leggen. Op de dierenplaat zit een RFID tag die de dierendoos kan lezen zo weet hij welke dierenplaat er op ligt.
Het is de bedoeling om de 2 bij elkaar horende lichaamsdelen van de dieren met elkaar te verbinden.
Dit doe je door de knoppen boven het plaatje tegelijk in te drukken. Hiervoor krijg je 2 punten die op het scherm verschijnen. 
Het is niet mogelijk om het zelfde dier meerdere keren te verbinden. Als je de juiste combinaties  hebt gemaakt kan je de plaat er af halen en vervangen voor een andere dierenplaat. 
De punten blijven behouden tot dat je de usb kabel loshaalt hierdoor woord het spel gereset en staan de punten weer op 0.


Meer informatie kan je vinden op: https://stud.hosted.hr.nl/0884930/kleuterspel/
*/

#include <SPI.h>
#include <MFRC522.h>  // library voor de RFID
 
#define SS_PIN 10 // declaratie RFID pinnnen
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // functie voor de RFID

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>  // library voor het scherm


LiquidCrystal_I2C lcd(0x3F, 16, 2); // dit is het adres voor een 16X2 scherm

int i = 0; // i houd de punten bij op het scherm

// dit zijn per dieren kaart de mogelike combinaties
boolean e1Combo =false; // als een combinatie is gemaakt komt hij op TRUE zodat hij niet nog een keer gemaakt kan worden
boolean e2Combo =false; 
boolean e3Combo =false; 

boolean e4Combo =false; 
boolean e5Combo =false; 
boolean e6Combo =false; 


int greenLedPin = 4;  // ledje als de juiste combinatie is gemaakt
int redLedPin = 3;   // ledje als er geen of een foute combinatie is gemaakt

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

////////////////////////setup/////////////////////////////////
 
void setup() 
{
  Serial.begin(9600);  
  SPI.begin();      
  Serial.println("leg een kaart op de reader...");
  mfrc522.PCD_Init();  
  Serial.println();

  pinMode(greenLedPin,OUTPUT);// zet de poorten als in of output 
  pinMode(redLedPin,OUTPUT);
  pinMode(knop1,INPUT);
 
 beginScherm(); // zodra de arduino opstart gaat hij eenmalig naar deze functie waar hij het welkom woord laat zien.
 
} // einde setup()

////////////////////loop//////////////////////////////////
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) // Als er geen kaarten op de RFID scanner liggen voert hij de volgende code uit:
  {
    Serial.println("No card");     
    digitalWrite(greenLedPin,LOW);
    digitalWrite(redLedPin,LOW);
    return;
  }

  else{ // Als er wel een kaart op de RFID scanner ligt voert hij de volgende code uit

                 //// met de onderstaande for loop toont hij de UID van de kaart//////////
            Serial.print("UID tag :");
            String content= "";
            byte letter;
            for (byte i = 0; i < mfrc522.uid.size; i++) 
            {
               Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
               Serial.print(mfrc522.uid.uidByte[i], HEX);  // hij schrijft naar de Serial monitor de UID code van de RFID kaart
               content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
               content.concat(String(mfrc522.uid.uidByte[i], HEX));
            }
          
            //// kijkt of er een bekende kaart word gelezen en opend bijbehorende functie///
            Serial.println();
            Serial.print("Message : ");
            content.toUpperCase();
            if (content.substring(1) == dierenKaart1)// als de RFID dierenkaart1 leest voert hij de volgende code uit:
            {
                Serial.println("dierenKaart1");
                lcd.clear(); 
                lcd.print("Kaart 1");
                kaart1(); // gaat naar de functie van de eerste dieren kaart
            }
            else if (content.substring(1) == dierenKaart2)// als de RFID dierenkaart2 leest voert hij de volgende code uit:
            {
              Serial.println("dierenKaart2");
              lcd.clear(); 
              lcd.print("Kaart 2"); 
              kaart2(); // gaat naar de functie van de tweede dieren kaart  
            } 
    }
    
} // einde loop() 


/*/////////////////////////////////////////////////////////////
                        functie beginscherm   
////////////////////////////////////////////////////////////*/

int beginScherm(){  // dit is het welkom scherm
  lcd.begin();
  lcd.backlight();
  lcd.print("     Welkom");
  delay(2000);
} // einde functie beginScherm()


/*/////////////////////////////////////////////////////////////
                        kaart 1  
////////////////////////////////////////////////////////////*/

int kaart1(){

    val1 = digitalRead(knop1); //val1 woord nu gelijk gesteld aan knop1
    val2 = digitalRead(knop2); //enz..
    val3 = digitalRead(knop3);
    val4 = digitalRead(knop4);
    val5 = digitalRead(knop5);
    val6 = digitalRead(knop6);
  
      
    if(val1 == HIGH && val2 == HIGH){ // dit zijn de combinaties die je moet maken om punten te krijgen 
      
       digitalWrite(greenLedPin,HIGH); // de juiste combinatie is gemaakt 
       digitalWrite(redLedPin,LOW);

       if(e1Combo ==false){ // als de eerste combinatie is gemaakt telt hij 2 punten op. en zorgt dat je niet nog een keer de zelfde combinatie kan maken
          i=i+2;
          e1Combo = true; // door e1Combo op true te zetten kunnen de punten niet nog een keer worden opgeteld
          }
    }
    else if (val3 == HIGH && val4 == HIGH){ //2de combinatie
       digitalWrite(greenLedPin,HIGH);
       digitalWrite(redLedPin,LOW);

       if(e2Combo ==false){
          i=i+2;
          e2Combo = true;
          }
      }

    else if (val5 == HIGH && val6 == HIGH) { //3de combinatie
       digitalWrite(greenLedPin,HIGH);
       digitalWrite(redLedPin,LOW);

         if(e3Combo ==false){  
            i=i+2;
            e3Combo = true;
            }
      }
    
    else{digitalWrite(redLedPin,HIGH); // nu wordt er geen juiste combinatie gemaakt gegeven
         digitalWrite(greenLedPin,LOW);
        
    } 
       lcd.setCursor(0,1); // met deze code toont hij de totale score op het scherm
       lcd.print("score ");
       lcd.print(i); // i is de totale score
      
}  // einde functie kaart1()

/*/////////////////////////////////////////////////////////////
                        kaart 2  
////////////////////////////////////////////////////////////*/

int kaart2(){

    val1 = digitalRead(knop1); //val1 woord nu gelijk gesteld aan knop1
    val2 = digitalRead(knop2); //enz..
    val3 = digitalRead(knop3);
    val4 = digitalRead(knop4);
    val5 = digitalRead(knop5);
    val6 = digitalRead(knop6);
  
      
      if(val1 == HIGH && val3 == HIGH){ // dit zijn de combinaties die je moet maken om punten te krijgen 
      
       digitalWrite(greenLedPin,HIGH); // de juiste combinatie is gemaakt 
       digitalWrite(redLedPin,LOW);

       if(e4Combo ==false){ // als de eerste combinatie is gemaakt telt hij een punt op. en zorgt dat je niet nog een keer de zelfde combinatie kan maken
          i=i+2;
          e4Combo = true; // door e4Combo op true te zetten kunnen de punten niet nog een keer worden opgeteld
       }
    }
   else if (val6 == HIGH && val4 == HIGH){ //2de combinatie
       digitalWrite(greenLedPin,HIGH);
       digitalWrite(redLedPin,LOW);

       if(e5Combo ==false){
          i=i+2;
          e5Combo = true;
       }
      }

   else if (val5 == HIGH && val2 == HIGH) { //3de combinatie
       digitalWrite(greenLedPin,HIGH);
       digitalWrite(redLedPin,LOW);

         if(e6Combo ==false){   
            i=i+2;
            e6Combo = true;
          }
      }
    
    else{
         digitalWrite(redLedPin,HIGH);  // nu wordt er geen juiste combinatie gemaakt
         digitalWrite(greenLedPin,LOW);
        }
         
    lcd.setCursor(0,1); // met deze code toont hij de totale score op het scherm
    lcd.print("score ");
    lcd.print(i);   // i is de totale score

}  // einde functie kaart2()

// einde code

