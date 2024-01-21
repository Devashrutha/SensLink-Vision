
<a name="readme-top"></a>

[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Devashrutha/SensLink-Vision/">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">SensLink-Vision</h3>

  <p align="center">
    Custom STM32F4-based LoRa Transceiver with IMU, Baro and LIDAR
    <br />
    <a href="https://github.com/Devashrutha/SensLink-Vision"><strong>Explore the docs »</strong></a>
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project
This is a project that took a lot of time and effort. It is the culmination of everything I learned during my engineering. Although it is still a work in progress in the programming department fully written in `C/C++`, it is at a stage where it can be used.

The main PCB containing the `STM32F411CE` was designed in `Altium` while the `LoRa Transceiver PCB` was designed in `Ki-CAD`. The main board comprises an `MPU-6050` IMU, a `BMP280` barometer, and a `VI53L1X` laser range finder. An onboard SD card reader can log the data read from the sensors. A `type C` connector can stream data using a `virtual COM port`.

I decided to use two boards one for data collection and the other as a ground station. Both use `LCD screens` which stream the data from the sensors in real-time. An `RP2040` is used to drive these displays.

* MPU-6050 uses I2C for data communication.
* BMP-280 uses I2C for data communication.
* VI53L1X uses I2C for data communication.
* The LORA Ra-02 module uses USART for data communication between the module and MCU.
* The displays use SPI for data communication.
* The SD card uses SDIO for data communication.

All of this would not be possible if not for the open-source libraries that were available for the sensors and STM32-CUBE IDE.

Here are some of the pictures of the devices.



<p align="right">(<a href="#readme-top">back to top</a>)</p>








[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]:https://www.linkedin.com/in/devashrutha-s/
