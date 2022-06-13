/**
 * \file MP3ButtonPlayer2.ino
 *
 * \brief Example sketch of using the VS1053 Arduino driver using buttons,
 * with arduino recommended(simpler) debounce library
 * \remarks comments are implemented with Doxygen Markdown format
 *
 * \author Michael P. Flaga
 *
 * This sketch demonstrates the use of digital input pins used as buttons as 
 * NEXT, PLAY and STOP to control the tracks that are to be played.
 * Where PLAY or STOP will begin or cancel the stream of track000.mp3 through 
 * track999.mp3, as indexed by NEXT, begining with 0.

 * \note Use this example uses the bounce2 library to provide debouncing fuctions. Advocated by Arduino's website at http://playground.arduino.cc/code/bounce
 */

// libraries
#include <SPI.h>
#include <SdFat.h>
#include <vs1053_SdFat.h>
#include <Bounce2.h> 

/**
 * \breif Macro for the debounced NEXT pin, with pull-up
 */
#define B_TR1  A0

/**
 * \breif Macro for the debounced STOP pin, with pull-up
 */
#define B_TR2  A1

/**
 * \breif Macro for the debounced PLAY pin, with pull-up
 */
#define B_TR3  A2

/**
 * \breif Macro for the Debounce Period [milliseconds]
 */
#define BUTTON_DEBOUNCE_PERIOD 20 //ms

/**
 * \brief Object instancing the SdFat library.
 *
 * principal object for handling all SdCard functions.
 */
SdFat sd;

/**
 * \brief Object instancing the vs1053 library.
 *
 * principal object for handling all the attributes, members and functions for the library.
 */
vs1053 MP3player;

/**
 * \brief Object instancing the Next Button.
 */
Bounce b_TR1  = Bounce();

/**
 * \brief Object instancing the Stop Button library.
 */
Bounce b_TR2  = Bounce();

/**
 * \brief Object instancing the Play Button library.
 */
Bounce b_TR3  = Bounce();

/**
 * \brief Index of the current track playing.
 *
 * Value indicates current playing track, used to populate "x" for playing the 
 * filename of "track00x.mp3" for track000.mp3 through track254.mp3
 */
int8_t TouchPad_1 = 0001;
int8_t TouchPad_2 = 0002;
int8_t TouchPad_3 = 0003;
int8_t TouchPad_4 = 0004;

//------------------------------------------------------------------------------
/**
 * \brief Setup the Arduino Chip's feature for our use.
 *
 * After Arduino's kernel has booted initialize basic features for this
 * application, such as Serial port and MP3player objects with .begin.
 */
void setup() {
  Serial.begin(115200);

  pinMode(B_TR1, INPUT_PULLUP);
  pinMode(B_TR2, INPUT_PULLUP);
  pinMode(B_TR3, INPUT_PULLUP);

  //Attach button1 to pinmode TR1
  b_TR1.attach(B_TR1);
  b_TR1.interval(BUTTON_DEBOUNCE_PERIOD);

  //Attach button2 to pinmode TR2
  b_TR2.attach(B_TR2);
  b_TR2.interval(BUTTON_DEBOUNCE_PERIOD);

  //Attach button3 to pinmode TR3
  b_TR3.attach(B_TR3);
  b_TR3.interval(BUTTON_DEBOUNCE_PERIOD);

  if(!sd.begin(9, SPI_HALF_SPEED)) sd.initErrorHalt();
  if (!sd.chdir("/")) sd.errorHalt("sd.chdir");

  MP3player.begin();
  MP3player.setVolume(10,10);
  
  Serial.println(F("Looking for Buttons to be depressed..."));
}


//------------------------------------------------------------------------------
/**
 * \brief Main Loop the Arduino Chip
 *
 * This is called at the end of Arduino kernel's main loop before recycling.
 * And is where the user's is executed.
 *
 * \note If the means of refilling is not interrupt based then the
 * MP3player object is serviced with the availaible function.
 */
void loop() {

// Below is only needed if not interrupt driven. Safe to remove if not using.
#if defined(USE_MP3_REFILL_MEANS) \
    && ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) \
    ||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled)      )

  MP3player.available();
#endif

//Knop 1
  if (b_TR1.update()) {
    if (b_TR1.read() == LOW)  {
      Serial.print(F("B_PLAY pressed, Start Playing Track # "));
      Serial.println(TouchPad_3);
      MP3player.playTrack(TouchPad_3);
      delay(99);
      MP3player.stopTrack();
    }
  }

//Knop 2
  if (b_TR2.update()) {
    if (b_TR2.read() == LOW)  {
      Serial.print(F("B_PLAY pressed, Start Playing Track # "));
      Serial.println(TouchPad_2);
      MP3player.playTrack(TouchPad_2);
      delay(99);
      MP3player.stopTrack();
    }
  }

//Knop 3
    if (b_TR3.update()) {
    if (b_TR3.read() == LOW)  {
      Serial.print(F("B_PLAY pressed, Start Playing Track # "));
      Serial.println(TouchPad_2);
      MP3player.playTrack(TouchPad_2);
      delay(99);
      MP3player.stopTrack();
    }
  }




   //Do something. Have fun with it.

}
