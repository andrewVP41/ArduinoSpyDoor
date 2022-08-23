#include <Keypad.h>
#include <Servo.h>

Servo door;
int button = 10; // the secret button pin
int buttonState = 0; // the button press detector
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {  //define the symbols on the buttons of the keypads

  {'1','2','3','A'},

  {'4','5','6','B'},

  {'7','8','9','C'},

  {'*','0','#','D'}

};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //initialize an instance of class NewKeypad
int value = 0;
char customKey = 0;
int inc = 0; // number of incorrect tries
int buz = 12; // the buzzer pin that alerts for two incorrect tries
int PEye =A0;    //the analog pin the photo resistor is connected to
int PEValue=0; // the value for the photoeye that detects entry and shuts the door
int spy = 0; // counts the nummber spies entering the building
int lyst = 0;// counts the nummber analysts entering the building
int dr = 0;// counts the nummber directors entering the building
const int PotPin = A1;  // the potentiometer pin which shuts down and opens the agency i.e the additional feature
int PotValue = 0; // value read from the potentiometer
int openess = 0; // value for whether the agency is opened or closed

void setup() {
  door.attach(11);
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(PEye, INPUT); 

}

void loop() {

 PotValue = analogRead(PotPin);
 openess = map(PotValue, 0, 1023, 0, 11);
 if(openess == 0){
  clearScreen();
  Serial.println("Agency Closed");
  delay(1000);
 }
 else 
 { 
 buttonState = digitalRead(button);
 if ( buttonState == 1 ) {
    Serial.println("Welcome! Enter your pin!");
    delay(500); 
 }
  checkPCode();
  PEValue = analogRead(PEye);
  if(PEValue <= 100){
  door.write(0); 
  clearScreen();
  delay(500);
  }

 }
  
} 



void checkPCode(){
  customKey = customKeypad.getKey();   //check keypad for input

  if (customKey != NO_KEY)  //If any key is pressed
  {
    if ((customKey >= '0') && (customKey<='9'))  
    { 
      value = value*10;  
      value = value + customKey - '0';  
    }

    if(customKey =='#')

    {
      if(value == 700){
        Serial.println("Welcome Spy");
        door.write(180);
        spy = spy+1;
      } 
      
      if(value == 314) {
        Serial.println("Welcome Analyst");
        door.write(180);
        lyst = lyst+1;
      } 
      
      if(value == 161) {
        Serial.println("Welcome Director");
        door.write(180);
        dr = dr + 1;
      } 
      
      if((value != 700) && (value != 314) && (value != 161)) {
        Serial.println("Incorrect Attempt");
        inc = inc+1;
        if(inc % 2 == 0){
         tone(buz, 2000, 500); //after the second attempt print a message or sound an alarm for possible intruder
        }
      }
      
      Serial.println(value);
      value=0;  //reset value once it is printed
      Serial.print( "Spies : ");
      Serial.print( spy );
      Serial.print( " Analysts : ");
      Serial.print( lyst );
      Serial.print( " Directors : ");
      Serial.print( dr );
      Serial.print( " Incorrect :");
      Serial.println( inc );

    }

  } }


void clearScreen() {
  for(int i =0; i<= 20; i++){
    Serial.println(" ");
  }
}
  
