
#include <AFMotor.h>

#define trigf 13    // front ultrasonic
#define echof 10    // front ultrasonic
#define trigr 9    // right ultrasonic
#define echor 6    // right ultrasonic
#define trigl 5    // left ultrasonic
#define echol 2    // left ultrasonic
unsigned long durationf, distancef;
unsigned long durationr, distancer;
unsigned long durationl, distancel;
//AF_DCMotor motor(4);

void setup() 
{
 pinMode (echof,INPUT); 
 pinMode (trigf,OUTPUT);
 pinMode (echor,INPUT); 
 pinMode (trigr,OUTPUT);
 pinMode (echol,INPUT); 
 pinMode (trigl,OUTPUT);
  /*Serial.begin(9600);         // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motor.setSpeed(200);
 
  motor.run(RELEASE);*/
}

void loop() 
{
 
 tone (trigf,1,.20);
 durationf = pulseIn( echof, HIGH );
 distancef = durationf/58;
 
 if(distancef > 22)
   {
     //goforward(255);
 else if (distancef==20 || distancef<=22)
      {
        //motor_stop
        tone (trigr,1,.20);
        durationr = pulseIn( echor, HIGH );
        distancer = durationr/58;
        tone (trigl,1,.20);
        durationl = pulseIn( echol, HIGH );
        distancel = durationl/58;
       if(distancer > distancef)
         {
           //turn right
       else 
           {
                //turn left
            }
         }
        
      }
 else if (distancef < 20)
      {
        //gobackward(200);
      }
 delay (60);   
 }
   
   
  
  
  
 /* uint8_t i;
  Serial.print("tick");
  
  motor.run(FORWARD);
  for (i=0; i<255; i++) {
    motor.setSpeed(i);  
    delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor.setSpeed(i);  
    delay(10);
 }
  
  Serial.print("tock");

  motor.run(BACKWARD);
  for (i=0; i<255; i++) {
    motor.setSpeed(i);  
    delay(10);
 }
 
  for (i=255; i!=0; i--) {
    motor.setSpeed(i);  
    delay(10);
 }
  
  Serial.print("tech");
  motor.run(RELEASE);
  delay(1000); *********************/
}
