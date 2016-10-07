#include <AFMotor.h>
#include <NewPing.h>

//int Speed;

AF_DCMotor motor_FR(1);
AF_DCMotor motor_FL(2);
AF_DCMotor motor_BR(4);
AF_DCMotor motor_BL(3);

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, ULTRA_MAX_DISTANCE);
NewPing ultraLeft(18,19);   // (Trig PIN,Echo PIN)
NewPing ultraRight(14,15);  // (Trig PIN,Echo PIN)
NewPing ultraFront(16,17);  // (Trig PIN,Echo PIN)
int ULTRA_MAX_DISTANCE=200;

int MAX_RANGE=28;
int MIN_RANGE=MAX_RANGE-5;
int DELAY_In_TURN=15;
int ALERT_OBSTACLE=MAX_RANGE*1.3;

int MAX_SPEED=90;
int TURN_SPEED=140;
int NORMAL_SPEED=50;
int BACKWARD_SPEED=70;

int MARGIN_DISTANCE=20;

int HangCount=0;

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Motors test!");
  motor_FR.setSpeed(MAX_SPEED);
  motor_FL.setSpeed(MAX_SPEED);
  motor_BR.setSpeed(MAX_SPEED);
  motor_BL.setSpeed(MAX_SPEED);
  
  Serial.print("Right Sensor: ");
  Serial.println(Get_Distance(ultraRight));
  
  Serial.print("Left Sensor: ");
  Serial.println(Get_Distance(ultraLeft));
  
  Serial.print("Front Sensor: ");
  Serial.println(Get_Distance(ultraFront));
}
void loop() {
  if (Get_Distance(ultraFront)>=ALERT_OBSTACLE){
      Serial.println("Forward Full Speed: ");
    Go_Forward(MAX_SPEED);
  }
    if (Get_Distance(ultraFront)<ALERT_OBSTACLE){
      Serial.println("Forward HalfSpeed: ");
    Go_Forward(NORMAL_SPEED);
  }
  // Truning
  if (Get_Distance(ultraFront)<=MAX_RANGE && Get_Distance(ultraFront)>=MIN_RANGE){
    Turn;
  }
  if (Get_Distance(ultraFront)<=MAX_RANGE && Get_Distance(ultraFront)>=MIN_RANGE){
    Turn;
  }
  // Obsacle
  if (Get_Distance(ultraFront)<=MIN_RANGE){
      Serial.println("Backward: ");
    do{ 
        Go_Backword(BACKWARD_SPEED);
              Serial.println("Backward LOOP: ");
      }while (Get_Distance(ultraFront)<=MIN_RANGE);
      //Turning
       Turn();

  }
  Checker();
}


void Turn(){
      Stop();
//      delay(50);
      if(Get_Distance(ultraRight)>=MAX_RANGE && Get_Distance(ultraRight)>=Get_Distance(ultraLeft)){
        //Turning Right
//        //Turning Till FRONT = RIGHT
          Serial.println("Right: ");
          do{
              TurnRight(TURN_SPEED);
              delay(DELAY_In_TURN);
          }while (Get_Distance(ultraFront)<MIN_RANGE && Get_Distance(ultraFront)<Get_Distance(ultraRight));


//          if (Get_Distance(ultraFront)<MIN_RANGE){
//              Serial.println("More Right: ");
//              delay(DELAY_In_TURN);
//          }
     }
      
      if(Get_Distance(ultraLeft)>=MAX_RANGE && Get_Distance(ultraLeft)>=Get_Distance(ultraRight)){
        //Turning Left
          Serial.println("Left: ");
          do{
             TurnLeft(TURN_SPEED);             
            delay(DELAY_In_TURN);
          }while (Get_Distance(ultraFront)<MAX_RANGE && Get_Distance(ultraFront)<Get_Distance(ultraLeft));


//          if (Get_Distance(ultraFront)<MIN_RANGE){
//              Serial.println("More Left: ");
//              delay(DELAY_In_TURN);
//          }
//          if (Get_Distance(ultraFront)<MIN_RANGE){
//              Serial.println("More Left: ");
//              delay(DELAY_In_TURN);
//          }
//          if (Get_Distance(ultraFront)<MIN_RANGE){
//              Serial.println("More Left: ");
//              delay(DELAY_In_TURN);
//          }
      }
}


int Get_Distance(NewPing UltaSonic){
  delay(70);
  unsigned int uS = UltaSonic.ping(); // Send ping, get ping time in microseconds (uS).
  int Distance=uS / US_ROUNDTRIP_CM;
  if (Distance==0){
    Distance=ULTRA_MAX_DISTANCE;
  }
  return (Distance); // Convert ping time to distance in cm and print result (0 = outside set distance range)
}
void Stop(){
    Serial.println("Stop");
    motor_FR.run(RELEASE);
    motor_FL.run(RELEASE);
    motor_BR.run(RELEASE);
    motor_BL.run(RELEASE);
  }
void Go_Forward(int Speed){
//  Serial.println("Going Forward");
  motor_FR.run(FORWARD);
  motor_FL.run(BACKWARD);
  motor_BR.run(FORWARD);
  motor_BL.run(BACKWARD);
  motor_FR.setSpeed(Speed);
  motor_FL.setSpeed(Speed);
  motor_BR.setSpeed(Speed);
  motor_BL.setSpeed(Speed); 
}
void Go_Backword(int Speed){
  motor_FR.run(BACKWARD);
  motor_FL.run(FORWARD);
  motor_BR.run(BACKWARD);
  motor_BL.run(FORWARD);
  motor_FR.setSpeed(Speed);
  motor_FL.setSpeed(Speed);
  motor_BR.setSpeed(Speed);
  motor_BL.setSpeed(Speed); 
}
void TurnLeft(int Speed){
//  Serial.println("Turning Left");
  motor_FR.run(FORWARD);
  motor_FL.run(FORWARD);
  motor_BR.run(FORWARD);
  motor_BL.run(FORWARD);
  motor_FR.setSpeed(Speed);
  motor_FL.setSpeed(Speed);
  motor_BR.setSpeed(Speed);
  motor_BL.setSpeed(Speed); 
}
void TurnRight(int Speed){
//    Serial.println("Turning Right");
  motor_FR.run(BACKWARD);
  motor_FL.run(BACKWARD);
  motor_BR.run(BACKWARD);
  motor_BL.run(BACKWARD);
  motor_FR.setSpeed(Speed);
  motor_FL.setSpeed(Speed);
  motor_BR.setSpeed(Speed);
  motor_BL.setSpeed(Speed); 
}
void Checker(){
    Serial.println("Checker test!");
    if (HangCount>=1){
       HangCount=0;
       Turn(); 
    }
    else{
      int Left=Get_Distance(ultraLeft);
      int Right=Get_Distance(ultraRight);
      int Front=Get_Distance(ultraFront);
      
      if (Left==Get_Distance(ultraLeft) && Right==Get_Distance(ultraRight) && Front==Get_Distance(ultraFront)){
          // Hanged
          Serial.println("----------");
          Serial.println("Found Hang");
          Serial.println("Right,Front,Left");
          Serial.println(Right);
          Serial.println(Front);
          Serial.println(Left);
          Serial.println("----------");
          do{ 
          Go_Backword(BACKWARD_SPEED*1.5);
              Serial.println("Backward LOOP: ");
          }while (Get_Distance(ultraFront)<=MIN_RANGE);
//          delay(50);
          HangCount++;
          Turn(); 
      }
    }
}
