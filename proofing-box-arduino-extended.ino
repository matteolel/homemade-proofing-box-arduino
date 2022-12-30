#include <LiquidCrystal.h>

// initialize LCD library
const int rs = 11, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Costanstans
const int tempSensor = A3;
const int tempSetting = A5;
const int resistor = 12;

// Variables
bool heatOn = false;
double curTemp = 0.0;
double targetTemp = 26.0;
char LCDmsg[21];
bool curFlameState = false;

// create some custom characters
// degree symbol
byte degChar[] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};
// a stylized flame
byte flameChar1[] = {
  B00110,
  B00110,
  B01100,
  B01100,
  B00110,
  B00110,
  B11111,
  B11111
};
// another stylized flame
byte flameChar2[] = {
  B01100,
  B01100,
  B00110,
  B00110,
  B01100,
  B01100,
  B11111,
  B11111
};

void setup()
{
  // Setup debug serial
  Serial.begin(9600);

  // Setup I/Os
  pinMode(tempSensor, INPUT);
  pinMode(tempSetting, INPUT);
  pinMode(resistor, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // create cusom characters
  lcd.createChar(0, degChar);
  lcd.createChar(1, flameChar1);
  lcd.createChar(2, flameChar2);
}

// read the current temperature from LM32
double readTermperature() {
  double vout;

  // set the reference to INTERNAL (1.1V) in order to have a better definition
  analogReference(INTERNAL);

  // a "fake" read is needed
  analogRead(0);
  delay(10);

  // sadly the first read is less accurate... use the second one
  vout = analogRead(tempSensor);
  vout = analogRead(tempSensor);

  Serial.print("sample:");
  Serial.print(vout);
  Serial.print(",");
  vout = vout * 1.129 / 1023.0; // little bit tuned
  Serial.print("v:");
  Serial.print(vout);
  Serial.print(",");

  // Returning value in Degree Celsius
  vout = vout * 100;
  Serial.print("t:");
  Serial.println (curTemp);

  return vout;
}

// read the wanted temperature
double readSetTemp() {
  double readT;

  // set the reference to 5V
  analogReference(DEFAULT);

  // a "fake" read is needed
  analogRead(0);
  delay(10);

  // sadly the first read is less accurate... use the second one
  readT = analogRead(tempSetting);
  readT = analogRead(tempSetting);
  Serial.print("readT:");
  Serial.print(readT);
  Serial.print(",");
  return readT * 40 / 1023; // set a max of 40C
}

void loop()
{
  // read temperature
  curTemp = readTermperature();
  // read the taget temperature
  targetTemp = readSetTemp();
  // do we need to switch on the heat source?
  heatOn = curTemp < targetTemp;

  // LCD: display values
  lcd.clear();
  lcd.setCursor(0, 0);
  dtostrf(curTemp, 4, 1, LCDmsg); // print only a decimal digit
  lcd.print(LCDmsg);
  lcd.write((byte)0);
  lcd.print("C => ");
  dtostrf(targetTemp, 4, 1, LCDmsg); // print only a decimal digit
  lcd.print(LCDmsg);
  lcd.write((byte)0);
  lcd.print("C");

  // on the second line, write a "moving" flame if heat is on
  if (heatOn) {
    lcd.setCursor(6, 1);
    if (curFlameState) {
      lcd.write((byte)1);
      lcd.write((byte)1);
      lcd.write((byte)1);
    } else {
      lcd.write((byte)2);
      lcd.write((byte)2);
      lcd.write((byte)2);
    }
    curFlameState = !curFlameState;
  }

  // if the temperature is low, switch on the heat source
  if (heatOn)
    digitalWrite(resistor, HIGH);
  else
    digitalWrite(resistor, LOW);

  delay(1000);
}