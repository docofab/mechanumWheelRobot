/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Omni direction Mecanum Wheel Arduino Smart Car Tutorial Lesson 2 Obstacle avoidance auto driving
 * Tutorial URL http://osoyoo.com/?p=30022
 * CopyRight www.osoyoo.com

 * This project will show you how to make Osoyoo robot car in auto drive mode and avoid obstacles
 *   
 * 
 */
#include <Servo.h>
#define speedPinR 9   //  RIGHT WHEEL PWM pin D45 connect front MODEL-X ENA 
#define RightMotorDirPin1  22    //Front Right Motor direction pin 1 to Front MODEL-X IN1  (K1)
#define RightMotorDirPin2  24   //Front Right Motor direction pin 2 to Front MODEL-X IN2   (K1)                                 
#define LeftMotorDirPin1  26    //Left front Motor direction pin 1 to Front MODEL-X IN3 (  K3)
#define LeftMotorDirPin2  28   //Left front Motor direction pin 2 to Front MODEL-X IN4 (  K3)
#define speedPinL 10   // Left WHEEL PWM pin D7 connect front MODEL-X ENB

#define speedPinRB 11   //  RIGHT WHEEL PWM pin connect Back MODEL-X ENA 
#define RightMotorDirPin1B  5    //Rear Right Motor direction pin 1 to Back MODEL-X IN1 (  K1)
#define RightMotorDirPin2B 6    //Rear Right Motor direction pin 2 to Back MODEL-X IN2 (  K1) 
#define LeftMotorDirPin1B 7    //Rear left Motor direction pin 1 to Back MODEL-X IN3  K3
#define LeftMotorDirPin2B 8  //Rear left Motor direction pin 2 to Back MODEL-X IN4  k3
#define speedPinLB 12    //   LEFT WHEEL  PWM pin D8 connect Rear MODEL-X ENB

#define SERVO_PIN     13  //servo connect to D5
#define Echo_PIN    31 // Ultrasonic Echo pin connect to A5
#define Trig_PIN    30  // Ultrasonic Trig pin connect to A4

#define FAST_SPEED  110   //both sides of the motor speed
#define SPEED  80     //both sides of the motor speed
#define TURN_SPEED  110   //both sides of the motor speed
#define FORWARD_TIME 200   //Forward distance
#define BACK_TIME  300  // back distance
#define TURN_TIME  250  //Time the robot spends turning (miliseconds)
#define OBSTACLE_LIMIT 30  //minimum distance in cm to obstacles at both sides (the car will allow a shorter distance sideways)
int distance;

Servo head;
/*motor control*/
void go_Advance()  //Forward
{
 
FR_fwd();
FL_fwd();
RR_fwd();
RL_fwd();
}
void go_Left()  //Turn left
{
FR_fwd();
FL_bck();
RR_fwd();
RL_bck();
}
void go_Right()  //Turn right
{
FR_bck();
FL_fwd();
RR_bck();
RL_fwd();
}
void go_Back()  //Reverse
{
 
FR_bck();
FL_bck();
RR_bck();
RL_bck();
}
 
 

void stop_Stop()    //Stop
{
  digitalWrite(RightMotorDirPin1, LOW);
  digitalWrite(RightMotorDirPin2,LOW);
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,LOW);
  digitalWrite(RightMotorDirPin1B, LOW);
  digitalWrite(RightMotorDirPin2B,LOW);
  digitalWrite(LeftMotorDirPin1B,LOW);
  digitalWrite(LeftMotorDirPin2B,LOW);
  set_Motorspeed(0,0,0,0);
}

/*set motor speed */
void set_Motorspeed(int leftFront,int rightFront,int leftBack,int rightBack)
{
  analogWrite(speedPinL,leftFront); 
  analogWrite(speedPinR,rightFront); 
 analogWrite(speedPinLB,leftBack);  
 analogWrite(speedPinRB,rightBack);

}

void FR_fwd()  //front-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1,LOW);
  digitalWrite(RightMotorDirPin2,HIGH); 

}
void FR_bck() // front-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1,HIGH);
  digitalWrite(RightMotorDirPin2,LOW); 

}
void FL_fwd() // front-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);

}
void FL_bck() // front-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin2,LOW);
 
}

void RR_fwd()  //rear-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1B, LOW);
  digitalWrite(RightMotorDirPin2B,HIGH); 

}
void RR_bck()  //rear-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1B, HIGH);
  digitalWrite(RightMotorDirPin2B,LOW); 

}
void RL_fwd()  //rear-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1B,LOW);
  digitalWrite(LeftMotorDirPin2B,HIGH);

}
void RL_bck()    //rear-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1B,HIGH);
  digitalWrite(LeftMotorDirPin2B,LOW);

}



/*detection of ultrasonic distance*/
int watch(){
  long echo_distance;
  digitalWrite(Trig_PIN,LOW);
  delayMicroseconds(5);                                                                              
  digitalWrite(Trig_PIN,HIGH);
  delayMicroseconds(15);
  digitalWrite(Trig_PIN,LOW);
  echo_distance=pulseIn(Echo_PIN,HIGH);
  echo_distance=echo_distance*0.01657; //how far away is the object in cm
 //Serial.println((int)echo_distance);
  return round(echo_distance);
}
//Meassures distances to the left,center,right return a 
String watchsurrounding(){
/*  obstacle_status is a binary integer, its last 3 digits stands for if there is any obstacles in left front,direct front and right front directions,
 *   3 digit string, for example 100 means front left front has obstacle, 011 means direct front and right front have obstacles 
 */
  int obstacle_status =B1000;
  head.write(160); //senfor facing left front direction
  delay(400);
  distance = watch();
  if(distance<OBSTACLE_LIMIT){
    stop_Stop();
    
     obstacle_status  =obstacle_status | B100;
    }
  head.write(90); //sehsor facing direct front
  delay(400);
  distance = watch();
  if(distance<OBSTACLE_LIMIT){
    stop_Stop();
    
    obstacle_status  =obstacle_status | B10;
    }

  head.write(20); //sensor faces to right front 20 degree direction
  delay(400);
  distance = watch();
  if(distance<OBSTACLE_LIMIT){
    stop_Stop();
    
    obstacle_status  =obstacle_status | 1;
    }

   String obstacle_str= String(obstacle_status,BIN);
  obstacle_str= obstacle_str.substring(1,4);
  
  return obstacle_str; //return 5-character string standing for 5 direction obstacle status
}

void auto_avoidance(){
 String obstacle_sign=watchsurrounding(); // 5 digits of obstacle_sign binary value means the 5 direction obstacle status
 Serial.print("begin str=");
 Serial.println(obstacle_sign);
 if( obstacle_sign=="100"){
     Serial.println("SLIT right");
     set_Motorspeed(FAST_SPEED,SPEED,FAST_SPEED,SPEED);
     go_Advance();
     delay(TURN_TIME);
     stop_Stop();
 }
if( obstacle_sign=="001"  ){
     Serial.println("SLIT LEFT");
       set_Motorspeed(SPEED,FAST_SPEED,SPEED,FAST_SPEED);
      go_Advance();
  
      delay(TURN_TIME);
      stop_Stop();
 }
 if( obstacle_sign=="110" ){
     Serial.println("hand right");
	    go_Right();
      set_Motorspeed(TURN_SPEED,TURN_SPEED,TURN_SPEED,TURN_SPEED);
      delay(TURN_TIME);
      stop_Stop();
 } 
 if(  obstacle_sign=="011" || obstacle_sign=="010"){
    Serial.println("hand left");
     go_Left();//Turn left
     set_Motorspeed(TURN_SPEED,TURN_SPEED,TURN_SPEED,TURN_SPEED);
     delay(TURN_TIME*2/3);
     stop_Stop();
  }
 
 if(  obstacle_sign=="111" || obstacle_sign=="101"  ){
    Serial.println("hand back left");
    go_Right();
    set_Motorspeed(SPEED,FAST_SPEED,SPEED,FAST_SPEED);
    delay(BACK_TIME);
    stop_Stop();
   } 
  if( obstacle_sign=="000"  ){
    Serial.println("go ahead");
    go_Advance(); 
    set_Motorspeed(SPEED,SPEED,SPEED,SPEED);
    delay(FORWARD_TIME);
    stop_Stop();
  }    
}

void setup() {
  /*setup L298N pin mode*/
  pinMode(RightMotorDirPin1, OUTPUT); 
  pinMode(RightMotorDirPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
 
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT);
     pinMode(RightMotorDirPin1B, OUTPUT); 
  pinMode(RightMotorDirPin2B, OUTPUT); 
  pinMode(speedPinLB, OUTPUT);  
 
  pinMode(LeftMotorDirPin1B, OUTPUT);
  pinMode(LeftMotorDirPin2B, OUTPUT); 
  pinMode(speedPinRB, OUTPUT);
  stop_Stop();//stop move
  /*init HC-SR04*/
  pinMode(Trig_PIN, OUTPUT); 
  pinMode(Echo_PIN,INPUT); 
  /*init buzzer*/
 
  digitalWrite(Trig_PIN,LOW);
  /*init servo*/
  head.attach(SERVO_PIN); 

  head.write(90);
   delay(2000);
  
  Serial.begin(9600);
 
 
 
  stop_Stop();//Stop
 
}

void loop() {
 auto_avoidance();
// Serial.println( watch());
 //delay(2000);
}
