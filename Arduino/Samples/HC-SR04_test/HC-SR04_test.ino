//
// HC-SR04 test program
//
//

/* HC-SR04 */
#define Trig_PIN 6
#define Echo_PIN 7

/*detection of ultrasonic distance*/
int watch(){
  long echo_distance;

  /* TRIGパルスを作る
        --------
   5ms |  15ms  |
  -----         --------- */
  digitalWrite(Trig_PIN,LOW);    // TRIGをLOWにする  
  delayMicroseconds(5);          // 5ms待つ                                                                    
  digitalWrite(Trig_PIN,HIGH);   // TRIGをHIGHにする
  delayMicroseconds(15);         // 15ms待つ
  digitalWrite(Trig_PIN,LOW);    // TRIGをLOWにする

  /* ECHOパルス幅を取得する */
  echo_distance=pulseIn(Echo_PIN,HIGH); // pulseIn()：信号がHIGHとなっている時間をマイクロ秒で返します
  
  echo_distance=echo_distance*0.01657; //how far away is the object in cm
 
//Serial.println((int)echo_distance);   // デバック用。コメントをはすずと距離の値がシリアル出力される。
 
  /* 距離の値を返す */
  return round(echo_distance);   /* round()は四捨五入する関数 */
}

void setup() {
  // put your setup code here, to run once:
  /*init HC-SR04*/
  pinMode(Trig_PIN, OUTPUT); 
  pinMode(Echo_PIN,INPUT);
   
  /*init Serial*/
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(watch());
  delay(1000);
}
