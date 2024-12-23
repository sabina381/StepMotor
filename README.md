## Structure
```
StepMotor 
 - src 
   - StepMotor.h
   - Stepper.cpp
   - MultiStepper.cpp
 - example 
 - keywords.txt
 - library.properties
```

## How to use
1.	Clone the repository to your desktop.
2.	Move the cloned folder to `/Documents/Arduino/libraries`.

```{cpp}
#include <StepMotor.h>

Stepper stepper_1(3, 4, 5, 6);

void setup() {
  Serial.begin(115200);
}

void loop() {
    stepper_1.step(STEP4LAP, 1);
    delay(2000);
    stepper_1.step(STEP4LAP, -1);
    delay(2000);
}
```

## Target stepmotor 
name : 28BYJ-48(5V) motor  
link : [AliExpress](https://ko.aliexpress.com/item/1005006141719157.html?spm=a2g0o.productlist.main.1.64ee439aCk2cQE&algo_pvid=0028234f-f163-40ff-af87-7c5225081d42&aem_p4p_detail=202409110014239502571167064400008634737&algo_exp_id=0028234f-f163-40ff-af87-7c5225081d42-0&pdp_npi=4%40dis%21KRW%212680%212680%21%21%2113.85%2113.85%21%402101584517260388637604119ea2ac%2112000035947534362%21sea%21KR%210%21ABX&curPageLogUid=SUfcCKzo8Wsh&utparam-url=scene%3Asearch%7Cquery_from%3A&search_p4p_id=202409110014239502571167064400008634737_1)

## Reference
1.  [아두이노 중급_29. 스텝모터,스테핑모터](https://m.blog.naver.com/PostView.naver?blogId=darknisia&logNo=221652111026&proxyReferer=https:%2F%2Fwww.google.com%2F&trackingCode=external)
2.  [http://www.arduino.cc/en/Reference/Stepper](http://www.arduino.cc/en/Reference/Stepper)
