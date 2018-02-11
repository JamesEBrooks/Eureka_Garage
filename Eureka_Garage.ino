#define APOSTROPHE  5
#define COLON       4
#define DECIMAL4    3
#define DECIMAL3    2
#define DECIMAL2    1
#define DECIMAL1    0

int HornsList[] = { 1,3,4,5,6,7,8,11,15,16,17,19,21,23,24,25,26,27,28,30,31,32,34,35};
int TillBellList[] = { 2,9,10,12,13,14,18,20,22,29,33 };

int Tsound = 0;
int Hsound = 0;

int testsound = 0;

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
SoftwareSerial mySerial2(4, 5); // RX, TX
SoftwareSerial mySerialSound(25, 23); // RX, TX

#define ButtonA 8
#define ButtonB 9
#define ButtonC 10
#define ButtonD 11

#define PetrolPumpA_Input 31 // counter signal from pumpA
#define PetrolPumpB_Input 33 // counter signal from pumpB
#define PetrolPumpA_Reset 35 // output to pump
#define PetrolPumpB_Reset 37 // output to pump

int PetrolPumpA_State = LOW;
int PetrolPumpB_State = LOW;
int OldPetrolPumpA_State = LOW;
int OldPetrolPumpB_State = LOW;

unsigned long debounceDelay = 50;  

int buttonStateA;             
int lastButtonStateA = LOW;   
unsigned long lastDebounceTimeA = 0;  
  
int buttonStateB;             
int lastButtonStateB = LOW;   
unsigned long lastDebounceTimeB = 0;  

int buttonStateC;             
int lastButtonStateC = LOW;   
unsigned long lastDebounceTimeC = 0;  

int buttonStateD;             
int lastButtonStateD = LOW;   
unsigned long lastDebounceTimeD = 0;  

int readingA = 0; 
int readingB = 0; 
int readingC = 0; 
int readingD = 0; 

int cycles = 0;
int cycles2 = 0;

int Liters1 = 0;
int Liters2 = 0;

void setup() {
  mySerialSound.begin(38400);
  mySerial.begin(9600);
  mySerial2.begin(9600);
  
  Serial1.begin(9600);
  //Serial2.begin(9600);
  Serial3.begin(9600); 
  
 // mySerial.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
 // Serial1.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
 // Serial2.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
 // Serial3.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display

  pinMode(PetrolPumpA_Input, INPUT);
  pinMode(PetrolPumpB_Input, INPUT);

  pinMode(PetrolPumpA_Reset, OUTPUT);
  pinMode(PetrolPumpB_Reset, OUTPUT);

  digitalWrite(PetrolPumpA_Reset, HIGH);
  digitalWrite(PetrolPumpB_Reset, HIGH);
  
  pinMode(ButtonA,INPUT);
  pinMode(ButtonB,INPUT);
  pinMode(ButtonC,INPUT);
  pinMode(ButtonD,INPUT);
  
  digitalWrite(ButtonA, HIGH);
  digitalWrite(ButtonB, HIGH);
  digitalWrite(ButtonC, HIGH);
  digitalWrite(ButtonD, HIGH);
  
  

  mySerial.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  Serial1.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  mySerial2.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
  Serial3.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
 // Serial3.write(0x81);
delay(2000);
    
mySerial.write(0x77);  
mySerial.write(  (1<<DECIMAL2) );
Serial1.write(0x77);  
Serial1.write(  (1<<DECIMAL2) );
mySerial2.write(0x77);  
mySerial2.write(  (1<<DECIMAL3) );
Serial3.write(0x77);  
Serial3.write(  (1<<DECIMAL3) );
}








void loop() 
{
  
  PetrolPumpA_State = digitalRead(PetrolPumpA_Input);
  PetrolPumpB_State = digitalRead(PetrolPumpB_Input);

  if(PetrolPumpA_State == HIGH && OldPetrolPumpA_State == LOW)
  {
    // count one
    cycles+=1; /// does this need de bouncing???
    if(cycles % 5 == 0){Liters1 +=1;}
  }

  if(PetrolPumpB_State == HIGH && OldPetrolPumpB_State == LOW)
  {
    // count one
    cycles2+=1;
    if(cycles2 % 5 == 0){Liters2 +=1;}
  }



  OldPetrolPumpA_State = PetrolPumpA_State; 
  OldPetrolPumpB_State = PetrolPumpB_State; 
  
  readingA = digitalRead(ButtonA);
  readingB = digitalRead(ButtonB);
  readingC = digitalRead(ButtonC);
  readingD = digitalRead(ButtonD);

  if (readingA != lastButtonStateA) {
    lastDebounceTimeA = millis();
  }

  if (readingB != lastButtonStateB) {
    lastDebounceTimeB = millis();
  }

  if (readingC != lastButtonStateC) {
    lastDebounceTimeC = millis();
  }

  if (readingC != lastButtonStateC) {
    lastDebounceTimeC = millis();
  }

///////////////////////////////////////////////////////

    if ((millis() - lastDebounceTimeA) > debounceDelay) {
      if (readingA != buttonStateA) {
       buttonStateA = readingA;
       if (buttonStateA == LOW) {

        mySerialSound.write('p');
      mySerialSound.write(HornsList[Hsound]);
      Hsound += 1;
      if(Hsound>23){Hsound = 0;}
      
      }
    }
  }
  
///////////////////////////////////////////////////////

  if ((millis() - lastDebounceTimeB) > debounceDelay) {
    if (readingB != buttonStateB) {
      buttonStateB = readingB;
      if (buttonStateB == LOW) {
        
       mySerialSound.write('p');
      mySerialSound.write(TillBellList[Tsound]);
    //mySerialSound.write(testsound);
    //testsound+=1;
      Tsound += 1;
      if(Tsound>10){Tsound = 0;}
      
       cycles2=0;
       Liters2=0;
       digitalWrite(PetrolPumpB_Reset, LOW);
       delay(200);
       digitalWrite(PetrolPumpB_Reset, HIGH);
     //  Serial1.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
     //  Serial2.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
      }
    }
  }
  
///////////////////////////////////////////////////////  

  if ((millis() - lastDebounceTimeC) > debounceDelay) {
    if (readingC != buttonStateC) {
      buttonStateC = readingC;
      if (buttonStateC == LOW) {
        
        mySerialSound.write('p');
      mySerialSound.write(TillBellList[Tsound]);
      Tsound += 1;
      if(Tsound>10){Tsound = 0;}
      
       cycles=0;
       Liters1=0;
       digitalWrite(PetrolPumpA_Reset, LOW);
       delay(200);
       digitalWrite(PetrolPumpA_Reset, HIGH);  
     //  mySerial.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display
     //  Serial3.write('v'); //Reset the display - this forces the cursor to return to the beginning of the display         
      }
    }
  }

///////////////////////////////////////////////////////

  if ((millis() - lastDebounceTimeD) > debounceDelay) {
    if (readingD != buttonStateD) {
      buttonStateD = readingD;
      if (buttonStateD == LOW) {
       mySerialSound.write('p');
      mySerialSound.write(HornsList[Hsound]);
      Hsound += 1;
      if(Hsound>23){Hsound = 0;}
      }
    }
  }

/////////////////////////////////////////////////////
  
  lastButtonStateA = readingA;
  lastButtonStateB = readingB;
  lastButtonStateC = readingC;
  lastButtonStateD = readingD;
  char stin[10] ;
  char tempString[10]; //Used for sprintf
  char tempString2[10]; //Used for sprintf
  char tempString3[10]; //Used for sprintf
  char tempString4[10]; //Used for sprintf

   char tempString5[10]; //Used for sprintf
  
  sprintf(tempString, "%4d", cycles); //Convert deciSecond into a string that is right adjusted
  sprintf(tempString2, "%4d", cycles2); //Convert deciSecond into a string that is right adjusted
  sprintf(tempString3, "%4d", Liters1); //Convert deciSecond into a string that is right adjusted
  sprintf(tempString4, "%4d", Liters2); //Convert deciSecond into a string that is right adjusted
  sprintf(tempString5, "%4d", testsound); //Convert deciSecond into a string that is right adjusted

  // pump 1
  mySerial.print(tempString); //Send serial string out the soft serial port to the S7S
  Serial3.print(tempString3); //Send serial string out the soft serial port to the S7S

  // pump 2
  Serial1.print(tempString2); //Send serial string out the soft serial port to the S7S
  mySerial2.print(tempString4); //Send serial string out the soft serial port to the S7S
  //Serial2.print(tempString5); //Send serial string out the soft serial port to the S7S
  
 // Serial3.print(stin); //Send serial string out the soft serial port to the S7S
  //Serial.write(1);
//cycles+=1;
//cycles2+=1;
//Liters1+=2;
//Liters2+=2;
//delay(100);
}


