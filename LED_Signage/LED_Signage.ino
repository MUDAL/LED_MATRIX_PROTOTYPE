// Use the Parola library to scroll text on the display
// Demonstrates the use of the scrolling function to display text
// MD_MAX72XX library can be found at https://github.com/MajicDesigns/MD_MAX72XX

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Parola_Fonts_data.h"

#define NUM_OF_LANG 50 //50 languages

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8
#define CLK_PIN   18
#define DATA_PIN  23
#define CS_PIN     5

// HARDWARE SPI
MD_Parola signage = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

typedef struct
{
  char name[10];
  MD_MAX72XX::fontType_t *pFont;
  textEffect_t effect;
  char pMsg[100];
} message_t;

uint8_t scrollSpeed = 70; // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_CENTER;
uint16_t scrollPause = 400; // in milliseconds
//Languages
static  char language[NUM_OF_LANG][100] = 
{
  "Welcome to Nigeria", //English
  "Kabu da Nigeria", //Bassa Nge
  "Ola'le Nigeria", //Igala
  "\x0FE k\x0E1\x0E0\x062\x0FF s\x0ED N\x0E0\x0ECj\x0EDr\x0ED\x0E0", //Yoruba
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
//Global message buffer  
message_t M =
{
  "All", customFont, PA_SCROLL_LEFT, ""
};

void setup()
{
  signage.begin();
  signage.setFont(M.pFont);
  signage.displayText(M.pMsg, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
}

void loop()
{
  if(signage.displayAnimate())
  {
    static int i;
    if(strcmp(language[i % NUM_OF_LANG],"") != 0)
    {
      signage.setTextBuffer(M.pMsg);
      signage.setTextEffect(M.effect,M.effect);
      signage.displayReset();
      strcpy(M.pMsg,language[i % NUM_OF_LANG]);  
      i++; 
    }
    else
    {//if no new language, restart display from first language
      i = 0;
    }  
  }
}

