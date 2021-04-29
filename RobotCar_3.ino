 //**************************** RobotCar_3 ********************************
// Only files with the .ino extension are scanned for include files.     *
// This is by design, for simplicity for one thing and so that a         *
// library can't include another library that includes another library   *
// and so on.                                                            *
// Athugid ad setja snuningsAtt i RobotFunctions.h a -1 ef servomotor    *
// er orvhentur  Breytt 23.3.2017                                        *
//***********************************************************************/
#include "Arduino.h"
#include "RobotFunctions.h"
#include <SoftwareSerial.h>
#include "MyDFPlayer.h"
    int ledPin = 13;
    int x = 3;


//************************** uppsetning á forritinu *****************
void setup() 
{ 
    x=11;
    pinMode(ledPin,OUTPUT);

    pinMode(motorVpwm_,OUTPUT);
    pinMode(motorVgir_,OUTPUT);
    pinMode(motorHpwm_,OUTPUT);
    pinMode(motorHgir_,OUTPUT);
  
    servoMain.attach(10);//Servo on digital pin ~10
  
    pinMode(sonarTrigger_,OUTPUT);
    pinMode(sonarEcho_,INPUT_PULLUP); //Allir inngangar verda að hafa pullup vidnam 
                                      //her notum við internal pullup (20kohm) orgjorvans 
    pinMode(TXspilari_,OUTPUT);
    pinMode(RXspilari_,INPUT_PULLUP); //Notum aftur Internal pullup vidnam

    Serial.begin(9600); 
    //******************** Setja upp MDFPlayer *************************
    mySerial.begin(9600);
    delay(500);
    //mp3_set_volume(15);
    mp3_set_volume(15);
    //mp3_set_volume(10);
    delay(100); 
    
     mp3_play_track(17);  // 17. Bíll í gang (gamli bíllinn)
     delay(5000); 
    //mp3_play_track(1);     // 1. Riding along in my automobile 
     //lagNr=2;
     //Timar
     time=millis(); 
   
     timeX=time;
     reiknaPulsBreidd(0,-1); //SONAR beint framm, í þessum bíl er leiðrétt um +2°
     lengdX=lengd(); 
}//End of setup *********

//*************************** Keyrslulykkjan **********************
void loop()
{  
    reiknaPulsBreidd(0,-1); //SONAR beint framm, í þessum bíl er leiðrétt um +2°
    delay(100);    
    startCar(); // Bíll keyrir áfram
    delay(100);
    /*if(digitalRead(RXspilari_)==1) //Ef Spilari upptekinn þá er RXspilari==0
    {                              //RXspilari (D2) tengist BUSY tengi á spilara sjá mynd 17
      if(lagNr==17)
         lagNr=1;
      mp3_play_track(lagNr++);   
    }*/

    digitalWrite(ledPin,HIGH);

//  int oldLengd = 0;
  if(millis() >= (timeX+1000)) {
    if (lengd() >= (lengdX - 5) && lengd() <= (lengdX +5)){
      stopCar();
      delay(200);
      backCar();
      delay(400);
      stopBackCar();
      delay(400);
      driveRight();
      delay(300);
      //stopCar();
      //delay(200);
      startCar();
    }
    timeX = millis();
    lengdX = lengd();
  }
  

   if(lengd()<40)
   {  
      mp3_play_track(18);  // 17. Bíll í gang (gamli bíllinn)
      stopCar();
      reiknaPulsBreidd(80,-1);
      delay(500);
      int left = lengd();
      delay(200);
      reiknaPulsBreidd(0,-1);
      delay(200);
      int beint = lengd();
      delay(200);
      reiknaPulsBreidd(-80,-1);
      delay(500);
      int right = lengd();
      delay(200);
      reiknaPulsBreidd(0,-1);
      delay(1000);
      if(right > left){
        driveRight();
        delay(200);
      }
      else if(left > right){
        driveLeft();
        delay(200);
      }
      
      
      delay(200);
      left = 0;
      right = 0;
      startCar();
      /*stopCar();        
      if(randomTurn==1)
         driveRight(); // bíll snýst til hægri
      else if (randomTurn==-1)
         driveLeft();  // bíll snýst til binstri
      delay(300);      // Gefa tíma til að beygja ca +/- 90°
      startCar();  
      randomTurn=randomTurn*-1;    
      delay(1000); */               
   }

   else if (lengd()<10)
   {
    backCar();
    
   }
}//End of loop *********************
