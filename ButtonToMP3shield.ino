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

//bindnd variabalele to a Analog pin.
#define B_TR1  A0
#define B_TR2  A1
#define B_TR3  A2

//Define "debounce" period for every input.
#define BUTTON_DEBOUNCE_PERIOD 20 //ms

SdFat sd;
vs1053 MP3player;

// bind the varabeles to the Bounce-libary
Bounce b_TR1  = Bounce();

Bounce b_TR2  = Bounce();

Bounce b_TR3  = Bounce();


 //Connect the variables to a soundfile.
int8_t TouchPad_1 = 0001;
int8_t TouchPad_2 = 0002;
int8_t TouchPad_3 = 0003;
int8_t TouchPad_4 = 0004;

//------------------------------------------------------------------------------
/**
 * \This is where the magic happens for the code to setup stuff
 */

 //Make sure the Serial Monitor is on 115200 Baud
void setup() {
  Serial.begin(115200);

//Define the input for every variabele.
  pinMode(B_TR1, INPUT_PULLUP);
  pinMode(B_TR2, INPUT_PULLUP);
  pinMode(B_TR3, INPUT_PULLUP);

//Connect the variables to the pin.
  //Attach button1 to pinmode TR1
  b_TR1.attach(B_TR1);
  b_TR1.interval(BUTTON_DEBOUNCE_PERIOD);

  //Attach button2 to pinmode TR2
  b_TR2.attach(B_TR2);
  b_TR2.interval(BUTTON_DEBOUNCE_PERIOD);

  //Attach button3 to pinmode TR3
  b_TR3.attach(B_TR3);
  b_TR3.interval(BUTTON_DEBOUNCE_PERIOD);

//debugging stuff
  if(!sd.begin(9, SPI_HALF_SPEED)) sd.initErrorHalt();
  if (!sd.chdir("/")) sd.errorHalt("sd.chdir");

//Call MP3 shield
  MP3player.begin();
  MP3player.setVolume(10,10);

  //Make sure the serial Monitor is ready for action.
  Serial.println(F("Looking for Buttons to be pressed..."));
}


//------------------------------------------------------------------------------
/**
 * \Loop to let everything work again after something is pressed.
 */
void loop() {

// refil buffer of MP3Shield
#if defined(USE_MP3_REFILL_MEANS) \
    && ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) \
    ||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled)      )

  MP3player.available();
#endif

//Setup every button + their functionalities in a if-loop. 
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




//We're no strangers to love
//You know the rules and so do I (do I)
//A full commitment's what I'm thinking of
//You wouldn't get this from any other guy
//I just wanna tell you how I'm feeling
//Gotta make you understand
//Never gonna give you up
//Never gonna let you down
//Never gonna run around and desert you
//Never gonna make you cry
//Never gonna say goodbye
//Never gonna tell a lie and hurt you
//We've known each other for so long
//Your heart's been aching, but you're too shy to say it (say it)
//Inside, we both know what's been going on (going on)
//We know the game and we're gonna play it
//And if you ask me how I'm feeling
//Don't tell me you're too blind to see
//Never gonna give you up
//Never gonna let you down
//Never gonna run around and desert you
//Never gonna make you cry
//Never gonna say goodbye
//Never gonna tell a lie and hurt you
//Never gonna give you up
//Never gonna let you down
//Never gonna run around and desert you
//Never gonna make you cry
//Never gonna say goodbye
//Never gonna tell a lie and hurt you
//We've known each other for so long
//Your heart's been aching, but you're too shy to say it (to say it)
//Inside, we both know what's been going on (going on)
//We know the game and we're gonna play it
//I just wanna tell you how I'm feeling
//Gotta make you understand
//Never gonna give you up
//Never gonna let you down
//Never gonna run around and desert you
//Never gonna make you cry
//Never gonna say goodbye
//Never gonna tell a lie and hurt you
//Never gonna give you up
//Never gonna let you down
//Never gonna run around and desert you
//Never gonna make you cry
//Never gonna say goodbye
//Never gonna tell a lie and hurt you
//Never gonna give you up
//Never gonna let you down
//Never gonna run around and desert you
//Never gonna make you cry
//Never gonna say goodbye
//Never gonna tell a lie and hurt you


}
