// Costanstans
const int tempSensor = A5;
const int resistor = 11;

// Variables
double curTemp = 0.0;
double targetTemp = 26.0;

void setup()
{
  // Setup debug serial
  Serial.begin(9600);

  // Setup I/Os
  pinMode(tempSensor, INPUT);
  pinMode(resistor, OUTPUT);
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

void loop()
{
  // read temperature
  curTemp = readTermperature();

  // if the temperature is low, switch on the heat source
  if (curTemp < targetTemp)
    digitalWrite(resistor, HIGH);
  else
    digitalWrite(resistor, LOW);

  delay(1000);
}

