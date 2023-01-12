# Arduino Auto-Irrigation System

## I. Introduction

This project looks into developing an automated irrigation system that could be controlled and monitored through a mobile application. This system shall work to minimize the number of workers in a crop field, control and save water and electricity, increase agricultural yield using small quantities of water, minimize manual intervention in watering operations with increasing watering speed, and preserve plants from fungi. All these features contribute to making this system a technological advancement in the world of manual irrigation, which is both time and effort consuming.

## II. Items Used

The following items were used in building this project: Arduino UNO, 16x2 LCD, Breadboard, Soil moisture sensor, One channel 5V Relay, Ultrasonic sensor, Real time clock chip, Ethernet shield, Water level sensor, Jumper cables, LED, Buzzer, and Resistor.

<img width="469" alt="image" src="https://user-images.githubusercontent.com/112485986/212203564-348501f7-5e36-4a2b-8e1b-db5995e02bb7.png">

## III. Basic Working

The Arduino reads the status of the soil: dry, moist, soggy using the soil moisture sensor. If the soil is DRY, it performs the following operations:
1) Checks for the availability of water using the water level sensor.
2) If the water is available, the Pump is turned ON and is automatically turned OFF when sufficient water is supplied. A relay driver circuit drives the pump.
3) If the Water is unavailable, the buzzer buzzes to notify you with a buzz.
The status of soil and the status of the pump is displayed on the LCD screen, sending the data to a website/app, so that the user can monitor the status of the system through the website/app from anywhere in the world.

## IV. Benefits

1. Easy to implement: The materials required for this project are easy to install, easy to replace, and easy to connect thereby contributing to implement a successful project
2. Open source: Use of an open-source controller due to which the used hardware comes at a reasonable price with a free development software.  
3. Modifiability: The project can run in any type of soil and environment with simple and easy modifications to fit the requirements.
4. Communication: Use of internet and a real-time clock to send accurate data to the web server; data including starting and stopping time of the water pump, volume of water used can be seen on the app, making the system able to be monitored easily from everywhere. 
5. Automatic: Automation eliminates the manual operation of opening or closing valves.
6. Energy Saving: Irrigation process starts and stops exactly when required, thus optimizing energy requirements.
7. Cost: While it may seem a tad expensive in the initial stages of buying this product for the farmers in the rural areas, in the long run, it pays off by outweighing the money they used to use for irrigating. 
8. Effective plant growth:  Minimizes water waste and improves plant growth as the plants get the required amount of water in fixed intervals.
9. Saves time

The benefits are totally applicable in the context of our country (Nepal) as the mentioned uses go hand in hand in solving the problems we face.

## VI. Some drawbacks that were found:
1.  Requires electricity.
2.  Initially it might be expensive:
Buying all the technical stuff may seem expensive initially, but if we really look at it in the long-term, then it is cost-effective. You may ask how? So, after installing this system, there is no need for any manpower to operate as the whole system is automatic. The time that farmers used to water the plants is conserved and now can be utilized in other productive works.  Thus, we’ll be able to save energy, time and manpower and therefore in the long-term, we’ll be saving money.

## VII. Further improvements:
Following concepts can be applied to improve the entire system and take it to the next level:
1. Use of a rain sensor that checks the presence of rainwater when the soil is dry to stop interfering with natural irrigation to prevent water loss.
2. Another addition could be use of a temperature sensor and a light sensor. If the temperature is high and the percentage of light is high, then the system will not work because it is not the right time for the irrigation process because the water will easily evaporate during that time. So, the system will only turn on in conditions when there is low light (like during night). 
3. If the water level is low in the tank, then the system will shut down automatically and send SMS to the user, by using a water level sensor. 
4. The problem of electricity can be countered by powering the system with solar power.
5. We can further enhance the system by figuring out different conditions required for proper growth of different types of plants as all plants are different. We can research more about this with the help of agriculture specialists.


