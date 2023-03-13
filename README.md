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

Hardware TinyML project with Arduino Nano 33 BLE Sense with the use of Edge Impulse. <br>
What is TinyML? TinyML enables the deployment and on-device processing of ML models into resource constrainted edge devices. This brings a lot of benefits like low latency, privacy, low power and reduced bandwidth (cf. Warden, P., & Situnayake, D. 2019, p. 3; Sharma, R. 2022, p. 12) In the past few years, a set of technologies have been developed that make it possible to run miniature, highly optimized machine learning models on low-power microcontrollers like the one described above. By using machine learning to interpret sensor data right at the source, embedded applications can become smarter, faster, and more energy efficient, making their own decisions rather than having to stream data to the cloud and wait for a response. This concept is known as embedded machine learning, or TinyML. (cf. Tensorflow 2023) <br>
How to use Tensorflow with Edge Impulse? The Edge Impulse is an end-to-end suite of tooling that helps embedded engineers and domain experts build and test machine learning applications. Edge Impulse makes use of the TensorFlow ecosystem for training, optimizing, and deploying deep learning models to embedded devices. <br>
Use case of the project?
Password entry of handwritten digits by moving in the air to facilitate different activities in the daily life of visually impaired people, for example, to have the front door opened. <br>
Goal of the project?


-> Add picture of project plan

<a name="work"></a>
## 2. Related work

As handwriting recognition (HWR) is a topic of growing interest in the research community which can solve a lot of real-world problems, there are a lot of successful papers. For HWR there are different approaches which can be using the cameras and scanners or using motion sensors. Chen, L. et al. proposed with their paper a real-time air-wirting character recognition wearable system based on edge computing and deep learning. They could reach an accurary of 97.95% with their approach of using an Arudino Nano 33 BLE sense and capturing motion data by inertial measurement units (IMUs). This is way more than any air-writing recognition with optical sensors could reach as there are around 90% accuracy. Chen, L. et al. use a five-layer CNN which has been converted into TensorFlow Lite format to run on Arduino Nano 33 BLE Sense to recognize 10 digits and 26 lower-case letters. For the data aquistion, 35 students of their institute were recruited to collect data for model training. This means there had people with different gender and dominant hand. (Cf.  Chen, L. et al. 2022) <br>
Also Chai, Y. et al. on the other presented a wireless-inertial-measurement-unit - (WIMU-) based hand motion analysis technique for handwirting recognition and achieved an accuracy of 98% with an accelerometer and gyroscope-based method. They were using their WIMU motion sensor-based hand-writing interface using the 26 lowercase letetrs of the English alphabet and digits. <br>
Alemayoh, T. T. et al. developed in their paper a deep-learing-based compact smart digital pen that recognizes 36 alphanumeric characters. Unlike common methods they used not only inertial data but using an inertial force sensor. The data was recorded of six volunteers and different ddeep-learning methods where used like Vison transformer (ViT), CNN, DNN and LSTM. The ViT network outperformed the others to achieve a validation accurary of 99.05%. (Cf. Alemayoh, T. T. et al. 2022). <br>
Preethi, K., & Chithra, S. also developed an on-air recognition system but specificly for impared people. Their goal was to develop character recognition system used to develop cost effective assistive technologies to provide blind people with greater degree of confidence in their activities. The device here is also equipped with gyroscope and accelerometer to recognize the hand movement. (Cf. Preethi, K., & Chithra, S. 2018)
All the named papers where used for inspiration and planning purposeses of the project.

<a name="impl"></a>
## 3. Implementation and hardware setup

* Picture system architecture

### Hardware setup
* Arduino Nano 33 BLE Sense
* Button
* Power Bank
* Speaker

<br>
-> Arduino in more detail - close-up and Picture from complete hardware structure

### Software tools
* Edge Impulse
* Arduino IDE

### Deep Learning Workflow
1. Decide on a goal: Air-writing recognition of the digits 1, 2 and 3 with Arduino Nano 33 BLE Sense
2. Collect a dataset 
* Pcture from hardware usage/training
* Charts about training and test data and dominant/used hand
* Picture of all digits and guide how to draw - start and end point and angle how to use device
3. Design a model architecture
* Structure ML model or screenshots Edge Impulse
4. Train the model
* Screenshots Edge Impulse
5. Convert the model
* Screenshots Edge Impulse
6. Run inference
* Screenshots Edge Impulse
7. Evaluate and troubleshoot
* Confusion matrix of measuring accuracy
(cf. Warden, P., & Situnayake, D. 2019).


### Libraries
* tbd

<a name="trouble"></a>
## 4. Troubleshooting

* enter everything that didn't work

<a name="con"></a>
## 5. Conclusion and future work

* add more digits and letters + sonderzeichen to make a passwort entry possible
* possiblity to check and enter more than one digit etc.
* connection/wifi to specific system like door lock etc.

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
