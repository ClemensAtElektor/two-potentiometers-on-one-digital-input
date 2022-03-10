/*
 * Purpose: read two potentiometers with one digital pin using 
 *          frequency- and pulse width modulation.
 *
 * Author: cpv
 * Date: March 4, 2022
 *
 * Board: Arduino UNO
 * Arduino IDE 1.8.15
 */

int input = 3;
int f_min = 250; // Hz
int f_max = 500; // Hz
int d_min = 10; // %
int d_max = 90; // %

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Two potentiometers on one digital input, polling.");
  pinMode(input,INPUT);
}

void loop(void)
{
  // Make sure to start at the beginning of a period.
  while (digitalRead(input)==1);
  while (digitalRead(input)==0);
  // Pulse start.
  uint32_t t0 = micros();
  while (digitalRead(input)==1);
  // Pulse end, pause start.
  uint32_t t1 = micros();
  while (digitalRead(input)==0);
  // Pause end.
  uint32_t t2 = micros();

  // Do the maths.
  uint32_t pulse = t1 - t0; // in us
  uint32_t period = t2 - t0; // in us
  uint32_t frequency = 1000000/period; // in Hz
  int pot1 = 100*(frequency-f_min)/(f_max-f_min); // as %
  int pot2 = 100*pulse/period; // as %
  pot2 = 100*(pot2-d_min)/(d_max-d_min); // as %

  // Show the results.
  Serial.print("P1: ");
  Serial.print(pot1);
  Serial.print("\tP2: ");
  Serial.print(pot2);
  Serial.println();

  // Do something else.
  delay(100);
}
