/* -----------------------------------------------------------------------------
[MIDI Lighting Keyboard Project.]
Kotohiro Masuda. 2020/4/23
-----------------------------------------------------------------------------*/
/*
1.[Board setting]
File ->>> Enviroment ->>> add URL
https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

 [Tool ->>> Setting] 
Board : Seed Studio XIAO
USB stack : Arduino
Debug:off

2.[Library Install]
FastLED 3.3.3 "5kft" fork.
Tools -> Library manager.
https://github.com/5kft/FastLED/tree/platform-xiao

Arduiono MIDI 5.0
Tools -> Library manager.
https://github.com/FortySevenEffects/arduino_midi_library

Arduino USB-MIDI
Tools -> Library manager.
https://github.com/lathoub/Arduino-USBMIDI

MIDIUSB
Tools -> Library manager.
https://github.com/arduino-libraries/MIDIUSB

3.[Over write "buffer memory" & "RunningStatus" setting.]
 
 "midi_Settings.h" over write or  USE static  const
 -> static const unsigned SysExMaxSize = 10240;
 -> static const bool UseRunningStatus = true;


4.[HARDWARE Wireing to LED(APA102)]
 5V    with Capacitor 100uF is Better.
 GND   
 MOSI is  10
 CLK  is  8

-----------------------------------------------------------------------------*/
#include <USB-MIDI.h>
static  const  unsigned SysExMaxSize = 1024*28 ;  //1024*24K
static  const  bool UseRunningStatus = true ; 
USBMIDI_CREATE_DEFAULT_INSTANCE();

int FastLEDSet_Ch[128];          // Map of Who(channel) use LED?
int octave_shift= 2 *12;           // Shift Octave, if few LEDs. "1"octave=12LEDs.
int Reverse = 127+5 ;

// -----------------------------------------------------------------------------
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 128
#define DATA_PIN 10
#define CLOCK_PIN 8
#define BRIGHTNESS 24

// Define the array of leds
CRGB leds[NUM_LEDS];

int delayval = 2; // delay for test

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------
// LED Blink control. 

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  if (velocity == 0) {  // 　Note ON "Velocity = 0" is NOTE Off.
    leds[pitch].setRGB( 0, 0, 0);
  } else {
    switch (channel) {  //  Select Ch       //　Blink velocity power!
      case 1:
        leds[Reverse-pitch-octave_shift] = CRGB::Green;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=1;
        break;
      case 2:
        leds[Reverse-pitch-octave_shift] = CRGB::Blue;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=2;
        break;
      case 3:
        leds[Reverse-pitch-octave_shift] = CRGB::Red;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=3;
        break;
      case 4:
        leds[Reverse-pitch-octave_shift] = CRGB::Yellow;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=4;
        break;
      case 5:
        leds[Reverse-pitch-octave_shift] = CRGB::Orange;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=5;
        break;
      case 6:
        leds[Reverse-pitch-octave_shift] = CRGB::Fuchsia;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=6;
        break;
      case 7:
        leds[Reverse-pitch-octave_shift] = CRGB::DeepSkyBlue;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=7;
        break;
      case 8:
        leds[Reverse-pitch-octave_shift] = CRGB::MistyRose;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=8;
        break; 
      case 9:
        leds[Reverse-pitch-octave_shift] = CRGB::GreenYellow;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=9;
        break;
      case 10:
        leds[Reverse-pitch-octave_shift] = CRGB::DarkBlue;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=10;
        break;
      case 11:
        leds[Reverse-pitch-octave_shift] = CRGB::Cyan;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=11;
        break;
      case 12:
        leds[Reverse-pitch-octave_shift] = CRGB::LightCoral;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=12;
        break;
      case 13:
        leds[Reverse-pitch-octave_shift] = CRGB::Purple;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=13;
        break;
      case 14:
        leds[Reverse-pitch-octave_shift] = CRGB::FireBrick;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=14;
        break;
      case 15:
        leds[Reverse-pitch-octave_shift] = CRGB::DeepSkyBlue;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=15;
        break;
      case 16:
        leds[Reverse-pitch-octave_shift] = CRGB::WhiteSmoke;
        FastLEDSet_Ch[Reverse-pitch-octave_shift]=16;
        break;        
    }

  }
      FastLED.show();
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  switch (channel) {
    case 1: 
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
      leds[Reverse-pitch-octave_shift].setRGB( 0, 0, 0); FastLEDSet_Ch[Reverse-pitch-octave_shift]=0;
      FastLED.show();
      break;
  }
}

void handleControlChange(byte channel , byte number , byte value )
{

  switch (number) {
    case 120: for(int i=0;i<NUM_LEDS;i++){leds[i].setRGB( 0, 0, 0);}  break;  // 120 is All sound Off      : All LED OFF
    case 121: for(int i=0;i<NUM_LEDS;i++){leds[i].setRGB( 0, 0, 0);}  break;  // 121 Reset All controller  : All LED OFF
    case 123: for(int i=0;i<NUM_LEDS;i++){leds[i].setRGB( 0, 0, 0);}  break;  // 123 All Note Off         : All LED OFF
   }
  
  FastLED.show();  
}


// -----------------------------------------------------------------------------

void setup()
{

    // -----------------------------------------------------------------------------
    // UsehandleNoteOn Handler with MIDI Library ,after NoteOn Call Back Handler
    MIDI.setHandleNoteOn(handleNoteOn);  //argument is Handler [function].

    // Use NoteOff Handler
    MIDI.setHandleNoteOff(handleNoteOff);

    // Use ControlChange Handler
    MIDI.setHandleControlChange(handleControlChange);

    // All Ch read with MIDI instance initialize.
    MIDI.begin(MIDI_CHANNEL_OMNI);
    // -----------------------------------------------------------------------------

    
    //LED test All On! after OFF
    FastLED.setBrightness (BRIGHTNESS);
    // -----------------------------------------------------------------------------
    FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    //FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS); 
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 10, 0, 0);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }

    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 0, 10, 0);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }
               
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 0, 0, 10);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }
            
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot].setRGB( 0, 0, 0);
            FastLED.show();
            // clear this led for the next time around the loop
            delay(delayval); // Delay for a period of time (in milliseconds).
            }

}


void loop()
{
    MIDI.read();    
}
