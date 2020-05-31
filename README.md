# MIDI-Lighting-Keyboard-XIAO  
This repository for like this video.  
https://www.youtube.com/watch?v=D2VWIVyrJ5M&feature=youtu.be  
 
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
 
 
4.[HARDWARE Wireing to LED (SK9822 or APA102)]  
 5V    with Capacitor 100uF is Better.  
 GND   
 MOSI is  10(XIAO)  
 CLK  is  8(XIAO)  
