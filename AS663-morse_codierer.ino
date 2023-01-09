/*  AS663 Morsekennungsgeber für AS829
 *  Übernommen von DF5SK 22.11.2022
 *  Umgestellt auf Reset auf PB0
 *  Erweiterung um Intervallsteuerung
 *  Einsatz Peilsender
 *  MOE  MOI  MOS Einstellbar
 *  Umstellung auf interne Pullwiderstände
 *  Korrekte Einstellung der Pausen bei dem Betrieb von 2 Sendern (MOE und MOI mit DIP 3 ON)
 *  2.1.2023
 *  Byte wiederholung stellt die Anzahl der Rufzeichen je Durchgang bei zwei Sendern ein
 *  9.1.2023
 *  DK4MZ Wolfgang
 */


/*#define DOT 250 //Länge des DIT in ms
#define PIN_out    0
#define PIN_ctrl_1 5
#define PIN_ctrl_2 3
*/
//250
byte DOT = 125;
byte PIN_out = PB0;
byte PIN_ctrl_1 = PB4;
byte PIN_ctrl_2 = PB3;
byte PIN_ctrl_3 = PB1;
byte ctrl_1 = 0;
byte ctrl_2 = 0;
byte ctrl_3 = 0;
byte reset = PB5;
byte anzahl_v = 0;
byte wiederholung = 4; // 2


void setup()
{
  pinMode(PIN_out, OUTPUT);
  pinMode(PIN_ctrl_1, INPUT_PULLUP);
  pinMode(PIN_ctrl_2, INPUT_PULLUP);
  pinMode(PIN_ctrl_3, INPUT_PULLUP);
  pinMode(reset, INPUT_PULLUP);

  anzahl_v = 0;
  
  
}

void loop()
{
  // Anzahl setzen
  anzahl_v = anzahl_v + 1;
  if (anzahl_v == wiederholung * 2) {
    anzahl_v = 0;
  }
  // Lesen der Steuerports
  ctrl_1 = digitalRead(PIN_ctrl_1);
  ctrl_2 = digitalRead(PIN_ctrl_2);
  ctrl_3 = digitalRead(PIN_ctrl_3);
  
  if (ctrl_3 == 1){
  // M
  dah();
  dah();

  blank();

  // O
  dah();
  dah();
  dah();

  blank();

  if (ctrl_1 == 1 && ctrl_2 == 1){
    // E
    dit();
    blank();

  }  

if (ctrl_1 == 0 && ctrl_2 == 1) {
    // I
    dit();
    dit();
    blank();

  }  
  if (ctrl_1 == 1 && ctrl_2 == 0) {
    // S
    dit();
    dit();
    dit();
    blank();

  } 
  }
  if (ctrl_1 == 1 && ctrl_2 == 1 && ctrl_3 == 0 && anzahl_v < wiederholung) {
  // M
  dah();
  dah();

  blank();

  // O
  dah();
  dah();
  dah();

  blank();

  // E
  dit();
  blank();

  } 

  if (ctrl_1 == 1 && ctrl_2 == 1 && ctrl_3 == 0 && anzahl_v >= wiederholung) {
  //Wartezeit fuer das andere Rufzeichen
//  blank();
//  blank();
//  blank();
//
//  blank();
//  blank();
//  blank();
//
//  blank();
//  blank();
//  blank();
  // M
  dah_dummy();
  dah_dummy();

  blank();

  // O
  dah_dummy();
  dah_dummy();
  dah_dummy();

  blank();
  
    // I
    dit_dummy();
    dit_dummy();
    blank();

  }

  
  if (ctrl_1 == 0 && ctrl_2 == 1 && ctrl_3 == 0 && anzahl_v >= wiederholung) {
  // M
  dah();
  dah();

  blank();

  // O
  dah();
  dah();
  dah();

  blank();

  // E
  dit();
  dit();
  blank();

  } 

  if (ctrl_1 == 0 && ctrl_2 == 1 && ctrl_3 == 0 && anzahl_v < wiederholung) {
    // Wartezeit für das andere Rufzeichen
//  blank();
//  blank();
//  blank();
//
//  blank();
//  blank();
//  blank();
//
//  blank();
//  blank();
//  blank();
  // M
  dah_dummy();
  dah_dummy();

  blank();

  // O
  dah_dummy();
  dah_dummy();
  dah_dummy();

  blank();
  
    // E
    dit_dummy();
    blank();            
  }
 

  blank();
  blank();
  blank();
}




void dit()
{
  digitalWrite(PIN_out, HIGH);
  delay(DOT);
  digitalWrite(PIN_out, LOW);
  delay(DOT);
}

void dah()
{
  digitalWrite(PIN_out, HIGH);
  delay(3 * DOT);
  digitalWrite(PIN_out, LOW);
  delay(DOT);
}

void blank()
{
  delay(3 * DOT);
}

void dit_dummy()
{
  digitalWrite(PIN_out, LOW);
  delay(DOT);
  digitalWrite(PIN_out, LOW);
  delay(DOT);
}

void dah_dummy()
{
  digitalWrite(PIN_out, LOW);
  delay(3 * DOT);
  digitalWrite(PIN_out, LOW);
  delay(DOT);
}
