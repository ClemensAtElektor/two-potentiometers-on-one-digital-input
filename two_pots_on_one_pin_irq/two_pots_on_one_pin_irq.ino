/*
 * Purpose: read two potentiometers with one digital pin using 
 *          frequency- and pulse width modulation.
 *          Uses interrupts.
 *
 * Author: cpv
 * Date: March 9, 2022
 *
 * Board: Arduino UNO
 * Arduino IDE 1.8.15
 */

int input = 3; // Or 2, requirement for attachInterrupt on the UNO.
int f_min = 250; // Hz
int f_max = 500; // Hz
int d_min = 10; // %
int d_max = 90; // %

volatile uint32_t t0 = 0;
volatile uint32_t t1 = 0;
volatile uint32_t t2 = 0;
volatile bool isr_ready = false;

void potentiometer_isr(void)
{
  static bool busy = false;
  
  // Don't overwrite unread results.
  if (isr_ready==false)
  {
    uint32_t t = micros();
    if (digitalRead(input)==1)
    {
      // Rising edge.
      if (busy==false)
      {
        // First edge.
        t0 = t;
        busy = true;
      }
      else
      {
        // Third edge.
        t2 = t;
        busy = false;
        isr_ready = true;
      }
    }
    else if (busy==true) t1 = t; // Second (falling) edge.
  }
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("Two potentiometers on one digital input with interrupts.");
  pinMode(input,INPUT);
  attachInterrupt(digitalPinToInterrupt(input),potentiometer_isr,CHANGE);
  isr_ready = false;
}

void loop(void)
{
  if (isr_ready==true)
  {
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
    
    isr_ready = false;
  }
}
