// Version 1.5


#include "constants.h"
#include <avr/pgmspace.h>
#include "Lichtprogramme.h"

/*
** Nachfolgend: Hard core stuff. Nicht anfassen!
*/
#include "RecieverChannel.h"
#include "StateFromLeverUp.h"
#include "StateFromLeverDown.h"
#include "FlagState.h"
#include "Counter.h"
#include "StateFromButton.h"
#include "Led.h"
#include "PwmLed.h"
#include "SimPwmLed.h"
#include "NoopLed.h"


#define MAX_PROGRAMS 50
int modelStart = 0;
int programStarts[MAX_PROGRAMS];

Led* ledState[PIN_ANZAHL];

long frameStarted = 0;
int frame = -1;


//#define DEBUG_ON
#ifdef DEBUG_ON
#define DEBUG_INIT   Serial.begin(115200);
#define DEBUG(X)  Serial.println(X)
#else
#define DEBUG_INIT
#define DEBUG(X)
#endif

/************************************************************************************
*********************          Setup      *******************************************
************************************************************************************/

RecieverChannel *reciever = new RecieverChannel(SIG_PIN, RECIEVER_MIN, RECIEVER_MAX);
FlagState *powerState;
Counter *lightProgramSelect;

void setup() {
  DEBUG_INIT

  switchToSelectedModel();

  int programCount = setupProgramStarts();

  State *programSelectStateSource;
  State *powerStateSource;
  if (SWITCH_TYPE == 1) {
    programSelectStateSource = new StateFromLeverUp(reciever, ACTIVATE_PERIOD);
    powerStateSource = new StateFromLeverDown(reciever, ACTIVATE_PERIOD);
  }
  if (SWITCH_TYPE == 2) {
    programSelectStateSource = new StateFromButton(reciever, LESS_THAN, ACTIVATE_PERIOD);
    powerStateSource = new StateFromButton(reciever, GRATER_THAN, ACTIVATE_PERIOD);
  }
  lightProgramSelect = new Counter(programSelectStateSource, programCount);
  powerState = new FlagState(powerStateSource, START_WITH_LIGHT_ON);
  
  setupLedState();
  
  resetLedState();

  if (START_WITH_LIGHT_ON) {
    activateLightMashine();
  }
}




void switchToSelectedModel() {
  byte model = 0;
  bool selected = false;
  while (!selected && modelSelectPins[model] != NICHT_DA) {
    if (digitalRead(modelSelectPins[model]) == HIGH) {
      selected = true;
    } else {
      model++;
    }
  }
  
  // for model 0 there is nothing to do
  if (model == 1) {
    for (int  i = 0; i < PIN_ANZAHL; i++) {
      led_pin_mapping[i] = led_pin_mapping_2[i];
    }
  }
  if (model == 2) {
    for (int  i = 0; i < PIN_ANZAHL; i++) {
      led_pin_mapping[i] = led_pin_mapping_3[i];
    }  }
  if (model == 3) {
    for (int  i = 0; i < PIN_ANZAHL; i++) {
      led_pin_mapping[i] = led_pin_mapping_4[i];
    }  }
  if (model == 4) {
    for (int  i = 0; i < PIN_ANZAHL; i++) {
      led_pin_mapping[i] = led_pin_mapping_5[i];
    }
  }
  DEBUG("model " + String(model) + " selected");
  
  // set modelStart
  int currentModel = 0;
  int ledLine = 0;
  while (currentModel < model) {
    while (!endOfProgramChain(readLeds(ledLine,0))) {
      ledLine++;
    }
    if (readLeds(ledLine,0) == MODEL_WECHSEL) {
      currentModel++;
      ledLine++;
      DEBUG("model " + String(currentModel) + " starts at line " + String(ledLine));
    }
  }
  modelStart = ledLine;
}





void setupLedState() {
  for (int i = 0; i < PIN_ANZAHL; i++) {
    int pinNr = led_pin_mapping[i];
    if (pinNr == NICHT_DA
#ifdef DEBUG_ON
        // pins 0 and 1 are used for serial communication. so let them be.
        || pinNr < 2
#endif    
    ) {
      ledState[i] = new NoopLed(pinNr);
    } else {
      ledState[i] = new SimPwmLed(pinNr);
    }
  }
}



int setupProgramStarts() {
  // very first program
  int programCounter = 0;
  programStarts[programCounter] = modelStart;
  programCounter++;
  
  int i = modelStart;
  // all others
  while (!endOfProgramChain(readLeds(i,0))) {
    if (readLeds(i,0) == PROGRAM_ENDE) {
      if (!endOfProgramChain(readLeds(i+1,0))) {
        programStarts[programCounter] = i+1;
        programCounter++;
      }
    }
    i++;
  }
  
  return programCounter;
}



bool endOfProgramChain(byte ledValue) {
  return ledValue == FIN || ledValue == MODEL_WECHSEL;
}


















/************************************************************************************
*********************          Loop      *******************************************
************************************************************************************/



#define UPDATE_PERIOD 10
long counter = 0;
long lastTime = millis();
int iterationsToMatchUpdatePeriod = 1000;
int currentIterations = iterationsToMatchUpdatePeriod;
long lastUpdate = millis();
long globalNow = millis();
void loop() {
  counter++;
  currentIterations--;
  reciever->read();
  if (currentIterations == 0) {
    globalNow = millis();
    currentIterations = iterationsToMatchUpdatePeriod;

    if ((globalNow - lastTime) > 1000) {
      lastTime = globalNow;
      DEBUG(String(counter) + " ips, " + String(iterationsToMatchUpdatePeriod) + " iterations per update, update period = " + String(globalNow - lastUpdate));
      counter = 0;
    }

    long thisUpdateTook = globalNow - lastUpdate;
    if (thisUpdateTook > UPDATE_PERIOD) {
      iterationsToMatchUpdatePeriod-=100;
      if (iterationsToMatchUpdatePeriod <= 0) iterationsToMatchUpdatePeriod = 100;
    } else if (thisUpdateTook < UPDATE_PERIOD) {
      iterationsToMatchUpdatePeriod+=100;
    }
 
    lastUpdate = globalNow;

    powerState->read();
    lightProgramSelect->read();

    if (powerState->hasChanged()) {
      if (powerState->isOn()) {
        activateLightMashine();
      } else {
        deactivateLightMashine();
      }
    }
    
    if (lightProgramSelect->hasChanged()) {
      DEBUG("light program change " + String(lightProgramSelect->getCount()));
      frame = programStarts[lightProgramSelect->getCount()];
    }

    if (powerState->isOn()) {
      if (itIsTimeForNextFrame()) {
        nextFrame();
        copyFrameToLedState();
      }
    }
  }
  

  if (powerState->isOn()) {
    // update sw pwm leds
    updateLeds();
  }

}

void updateLeds() {
  for (int i = 0; i < PIN_ANZAHL; i++) {
    ledState[i]->update();
  }
}



void resetLedState() {
  // init ledState
  for (int i = 0; i < PIN_ANZAHL; i++) {
    ledState[i]->set(0);
  }
}



void activateLightMashine() {
  DEBUG("activate light mashine");
  lightProgramSelect->reset();
  frame = programStarts[lightProgramSelect->getCount()];
}



void deactivateLightMashine() {
  DEBUG("deactivate light mashine");
  resetLedState();
}



boolean itIsTimeForNextFrame() {
  long timeForNextFrame = frameStarted + FRAME_PAUSE;
  return globalNow >= timeForNextFrame;
}



void nextFrame() {
  frame++;
  if (readLeds(frame,0) == PROGRAM_ENDE) {
    frame = programStarts[lightProgramSelect->getCount()];
  }
  frameStarted = globalNow;
}



void copyFrameToLedState() {
  for (int i = 0; i < PIN_ANZAHL; i++) {
    ledState[i]->set(readLeds(frame,i));
  }
}



byte readLeds(int lineNr, int rowNr) {
  return pgm_read_byte_near(&(leds[lineNr][rowNr]));
}

