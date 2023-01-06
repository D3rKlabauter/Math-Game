/*
 * Math Game
 * 
 * Edwin Lang
 * 04.01.2023
*/

#include "Free_Fonts.h" // Include the header file attached to this sketch
#include "equations.h" // Include the 2nd header file attached to this sketch

#include "SPI.h"
#include "TFT_eSPI.h"

#define BUTTON_PIN 16

// counter
boolean trigger = true;
int counter = 0;

String state;

// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();

unsigned long drawTime = 0;

void setup(void) {

  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  tft.begin();
}

void loop() {

  // Set text datum to middle centre
  tft.setTextDatum(MC_DATUM);

  // Set text colour to white with black background
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  // rotate screen
  tft.setRotation(2);
  
  // Select the font
  tft.setFreeFont(FF8);                 

  
  // on counter change
  if (trigger == true){
    int index = int(random(0,8));
    
    // Clear screen
    tft.fillScreen(TFT_BLACK);            

    // get one equation out of the array
    String equation = equations[0][index];

    // format the String
    int index1 = equation.indexOf('\n');
    int index2 = equation.lastIndexOf('\n');
    int index3 = equation.length();

    // draw the String
    tft.drawString(equation.substring(0,index1), 120, 100, GFXFF);// Print the string name of the font
    tft.fillRect(0, 158, 240, 4, TFT_WHITE);
    tft.drawString(equation.substring(index2,index3), 120, 220, GFXFF);// Print the string name of the font
    
    // set the flags
    state = equations[1][index];
    trigger = false;
  }
  
  
  // push button pressed
  if (digitalRead(BUTTON_PIN) == LOW){
      if (state == "1"){
        tft.fillScreen(TFT_GREEN);
      }
      if (state == "0"){
        tft.fillScreen(TFT_BLUE);
      }
      
      delay(2000);
      trigger = true;
      counter = 0;
  }
  
  count();
  delay(20);
}

// slower counter for focus point
void count(){
  counter++;
  if (counter == 250){
    trigger = true;
    counter = 0;
    }
}


#ifndef LOAD_GLCD
//ERROR_Please_enable_LOAD_GLCD_in_User_Setup
#endif

#ifndef LOAD_GFXFF
//ERROR_Please_enable_LOAD_GFXFF_in_User_Setup!
#endif
