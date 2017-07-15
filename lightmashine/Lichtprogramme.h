#include "Arduino.h"

/*
** Grundeinstellungen
*/

// gibt an ob der Arduino sofort mit dem ersten
// Lichtprogramm loslegt, oder erst auf den
// Einschaltbefehl wartet.
// true - sofort loslegen
// false - warten
#define START_WITH_LIGHT_ON true

// Anzahl der Pins, die am Arduino angesteuert werden sollen.
// Davon haengt die Anzahl Werte ab, die man bei den Lichtprogrammen
// in der horizontalen angegeben werden.
#define PIN_ANZAHL 14

// Pause zwischen der Frames in Millisekunden. Je kleiner, desto schneller.
#define FRAME_PAUSE 100

// Von links nach rechts platziert man sich sich
// die LEDs, zum bequemen LED-Programm bauen spaeter.
// an die jeweilige Position kommt die Pin-Nummer
// an der die LED angeschlossen ist.
byte led_pin_mapping[PIN_ANZAHL] =
// Vorne links      Vorne rechts   Hinten Links    Hinten Rechts
// 
// B  B  w  w       w  w  B  B     A  B  I           I  B  A
// l  l  e  e       e  e  l  l     u  l  n           n  l  u
// i  a  i  i       i  i  a  i     s  i  n           n  i  s
// n  u  s  s       s  s  u  n     s  n  e           e  n  s
// k     s  s       s  s     k     e  k  n           n  k  e
// e                         e     n  e                 e  n
// r                         r        r                 r
 { 0, 1, 2, 3,      4, 5, 6, 7,    8, 9,10,         11,12,13,};


// Licht-Programme
const byte leds[][PIN_ANZAHL] PROGMEM = {

// Vorlagen zum kopieren:
//  {  X,  X,  X,  X,      X,  X,  X,  X,       X,  X,  X,      X,  X,  X,},
//  {  _,  _,  _,  _,      _,  _,  _,  _,       _,  _,  _,      _,  _,  _,},
 
/*
** Modell 1, 8 LEDs vorne, 6 hinten
*/

/* flash */
 {  X,  _,  X,  X,      X,  X,  _,  X,       X,  X,  X,      X,  X,  X,},
 {  X,  _, 50, 50,     50, 50,  _,  X,       X,  X,  X,      X,  X,  X,},
 {  _,  _,  X,  X,      X,  X,  _,  _,       X,  _,  X,      X,  _,  X,},
 {  _,  _, 50, 50,     50, 50,  _,  _,       X,  _,  X,      X,  _,  X,},
 {  _,  _, 30, 30,     30, 30,  _,  _,       X,  _,  X,      X,  _,  X,},
 {  X,  _, 10, 10,     10, 10,  _,  X,       X,  X,  X,      X,  X,  X,},
 {  X,  _,  _,  _,      _,  _,  _,  X,       X,  X,  X,      X,  X,  X,},
 {  _,  _,  _,  _,      _,  _,  _,  _,       X,  _,  X,      X,  _,  X,},
 {  _,  _,  _,  _,      _,  _,  _,  _,       X,  _,  X,      X,  _,  X,},
 {  _,  _,  _,  _,      _,  _,  _,  _,       X,  _,  X,      X,  _,  X,}, 
 {  PROGRAM_ENDE},

/* normal on */
 {  _,  _, 70, 40,     40, 70,  _,  _,      40,  _,  _,      _,  _, 40,},
 {  PROGRAM_ENDE},

/* normal on, waving headlights */
 {  _,  _, 10, 50,     70, 30,  _,  _,      40,  _,  _,      _,  _, 40,},
 {  _,  _, 20, 60,     60, 40,  _,  _,      45,  _,  _,      _,  _, 45,},
 {  _,  _, 30, 70,     50, 50,  _,  _,      50,  _,  _,      _,  _, 50,},
 {  _,  _, 40, 60,     40, 60,  _,  _,      55,  _,  _,      _,  _, 55,},
 {  _,  _, 50, 50,     30, 70,  _,  _,      60,  _,  _,      _,  _, 60,},
 {  _,  _, 60, 40,     20, 60,  _,  _,      65,  _,  _,      _,  _, 65,},
 {  _,  _, 70, 30,     10, 50,  _,  _,      70,  _,  _,      _,  _, 70,},
 {  _,  _, 60, 20,     20, 40,  _,  _,      65,  _,  _,      _,  _, 65,},
 {  _,  _, 50, 10,     30, 30,  _,  _,      60,  _,  _,      _,  _, 60,},
 {  _,  _, 40, 20,     40, 20,  _,  _,      55,  _,  _,      _,  _, 55,},
 {  _,  _, 30, 30,     50, 10,  _,  _,      50,  _,  _,      _,  _, 50,},
 {  _,  _, 20, 40,     60, 20,  _,  _,      45,  _,  _,      _,  _, 45,},
 {  PROGRAM_ENDE},

/* full on */
 {  X,  X,  X,  X,      X,  X,  X,  X,       X,  X,  X,      X,  X,  X,},
 {  PROGRAM_ENDE},

/* party */
 {  X,  _,  _,  _,      _,  X,  _,  _,       _,  _,  _,      X,  _,  _,},
 {  X,  _,  X,  _,      _,  _,  X,  _,       X,  _,  _,      _,  _,  X,},
 {  _,  X,  _,  _,      _,  X,  X,  _,       _,  X,  _,      X,  _,  _,},
 {  _,  _,  _,  X,      _,  _,  X,  _,       X,  _,  X,      _,  X,  _,},
 {  X,  X,  _,  X,      X,  X,  _,  _,       X,  _,  _,      X,  _,  _,},
 {  X,  _,  _,  _,      X,  _,  _,  _,       _,  _,  X,      _,  X,  X,},
 {  _,  _,  X,  _,      _,  X,  _,  X,       X,  _,  _,      X,  X,  X,},
 {  X,  X,  _,  X,      X,  _,  _,  _,       _,  _,  X,      _,  _,  _,},
 {  _,  X,  X,  X,      _,  X,  _,  X,       _,  X,  X,      X,  _,  _,},
 {  PROGRAM_ENDE},



 { MODEL_WECHSEL },
  
 
/*
** Modell 2, 6 LEDs vorne, 6 hinten
*/

 
/* normal on */
 {  _,  70, 40,     40, 70,  _,      _, 40, 40,     40, 40, _,},
 {  PROGRAM_ENDE},

/* normal on, waving headlights */
 {  _,  10, 50,     70, 30,  _,       _, 40, 40,        40, 40,  _,},
 {  _,  20, 60,     60, 40,  _,       _, 45, 45,        45, 45,  _,},
 {  _,  30, 70,     50, 50,  _,       _, 50, 50,        50, 50,  _,},
 {  _,  40, 60,     40, 60,  _,       _, 55, 55,        55, 55,  _,},
 {  _,  50, 50,     30, 70,  _,       _, 60, 60,        60, 60,  _,},
 {  _,  60, 40,     20, 60,  _,       _, 65, 65,        65, 65,  _,},
 {  _,  70, 30,     10, 50,  _,       _, 70, 70,        70, 70,  _,},
 {  _,  60, 20,     20, 40,  _,       _, 65, 65,        65, 65,  _,},
 {  _,  50, 10,     30, 30,  _,       _, 60, 60,        60, 60,  _,},
 {  _,  40, 20,     40, 20,  _,       _, 55, 55,        55, 55,  _,},
 {  _,  30, 30,     50, 10,  _,       _, 50, 50,        50, 50,  _,},
 {  _,  20, 40,     60, 20,  _,       _, 45, 45,        45, 45,  _,},
 {  PROGRAM_ENDE},

/* full on */
 {  X,  X,  X,      X,  X,  X,       X,  X,  X,      X,  X,  X,},
 {  PROGRAM_ENDE},

/* flash */
 {  X,   X,  X,      X,  X,  X,        X, X,  X,      X,  X,  X,},
 {  X,   5,  5,      5,  5,  X,        X, X,  X,      X,  X,  X,},
 {  _,   X,  X,      X,  X,  _,        _, X,  X,      X,  X,  _,},
 {  _,   5,  5,      5,  5,  _,        _, X,  X,      X,  X,  _,},
 {  _,   5,  5,      5,  5,  _,        _, X,  X,      X,  X,  _,},
 {  X,   5,  5,      5,  5,  X,        X, X,  X,      X,  X,  X,},
 {  X,   5,  5,      5,  5,  X,        X, X,  X,      X,  X,  X,},
 {  _,   5,  5,      5,  5,  _,        _, X,  X,      X,  X,  _,},
 {  _,   5,  5,      5,  5,  _,        _, X,  X,      X,  X,  _,},
 {  _,   5,  5,      5,  5,  _,        _, X,  X,      X,  X,  _,},
 {  PROGRAM_ENDE},

/* party */
 {  X,  _,  _,      _,  X,  _,       _,  _,  _,      X,  _,  _,},
 {  X,  _,  _,      _,  _,  _,       X,  _,  _,      _,  _,  X,},
 {  _,  X,  _,      _,  X,  _,       _,  X,  _,      X,  _,  _,},
 {  _,  _,  X,      _,  _,  _,       X,  _,  X,      _,  X,  _,},
 {  X,  X,  X,      X,  X,  _,       X,  _,  _,      X,  _,  _,},
 {  X,  _,  _,      X,  _,  _,       _,  _,  X,      _,  X,  X,},
 {  _,  _,  _,      _,  X,  X,       X,  _,  _,      X,  X,  X,},
 {  X,  X,  X,      X,  _,  _,       _,  _,  X,      _,  _,  _,},
 {  _,  X,  X,      _,  X,  X,       _,  X,  X,      X,  _,  _,},
 {  PROGRAM_ENDE},
 

 {FIN}


};




/*
** Erweiterte Einstellungen
*/

// Der Pin, an dem der Empfaenger angeschlossen ist.
#define SIG_PIN A0

// Die Signalwerte, die der Empfaenger fuer mindest und maximal Wert uebermittelt.
#define RECIEVER_MIN 1078
#define RECIEVER_MAX 1885

// Zeitraum in Millisekunden. Dieser wird verwendet um festzulegen ab welcher Dauer und wie Lightmashine
// den ueber Funke uebertragenen Befehl interpretiert.
// Bei Hebel-Steuerung: Hebel muss laenger als dieser Wert in Position gehalten werden, damit 
//                      Lightmashine das als Befehl erkennt.
// Bei Knopf-Steuerung: Knopf laenger als dieser Wert gedrueckt: Licht an/aus. Knopf kuerzer als der Wert
//                      gedrueckt: naechstes Lichtprogramm.
#define ACTIVATE_PERIOD 500

// Verwendeter Funke-Umschalter.
// 1 - fuer Umschalten per Hebel
// 2 - fuer Umschalten per Knopf
#define SWITCH_TYPE 2

const byte modelSelectPins[] = { NICHT_DA };
const byte led_pin_mapping_2[PIN_ANZAHL] = { };

const byte led_pin_mapping_3[PIN_ANZAHL] = { };
 
 
const byte led_pin_mapping_4[PIN_ANZAHL] = { };


 
const byte led_pin_mapping_5[PIN_ANZAHL] = { };


