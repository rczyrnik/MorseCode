#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int buttonApin = 6;
int buttonBpin = 5;
int count = 0;
int i = 0;
int w = 0;
int my_Morse[5];
int len = 10;
char my_line[16];
int wait = 0;



void setup()
{
 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);

 // set up serial monitor
 Serial.begin(9600);

 // set up buttons
 pinMode(buttonApin, INPUT_PULLUP); 
}

void loop()
{
  // wait for a button press
  while (digitalRead(buttonApin) == HIGH) {
    delay(1);
  }
  
  // counts how long a button is pressed
  count = 0; 
  while (digitalRead(buttonApin) == LOW) {
    count = count + 1;
    delay(1);}
    
  // was that a dot, a dash, or an erase?
  if (count > 1000) {
      my_line[w] = ' ';
  } else if (count < 150 && count > 50) {
    my_Morse[i] = 1;
    i +=1;
  } else if (count > 50) {
    my_Morse[i] = 2; 
    i +=1;
  }
  //for(int j = 0; j < 5; j++) {Serial.print(my_Morse[j]);}
  
  wait = 0;
  while (digitalRead(buttonApin) == HIGH && wait <=500) {
    delay(1);
    wait += 1;

    if (wait > 500) {
        char letter = MorseTree(my_Morse);
        if (letter == '?') {
          //Serial.println("questionmark");
          w-=1;
          my_line[w] = ' ';
        } else {
          my_line[w] = letter;
          w++;
        }
        
        lcd.setCursor(0, 0);
        //Serial.print(letter);
        for(int j = 0; j < w; j++) {
          Serial.print(my_line[j]);
          
          lcd.print(my_line[j]);
        }
        
        Serial.println("");

        
        for(int j = 0; j < 5; j++) {my_Morse[j] = 0;}
        i = 0;
        
        } 
  }

} // END MAIN LOOP

// helper function to compare two arrays
boolean array_cmp(int *a, int *b, int len_a, int len_b){
     int n;

     // test each element to be the same. if not, return false
     for (n=0;n<len_a;n++) if (a[n]!=b[n]) return false;

     //ok, if we have not returned yet, they are equal :)
     return true;
}


// tree decode fn
char MorseTree(int string[]) {
  char letter = '?';  
  
  // starts with dot
  if (string[0] == 1) {
      if (string[1] == 1) {
          if (string[2] == 1) {
                if (string[3] == 1) {letter = 'h';} 
                else if (string[3] == 2) {letter = 'v';} 
                else {letter = 's';}
          } else if (string[2] == 2) {
                if (string[3] == 1) { letter = 'f'; }
                else if (string[3] == 2) {letter = '?';} 
                else {letter = 'u';}
          } else {letter = 'i';}
      
      } else if (string[1] == 2) {
          if (string[2] == 1) {
                if (string[3] == 1) {letter = 'l';} 
                else if (string[3] == 2) {letter = '!';} 
                else {letter = 'r';}
          } else if (string[2] == 2) {
                if (string[3] == 1) { letter = 'p'; }
                else if (string[3] == 2) {letter = 'j';} 
                else {letter = 'w';}
          } else {letter = 'a';}
      } else {letter = 'e';}
  } else if (string[0] == 2) {
      if (string[1] == 1) {
          if (string[2] == 1) {
                if (string[3] == 1) {letter = 'b';} 
                else if (string[3] == 2) {letter = 'x';} 
                else {letter = 'd';}
          } else if (string[2] == 2) {
                if (string[3] == 1) { letter = 'c'; }
                else if (string[3] == 2) {letter = 'y';} 
                else {letter = 'k';}
          } else {letter = 'n';}
      
      } else if (string[1] == 2) {
          if (string[2] == 1) {
                if (string[3] == 1) {letter = 'z';} 
                else if (string[3] == 2) {letter = 'q';} 
                else {letter = 'g';}
          } else if (string[2] == 2) {
                if (string[3] == 1) { letter = '?'; }
                else if (string[3] == 2) {letter = '?';} 
                else {letter = 'o';}
          } else {letter = 'm';}
      } else {letter = 't';}         
   // starts with zero
   } else {letter = ' ';}
   
  return letter;
}
