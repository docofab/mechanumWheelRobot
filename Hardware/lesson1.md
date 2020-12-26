# Lesson1

## 目的とする動作

1. 前進して2秒間後退
1. 左折と右折を2秒間
1. 右シフトと左シフトで2秒間
1. 左斜め後方と右斜め前方に2秒間
1. 左斜め前方と右斜め後方2秒間
1. 停止

## モータの配置

* 上からみた図。
* Left Model X, Right Model Xはモータードライバ基板
* Mがモーター

```
                FRONT
      LEFT                RIGHT
        --M  R-K3    R-K1  M--  

  (Left Model X)     (Right Model X)

        --M  L-K1    L-K3  M--  

                 REAR 
```

## Arduinoで使用する出力ピン

|定数名|Arduinoピン番号|信号の向き|役割|
|-----|--------------|--------|---|
|speedPinR|9|出力|右前輪の回転数(PWM出力)| 
|RightMotorDirPin1|22|出力|右前輪の回転方向(Pin1)|
|RightMotorDirPin2|24|出力|右前輪の回転方向(Pin2)|
|LeftMotorDirPin1|26|出力|左前輪の回転方向(Pin1)|
|LeftMotorDirPin2|28|出力|左前輪の回転方向(Pin2)|
|speedPinL|10|出力|左前輪の回転数(PWM出力)|
|speedPinRB|11|出力|右後輪の回転数(PWM出力)|
|RightMotorDirPin1B|5|出力|右後輪の回転方向(Pin1B)|
|RightMotorDirPin2B |6 |出力|右後輪の回転方向(Pin2B)|
|LeftMotorDirPin1B| 7|出力|左後輪の回転方向(Pin1B)|
|LeftMotorDirPin2B |8 |出力|左後輪の回転方向(Pin2B)|
|speedPinLB| 12|出力|左後輪の回転数(PWM出力)|

## モーターの動かし方と対応する関数

* speedで指定する値
  * SPEED 140（通常）   
  * TURN_SPEED 160（回転）

### 右側のモータードライバ（Right MODEL-X）での右前輪制御

|関数名|モーターの動作|RightMotorDirPin1|RightMotorDirPin2|speedPinR|
|-----|------------|-----------------|-----------------|--------|
|void FR_fwd(int speed)|右前輪を前進方向|HIGH|LOW|speedの値(アナログ出力)|
|void FR_bck(int speed)|右前輪を後進方向|LOW|HIGH|speedの値(アナログ出力)|

### 右側のモータードライバ（Right MODEL-X）での左前輪制御

|関数名|モーターの動作|LeftMotorDirPin1|LeftMotorDirPin2|speedPinL|
|-----|------------|-----------------|-----------------|--------|
|void FL_fwd(int speed)|左前輪を前進方向|HIGH|LOW|speedの値(アナログ出力)|
|void FL_bck(int speed)|左前輪を後進方向|LOW|HIGH|speedの値(アナログ出力)|

### 左側のモータードライバ（Left MODEL-X)での右後輪制御

|関数名|モーターの動作|RightMotorDirPin1B|RightMotorDirPin2B|speedPinRB|
|-----|------------|-----------------|-----------------|--------|
|void RR_fwd(int speed)|右後輪を前進方向|HIGH|LOW|speedの値(アナログ出力)|
|void RR_bck(int speed)|右後輪を後進方向|LOW|HIGH|speedの値(アナログ出力)|

### 左側のモータードライバ（Left MODEL-X)での左後輪制御

|関数名|モーターの動作|LeftMotorDirPin1B|LeftMotorDirPin2B|speedPinLB|
|-----|------------|-----------------|-----------------|--------|
|void RL_fwd(int speed)|左後輪を前進|HIGH|LOW|speedの値(アナログ出力)|
|void RL_bck(int speed)|左後輪を後進|LOW|HIGH|speedの値(アナログ出力)|
