//Defines for hardware setup
#define START_PIN    A0  // Feedback from the remote on/off switch
#define NUM_OUTPUTS  32  // will never change for this board

//Defines for application
#define UPDATES_PER_SECOND 10     // 10Hz
#define DISABLED -1               // Set this as the output time to disable it
#define STAY_ON_DURATION_MS 1000  // one second stay on time

// The global timer used to play the show
unsigned long timer = 0;  

// Memory structure to store the pin and output ignite time
typedef struct 
{
  int pin;
  long igniteTime;
}output;

// All 32 outputs
// Set the time in 100ms increments (because this runs at 10Hz)
// The pin is the digital output, should not be changed
// This time is when you want the firework to ignite
// Set time to 'DISABLE' for any outputs that are not used 
output outputs[NUM_OUTPUTS] = 
{
 // PIN, Time
   {22, 500}, // OUTPUT 1
   {23, 1000}, // OUTPUT 2
   {24, 1500}, // OUTPUT 3
   {25, 2000}, // OUTPUT 4
   {26, 2500}, // OUTPUT 5
   {27, 3000}, // OUTPUT 6
   {28, 3500}, // OUTPUT 7
   {29, 4000}, // OUTPUT 8
   {30, 4500}, // OUTPUT 9
   {31, 5000}, // OUTPUT 10
   {32, 5500}, // OUTPUT 11
   {33, 6000}, // OUTPUT 12
   {34, 6500}, // OUTPUT 13
   {35, 7000}, // OUTPUT 14
   {36, 7500}, // OUTPUT 15
   {37, 8000}, // OUTPUT 16
   {38, 8500}, // OUTPUT 17
   {39, 9000}, // OUTPUT 18
   {40, 9500}, // OUTPUT 19
   {41, 10000}, // OUTPUT 20
   {42, 10500}, // OUTPUT 21
   {43, 11000}, // OUTPUT 22
   {44, 11500}, // OUTPUT 23
   {45, 12000}, // OUTPUT 24
   {46, 12500}, // OUTPUT 25
   {47, 13000}, // OUTPUT 26
   {48, 13500}, // OUTPUT 27
   {49, 14000}, // OUTPUT 28
   {50, 14500}, // OUTPUT 29
   {51, 15000}, // OUTPUT 30
   {52, 15500}, // OUTPUT 31
   {53, 16000}  // OUTPUT 32
};

//comment out the next line if your relays are active LOW
#define ACTIVE_HIGH

#ifdef ACTIVE_HIGH
#define ACTIVE HIGH
#define INACTIVE LOW
#else
#define ACTIVE LOW
#define INACTIVE HIGH
#endif

// Turn off all outputs
void allOff()
{
  //Turn off all outputs
  for( int i = 0; i < NUM_OUTPUTS; i++) 
  {
      digitalWrite(outputs[i].pin, INACTIVE);
  }
}

// Cycle through the array and turn on or off the outputs 
void playShow()
{
  for( int i = 0; i < NUM_OUTPUTS; i++) 
  {  
    if( outputs[i].igniteTime != DISABLED &&
        timer >= (unsigned long)outputs[i].igniteTime && 
        timer < (unsigned long)(outputs[i].igniteTime + STAY_ON_DURATION_MS) )
    {
      //Check if it is currently off
       if(digitalRead(outputs[i].pin) == INACTIVE)
       {
        Serial.print("Output ");
        Serial.print(outputs[i].pin);
        Serial.println(" is On");
       }
       
       //Turn output on
       digitalWrite(outputs[i].pin, ACTIVE);
    }
    else
    {
      //Check if it is currently on
      if(digitalRead(outputs[i].pin) == ACTIVE)
       {
        Serial.print("Output ");
        Serial.print(outputs[i].pin);
        Serial.println(" is Off");
       }
       
      //Turn output off
      digitalWrite(outputs[i].pin, INACTIVE);
    }
  }
}

// setup serial and digital outputs
void setup() 
{
  Serial.begin(9600);
  
  for( int i = 0; i < NUM_OUTPUTS; i++) 
  {
      pinMode(outputs[i].pin, OUTPUT);
      digitalWrite(outputs[i].pin, INACTIVE);
  }

  // This is an analog input pin
  pinMode(START_PIN, INPUT);

  Serial.println("Ready");
}

// Run loop at a fixed frequency
void loop() 
{
  static unsigned long current_time = millis();
  static const int interval = 1000 / UPDATES_PER_SECOND;

  // cycle set to 10Hz
  if(millis() > current_time + interval)
  {
    // Reset our frequency timer
    current_time = millis();

    
    if(digitalRead(START_PIN) == HIGH)
    {
      if(timer == 0)
      {
        Serial.println("Show has started.");
      }
      
      // Set next cycle time
      timer += interval; 

      // show time!
      playShow();
    }
    else
    {
      if(timer != 0)
      {
        Serial.println("Show has stopped.");
      }

      // turn all the relays off
      allOff();

      // reset our timer to restart the show
      timer = 0;  
    }
  }
}
