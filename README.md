# ArduinoSpyDoor
Automated entryway for a secretive spy organization

A screen appears blank until someone approaches the "door"(servo) based on the person's distance from the “door”. A photometer is used to detect the person's distance from the door 
It then displays a “Welcome” message. Then the screen prompts them for an access code. There are 3 types of access codes: Spy (700), Analyst (314), Director (161). 
After 2 incorect attempts, the system alerts those inside that there was an incorrect attempt. On the first try, a message is displayed on the screen, on the second try, a visual signal(Blinking red LED) is made inside HQ to alert them of a potential intruder. 
Once the correct code is put in, the door opens
The values of the sensor for the door, and the number of times each code is used is collected and printed it to a file.
