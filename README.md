# lightmashine

Use Arduino as a RC light controller

Latest release: [lightmashine 1.6](https://github.com/ewirch/lightmashine/archive/1.6.zip)

# Verwendung
Ich gehe hier davon aus, dass die Arduino Software auf deinem Rechner schon läuft und du Programme auf den Arduino laden kannst. Falls nicht, hier: [Arduino Getting Started](http://arduino.cc/en/Guide/HomePage).

## Hardware
### Teile-Liste
Neben einem Arduino benötigst Du für eine komplette Lichtsteuerung folgendes:
* LEDs. In Anzahl und Farbe wie's beliebt.
* Widerstände
* Stiftleisten
* Draht. Sehr praktisch ist [Lackdraht](http://www.conrad.de/ce/de/product/605125/Kupferlackdraht-CUL-Draht-Durchmesser-035-mm-1-Pckg-Block).
* Und zum Befestigen des Arduino entweder Klettband oder eine eigens angefertigte Platine, die dann in die Karo eingeklebt wird. Dazu später mehr.

Die Widerstände braucht man als Vorwiderstände. Je nach Bauart benötigt eine LED unterschiedliche Spannungen. Die Betriebsspannung ist normal in den Artikeldaten genannt. Der Arduino UNO liefert an seinen Ausgängen konstant 5V. Damit die LEDs nicht durchbrennen werden Sie mit einem Vorwiderstand geschützt. Die Berechnung des genauen Vorwiderstands ist eine komplizierte Sache. Aber zum Glück gibt es Webseiten, die einem das abnehmen: [led-rechner.de](http://www.led-rechner.de/)

Stiftleisten sehen so aus: [Stiftleiste 32 Pole](http://www.conrad.de/ce/de/product/393492/Stiftleiste-RM-254-gerade-10120511-BKL-Electronic-Inhalt-1-St). Je nachdem wie Du den Arduino befestigen willst benötigst Du die Stiftleisten hier:
* Befestigung mit Klettband: Du lötest die LEDs direkt an die Stiftleisten. Die Stiftleisten steckst Du in deinen Arduino sobald Du in in der Karo befestigt hast. Die Widerstände musst Du irgendwie zwischen Stiftleiste und LED unterbringen.
* Befestigung über Shield (also die gefertigte Platine): Stiftleisten in Platine löten. Platine in Karo kleben. Arduino kann dann einfach auf die Platine aufgesteckt werden. Die Widerstände können auf der Platine verlötet werden.

Ein fertiges Platinenlayout für Arduino UNO findet sich im lightmashine ZIP-Archiv unter dem Namen `lightmashine-shield.fzz`. Sofware zum Bearbeiten des Layouts gibt's hier: [fritzing.org](http://fritzing.org). Platine zum Fertigen bestellen kann man hier: [fab.fritzing.org](http://fab.fritzing.org). 



### Empfänger-Signal-Leitung anschließen
Einen Empfänger-Kanal auswählen und die Leitungen folgend verbinden:

| Empfänger-Ausgang | Arduino |
|-------------------|---------|
| Plus              | Vin     |
| Minus             | GND     |
| Signal            | A0      |


Falls kein Empfänger-Kanal mehr frei ist, kann man auch ausschließlich die Plus und Minus Leitungen eines belegten Kanals für die Stromversorgung des Arduino abgreifen. Ohne die Signal-Leitung funktioniert Lightmashine auch. Dann kann dann allerdings das Licht nicht über die Funke gesteuert werden. In dem Fall (Signal-Pin unverwendet) sollte der Signal-Pin und GND mit einem 150kOhm Widerstand verbunden werden. Sonst können Störungen auftreten, und Lightmashine diese Störungen als Befehle misinterpretieren.

## Schnellstart
Lightmashine herunter laden: [lightmashine-1.5.1](https://github.com/ewirch/lightmashine/archive/lightmashine-v1.5.1.zip), entpacken und `lightmashine.ino` (im Ordner lightmashine) mit der Arduino Software öffnen.

Versuche gleich lightmashine auf deinen Arduino zu laden. Wenn er an Strom und LEDs angeschlossen ist, sollte gleich schon was blinken. 

## Konfiguration 
Lightmashine muss man mindestens vier Dinge mitteilen: 
* wie viele Pins sollen benutzt werden
* Geschwindigkeit mit der die LEDs blinken sollen
* an welchen Pins sind LEDs angeschlossen
* die Lichtprogramme

**Bevor** Du in den Inhalt der Dateien abtauchst, eine ganz kurze Einführung zur Syntax, die in den Arduino-Dateien verwendet wird. In den Dateien werden an etlichen Stellen Kommentare verwendet. Kommentare sind nur für den Betrachter. Arduino ignoriert sie komplett. Einzeilige Kommentare werden mit zwei Slashes eingeleitet: `//`. Alles was dahinter kommt, bis Ende der Zeile ist ein Kommentar und wird ignoriert. Beispiel:
```
#define EINE_EINSTELLUNG 7 // dies ist ein Kommentar zur Verdeutlichung
// ich bin auch ein Kommentar
```
Mehrzeilige Kommentare beginnen mit `/*` und erstrecken sich bis zum nächsten `*/`. Beispiel:
```
#define EINE_EINSTELLUNG 7 /* dies ist ein Kommentar zur Verdeutlichung
ich bin auch ein Kommentar */
```
Häufig werden Mehrzeilige Kommentare verwendet um einen Textblock zu schreiben. Etwa so:
```
/*
** Hier kommt ein erklärender Text,
** der genau beschreibt, wie das
** Nachfolgende verwendet werden soll.
*/
#define NACHFOLGENDE 3
```
So, nun ab zum Code:

Alle drei Einstellungen finden sich in `Lichtprogramme.h` im Oberen Bereich “Grundeinstellungen”. Die Anzahl der Pins stellst Du über diese Zeile ein:

<pre>#define PIN_ANZAHL 14</pre>

Wenn man alle Ausgänge des UNO verwendet, dann sind es 12 Pins. 
Die Geschwindigkeit wird darüber gesteuert:

<pre>#define FRAME_PAUSE 100</pre>

Einheit ist Millisekunden. Somit: je kleiner, desto schneller. Erstmal kannst Du den Wert so lassen. Du kannst ihn später anpassen.
Nun die Pin-Zuordnung:

<pre>
byte led_pin_mapping[PIN_ANZAHL] =
 { 0, 1, 2, 3,      4, 5, 6, 7,    8, 9,10,         11,12,13,};
</pre>

Die Idee ist, dass man sich eine Reihenfolge überlegt in der man die LEDs programmieren will. Z.b.: Vorne links: blinker, weiss,  weiss,  Vorne rechts: weiss, weiss, Blinker. 
Und dann angibt an welchen Pins diese LEDs angeschlossen sind. Eine sinnvolle Reihenfolge macht es einem später einfacher. Ich habe in `Lichtprogramme.h` das Mapping mit einem Kommentar ausgestattet, der es verständlicher machen soll:

<pre>
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
</pre>

Und noch mal in einer nicht technischen Ansicht:
<table>
 <tr>
  <td colSpan="4">Vorne links</td>
  <td colSpan="4">Vorne rechs</td>
  <td colSpan="3">Hinten links</td>
  <td colSpan="3">Hinten rechts</td>
 </tr>
 <tr>
   <td>Blinker</td> <td>Blau</td> <td>Weiss</td> <td>Weiss</td>
   <td>Weiss</td> <td>Weiss</td> <td>Blau</td> <td>Blinker</td>
   <td>Aussen</td> <td>Blinker</td> <td>Innen</td>
   <td>Innen</td> <td>Blinker</td> <td>Aussen</td>
 </tr>
 <tr>
   <td>0</td> <td>1</td> <td>2</td> <td>3</td> 
   <td>4</td> <td>5</td> <td>6</td> <td>7</td> 
   <td>8</td> <td>9</td> <td>10</td> 
   <td>11</td> <td>12</td> <td>13</td> 
 </tr>
</table>

Hier haben wir die vorderen LEDs (4 links, 4 rechts) von links nach rechts und die hinteren LEDs (3 links, 3 rechts). An der selben Position werden später die Anweisungen für die LEDs in den Licht-Programmen stehen. Der Arduino "weiss" nicht welche LED vorne welche LED hinten ist. Ihm ist es auch egal. Er muss nur wissen welchen PIN er jetzt einschalten soll. D.h. die ganze Festlegung der Reihenfolge ist nur für Dich, damit es Dir leichter fällt die Lichtprogramme zu schreiben.
Dass die Pin-Nummern hier aufsteigend sind, ist rein zufällig. Du trägst die Pin-Nummern ein, an denen die gewünschten LEDs angeschlossen sind. Soll Blinker-Links-Vorne in der ersten Spalte stehen, und ist Blinker-Links-Vorne an Pin 7 angeschlossen, dann trägst Du da 7 ein.

## LED Programme erstellen 
Die Idee ist folgende man gibt welche LEDs leuchten sollen, lässt etwas Zeit verstreichen und gibt an wie die LEDs jetzt leuchten sollen, lässt wieder Zeit verstreichen, und so weiter. Hier einfach mal ein einfaches Beispiel, mit der LED-Konfiguration von oben. Erst mal in Klartext:
* Alles aus
* die vier weissen LEDs an
* alles aus
* weisse wieder an
* alles aus
* immer noch aus (macht die pause länger)
* blinker an
* alles aus
* blinker an
* alles aus
* immer noch aus
* immer noch aus

Und nun in Programmcode:
<pre>
/* flash */
 { _, _, _, _,     _, _, _, _,    _, _, _,    _, _, _,},
 { _, _, X, X,     X, X, _, _,    _, _, _,    _, _, _,},
 { _, _, _, _,     _, _, _, _,    _, _, _,    _, _, _,},
 { _, _, X, X,     X, X, _, _,    _, _, _,    _, _, _,},
 { _, _, _, _,     _, _, _, _,    _, _, _,    _, _, _,},
 { _, _, _, _,     _, _, _, _,    _, _, _,    _, _, _,},
 { X, _, _, _,     _, _, _, X,    _, _, _,    _, _, _,},
 { _, _, _, _,     _, _, _, _,    _, _, _,    _, _, _,},
 { X, _, _, _,     _, _, _, X,    _, _, _,    _, _, _,},
 { _, _, _, _,     _, _, _, _,    _, _, _,    _, _, _,},
 { _, _, _, _,     _, _, _, _,    _, _, _,    _, _, _,},
 { _, _, _, _,     _, _, _, _,    _, _, _,    _, _, _,},
 {PROGRAM_ENDE}, 
</pre>

Erinnere Dich an das LED-Mapping von oben. Ganz links Blinker, dann Weiss, Weiss, rechte seite Weiss, Weiss, und der rechte Blinker. Der Arduino arbeitet diesen Block von oben nach unten ab. Kommt er unten an, fängt er wieder oben an. Zwischen jeder Zeile wartet er die `FRAME_PAUSE` Millisekunden ab, die Du vorher eingestellt hast. Den Block für das Lichtprogramm findest Du in `Lichtprogramme.h` ab der Zeile `prog_uchar leds[][PIN_ANZAHL] PROGMEM = {`.

Nun zur Syntax. Die geschweiften Klammern und die Kommas müssen Dich nicht kümmern. Kopiere einfach eine Zeile und verändert sie. Den Unterstrich verwendet man um ein leicht zu erkennendes “LED aus” anzugeben. Das X verwendet man, leicht zu erraten, “LED an”. Die letzte Zeile mit `{PROGRAM_ENDE},` ist extrem wichtig um das Programmende zu markieren.

### Mehrere Lichtprogramme
Mehrere Programme werden einfach hintereinander angegeben. Daher ist die `PROGRAM_ENDE`-Zeile wichtig. Durch sie weiss lightmashine wann das nächste Programm beginnt. Hier zwei Programme:

<pre>
prog_uchar leds[][PIN_ANZAHL] PROGMEM = {
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

 {FIN}
};
</pre>

Die FIN-Zeile markiert das endgültige Ende der Program-Liste. Die Zeile darf nicht fehlen, sonst läuft gar nichts.

Hier könntest Du zum Kapitel "Einstellung der Funke" springen, wenn Du jetzt gleich etwas experementieren möchtest. Oder Du liest das nächste Kapitel, wenn Dich die Zahlen im obigen Programm gewundert haben.

### LEDs dimmen
Lightmashine unterstützt nicht nur LED an/aus. Die Helligkeit aller LEDs kann in Prozent angegeben werden. Die Syntax mit dem Unterstrich `_` und dem `X` entsprechen dabei 0% und 100% Helligkeit. Genau so könntest Du 0 und 100 angeben. Unterstrich und `X` sind einfach lesbarer.

### Weicher Dimm-Verlauf
Lightmashine optimiert den Helligkeitsverlauf zwischen zwei Frames. Soll eine LED von 20% Helligkeit auf 80% Helligkeit umgeschaltet werden, dann wird sie nicht einfach hart auf 80% gestellt, sondern lightmashine blendet die LED sanft von 20% auf 80% hoch. Dieses einfache Licht-Programm steuert eine LED, die langsam hell und dunkel wird:
<pre>
#define PIN_ANZAHL 1

#define FRAME_PAUSE 1000 // 1 Sekunde

byte led_pin_mapping[PIN_ANZAHL] =
  { 3, };

prog_uchar leds[][PIN_ANZAHL] PROGMEM = {
 {   0,}
 { 100,}
 { PROGRAM_ENDE},

 { FIN},
};
</pre>

In dem Programm sind mit Absicht nicht der Unterstrich und das X verwendet worden. Manchmal möchte man doch nicht einen weichen Verlauf haben. Manchmal möchte man harte Schaltvorgänge. Hier macht lightmashine enie Unterscheidung zwischen `_` / `0` und `X` / `100`. Ist der nächste Wert in einem Frame eine Prozentangabe (Zahl) wird die LED sanft überblendet. Ist der nächste Wert ein Unterstrich oder eine X wird die LED sofort aus bzw. an gemacht. Hier, z.B. wird eine LED sanft heller und geht abrupt aus:

```
 {   0,}
 {  50,}  // <-- von 0 auf 50 überblenden
 { 100,}  // <-- von 50 auf 100 überblenden
 {   _,}  // <-- abrupt aus
 { PROGRAM_ENDE},
```

Hier das selbe nochmal, nur dass die LED zum Schluss ausgeblendet wird:
```
 {   0,}
 {  50,}
 { 100,}
 {   0,}
 { PROGRAM_ENDE},
```

Das selbe mit dem X. Sofort an, weich ausblenden:
<pre>
 {  0,}
 {  X,}
 { PROGRAM_ENDE},
</pre>

Weich einblenden, weich ausblenden:
<pre>
 {  0,}
 {  X,}
 { PROGRAM_ENDE},
</pre>

Sofort an, sofort aus:
<pre>
 {  _,}
 {  X,}
 { PROGRAM_ENDE},
</pre>


### Beispiel: Lauflicht Vorne/Hinten synchron, 12 LEDs
<pre>
#define PIN_ANZAHL 12

#define FRAME_PAUSE 100

// LEDs sind sind in aufsteigender Reihenfolge an
// die Pins gelötet. Säulen sind: Vorne Links, 
// Vorne Rechts, Hinten Links, Hinten Rechts
int led_pin_mapping[PIN_ANZAHL] =
 { 2, 3, 4,   5, 6, 7,   8, 9, 10,   11, 12, 13};

int leds[][PIN_ANZAHL] = {
/* lauflicht synchron */
 { X, _, _,     _, _, _,   X, _, _,   _, _, _,},
 { _, X, _,     _, _, _,   _, X, _,   _, _, _,},
 { _, _, X,     _, _, _,   _, _, X,   _, _, _,},
 { _, _, _,     X, _, _,   _, _, _,   X, _, _,},
 { _, _, _,     _, X, _,   _, _, _,   _, X, _,},
 { _, _, _,     _, _, X,   _, _, _,   _, _, X,},
 { _, _, _,     _, X, _,   _, _, _,   _, X, _,},
 { _, _, _,     X, _, _,   _, _, _,   X, _, _,},
 { _, _, X,     _, _, _,   _, _, X,   _, _, _,},
 { _, X, _,     _, _, _,   _, X, _,   _, _, _,},
 { PROGRAM_ENDE,},

 {FIN,}
};
</pre>

Das selbe nochmal, nur mit einem leichten Verwisch-Effekt:
<pre>
#define PIN_ANZAHL 12

#define FRAME_PAUSE 100

// LEDs sind sind in aufsteigender Reihenfolge an
// die Pins gelötet. Säulen sind: Vorne Links, 
// Vorne Rechts, Hinten Links, Hinten Rechts
int led_pin_mapping[PIN_ANZAHL] =
 { 2, 3, 4,   5, 6, 7,   8, 9, 10,   11, 12, 13};

int leds[][PIN_ANZAHL] = {
/* lauflicht synchron */
 { 100,   0,   0,       0,   0,   0,     100,   0,   0,       0,   0,   0,},
 {   0, 100,   0,       0,   0,   0,       0, 100,   0,       0,   0,   0,},
 {   0,   0, 100,       0,   0,   0,       0,   0, 100,       0,   0,   0,},
 {   0,   0,   0,     100,   0,   0,       0,   0,   0,     100,   0,   0,},
 {   0,   0,   0,       0, 100,   0,       0,   0,   0,       0, 100,   0,},
 {   0,   0,   0,       0,   0, 100,       0,   0,   0,       0,   0, 100,},
 {   0,   0,   0,       0, 100,   0,       0,   0,   0,       0, 100,   0,},
 {   0,   0,   0,     100,   0,   0,       0,   0,   0,     100,   0,   0,},
 {   0,   0, 100,       0,   0,   0,       0,   0, 100,       0,   0,   0,},
 {   0, 100,   0,       0,   0,   0,       0, 100,   0,       0,   0,   0,},
 { PROGRAM_ENDE,},

 {FIN,}
};
</pre>

## Steuerung von Lightmashine über die Funke
Falls Du das Signal-Kabel an den Arduino angebunden hast, kannst Du Lichtprogramme umschalten und Lightmashine an/aus schalten. Lightmashine unterstützt dabei zwei mögliche Steuerungsmodi:
* Steuerung per Hebel (Funke überträgt je nach Hebelposition -100%-0%-100% an den Empfänger)
* Steuerung per Knopf (Funke überträgt bei Knopf gedrückt 100%, bei Knopf losgelassen 0%)

In beiden Fällen muss man Lightmashine den Pin mitteilen, an dem die Signalleitung des Empfängers angeschlossen ist (siehe `Lightprogramme.h`):
```
// Der Pin, an dem der Empfaenger angeschlossen ist.
#define SIG_PIN A0
```

Nachfolgend beschreibe ich auch die Einstellung der Funke. Falls Deine Funke nicht aufgeführt ist und Du es erfolgreich zum Laufen gebracht hast, schick mir die Beschreibung, ich werde es übernehmen.

### Steuerung per Hebel (an der Funke)
Wenn du einen freien Hebel an deiner Funke hast und diesen Verwenden möchtest, stelle die Einstellung `SWITCH_TYPE` (in `Lichtprogramme.h`) auf 1:
```
#define SWITCH_TYPE 1
```
Die Steuerung per Hebel geht so:

Hebel runter, kurz warten, Hebel zurück in Mittelposition: **Licht an/aus**.

Hebel hoch, kurz warten, zurück in Mittelposition: **Nächstes Licht-Programm**.

Wichtig ist, dass die Funke bei Betätigung des Hebels die Werte `-100% / 0% / 100%` übermittelt.

#### Einstellung der Funke: Sanwa MT-4
Die Sanwa MT-4 hat einen kleinen Hebel hinten. Dieser kann dazu verwendet werden. Ich gehe in der Beschreibung davon aus, dass Du am Empfänger den Kanal AUX1 gewählt hast. Unter `System -> Key Assign -> Lever`, den Wert `Function` auf den Kanal AUX1 stellen. Den Wert `TWEAK(H)` auf 100 stellen, den Wert `TWEAK(L)` auf -100. Dann zurück im Hauptmenü unter `AUX1`, sicherstellen, dass der Wert auf 0 steht.  Hebel in Mittelposition bringen. Dann Arduino einschalten. Falls der Hebel nicht in Mittelposition ist, wenn Du den Arduino einschaltest, dann liest Lightmashine den Hebelwert, als hättest Du den Hebel gerade in diese Position geschoben. War der Hebel also unten, dann wird Lightmashine aus gehen (oder an gehen, wenn es vorher aus war).

### Steuerung per Knopf (an der Funke)
Hast Du einen frei programmierbaren Knopf an deiner Funke, kannst du diesen benutzen. Die Steuerung geht so:

Knopf lange gerückt halten: **Licht an/aus**.
Knopf kurz gedrückt halten: **Nächstes Licht-Programm**.

Stelle die Einstellung `SWITCH_TYPE` so ein:
```
#define SWITCH_TYPE 2
```

#### Einstellung der Funke: Sanwa MT-4
Die Sanwa MT-4 hat zwei frei programmierbare Knöpfe. Der eine befindet sich direkt über dem Daumen: Sw2. Und der andere unter dem Daumen, wenn man den Daumen nach oben hält: Sw1. Wähle einen. Ich beschreibe die Einstellung für Sw2 und Kanal AUX1. Für Sw1 ist das Vorgehen genau so.

Im Menü `System -> Key Assign -> Switch`, die Zeile mit SW2 auswählen, und für `Function` AUX1 auswählen. Für `MODE` den Wert `PUSH` auswählen. Dieser legt fest, dass die Funke nur so lange einen anderen Wert übermittelt, solange der Knopf gedrückt wird. Dann zurück ins Hauptmenü und das Menü `AUX1` auswählen. Den Knopf Sw2 drücken und gedrückt halten. Nun das Wählrad zum "auswählen" drücken und den Wert auf 100 stellen. Wählrad zum Bestätigen noch mal drücken. Sw2 loslassen. Nun müsste der Wert 0 angezeigt werden. Wenn Du Sw2 gedrückt hältst der Wert 100.

## Steuerung per Knopf (an der Karo)
Falls man keinen freien Kanal an der Funke hat, den man verwenden kann, kann man Lightmashine auch über einen Taster an der Karo steuern. `SWITCH_TYPE` wird dazu auf 3 gesetzt:
```
#define SWITCH_TYPE 3
```
Der Taster (Taste gedrückt: Kontakt geschlossen, Taste losgelassen: Kontakt offen) wird zwischen dem Pin, der durch `SIG_PIN` Beschrieben wurde und Masse (GND) geschaltet. Der Taster setzt somit den Pin `SIG_PIN` beim Betätigen auf LO.
Wird der Taster kurz gedrückt, wird zum nächsten Lichtprogramm weiter geschaltet. Wird der Taster lange gedrückt gehalten, geht Lightmashine an/aus.


## Fehlersuche
### error: too many initializers for 'int [X]'
Die Pin-Anzahl, die bei PIN_ANZAHL angegeben wurde, stimmt nicht mit der Anzahl Spalten von `led_pin_mapping` und `leds` (Licht-Programme) überein.

### error: expected `}' before '{' token
Eine Zeile vorher fehlt ein Komma.

### error: expected `}' before numeric constant
In der Zeile fehlt ein Komma.



## Erweiterte Einstellungen 
Unter dem Kommentar “Erweiterte Einstellungen” findet sich:

### RECIEVER_MIN, RECIEVER_MAX
Die Signalwerte, die der Empfänger für Mindest- und Maximal-Wert übermittelt.
* RECIEVER_MIN
* RECIEVER_MAX
Falls Lightmashine gar nicht oder falsch auf die Befehle per Funke reagiert, könnte es sein, dass Dein Empfänger andere Werte an den Arduino überträgt als den, den ich zum Testen verwendet habe. Falls Du Dich mit Arduino-Programmierung auskennst, miss die Werte (`pulseIn()`) und stelle sie hier ein.

### ACTIVATE_PERIOD
Zeitraum in Millisekunden. Dieser wird verwendet um festzulegen ab welcher Dauer, und wie Lightmashine den über die Funke übertragenen Befehl interpretiert.
* **Bei Hebel-Steuerung**: Hebel muss länger als dieser Wert in Position gehalten werden, damit Lightmashine das als Befehl erkennt.
* **Bei Knopf-Steuerung**: Knopf länger als dieser Wert gedrückt: Licht an/aus. Knopf kürzer als der Wert gedrückt: nächstes Lichtprogramm.


## Umstellung 1.3 nach 1.5

### Lichtprogramme auslagern
Die Lichprogramme sind in eine eigene Datei gewandert: `Lichtprogramme.h`. Nachdem Du die neue Version herunter geladen hast, öffne Deine alte `lightmashine.ino`, kopiere alle Deine Lichtprogramme:

```
byte leds[][PIN_ANZAHL] = {

 {  _,  _, 50, 50,     30, 70,  _,  _,      60,  _,  _,      _,  _, 60,},
 {  _,  _, 60, 40,     20, 60,  _,  _,      65,  _,  _,      _,  _, 65,},
 {  _,  _, 70, 30,     10, 50,  _,  _,      70,  _,  _,      _,  _, 70,},
 {  _,  _, 60, 20,     20, 40,  _,  _,      65,  _,  _,      _,  _, 65,},
 {  E,  E,  E,  E,      E,  E,  E   E,       E,  E,  E,      E,  E,  E,},

 {  _,  _, 30, 30,     30, 30,  _,  _,       X,  _,  X,      X,  _,  X,},
 {  X,  _, 10, 10,     10, 10,  _,  X,       X,  X,  X,      X,  X,  X,},
 {  X,  _,  _,  _,      _,  _,  _,  X,       X,  X,  X,      X,  X,  X,},
 {  _,  _,  _,  _,      _,  _,  _,  _,       X,  _,  X,      X,  _,  X,},
 {  E,  E,  E,  E,      E,  E,  E   E,       E,  E,  E,      E,  E,  E,},

 {FIN,FIN,FIN,FIN,    FIN,FIN,FIN,FIN,     FIN,FIN,FIN,    FIN,FIN,FIN,},
};
```
**Wichtig! Achte darauf, nicht die erste und die letzte Zeile zu kopieren. Nur Deine Licht-Programm-Zeilen!**
Öffne die neue `Lichtprogramme.h` und lösche die Beispiel-Licht-Programme. Hier kannst Du nun Deine Licht-Programme einfügen. Übertrage auch die anderen Einstellungen, indem Du die Werte einen nach dem anderen übernimmst. Die Struktur der Datei ist leicht anders, daher kannst Du nicht einfach alle Zeilen kopieren.

In Zukunft kannst Du bei neuen Releases einfach die `Lichtprogramme.h` durch Deine überschreiben.

### Neues Program-Ende und Ende-Ende
Die neue Struktur verwendet anstelle von `E` für Programm-Ende, das mehr lesbare `PROGRAM_ENDE`. Weiter muss das nicht mehr zig mal angegeben werden. Ein Mal reicht. Das selbe gilt für das Ende der Enden: `FIN`. Das Obere Beispiel sieht nach der Anpassung so aus:

```
prog_uchar leds[][PIN_ANZAHL] PROGMEM = {

 {  _,  _, 50, 50,     30, 70,  _,  _,      60,  _,  _,      _,  _, 60,},
 {  _,  _, 60, 40,     20, 60,  _,  _,      65,  _,  _,      _,  _, 65,},
 {  _,  _, 70, 30,     10, 50,  _,  _,      70,  _,  _,      _,  _, 70,},
 {  _,  _, 60, 20,     20, 40,  _,  _,      65,  _,  _,      _,  _, 65,},
 { PROGRAM_ENDE },

 {  _,  _, 30, 30,     30, 30,  _,  _,       X,  _,  X,      X,  _,  X,},
 {  X,  _, 10, 10,     10, 10,  _,  X,       X,  X,  X,      X,  X,  X,},
 {  X,  _,  _,  _,      _,  _,  _,  X,       X,  X,  X,      X,  X,  X,},
 {  _,  _,  _,  _,      _,  _,  _,  _,       X,  _,  X,      X,  _,  X,},
 { PROGRAM_ENDE },

 {FIN},
};
```

### pwmPins weg
Die Einstellung
```
byte pwmPins[] = {3, 5, 6, 9, 10, 11, 0xFF};
```
Ist raus geflogen. Da sie aber nicht dokumentiert war, wird es eh niemand bemerken. ;)

