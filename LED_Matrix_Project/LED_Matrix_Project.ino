// Program to demonstrate the MD_Parola library
//
// Uses the Arduino Print Class extension with various output types
//
// MD_MAX72XX library can be found at https://github.com/MajicDesigns/MD_MAX72XX
//

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   18
#define DATA_PIN  23
#define CS_PIN     5

// Hardware SPI connection
MD_Parola ledDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup(void)
{
  ledDisplay.begin();
  ledDisplay.setIntensity(5);
}

void loop(void)
{
  for(int i = 0; i < 52; i++)
  {
    ledDisplay.write(letters[i]);
    delay(1000);
  }
}
