#include <NewPing.h> // include a special library called NewPing (Libraries are long code which was written by experts to make our life easier) that helps us to communicate with the sensor.

#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Initiating a new sensor with our previous settings.

const int channelA_pwm = 3; //Defining the Pin to control Motor A speed.
const int channelA_break = 9; //Defining the Pin to control Motor A break.
const int channelA_direction = 12; //Defining the Pin to control Motor A direction.

const int channelB_pwm = 11; //Defining the Pin to control Motor B speed.
const int channelB_break = 8; //Defining the Pin to control Motor B break.
const int channelB_direction = 13; //Defining the Pin to control Motor B direction.
int distance = 10 //distance in cm 

void setup() {
  //Start serial communication between Arduino and the computer via USB
  Serial.begin(9600);

  //Setup Channel A & B
  pinMode(channelA_pwm, OUTPUT);
  pinMode(channelA_break, OUTPUT);
  pinMode(channelA_direction, OUTPUT);

  pinMode(channelB_pwm, OUTPUT);
  pinMode(channelB_break, OUTPUT);
  pinMode(channelB_direction, OUTPUT);

}

void loop() {
  int cm = sonar.ping_cm(); //declear a variable called "cm" to store the distance value from the sensor.
  //Printing the distance on the Serial Monitor.
  Serial.print("Distance: ");
  Serial.println(cm);

  if (cm > distance) // choose a distance to let the robot move foreward.
  {
    forward(150); //go forward @ speed 15

  }
  else if (cm <= distance) {  // choose a distance to let the robot turn.
  
    turn(100,200); //Turn @ 15 speed and 20 delay(in milliseconds)

  }

}

void forward(int motorSpeed) //This is the functions that controls the motores to go forward, and it has one argument which is the motor speed.
{

  //forward @ motorSpeed specified by user.
  digitalWrite(channelA_direction, HIGH);  //Setting direction of Channel A
  digitalWrite(channelA_break, LOW);   //Disengage the Brake for Channel A
  analogWrite(channelA_pwm, motorSpeed - 10);    //Spins the motor on Channel A at motorSpeed specified by user.
  digitalWrite(channelB_direction, LOW); //Setting direction of Channel B
  digitalWrite(channelB_break, LOW);   //Disengage the Brake for Channel B
  analogWrite(channelB_pwm, motorSpeed + 10);  //Spins the motor on Channel B at motorSpeed specified by user.

}

void turn(int motorSpeed, int turnDelay) //This functions controls the motores to turn, and it has two arguments which are the motor speed, and the time our robot will spend turning.
{

  //turn  @ motorSpeed, and turning delay specified by user.
  digitalWrite(channelA_direction, HIGH); //Setting direction of Channel A
  digitalWrite(channelA_break, LOW);   //Disengage the Brake for Channel A
  analogWrite(channelA_pwm, motorSpeed);    //Spins the motor on Channel A at motorSpeed specified by user.
  digitalWrite(channelB_direction, HIGH); //Setting  direction of Channel B
  digitalWrite(channelB_break, LOW);   //Disengage the Brake for Channel B
  analogWrite(channelB_pwm, motorSpeed);   //Spins the motor on Channel B at low speed
  delay(turnDelay);
}
