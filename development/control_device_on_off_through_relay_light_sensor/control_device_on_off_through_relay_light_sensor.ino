/*
 *  Control Device (On/Off) Through Relay & Light Sensor.
 *
 *  Copyright (C) 2010 Efstathios Chatzikyriakidis (contact@efxa.org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// sketch global variables.

const int sensorPin = 0; // the pin number of the light sensor.
const int relayPin = 2;  // the pin number of the relay switch.

const int sensorThreshold = 800; // sensor threshold value for the relay.

const int SAMPLES_LENGTH = 50; // number of sensor samples.
const long SAMPLE_DELAY = 40;  // delay time (ms) for next sensor sample.

int lightLevel; // the current fetched light sensor value.

// function prototypes.
const long getSensorValue (const int pin, const int N, const long time);

// startup point entry (runs once).
void setup () {
  // set the relay as an output.
  pinMode(relayPin, OUTPUT);

  // set the light sensor as an input.
  pinMode(sensorPin, INPUT);
}

// loop the main sketch.
void loop () {
  // get a value from the input sensor.
  lightLevel = getSensorValue(sensorPin, SAMPLES_LENGTH, SAMPLE_DELAY);

  // switch the relay (On/Off) according to the value of light sensor.
  digitalWrite(relayPin, (lightLevel > sensorThreshold) ? HIGH : LOW);
}

// get an average value from the input sensor.
const long getSensorValue(const int pin, const int N, const long time)
{
  static int curSample; // current sensor sample.
  static long curValue; // current sensor value.

  // current value variable first works as a sum counter.
  curValue = 0;

  // get sensor samples first with delay to calculate the sum of them.
  for (int i = 0; i < N; i++) {
    // get sensor sample.
    curSample = analogRead(pin);

    // add sample to the sum counter.
    curValue += curSample;

    // delay some time for the next sample.
    delay(time);
  }

  // get the average sensor value.
  return (curValue / N);
}
