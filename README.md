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

The implemented solution is a hardware **TinyML project** with an **Arduino Nano 33 BLE Sense** and the use of **Edge Impulse** - a machine learning platform. Therefore TinyML also known as embedded machine learning empowers the deployment and processing of machine learning (ML) models into resource constrainted edge devices. This brings a lot of benefits like low latency, privacy, low power, and reduced bandwidth. (Cf. Warden, P., & Situnayake, D. 2019, p. 3; Sharma, R. 2022, p. 12) In the last years, different technologies have been developed that make it possible to run miniature, highly optimized machine learning models on low-power microcontrollers. One famous library for embedded machine learning is TensorFlow Lite and the used platform Edge Impulse makes use of the TensorFlow ecosystem for training, optimizing, and deploying deep learning models. (Cf. Tensorflow 2023) <br>
<br>
The goal of this project is **handwritten digit recognition by movement in the air**. This can be used for the password entry of handwritten digits to facilitate different activities in the daily life of visually impaired people, for example, to have the front door opened. <br>
To implement and deploy the project, the following high-level project plan was set up.

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/project_plan.png"
     height="400" width="711"/>
</p>
<div align="center"><i>Figure 1: Project plan</i></div>

<a name="work"></a>
## 2. Related work

Handwriting recognition (HWR) is a topic of growing interest in the research community and can solve real-world problems. For HWR there are different approaches which, on the one hand, use cameras and scanners and, on the other hand, use motion sensors. Chen, L. et al. proposed a real-time air-wirting character recognition wearable system based on edge computing and deep learning. The reached accurary of there approach is 97.95% by using an Arduino Nano 33 BLE sense and capturing motion data by inertial measurement units (IMUs). This accurary is more than any air-writing recognition with optical sensors could reach, as there are around 90% accuracy. Chen, L. et al. use a five-layer CNN which has been converted into TensorFlow Lite format to run on Arduino Nano 33 BLE Sense to recognize 10 digits and 26 lower-case letters. For the data aquistion, 35 students with different gender and dominant hand collected data for model training. (Cf. Chen, L. et al. 2022) <br> <br>
Furthermore, Chai, Y. et al. presented a wireless-inertial-measurement-unit- (WIMU-) based hand motion analysis technique for handwirting recognition and achieved an accuracy of 98% with an accelerometer and gyroscope-based method. They used their WIMU motion sensor-based hand-writing interface using the 26 lowercase letters of the English alphabet and digits. Moreover, Alemayoh, T. T. et al. developed in their paper a deep-learing-based compact smart digital pen that recognizes 36 alphanumeric characters. Unlike others methods they used not only inertial data but using an inertial force sensor. The data was recorded of six volunteers and trained with different deep-learning methods. The Vison transformer (ViT) network outperformed the other methods by achieving a validation accurary of 99.05%. (Cf. Alemayoh, T. T. et al. 2022) A paper of Preethi, K., & Chithra, S. researched specificly in the field of on-air recognition system impared people. Their goal was to develop character recognition system to develop cost effective assistive technologies to provide blind people with greater degree of confidence in their activities. The device here is also equipped with gyroscope and accelerometer to recognize the hand movement. (Cf. Preethi, K., & Chithra, S. 2018) <br> <br>
All the papers studied and analyzed formed the basis for this research project.

<a name="impl"></a>
## 3. Implementation and hardware setup

Before starting with the implementation and hardware setup of the project, the whole process to be mapped whas been modeled using a process diagram with BPMN 2.0 notation. <br>
<br>
<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/process_diagram.png"
     height="1000" />
</p>
<div align="center"><i>Figure 2: Process diagram</i></div>
<br>

### Hardware setup
The hardware setup of the projects consists of different components listed below. 
<br>
<br>
**Technical components**
* [Arduino Nano 33 BLE Sense](https://docs.arduino.cc/hardware/nano-33-ble-sense)
* Push button
* Power bank (5V/1A) - older version that doesn't turn off directly
* Power cable (USB/Micro USB)
* Piezo element
* Bread board
* 2x Jumper wire cable
<br><br>

**Additional components**
* 2x Cable ties
* Wooden spoon
* Sticky tape
<br>
The system architecture and hardware setup shows how the components are used in the project and how there were build together. The Arduino close-up shows in more detail which elements of the Arduino Nano 33 BLE Sense are used.
<br>
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

### Software tools and libraries
The following software tools are used for the implementation of the project. <br>
* [Edge Impulse](https://www.edgeimpulse.com/)
* [Arduino IDE](https://www.arduino.cc/en/software)

The following software libraries are used for the implementation of the project. <br>
* [Arduino_LSM9DS1](https://www.arduino.cc/reference/en/libraries/arduino_lsm9ds1/)
* [AirWriting_inferencing - ML model library](https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/AirWriting_inferencing.zip)

### Deep Learning Workflow
The deep learning workflow was implemented based on Warden, P., & Situnayake, D. and using the software suite Edge Impulse. The individual steps of the deep learning workflow are described and explained in more detail below.
<br> <br>
**1. Decide on a goal** <br>
The goal is the handwritten digit recognition of the digits 1, 2 and 3 with an Arduino Nano 33 BLE Sense. The described problem is a classification problem. Classification is a machine learning task that takes a set of input data and returns the probability that this data fits each of a set of known classes. In this example, the classes are: number_1, number_2 and number_3. (Cf. Warden, P., & Situnayake, D. 2019)<br>
<br>
**2. Collect a dataset** <br>
In the second step, the data that is needed has to be identified and the final dataset is created. In our project, the data was collected using the hardware setup above and the drawn digit template in the following figure. The training and test data was split with 80/20 distribution. Overall, 600 data entries are collected, 300 in sitting position and 300 in standing position. The data entries are split equally to all digits (1, 2 and 3). Furthermore, 300 data entries were collected with the right hand and 300 with the left hand. <br>

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
In the next step, the model architecture is designed by generating features from data. The settings and features can be found in the following Screenshot of Edge Impulse. (Cf. Warden, P., & Situnayake, D. 2019) <br>

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/design_model.jpg"/>
<div align="center"><i>Figure 8: Machine learning model design</i></div> <br>
<br>

**4. Train the model** <br>
During the training the model learns how to produce the correct output for a given set of inputs. This involves feeding training data through a model and making small adjustments until it makes the most accurate predictions possible. (Cf. Warden, P., & Situnayake, D. 2019) All the settings for training can be seen in the following Screenshots of Edge Impulse.
<br>
<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/train_model.jpg"/>
<div align="center"><i>Figure 9: Model training</i></div> <br>

**5. Convert the model** <br>
The last step before running inference is to convert the model in TensorFlow Lite with Edge Impulse. <br>

**6. Run inference** <br>
After the model has been converted, it’s ready to deploy! <br>
<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/ML_inference.gif" />
<div align="center"><i>Figure 10: Run inference</i></div> <br>
<br>

**7. Evaluate and troubleshoot** <br>
In conclusion, the trained model is already pretty good for the fewer data that was collected for the project due to time and resource restrictions,. To improve the accuracy of the model more data is needed with different positions of users etc. With the second deployed model, it was recognized that the model performs badly if the user is standing. This was because the training and test data were collected only in a sitting position.<br>

### How to execute and run
1. [Getting started and setup the Arduino Nano 33 BLE Sense](https://docs.arduino.cc/hardware/nano-33-ble) <br>
2. Build the hardware setup with the above mentioned components and as shown in the given figure <br>
3. Import and install the needed libraries as shown below <br>
<br>
<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/add%20library.png" />
<div align="center"><i>Figure x: Add Library</i></div> <br>

<p align="center">
  <img src="https://github.com/moellpau/HandwrittenDigitRecognition/blob/main/images/examples.png" />
<div align="center"><i>Figure x: Examples</i></div> <br>
4. Open, compile and upload the code to the Arduino Nano 33 BLE Sense <br>
Screenshots <br>
5. Start the process with pushing the Push button <br>

<a name="trouble"></a>
## 4. Troubleshooting
This troubleshooting documentation is intended to give information on how to solve and prevent problems that appeared during the implementation process. <br>
| No. | Trouble    | Fixes   |
| :---:   | :---: | :---: |
| #1 | Edge Impulse lost connection to Arduino device while data acquistion  | Flash Arduino  |
| #2 | Add Arduino device to Edge Impulse, connect a fully supported development board   | [Use tutorial](https://docs.edgeimpulse.com/docs/development-platforms/officially-supported-mcu-targets/arduino-nano-33-ble-sense) and execute more than ones   |
| #3 | tbd   | [Use forum entry](https://forum.edgeimpulse.com/t/arduino-ble-sense-libraries-invalid-model-for-current-sensor/3730/2) or add this line of code "#define EI_CLASSIFIER_SENSOR EI_CLASSIFIER_SENSOR_ACCELEROMETER"  |
| #4 | Error "ERR: EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME should be equal to 3 (the 3 sensor axes)" while compiling and uploading code to Arduino   | estart Arduino IDE and upload code again   |
| #5 | Die Schleife hat vorher nämlich darauf gewartet, dass eine serielle Verbindung aufgebaut wird. Das geschieht nur, wenn ein PC angeschlossen ist. Quasi „Solange Seriell nicht existiert, lass die Schleife laufen“  | Remove "while (!Serial);"   |

<a name="con"></a>
## 5. Conclusion and future work

With the project work, a prototype for handwritten digit recognition by movement in the air could be developed and implemented. Furthermore, this project leaves much room for further investigation and future work. It would be beneficial for the use case to add more digits and letters to the model to make it possible to enter a more complex password. Moreover, there is the need for a possibility to check and enter more than one digit or letter and a connection to the specific system like a door etc. Another extension would be to add a speaker and amplifier to the Arduino to add custom sounds and spoken words. To improve the accuracy of the machine learning model, it is important to do hyperparameter tuning and train the model in the correct position of the user or add more training and test data.

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
