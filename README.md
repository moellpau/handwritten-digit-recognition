# Handwritten digit recognition by movement in the air

Authors: Friederike Marby and Paula Möller <br>
Date: 2023-03-24

## Table of content
1. [ Description and use case ](#desc)
2. [ Related work ](#work)
3. [ Implementation and hardware setup ](#impl)
4. [ Troubleshooting ](#trouble)
5. [ Sources ](#sour)

<a name="desc"></a>
## 1. Description and use case

Hardware TinyML project with Arduino Nano 33 BLE Sense with the use of Edge Impulse. <br>
What is TinyML? TinyML enables the deployment and on-device processing of ML models into resource constrainted edge devices. This brings a lot of benefits like low latency, privacy, low power and reduced bandwidth (cf. Warden, P., & Situnayake, D. 2019, p. 3; Sharma, R. 2022, p. 12) In the past few years, a set of technologies have been developed that make it possible to run miniature, highly optimized machine learning models on low-power microcontrollers like the one described above. By using machine learning to interpret sensor data right at the source, embedded applications can become smarter, faster, and more energy efficient, making their own decisions rather than having to stream data to the cloud and wait for a response. This concept is known as embedded machine learning, or TinyML. (cf. Tensorflow 2023) <br>
How to use Tensorflow with Edge Impulse? The Edge Impulse is an end-to-end suite of tooling that helps embedded engineers and domain experts build and test machine learning applications. Edge Impulse makes use of the TensorFlow ecosystem for training, optimizing, and deploying deep learning models to embedded devices. <br>
Use case of the project?
Password entry of handwritten digits by moving in the air to facilitate different activities in the daily life of visually impaired people, for example, to have the front door opened. <br>
Goal of the project?

<a name="work"></a>
## 2. Related work

* Deep-Learning-Based Character Recognition from Handwriting Motion Data Captured Using IMU and Force Sensors (cf. Alemayoh, T. T. et al. 2022).
* Handwriting Recognition in Free Space Using WIMU-Based Hand Motion Analysis (cf. Chai, Y. et al. 2016).
* A Wearable Real-Time Character Recognition System Based on Edge Computing-Enabled Deep Learning for Air-Writing (cf. Chen, L. 2022).
* On-Air Character Recognition System For Visually Impaired People. In International Conference for Phoenixes on Emerging Current Trends in Engineering and Management (cf.  Preethi, K., & Chithra, S. 2018).

<a name="impl"></a>
## 3. Implementation and hardware setup

### Hardware setup
* Arduino Nano 33 BLE Sense
* Button
* Power Bank
* Speaker

### Software tools
* Edge Impulse
* Arduino IDE

### Deep Learning Workflow
1. Decide on a goal
2. Collect a dataset
3. Design a model architecture
4. Train the model
5. Convert the model
6. Run inference
7. Evaluate and troubleshoot
(cf. Warden, P., & Situnayake, D. 2019).


### Libraries
* tbd

<a name="trouble"></a>
## 4. Troubleshooting


<a name="sour"></a>
## 5. Sources


* Alemayoh, T. T. et al. (2022): Deep-Learning-Based Character Recognition from Handwriting Motion Data Captured Using IMU and Force Sensors, https://doi.org/10.3390/s22207840.
* Arduino.CC (2023): Nano 33 BLE Sense, in: https://docs.arduino.cc/hardware/nano-33-ble-sense, (12.03.2023).
* Chai, Y. et al. (2016): Handwriting Recognition in Free Space Using WIMU-Based Hand Motion Analysis, https://doi.org/10.1155/2016/3692876.
* Chen, L. (2022): A Wearable Real-Time Character Recognition System Based on Edge Computing-Enabled Deep Learning for Air-Writing, https://doi.org/10.1155/2022/8507706.
* Edge Impulse (2023): Getting started, in: https://docs.edgeimpulse.com/docs/, (12.03.2023).
* Preethi, K., & Chithra, S. (2018): On-Air Character Recognition System For Visually Impaired People. In International Conference for Phoenixes on Emerging Current Trends in Engineering and Management (PECTEAM 2018) (pp. 155-158). Atlantis Press.
* Sharma, R. (2022): Introduction to TinyML, AI Technology & Systems Inc.
* Tensorflow (2023): How TensorFlow helps Edge Impulse make ML accessible to embedded engineers, in: https://blog.tensorflow.org/2021/06/how-tensorflow-helps-edge-impulse-make-ml-accessible.html, (12.03.2023).
* Tensorflow (2023a): How-to Get Started with Machine Learning on Arduino, in: https://blog.tensorflow.org/2019/11/how-to-get-started-with-machine.html, (12.03.2023).
* Warden, P., & Situnayake, D. (2019): Tinyml. Machine learning with tensorflow lite on arduino and ultra-low-power microcontrollers. O'Reilly Media.
