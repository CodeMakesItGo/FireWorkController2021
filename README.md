# FireWork Controller 2021

The build for this firework controller is featured here:
https://youtu.be/X29aCa7rGqE

This project is using the Arduino Mega and 32 relays to individually trigger fireworks.
The timing of the fireworks are in 100ms increments. 

There is not much to this project, as you can see, the program is very simple. 
After setting the time for each output, start the show by setting the analog input 0 high. 
The Arduino will trigger the output and keep it on for a set amount of time. The default is 1 second.
This gives the fuse enough time to ignite. Although the e-matches ignite very fast in my experience. 
