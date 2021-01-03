# Lesson2

## 目的とする動作

* 超音波距離センサーを使用して、ロボットカーが障害物を回避するようにします。

## ソースコード

* [metal-2560-lesson2.ino](/Arduino/osoyoo/metal-2560-lesson2/metal-2560-lesson2.ino)

## Arduinoで使用する出力ピン

* 出力ピンの初期化は void setup() 関数で行っています。

|定数名|Arduinoピン番号|信号の向き|役割|
|--------|--------------|--------|---|
|Trig_PIN|30|OUTPUT|HC-SR04のトリガ(A4)|
|Echo_PIN|31|INPUT|HC-SR04のエコー(A5)|
|SERVO_PIN|13|OUTPUT|サーボモーター(D5)|

## Lesson2で追加するハードウェア

* [超音波距離センサー HC-SR04](https://akizukidenshi.com/catalog/g/gM-11009/)
  * データシートの7. ModuleTimingを参照
     1. トリガ端子に最低10マイクロ秒のパルス信号を送る。
     1. 40KHzのバースト信号が送信される。
     1. 送信直後にECHO端子がHIGHになり、反射したバースト信号が戻ってくるタイミングでLOWになる。
     1. 距離はECHO端子のパルス幅のマイクロ秒/58の値がcmになる。
* サーボモーター 同等品：[マイクロサーボ9g SG-90](https://akizukidenshi.com/catalog/g/gM-08761/)  
  * 以下のArduino標準ライブラリを使用して制御する。
    * [Servoライブラリ](https://www.arduino.cc/reference/en/libraries/servo/)

## 超音波センサーで障害物までの距離を図る関数

* ソース中の 0.01657はおよそ1/60。データシートの値とやや食い違いがある。1/58=0.01724

```
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
  echo_distance=pulseIn(Echo_PIN,HIGH); // unsigned long pulseIn()：信号がHIGHとなっている時間をマイクロ秒で返します
  
  echo_distance=echo_distance*0.01657; //how far away is the object in cm
 
//Serial.println((int)echo_distance);  //デバック用。コメントをはすずと距離の値がシリアル出力される。
 
  /* 距離の値を返す */
  return round(echo_distance);   /* round()は四捨五入する関数 */
}
```

## 周囲を見渡す関数

### String watchsurrounding()

周囲の距離を測定し、それらをcm単位で変数に代入し、障害物ステータスを生成します。

|距離が代入される変数名|計測方向|障害物ステータス|センサーの方向(サーボモーターの角度)|
|------------------|-------|-------------|------------------------------|
|centerscanval|正面| XX1XX | 90° |
|ldiagonalscanval|左斜め前| X1XXX | 120° |
|leftscanval|左側| 1XXXX | 170° (180°までサーボが動かなかったため) |
|rightscanval|右側| XXXX1 | 0° |
|rdiagonalscanval|右斜め前| XXX1X | 40° |

* 障害物と判断する閾値
  * const int distancelimit = 30; // 前方の障害物までの最小距離（cm）           
  * const int sidedistancelimit = 30; // 両側の障害物までの最小距離（cm）


* 障害物ステータス
  * 障害物ステータスは2進数で、各ビットが障害物のある方向を示します。（５ビットなので５方向）
  * たとえば、B101000の最後の5桁は01000です。これは、左斜め前に障害物があることを表し、B100111は正面、右斜め前、右横を意味します。
  * 処理中でステータスの初期値をB100000と6桁にしているのは、前5桁をゼロ詰めするためと思われます。

(例)
```
  01000

    0  
  1   0
0       0

  00111

    1
  0   1
0       1
```

## 障害物を自動で回避する関数 void auto_avoidance()

* 定数および変数
  * #define LPT 2 // scan loop counter
  * int numcycles = 0; // サイクル数を示す変数
  * const int turntime = 250; //Time the robot spends turning (miliseconds)
  * const int backtime = 300; //Time the robot spends turning (miliseconds)
  * int thereis; // 障害物を検知した回数を記録するカウンタ

* サイクル変数の役割
  * 関数の頭でループの頭でサイクルを示す変数を1増やす。（++numcycles）
  * 最初は前進サイクル(numcycles=1)となり前進する。
  * 次のサイクル(numcycles>=2)で監視サイクルとなり、障害物がないか確認する。障害物があった場合は障害物を回避し、障害物が検知されない場合にサイクル変数をリセット（numcycles=0)し、前進サイクルに移行する。
  * この結果、前進サイクルと監視サイクルを繰り返す動きになる。

### 監視サイクル時の動き

```
  if(numcycles >= LPT){ // 監視サイクル時は、周りに何かがあるかどうかを監視します。
  　stop_Stop();  // 一時的にモーターを停止します。
    String obstacle_sign=watchsurrounding(); // 障害物ステータスを取得します。
    // 5桁のobstruction_signバイナリ値は、5方向の障害物ステータスを意味します
```

  * 障害物ステータスによって以下の動きをします。

|障害物のステータス(obstacle_sign)| println|speedPinL |speedPinR |speedPinLB |speedPinRB|ロボットの動作|delay| 
|--|---|---|---|--|--|--|--|--|
|10000|SLIT right|FAST_SPEED|SPEED|FAST_SPEED|SPEED|go_Advance()|turntime |
|00001|SLIT LEFT|SPEED|FAST_SPEED|SPEED|FAST_SPEED|go_Advance()|turntime  |
|11100,01000,11000,10100,01100,00100|hand right|TURN_SPEED|TURN_SPEED|TURN_SPEED|TURN_SPEED|go_Right()|turntime |
|00010,00111,00011,00101,00110,01010|hand left|TURN_SPEED|TURN_SPEED|TURN_SPEED|TURN_SPEED|go_Left()|turntime|
|01111,10111,11111|hand back left|BACK_SPEED1|BACK_SPEED2|BACK_SPEED1|BACK_SPEED2|go_Back()|backtime|
|11011,11101,11110,01110|hand back right|BACK_SPEED2|BACK_SPEED1|BACK_SPEED2|BACK_SPEED1|go_Back()|backtime|
|00000|no handle|SPEED|SPEED|SPEED|SPEED|go_Advance()|backtime|

  * 障害物が検知できなかった場合(no handle)の時は動作サイクルがリセット（numcycles=0）され、前進サイクルに移行する。

### 前進サイクル時の動き

```
} else {
      set_Motorspeed();
      go_Advance();  // 何も問題がない場合は、go_Advance()関数で前進します。
      delay(backtime);
      stop_Stop();
    }
}
```

### 監視サイクルまたは前進サイクルが終わった後に、前方に障害物がないか確認する。

  distance = watch(); // watch()関数を使用して、前方に何かがあるかどうかを確認します。（ロボットが前進しているだけで、周りを見回していない場合は、前方の距離がテストされます）
  
  // 前方に障害物があることが完全に確認された場合ロボットは停止します。
  // 25回トライすることで、超音波センサーの誤検知の影響を無くします。    
  
  // 前方に障害物がある場合
  if (distance < distancelimit){
    Serial.println("final go back");
	  go_Back(); // 障害物を避けるために後進します。
    set_Motorspeed(BACK_SPEED1,BACK_SPEED2,BACK_SPEED1,BACK_SPEED2);
    delay(backtime);
    ++thereis; // 障害物のためバックした回数をカウントします。
  }

  // 前方に障害物がなかった場合（またが障害物から離れた場合）
  if (distance > distancelimit){
    thereis=0;　　// 障害物より離れた場合（回避できた場合）は障害物カウンタをクリアします。
  }

  // 障害物カウンタが25を超えた場合は、その場で停止します。
  if (thereis > 25){  //
    Serial.println("final stop");
    stop_Stop(); // 障害物で動けないと判断してモーターを停止します。
    thereis=0;   // 障害物カウンタをクリアします。
  }
}
```
