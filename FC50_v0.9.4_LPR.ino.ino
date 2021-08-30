/* 
PC Mode: 1e keer programchange, daarna taptempo
CC_Mode: LEDS reageren
LPR_MODE: Led 6 en 7 branden: Led feedback voor Record e.d.?
SONG_MODE: Sw 7 en 8 starten Song Mode.



*/

#include <Bounce.h>

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
const int latchPin = 0;
const int clockPin = 12;
const int dataPin = 1;
const int Led1 = 19;
const int Led2 = 20;
const int Led3 = 21;
const int Led4 = 22;
const int Led5 = 23;
const int Led6 = 24;
const int Led7 = 25;

const int NUM_OF_BUTTONS = 10;
const int debnc_tm = 5;
int KNOB1waarde;
int KNOB2waarde;
int KNOB3waarde;
int KNOB4waarde;
int lastAnalogValue1;
int lastAnalogValue2;
int lastAnalogValue3;
int lastAnalogValue4;
int cc1;
int cc2;
int cc3;
int cc4;
const int midich = 1;
int bank_sel;
int double1;
int double2;
int double3;
int double4;
int double5;
int double6;
int double7;
int double8;
int disp[21] = {0b00000011, 0b11110011, 0b00100101, 0b01100001, 0b11010001, 0b01001001, 0b00001001, 0b11100011, 0b00000001, 0b01000001, 0b00000010, 0b11110010, 0b00100100, 0b01100000, 0b11010000, 0b01001000, 0b00001000, 0b11100010, 0b00000000, 0b01000000, 0b00011111};
int bankterm;
int songterm;
int led_cc[7] = {1, 1, 1, 1, 1, 0, 1};
int led_pc[7] = {0, 1, 1, 1, 1, 1, 0};
int led_song[7] = {1, 1, 1, 1, 1, 1, 1};
int led_lpr[7] = {1, 1, 1, 1, 1, 0, 1};
int last_pdl[] = {99,99};
int last_pdl_song[] = {99,99};

int lastbank;
int lastsong;

Bounce sw1 = Bounce(2, debnc_tm);
Bounce sw2 = Bounce(3, debnc_tm);
Bounce sw3 = Bounce(4, debnc_tm);
Bounce sw4 = Bounce(5, debnc_tm);
Bounce sw5 = Bounce(6, debnc_tm);
Bounce sw6 = Bounce(7, debnc_tm);
Bounce sw7 = Bounce(8, debnc_tm);
Bounce sw8 = Bounce(9, debnc_tm);
Bounce sw9 = Bounce(10, 10);
Bounce sw10 = Bounce(11, debnc_tm);

const int MIDI_MODE_PC = 0;
const int MIDI_MODE_CC = 1;
const int MIDI_MODE_SONG = 2;
const int MIDI_MODE_LPR = 3;

//Variable that stores the current MIDI mode of the device (what type of messages the push buttons send).
int midivar = MIDI_MODE_PC;
int midivar_last_status = MIDI_MODE_PC;
int bank = 1;
int song = 11;

// Switch 6 functions as a toggleswitch, short press toggles between CC and PC mode. Long press toggles Looper, short press toggles back to last state (PC or CC)
long buttonTimer = 0;
unsigned long timeElapsed;
boolean buttonActive = false;

void setup() 
{ 
Serial.begin(115200);
usbMIDI.setHandleControlChange(OnControlChange);
  //MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
  // Setup the first button with an internal pull-up :
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode (latchPin, OUTPUT);
  pinMode (clockPin, OUTPUT);
  pinMode (dataPin, OUTPUT);
  pinMode (Led1, OUTPUT);
  pinMode (Led2, OUTPUT);
  pinMode (Led3, OUTPUT);
  pinMode (Led4, OUTPUT);
  pinMode (Led5, OUTPUT);
  pinMode (Led6, OUTPUT);
  pinMode (Led7, OUTPUT);
  
  }

void loop(){

  usbMIDI.read(); // USB MIDI receive


  KNOB1waarde = analogRead(14); //knop 1 uitlezen
  //Serial.print(KNOB1waarde);
  //delay(1000)
  cc1 = map(KNOB1waarde, 1, 1014, 0, 127);  
 if (abs(lastAnalogValue1 - cc1)>1) {
    usbMIDI.sendControlChange(76,cc1,midich);}
    //update lastAnalogValue variable
    lastAnalogValue1 = cc1; 

     KNOB2waarde = analogRead(15); //knop 1 uitlezen
  //Serial.print(KNOB1waarde);
  //delay(1000)
  cc2 = map(KNOB2waarde, 1, 1014, 0, 127);  
 if (abs(lastAnalogValue2 - cc2)>1) {
    usbMIDI.sendControlChange(77,cc2,midich);}
    //update lastAnalogValue variable
    lastAnalogValue2 = cc2; 

     KNOB3waarde = analogRead(16); //knop 1 uitlezen
  //Serial.print(KNOB1waarde);
  //delay(1000)
  cc3 = map(KNOB3waarde, 1, 1014, 0, 127);  
 if (abs(lastAnalogValue3 - cc3)>1) {
    usbMIDI.sendControlChange(78,cc3,midich);}
    //update lastAnalogValue variable
    lastAnalogValue3 = cc3; 

     KNOB4waarde = analogRead(17); //knop 1 uitlezen
  //Serial.print(KNOB1waarde);
  //delay(1000)
  cc4 = map(KNOB4waarde, 1, 1014, 0, 127);  
 if (abs(lastAnalogValue4 - cc4)>1) {
    usbMIDI.sendControlChange(79,cc4,midich);}
    //update lastAnalogValue variable
    lastAnalogValue4 = cc4; 
    
  delay (20);

  sw1.update();
  sw2.update();
  sw3.update();
  sw4.update();
  sw5.update();
  sw6.update();
  sw7.update();
  sw8.update();
  sw9.update();
  sw10.update();
 
 
 

  
    if(sw1.fallingEdge()) {
      double1 = HIGH;
     
      if (midivar == MIDI_MODE_PC) {
        
       if (last_pdl[0] == bank && last_pdl[1] == 1)  {// denk aan array!!!
            usbMIDI.sendControlChange (60, 127, midich);}
          else {
            usbMIDI.sendProgramChange ((bank*5-5), midich);
            last_pdl[1] = 1;
            last_pdl[0] = bank;
            }
    } 
     else if (midivar == MIDI_MODE_CC) {
       usbMIDI.sendControlChange (70, 127, midich); }
     else if (midivar == MIDI_MODE_SONG) {
       last_pdl_song[1] = 1;
       last_pdl_song[0] = song;
       usbMIDI.sendNoteOn ((song*5-5), 127, 16);}
     else if (midivar == MIDI_MODE_LPR) {
      usbMIDI. sendControlChange (11, 127, 2);}
     
    } 

    if(sw1.risingEdge()) {
      double1 = LOW;
      if (midivar == MIDI_MODE_PC){
       ;}
       else if (midivar == MIDI_MODE_CC){
      usbMIDI.sendControlChange (70, 0, midich);}
      else if (midivar == MIDI_MODE_SONG) {
       usbMIDI.sendNoteOn ((song*5-5), 0, 16);}
       else if (midivar == MIDI_MODE_LPR) {
      usbMIDI. sendControlChange (11, 0, 2);}
    }

    if(sw2.fallingEdge()) {
      double2 = HIGH;
     
      if (midivar == MIDI_MODE_PC) {
       
       if (last_pdl[0] == bank && last_pdl[1] == 2) {
            usbMIDI.sendControlChange (60, 127, midich); 
           }
          else  {
            usbMIDI.sendProgramChange ((bank*5-4), midich);
             last_pdl[1] = 2;
             last_pdl[0] = bank;
            } 
      }
       else if (midivar == MIDI_MODE_CC){
       usbMIDI.sendControlChange (71, 127, midich);}
       else if (midivar == MIDI_MODE_SONG) {
       last_pdl_song[1] = 2;
       last_pdl_song[0] = song;
       usbMIDI.sendNoteOn ((song*5-4), 127, 16);}
       else if (midivar == MIDI_MODE_LPR) {
      usbMIDI. sendControlChange (12, 127, 2);}
    }

    if(sw2.risingEdge()) {
      double2 = LOW;
      if (midivar == MIDI_MODE_PC)
       ;
       else if (midivar == MIDI_MODE_CC) {
      usbMIDI.sendControlChange (71, 0, midich);}
      else if (midivar == MIDI_MODE_SONG) {
       usbMIDI.sendNoteOn ((song*5-4), 0, 16);}
       else if (midivar == MIDI_MODE_LPR) {
      usbMIDI. sendControlChange (12, 0, 2);}
      
    }
    
    if(sw3.fallingEdge()) {
      
      if (midivar == MIDI_MODE_PC){
       
       if (last_pdl[0] == bank && last_pdl[1] == 3)  {
          usbMIDI.sendControlChange (60, 127, midich); 
            }
          else  {
            usbMIDI.sendProgramChange ((bank*5-3), midich);
            last_pdl[1] = 3;
            last_pdl[0] = bank;
            } 
      }
       else if (midivar == MIDI_MODE_CC) {
       usbMIDI.sendControlChange (72, 127, midich);}
       else if (midivar == MIDI_MODE_SONG) {
       last_pdl_song[1] = 3;
       last_pdl_song[0] = song;
       usbMIDI.sendNoteOn ((song*5-3), 127, 16);}
       else if (midivar == MIDI_MODE_LPR) {
      usbMIDI. sendControlChange (13, 127, 2);}
    }

    if(sw3.risingEdge()) {
      if (midivar == MIDI_MODE_PC)
       ;
      else if (midivar == MIDI_MODE_CC) {
      usbMIDI.sendControlChange (72, 0, midich);}
      else if (midivar == MIDI_MODE_SONG) {
       usbMIDI.sendNoteOn ((song*5-3), 0, 16);}
       else if (midivar == MIDI_MODE_LPR) {
      usbMIDI. sendControlChange (13, 0, 2);}
      
    }
    if(sw4.fallingEdge()) {
      
      if (midivar == MIDI_MODE_PC) {
       
       if (last_pdl[0] == bank && last_pdl[1] == 4) {
         usbMIDI.sendControlChange (60, 127, midich); }    
          else  {
            usbMIDI.sendProgramChange ((bank*5-2), midich);
            last_pdl[0] = bank;
            last_pdl[1] = 4;
            }
          }
            
      
       else if (midivar == MIDI_MODE_CC) {
       usbMIDI.sendControlChange (73, 127, midich);}
       else if (midivar == MIDI_MODE_SONG) {
       last_pdl_song[1] = 4;
       last_pdl_song[0] = song;
       usbMIDI.sendNoteOn ((song*5-2), 127, 16);}
       else if (midivar == MIDI_MODE_LPR) {
      usbMIDI. sendControlChange (14, 127, 2);}
    }
    

    if(sw4.risingEdge()) {
      if (midivar == MIDI_MODE_PC)
       ;
       else if (midivar == MIDI_MODE_CC){
      usbMIDI.sendControlChange (73, 0, midich);}
      else if (midivar == MIDI_MODE_SONG) {
       usbMIDI.sendNoteOn ((song*5-2), 0, 16);}
       else if (midivar == MIDI_MODE_LPR) {
      usbMIDI. sendControlChange (14, 0, 2);}
    }
    
    if(sw5.fallingEdge()) {
     
      if (midivar == MIDI_MODE_PC) {
       
       if (last_pdl[0] == bank && last_pdl[1] == 5)  {
             usbMIDI.sendControlChange (60, 127, midich); }
          else  {
            usbMIDI.sendProgramChange ((bank*5-1), midich);
            last_pdl[0] = bank;
            last_pdl[1] = 5;
            }
            }
       else if (midivar == MIDI_MODE_CC){
       usbMIDI.sendControlChange (74, 127, midich);}
       else if (midivar == MIDI_MODE_SONG) {
       last_pdl_song[1] = 5;
       last_pdl_song[0] = song;
       usbMIDI.sendNoteOn ((song*5-1), 127, 16);}
       else if (midivar == MIDI_MODE_LPR) {
      usbMIDI. sendControlChange (15, 127, 2);}
    }

    if(sw5.risingEdge()) {
      if (midivar == MIDI_MODE_PC)
       ;
       else if (midivar == MIDI_MODE_CC){
      usbMIDI.sendControlChange (74, 0, midich);}
      else if (midivar == MIDI_MODE_SONG) {
       usbMIDI.sendNoteOn ((song*5-1), 0, 16);}
       else if (midivar == MIDI_MODE_LPR) {
      usbMIDI. sendControlChange (15, 0, 2);}
    }
    
    if(sw6.fallingEdge()) {  
      buttonTimer = millis();
      buttonActive = true;
     
            if (midivar == MIDI_MODE_CC){
            midivar = MIDI_MODE_PC;
            midivar_last_status = midivar;}
            else if (midivar == MIDI_MODE_PC){
            midivar = MIDI_MODE_CC;
            midivar_last_status = midivar;}
            else if (midivar == MIDI_MODE_SONG){ 
              song = song +1;
              if (song >19)
              song=11;
              led_song[0] = 1;
              led_song[1] = 1;
              led_song[2] = 1;
              led_song[3] = 1;
              led_song[4] = 1;
              }
             else if (midivar == MIDI_MODE_LPR) {
              midivar = MIDI_MODE_PC;
              midivar_last_status = midivar;}
             }
              
            
      
    
    if(sw6.risingEdge()) {                           //Toggle Switch
    buttonActive = false;
    }

    
    timeElapsed = millis() - buttonTimer;
    if (timeElapsed >350 && buttonActive == true) {
    midivar = MIDI_MODE_LPR;
  
      }
    if(sw7.fallingEdge()) {
      double7 = HIGH;
    }

    if(sw7.risingEdge()) {
      double7 = LOW;
      if (midivar != MIDI_MODE_SONG) {
      lastbank = bank;
      bank = bank + 1;
       if (bank > 9)
        bank = 1;}
      else {
      lastsong = song;
        song = song +1;
        if (song >19)
        song=11;
      }
        
    }
    if(sw8.fallingEdge()) {
       double8 = HIGH;
       
    }

    if(sw8.risingEdge()) {
      double8 = LOW;
      if (midivar != MIDI_MODE_SONG) {
      bank = bank - 1 ;
       if (bank < 1) 
        bank = 9;}
      else {
        song = song -1 ;
        if (song < 11)
        song = 19;}
      }

    
    if(sw9.fallingEdge()) {
       usbMIDI.sendControlChange (75, 127, midich);
    }

    if(sw9.risingEdge()) {
      usbMIDI.sendControlChange (75, 0, midich);
    }
    if(sw10.fallingEdge()) {
       usbMIDI.sendControlChange (64, 127, midich);
    }

    if(sw10.risingEdge()) {
      usbMIDI.sendControlChange (64, 0, midich);
    }

/*int type, cc, val, channel, d1, d2;
if (MIDI.read()) {                    // Is there a MIDI message incoming ?
    byte type = MIDI.getType();
    switch (type) {
      case ControlChange:
        cc = MIDI.getData1();
        val = MIDI.getData2();
        channel = MIDI.getChannel();
        if ( val > 0) {
          if (cc = 70) {led_cc[0] = 1}; 
          else if (cc = 71) {led_cc[1] = 1}; 
          else if (cc = 72) {led_cc[2] = 1}; 
          else if (cc = 73) {led_cc[3] = 1}; 
          else if (cc = 74) {led_cc[4] = 1}; 
          else if (cc = 75) {led_cc[5] = 1};
        }
        else
          if (cc = 70) {led_cc[0] = 0}; 
          else if (cc = 71) {led_cc[1] = 0}; 
          else if (cc = 72) {led_cc[2] = 0}; 
          else if (cc = 73) {led_cc[3] = 0}; 
          else if (cc = 74) {led_cc[4] = 0}; 
          else if (cc = 75) {led_cc[5] = 0};
        
        
  
}


*/
if (midivar == MIDI_MODE_PC) { 
    if (bank != last_pdl[0]) { 
        led_pc[0] = 1;
        led_pc[1] = 1;
        led_pc[2] = 1;
        led_pc[3] = 1;
        led_pc[4] = 1;  }
    else {
       if (last_pdl[1]== 1) {      
       led_pc[0] = 0;
       led_pc[1] = 1;
       led_pc[2] = 1;
       led_pc[3] = 1;
       led_pc[4] = 1;  }
       else if (last_pdl[1]== 2) {      
       led_pc[0] = 1;
       led_pc[1] = 0;
       led_pc[2] = 1;
       led_pc[3] = 1;
       led_pc[4] = 1;  }
       else if (last_pdl[1]== 3) {      
       led_pc[0] = 1;
       led_pc[1] = 1;
       led_pc[2] = 0;
       led_pc[3] = 1;
       led_pc[4] = 1;  }
       else if (last_pdl[1]== 4) {      
       led_pc[0] = 1;
       led_pc[1] = 1;
       led_pc[2] = 1;
       led_pc[3] = 0;
       led_pc[4] = 1;  }
       else if (last_pdl[1]== 5) {      
       led_pc[0] = 1;
       led_pc[1] = 1;
       led_pc[2] = 1;
       led_pc[3] = 1;
       led_pc[4] = 0;  }
     }
    } 
    else if (midivar == MIDI_MODE_SONG){
      if (song != last_pdl_song[0]) { 
        led_song[0] = 1;
        led_song[1] = 1;
        led_song[2] = 1;
        led_song[3] = 1;
        led_song[4] = 1;  }
    else {
       if (last_pdl_song[1]== 1) {      
       led_song[0] = 0;
       led_song[1] = 1;
       led_song[2] = 1;
       led_song[3] = 1;
       led_song[4] = 1;  }
       else if (last_pdl_song[1]== 2) {      
       led_song[0] = 1;
       led_song[1] = 0;
       led_song[2] = 1;
       led_song[3] = 1;
       led_song[4] = 1;  }
       else if (last_pdl_song[1]== 3) {      
       led_song[0] = 1;
       led_song[1] = 1;
       led_song[2] = 0;
       led_song[3] = 1;
       led_song[4] = 1;  }
       else if (last_pdl_song[1]== 4) {      
       led_song[0] = 1;
       led_song[1] = 1;
       led_song[2] = 1;
       led_song[3] = 0;
       led_song[4] = 1;  }
       else if (last_pdl_song[1]== 5) {      
       led_song[0] = 1;
       led_song[1] = 1;
       led_song[2] = 1;
       led_song[3] = 1;
       led_song[4] = 0;  }
     }
    } 
    else if (midivar == MIDI_MODE_LPR) {
       led_lpr[0] = 1;
       led_lpr[1] = 1;
       led_lpr[2] = 1;
       led_lpr[3] = 1;
       led_lpr[4] = 1;
       led_lpr[5] = 0;
       led_lpr[6] = 0;
       
    }
    
  




if (double7 == HIGH && double8 == HIGH){
    if (midivar != MIDI_MODE_SONG){
    midivar_last_status = midivar;  
    midivar = MIDI_MODE_SONG;
    digitalWrite (latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST,disp[song]);
    digitalWrite (latchPin, HIGH); 
    delay (250);}
    else if (midivar == MIDI_MODE_SONG){
    midivar = midivar_last_status;
    digitalWrite (latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST,disp[bank]);
    digitalWrite (latchPin, HIGH);
    delay(250);
    }
}


if (midivar == MIDI_MODE_PC) {    
    //if (bankterm != bank) {
      bankterm = bank;
      digitalWrite (latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST,disp[bank]);
      digitalWrite (latchPin, HIGH);
      //}
    }
else if (midivar == MIDI_MODE_CC){    
    if (bankterm != bank) {
      bankterm = bank;
      digitalWrite (latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST,disp[bank]);
      digitalWrite (latchPin, HIGH);
      }
    }
else if (midivar == MIDI_MODE_SONG) {
    if (songterm != song) {
      songterm = song;
      digitalWrite (latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST,disp[song]);
      digitalWrite (latchPin, HIGH);
    }
}
else if (midivar == MIDI_MODE_LPR) {
      digitalWrite (latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST,disp[20]);
      digitalWrite (latchPin, HIGH);
    }



    
  



if (midivar == MIDI_MODE_CC) {
 digitalWrite(Led1, led_cc[0]);
 digitalWrite(Led2, led_cc[1]);
 digitalWrite(Led3, led_cc[2]);
 digitalWrite(Led4, led_cc[3]);
 digitalWrite(Led5, led_cc[4]);
 digitalWrite(Led6, led_cc[5]);
 digitalWrite(Led7, led_cc[6]); 
}
else if (midivar == MIDI_MODE_PC) {
 digitalWrite(Led1, led_pc[0]);
 digitalWrite(Led2, led_pc[1]);
 digitalWrite(Led3, led_pc[2]);
 digitalWrite(Led4, led_pc[3]);
 digitalWrite(Led5, led_pc[4]);
 digitalWrite(Led6, led_pc[5]);
 digitalWrite(Led7, led_pc[6]); 
}
else if (midivar == MIDI_MODE_SONG) {
 digitalWrite(Led1, led_song[0]);
 digitalWrite(Led2, led_song[1]);
 digitalWrite(Led3, led_song[2]);
 digitalWrite(Led4, led_song[3]);
 digitalWrite(Led5, led_song[4]);
 digitalWrite(Led6, led_song[5]);
 digitalWrite(Led7, led_song[6]); 
}
else if (midivar == MIDI_MODE_LPR) {
 digitalWrite(Led1, led_lpr[0]);
 digitalWrite(Led2, led_lpr[1]);
 digitalWrite(Led3, led_lpr[2]);
 digitalWrite(Led4, led_lpr[3]);
 digitalWrite(Led5, led_lpr[4]);
 digitalWrite(Led6, led_lpr[5]);
 digitalWrite(Led7, led_lpr[6]); 
}
 
}  







void OnControlChange(byte channel, byte cc, byte value) {
if (value > 63) {
  if (cc==70) {
      led_cc[0]=0;
      }  
   else if (cc==71) {
      led_cc[1]=0;
      }  
    else if (cc==72) {
      led_cc[2]=0;
      }  
     else if (cc==73) {
      led_cc[3]=0;
      }
     else if (cc==74) {
      led_cc[4]=0;
      }
      else if (cc==11) {
      led_lpr[0]=0;
      }
            
      }
   else if (value < 64) {
    if (cc==70) {
      led_cc[0]=1;
      }  
   else if (cc==71) {
      led_cc[1]=1;
      }  
    else if (cc==72) {
      led_cc[2]=1;
      }  
     else if (cc==73) {
      led_cc[3]=1;
      }
     else if (cc==74) {
      led_cc[4]=1;
      }
      else if (cc==11) {
      led_lpr[0]=1;
      }
      
}
  
  
  
}



  
 



