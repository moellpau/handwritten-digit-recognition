/* Edge Impulse ingestion SDK
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* Includes ---------------------------------------------------------------- */
#include <AirWriting_inferencing.h>
#include <Arduino_LSM9DS1.h> //Click here to get the library: http://librarymanager/All#Arduino_LSM9DS1

/* Constant defines -------------------------------------------------------- */
#define CONVERT_G_TO_MS2 9.80665f
#define MAX_ACCEPTED_RANGE 2.0f  // starting 03/2022, models are generated setting range to +-2, but this example use Arudino library which set range to +-4g. If you are using an older model, ignore this value and use 4.0f instead

#define RED 22
#define GREEN 23
#define BLUE 24

#define EI_CLASSIFIER_SENSOR EI_CLASSIFIER_SENSOR_ACCELEROMETER  // EINFÜGEN IN JEDE DATEI

/*
 ** NOTE: If you run into TFLite arena allocation issue.
 **
 ** This may be due to may dynamic memory fragmentation.
 ** Try defining "-DEI_CLASSIFIER_ALLOCATION_STATIC" in boards.local.txt (create
 ** if it doesn't exist) and copy this file to
 ** `<ARDUINO_CORE_INSTALL_PATH>/arduino/hardware/<mbed_core>/<core_version>/`.
 **
 ** See
 ** (https://support.arduino.cc/hc/en-us/articles/360012076960-Where-are-the-installed-cores-located-)
 ** to find where Arduino installs cores on your machine.
 **
 ** If the problem persists then there's not enough memory for this model and application.
 */

/* Private variables ------------------------------------------------------- */
static bool debug_nn = false;  // Set this to true to see e.g. features generated from the raw signal

const int buttonPin = D6;  // the number of the pushbutton pin
const int soundPin = D7;   // the number of the LED pin


/**
* @brief      Arduino setup function
*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(soundPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  // comment out the below line to cancel the wait for USB connection (needed for native USB)
  
  // while (!Serial)
  //  ;

  Serial.println("Edge Impulse Inferencing Demo");

  if (!IMU.begin()) {
    ei_printf("Failed to initialize IMU!\r\n");
  } else {
    ei_printf("IMU initialized\r\n");
  }

  if (EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME != 3) {
    ei_printf("ERR: EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME should be equal to 3 (the 3 sensor axes)\n");
    return;
  }
}

/**
 * @brief Return the sign of the number
 * 
 * @param number 
 * @return int 1 if positive (or 0) -1 if negative
 */
float ei_get_sign(float number) {
  return (number >= 0.0) ? 1.0 : -1.0;
}

/**
* @brief      Get data and run inferencing
*
* @param[in]  debug  Get debug info if true
*/

void loop() {
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);

  int buttonState = digitalRead(buttonPin);

  //buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    delay(500);
    ei_printf("\nStarting inferencing in 3 seconds...\n");

    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);

    startSound();
    delay(250);

    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, HIGH);

    ei_printf("Sampling...\n");
    tone(soundPin, 800, 2000);
    digitalWrite(GREEN, LOW);  // gelbes Licht geht an während Sampling + Classifien
    digitalWrite(RED, LOW);

    // Allocate a buffer here for the values we'll read from the IMU
    float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = { 0 };

    for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += 3) {
      // Determine the next tick (and then sleep later)
      uint64_t next_tick = micros() + (EI_CLASSIFIER_INTERVAL_MS * 1000);

      IMU.readAcceleration(buffer[ix], buffer[ix + 1], buffer[ix + 2]);

      for (int i = 0; i < 3; i++) {
        if (fabs(buffer[ix + i]) > MAX_ACCEPTED_RANGE) {
          buffer[ix + i] = ei_get_sign(buffer[ix + i]) * MAX_ACCEPTED_RANGE;
        }
      }

      buffer[ix + 0] *= CONVERT_G_TO_MS2;
      buffer[ix + 1] *= CONVERT_G_TO_MS2;
      buffer[ix + 2] *= CONVERT_G_TO_MS2;

      delayMicroseconds(next_tick - micros());
    }

    // Turn the raw buffer in a signal which we can the classify
    signal_t signal;
    int err = numpy::signal_from_buffer(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
    if (err != 0) {
      ei_printf("Failed to create signal from buffer (%d)\n", err);
      return;
    }

    // Run the classifier
    ei_impulse_result_t result = { 0 };

    err = run_classifier(&signal, &result, debug_nn);
    if (err != EI_IMPULSE_OK) {
      ei_printf("ERR: Failed to run classifier (%d)\n", err);
      return;
    }

    // print the predictions
    ei_printf("Predictions ");
    ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
              result.timing.dsp, result.timing.classification, result.timing.anomaly);
    ei_printf(": \n");
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
      ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
    }

    // find maximum
    float highest_value = 0;
    size_t highest_idx = 0;
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
      if (result.classification[ix].value > highest_value) {
        highest_value = result.classification[ix].value;
        highest_idx = ix;
      }
    }

    digitalWrite(GREEN, HIGH);  // gelbes Licht geht aus, weil fertig mit Classifien
    digitalWrite(RED, HIGH);
    delay(700);

    ei_printf("    Highest Label: %s\n", result.classification[highest_idx].label);

    if (result.classification[highest_idx].label == "Number_1") {
      blinkTimes(1);
    }

    if (result.classification[highest_idx].label == "Number_2") {
      blinkTimes(2);
    }

    if (result.classification[highest_idx].label == "Number_3") {
      blinkTimes(3);
    }


    delay(500);

    if (result.classification[highest_idx].label == "Number_1") {
      ei_printf("Richtig");
      digitalWrite(GREEN, LOW);
      successSound();
      digitalWrite(GREEN, HIGH);
    } else {
      ei_printf("Falsch");
      digitalWrite(RED, LOW);
      failureSound();
      digitalWrite(RED, HIGH);
    }


#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("    anomaly score: %.3f\n", result.anomaly);
#endif
  }
}

void startSound() {
  tone(soundPin, 400);
  delay(600);
  noTone(soundPin);
  delay(250);
  tone(soundPin, 400);
  delay(600);
  noTone(soundPin);
  delay(250);
  tone(soundPin, 400);
  delay(600);
  noTone(soundPin);
}

void failureSound() {
  tone(soundPin, 650);
  delay(200);
  noTone(soundPin);
  tone(soundPin, 500);
  delay(500);
  noTone(soundPin);
}

void successSound() {
  tone(soundPin, 600);
  delay(200);
  noTone(soundPin);
  tone(soundPin, 750);
  delay(500);
  noTone(soundPin);
}

void blinkTimes(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BLUE, LOW);
    delay(250);
    digitalWrite(BLUE, HIGH);
    delay(250);
  }
}

#if !defined(EI_CLASSIFIER_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_ACCELEROMETER
#error "Invalid model for current sensor"
#endif
