/*
*  Simulating diesel VW 1.9 TDI engine sound with mechanical relays on Arduino boards/modules 
*  Made just for sound and joy ;)
*  vGamBIT 
*  v0.1
*  2024
*/

// Relay input pin configuration adjust to your hardware and preferences
#define FIRST_CYLINDER_PIN 26
#define SECOND_CYLINDER_PIN 27
#define THIRD_CYLINDER_PIN 14
#define FOURTH_CYLINDER_PIN 12

#define POTENTIOMETER_PIN 34

#if defined(ARDUINO_ARCH_ESP32)

#define POTENTIOMETER_ADC_MAX 4095 // Max value for ADC for ESP32 12 bit -> 4095, for ESP8266 10 bit -> 1023 and so on

#else

#define POTENTIOMETER_ADC_MAX 1023

#endif

#define MIN_RPM 900 // Minimum RPM for simulation1
#define MAX_RPM 3500 // Maximum RPM (try to adjust until relays will stop clicking and this is max rpm)
#define ADD_RAND_RPM 1200 // Maximum RPM before varying of strokes will work

void setup() {
  randomSeed(analogRead(0));

  pinMode(FIRST_CYLINDER_PIN, OUTPUT);
  pinMode(SECOND_CYLINDER_PIN, OUTPUT);
  pinMode(THIRD_CYLINDER_PIN, OUTPUT);
  pinMode(FOURTH_CYLINDER_PIN, OUTPUT);
  pinMode(POTENTIOMETER_PIN, INPUT);
}

void loop() {
  int rpm = map(analogRead(POTENTIOMETER_PIN), 0, POTENTIOMETER_ADC_MAX, MIN_RPM, MAX_RPM);

  int maxStrokeRand = 5; // Max difference between cycles for more realistic sound
  
  if (rpm > ADD_RAND_RPM) {
    maxStrokeRand = 1;
  }

  int strokeDuration = 1000 / (rpm / 60) / 4;

  digitalWrite(FIRST_CYLINDER_PIN, LOW);
  delay(strokeDuration + random(maxStrokeRand));
  digitalWrite(FIRST_CYLINDER_PIN, HIGH);
  delay(strokeDuration);

  digitalWrite(THIRD_CYLINDER_PIN, LOW);
  delay(strokeDuration + random(maxStrokeRand));
  digitalWrite(THIRD_CYLINDER_PIN, HIGH);
  delay(strokeDuration);

  digitalWrite(FOURTH_CYLINDER_PIN, LOW);
  delay(strokeDuration + random(maxStrokeRand));
  digitalWrite(FOURTH_CYLINDER_PIN, HIGH);
  delay(strokeDuration);

  digitalWrite(SECOND_CYLINDER_PIN, LOW);
  delay(strokeDuration + random(maxStrokeRand));
  digitalWrite(SECOND_CYLINDER_PIN, HIGH);
  delay(strokeDuration);

}
