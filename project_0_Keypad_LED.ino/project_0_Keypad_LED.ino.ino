#include <Keypad.h>

const byte ROWS = 4; //vier rijen
const byte COLS = 4; //vier kolommen

int ledpin  = 12;
//int buttonpin = 2;
byte rowPins[ROWS] = {6,5,4,3}; //pins rijen
byte colPins[COLS] = {10,9,8,7}; //cols rijen


int buttonState = 0;


char keys [ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
//layout keypad

//keypad aanmaken (keypad object)
Keypad keypad = Keypad(makeKeymap(keys), colPins, rowPins, ROWS, COLS);

#define password_length 5 //voor 4 cijfers + een NULL
char pass[password_length] = "5678"; // hardcoded pincode
char passdata[password_length];     // array waar de invoer in weggezet wordt
byte data_index = 0, pass_index = 0;  //bijhouders voor de invoer







void setup() {
  pinMode(ledpin, OUTPUT);
  //pinMode(buttonpin, INPUT_PULLUP);

  Serial.begin(9600);

}

void loop() {

  /* led + button
  buttonState = digitalRead(buttonpin);
  
  if(buttonState == LOW){
    digitalWrite(ledpin, HIGH);
  }
  else{
    digitalWrite(ledpin, LOW);
  }

  */

   /* led for periode
   openLock(1);
   delay(1000);
   */



   char key = keypad.getKey();

   if(key != NO_KEY){
      if(key!='#'){
          if(data_index <= password_length){
            passdata[data_index] = key;     //bewaar ingevoerde karakter
            data_index++;
            Serial.println(key);
          }
          else if(key=='*'){
              clearData();
            }                         //dit is niet logisch NOELLE DENK NA DOE DIT FF LOGISCHER
          else{
            //Serial.println("error: invoer groter dan password");
          }
      }
      else if(key == '#'){
          if(!strcmp(passdata,pass)){  //er is geen plek waar ze verschillend zijn
            openLock(3);               //activeer deurmagneet gedurende 3 seconden
          }
          else{
            //Serial.println("error: verkeerd password")
          }

          clearData();                  //ingevoerde code verwijderen uit array
      }
      else{
        //Serial.println("error: something went wrong");
      }
   }
}

void openLock(int timelapse){

  //timelapse = seconden dat deurmagneet activeert

  while(timelapse != 0){
    //testblock met onboard led
    digitalWrite(ledpin, HIGH);
    timelapse--;
    delay(1000);
  }

  digitalWrite(ledpin, LOW);   //deurmagneet weer deactiveren
  return;
}

//clearData functie haalt alle characters uit de passdata array en zet data_index weer op 0
void clearData(){
  while (data_index !=0){
    passdata[data_index--]=0;
  }
  return;
}

