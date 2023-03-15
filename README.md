# Handwritten digit recognition by movement in the air

Authors: Friederike Marby and Paula Möller <br>
Date: 2023-03-24

## Table of content
1. [ Description and use case ](#desc)
2. [ Related work ](#work)
3. [ Implementation and hardware setup ](#impl)
4. [ Troubleshooting ](#trouble)
5. [ Conclusion and future work ](#con)
6. [ Sources ](#sour)

<a name="desc"></a>
## 1. Description and use case

The implemented solution is a hardware **TinyML project** with an **Arduino Nano 33 BLE Sense** and the use of **Edge Impulse** as machine learning platform. Therefore TinyML also known as embedded machine learning empowers the deployment and processing of machine learning (ML) models into resource constrainted edge devices. This brings a lot of benefits like low latency, privacy, low power and reduced bandwidth. (Cf. Warden, P., & Situnayake, D. 2019, p. 3; Sharma, R. 2022, p. 12) In the last years, different technologies have been developed that make it possible to run miniature, highly optimized machine learning models on low-power microcontrollers. One famous library for membedded machine learning is TensorFlow Lite and the used platform Edge Impulse makes use of the TensorFlow ecosystem for training, optimizing, and deploying deep learning models to embedded devices. (Cf. Tensorflow 2023) <br>
<br>
The goal of this project is the **handwritten digit recognition by movement in the air**. This can be used for the password entry of handwritten digits to facilitate different activities in the daily life of visually impaired people, for example, to have the front door opened. <br>
To implement and deploy the project, the following high-level project plan was set up.

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/project_plan.png"
     height="400" width="711"/>
</p>
<div align="center"><i>Figure 1: Project plan</i></div>

<a name="work"></a>
## 2. Related work

As handwriting recognition (HWR) is a topic of growing interest in the research community which can solve a lot of real-world problems, there are a lot of successful papers. For HWR there are different approaches which can be using the cameras and scanners or using motion sensors. Chen, L. et al. proposed with their paper a real-time air-wirting character recognition wearable system based on edge computing and deep learning. They could reach an accurary of 97.95% with their approach of using an Arudino Nano 33 BLE sense and capturing motion data by inertial measurement units (IMUs). This is way more than any air-writing recognition with optical sensors could reach as there are around 90% accuracy. Chen, L. et al. use a five-layer CNN which has been converted into TensorFlow Lite format to run on Arduino Nano 33 BLE Sense to recognize 10 digits and 26 lower-case letters. For the data aquistion, 35 students of their institute were recruited to collect data for model training. This means there had people with different gender and dominant hand. (Cf.  Chen, L. et al. 2022) <br>
Also Chai, Y. et al. on the other presented a wireless-inertial-measurement-unit - (WIMU-) based hand motion analysis technique for handwirting recognition and achieved an accuracy of 98% with an accelerometer and gyroscope-based method. They were using their WIMU motion sensor-based hand-writing interface using the 26 lowercase letetrs of the English alphabet and digits. <br>
Alemayoh, T. T. et al. developed in their paper a deep-learing-based compact smart digital pen that recognizes 36 alphanumeric characters. Unlike common methods they used not only inertial data but using an inertial force sensor. The data was recorded of six volunteers and different ddeep-learning methods where used like Vison transformer (ViT), CNN, DNN and LSTM. The ViT network outperformed the others to achieve a validation accurary of 99.05%. (Cf. Alemayoh, T. T. et al. 2022). <br>
Preethi, K., & Chithra, S. also developed an on-air recognition system but specificly for impared people. Their goal was to develop character recognition system used to develop cost effective assistive technologies to provide blind people with greater degree of confidence in their activities. The device here is also equipped with gyroscope and accelerometer to recognize the hand movement. (Cf. Preethi, K., & Chithra, S. 2018)
All the named papers where used for inspiration and planning purposeses of the project.

<a name="impl"></a>
## 3. Implementation and hardware setup

Before starting with the implementation and hardware setup, the whole process was modeled using a process diagram. <br>
<br>
<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/process_diagram.png"
     height="1000" />
</p>
<div align="center"><i>Figure 2: Process diagram</i></div>
<br>

### Hardware setup
* [Arduino Nano 33 BLE Sense](https://docs.arduino.cc/hardware/nano-33-ble-sense)
* Push button
* Power bank (5V/1A) - older version that doesn't turn off directly
* Power cable (USB/Micro USB)
* Piezo element
* Bread board
* 2x Jumper wire cable

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/system_architecture.jpeg"/>
</p>
<div align="center"><i>Figure 3: System architecture</i></div>
<br>

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/hardware_setup.jpeg"
     height="400" />
</p>
<div align="center"><i>Figure 4: Hardware setup</i></div>
<br>

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/close_up_arduino.png"
     height="350" />
</p>
<div align="center"><i>Figure 5: Close-up Arduino Nano 33 BLE Sense</i></div>
<br>
<br>

### Software tools
* [Edge Impulse](https://www.edgeimpulse.com/)
* [Arduino IDE](https://www.arduino.cc/en/software)

### Libraries
* [Arduino_LSM9DS1] (https://www.arduino.cc/reference/en/libraries/arduino_lsm9ds1/)
* [Own machine learning model library](https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/AirWriting_inferencing.zip)

### Deep Learning Workflow
**1. Decide on a goal** <br>
Air-writing recognition of the digits 1, 2 and 3 with Arduino Nano 33 BLE Sense. This as a classification problem. Classification is a machine learning task that takes a set of input data and returns the probability that this data fits each of a set of known classes. In this example, there are three classes: number_1, number_2 and number_3.<br>
<br>
**2. Collect a dataset** <br>
Identify data that is needed and create final dataset. The data was collected using the hardware setup above and using the drawn digit template in following figure.
Text about training and test data and dominant/used hand 

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/digit_template.jpg"
     height="170" />
<div align="center"><i>Figure 6: Template of digits</i></div> <br>
<br>

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/data_collection.jpeg"/>
<div align="center"><i>Figure 7: Data collection in Edge Impulse</i></div> <br>
<br>

**3. Design a model architecture** <br>
Generating features from data <br>

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/design_model.jpg"/>
<div align="center"><i>Figure 8: Machine learning model design</i></div> <br>
<br>

**4. Train the model** <br>
Training is the process by which a model learns to produce the correct output for a given set of inputs. It involves feeding training data through a model and making small adjustments to it until it makes the most accurate predictions possible.
<br>
* Underfitting and Overfitting
* Training, validation, and testing
Screenshots Edge Impulse <br>
<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/train_model.jpg"/>
<div align="center"><i>Figure 9: Model training</i></div> <br>

**5. Convert the model** <br>
Throughout this book, we use TensorFlow to build and train models. A TensorFlow model is essentially a set of instructions that tell an interpreter how to transform data in order to produce an output. When we want to use our model, we just load it into memory and execute it using the TensorFlow interpreter.
However, TensorFlow’s interpreter is designed to run models on powerful desktop computers and servers. Since we’ll be running our models on tiny microcontrollers, we need a different interpreter that’s designed for our use case. Fortunately, Tensor‐ Flow provides an interpreter and accompanying tools to run models on small, low- powered devices. This set of tools is called TensorFlow Lite.
Before TensorFlow Lite can run a model, it first must be converted into the Tensor‐ Flow Lite format and then saved to disk as a file. We do this using a tool named the TensorFlow Lite Converter. The converter can also apply special optimizations aimed at reducing the size of the model and helping it run faster, often without sacrificing performance.<br>
Screenshots Edge Impulse <br>

**6. Run inference** <br>
After the model has been converted, it’s ready to deploy! We’ll now use the Tensor‐ Flow Lite for Microcontrollers C++ library to load the model and make predictions. <br>
<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/ML_inference.gif" />
<div align="center"><i>Figure x: Run inference</i></div> <br>
<br>

**7. Evaluate and troubleshoot** <br>
Confusion matrix of measuring accuracy <br>

(cf. Warden, P., & Situnayake, D. 2019).

### How to execute and run

* Hardware setup wie oben abgebildet + mit Kochlöffel
* Arduino initalisieren -> Tutorial verlinken
* welche libraries und wann installieren
* wie und wo den Code ausführen -> mit Screenshots hinterlegen

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/add%20library.png" />
<div align="center"><i>Figure x: Add Library</i></div> <br>

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/examples.png" />
<div align="center"><i>Figure x: Examples</i></div> <br>

<a name="trouble"></a>
## 4. Troubleshooting

* enter everything that didn't work
* Trouble: Edge Impulse lost connection to Arduino device while data acquistion Fix: Flash Arduino
* Trouble: Add Arduino device to Edge Impulse, connect a fully supported development board -> Fix: https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-mcu-targets/arduino-nano-33-ble-senseLink Tutorial and name tips, execute more than one
* Trouble: tbd Fix: https://forum.edgeimpulse.com/t/arduino-ble-sense-libraries-invalid-model-for-current-sensor/3730/2 or easier to add this line of code "#define EI_CLASSIFIER_SENSOR EI_CLASSIFIER_SENSOR_ACCELEROMETER  // EINFÜGEN IN JEDE DATEI"
* Trouble: ERR: EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME should be equal to 3 (the 3 sensor axes) -> Fix: Restart Arduino IDE and upload code again
* Trouble: Die Schleife hat vorher nämlich darauf gewartet, dass eine serielle Verbindung aufgebaut wird. Das geschieht nur, wenn ein PC angeschlossen ist. Quasi „Solange Seriell nicht existiert, lass die Schleife laufen“ Fix: remove "while (!Serial);"

<a name="con"></a>
## 5. Conclusion and future work

* add more digits and letters + sonderzeichen to make a passwort entry possible
* possiblity to check and enter more than one digit etc.
* connection/wifi to specific system like door lock etc.
* custom sounds and words -> connect speaker to Arduino
* Hyperparameter tuning for our model

<a name="sour"></a>
## 6. Sources


* Alemayoh, T. T. et al. (2022): Deep-Learning-Based Character Recognition from Handwriting Motion Data Captured Using IMU and Force Sensors, https://doi.org/10.3390/s22207840.
* Arduino.CC (2023): Nano 33 BLE Sense, in: https://docs.arduino.cc/hardware/nano-33-ble-sense, (12.03.2023).
* Chai, Y. et al. (2016): Handwriting Recognition in Free Space Using WIMU-Based Hand Motion Analysis, https://doi.org/10.1155/2016/3692876.
* Chen, L. et al. (2022): A Wearable Real-Time Character Recognition System Based on Edge Computing-Enabled Deep Learning for Air-Writing, https://doi.org/10.1155/2022/8507706.
* Edge Impulse (2023): Getting started, in: https://docs.edgeimpulse.com/docs/, (12.03.2023).
* Preethi, K. & Chithra, S. (2018): On-Air Character Recognition System For Visually Impaired People. In International Conference for Phoenixes on Emerging Current Trends in Engineering and Management (PECTEAM 2018) (pp. 155-158). Atlantis Press.
* Sharma, R. (2022): Introduction to TinyML, AI Technology & Systems Inc.
* Tensorflow (2023): How TensorFlow helps Edge Impulse make ML accessible to embedded engineers, in: https://blog.tensorflow.org/2021/06/how-tensorflow-helps-edge-impulse-make-ml-accessible.html, (12.03.2023).
* Tensorflow (2023a): How-to Get Started with Machine Learning on Arduino, in: https://blog.tensorflow.org/2019/11/how-to-get-started-with-machine.html, (12.03.2023).
* Warden, P., & Situnayake, D. (2019): Tinyml. Machine learning with tensorflow lite on arduino and ultra-low-power microcontrollers. O'Reilly Media.
