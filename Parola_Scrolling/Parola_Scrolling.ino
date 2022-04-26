// Use the Parola library to scroll text on the display
//
// Demonstrates the use of the scrolling function to display text received
// from the serial interface
//
// User can enter text on the serial monitor and this will display as a
// scrolling message on the display.
// Speed for the display is controlled by a pot on SPEED_IN analog in.
// Scrolling direction is controlled by a switch on DIRECTION_SET digital in.
// Invert ON/OFF is set by a switch on INVERT_SET digital in.
//
// UISwitch library can be found at https://github.com/MajicDesigns/MD_UISwitch
// MD_MAX72XX library can be found at https://github.com/MajicDesigns/MD_MAX72XX
//

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Parola_Fonts_data.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8

#define CLK_PIN   18
#define DATA_PIN  23
#define CS_PIN     5

// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

typedef struct
{
  char  name[10];
  MD_MAX72XX::fontType_t *pFont;
  textEffect_t effect;
  char pMsg[100];
} message_t;

uint8_t scrollSpeed = 40;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 500; // in milliseconds

// Global message buffers shared by Serial and Scrolling functions
char language[15][100] = 
{
  "Kabu da Nigeria", //Bassa Nge
  "Ola'le Nigeria", //Igala
  "Aooo Nigeria", //Ondo
  "Una Wekom to Naija", //Pidgin
  "Barka da zuma Nigeria", //Hausa
  "Alua Nigeria", //Ika
  "Anyaowa Nigeria", //Idoma
  "E kurabo hi ile Inaigiriya", //Yagba
  "Msugh da van ken Najeriya", //Tiv
  "Elua Nigeria", //Igbo (Bende)
  "Amedi Nigeria", //Ibibio
  "Awonke Nigeria", //Yakurr
  "Mbaa nyin kankrang njt" //Jju 
};
message_t M =
{
  "All", allFont, PA_SCROLL_LEFT, "Welcome to Nigeria"
};

void setup()
{
  P.begin();
  P.setFont(M.pFont);
  P.displayText(M.pMsg, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
}

void loop()
{
  if(P.displayAnimate())
  {
    static int i;
    P.setTextBuffer(M.pMsg);
    P.setTextEffect(M.effect, M.effect);
    P.displayReset();
    strcpy(M.pMsg,language[i%15]); 
    i++;   
  }
}

