/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +3.3V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogInPin4 = A4;  // Analog input pin that the potentiometer is attached to
const int analogInPin5 = A5;  // Analog input pin that the potentiometer is attached to
//const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue_1 = 0;        // value read from the pot
int sensorValue_2 = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int Count = 1;

#define LED_A  8          // P2.0
#define LED_B  9          // P2.1
#define LED_C  10         // P2.2
#define LED_D  11         // P2.3
#define TRIAC  12         // P2.4

#define SW     5         // P1.3

void setup() {
    // initialize serial communications at 9600 bps:
    Serial.begin(115200);

    pinMode(SW, INPUT);
    for (Count = 8;Count < 13;Count++)
    {
        pinMode(Count, OUTPUT);
        digitalWrite(Count, LOW);
    }
    Count = 1;
    Serial.println("Press Enter to Start");
    while (Serial.available() == 0);
}

void loop()
{
    // read the analog in value:
    sensorValue_1 = analogRead(analogInPin4);
    sensorValue_2 = analogRead(analogInPin5);
    // map it to the range of the analog out:
    //outputValue = map(sensorValue, 0, 1023, 0, 255);
    // change the analog out value:
    //analogWrite(analogOutPin, outputValue);
    // print the results to the serial monitor:

    Serial.print(Count++);
    while (millis() % 500);
    if (digitalRead(SW) == LOW)
    {
        if(outputValue == 1)
        {
            digitalWrite(TRIAC, LOW);
            digitalWrite(LED_D, LOW);
            outputValue = 0;
        }
        else
        {
            digitalWrite(TRIAC, HIGH);
            digitalWrite(LED_D, HIGH);
            outputValue = 1;
        }
    }

    Serial.print(", TIME mSec," );
    Serial.print(millis());
    Serial.print(", sensor," );
    if (sensorValue_1 > 900 | sensorValue_1 < 100)
        Serial.print("ERROR-");
    //else
    Serial.print(sensorValue_1);
    Serial.print("," );
    if (sensorValue_2 > 900 | sensorValue_2 < 100)
        Serial.print("ERROR-");
    //else
    Serial.print(sensorValue_2);
    Serial.print(", TRIAC = ,");
    Serial.println(outputValue);

    // wait 10 milliseconds before the next loop
    // for the analog-to-digital converter to settle
    // after the last reading:
    digitalWrite(LED_A, HIGH);
    delay(100);
    digitalWrite(LED_A, LOW);
}
