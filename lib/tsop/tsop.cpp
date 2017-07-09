#include <Arduino.h>
#include "tsop.h"

void TSOP::Setup(){
  pinMode(TSOP_POWER, OUTPUT);

  for(int i = 0; i < 12; i++){
    pinMode(TSOPPINS[i], INPUT);
  }

  digitalWrite(TSOP_POWER, HIGH);
}

void TSOP::ReadOnce(){
  for(int i = 0; i < 12; i++){
    TSOPTEMPVAL[i] += digitalRead(TSOPPINS[i])^1;
  }
  count++;
}

void TSOP::Refresh(){
  digitalWrite(TSOP_POWER, LOW);
  delay(2);
  digitalWrite(TSOP_POWER, HIGH);
}

void TSOP::Read(){
  while(count<200){
    ReadOnce();
  }
  FinishRead();
}

void TSOP::FinishRead(){
  for (int i = 0; i < 12; i++) {
    Serial.println("TSOP"+String(i)+": "+String(TSOPTEMPVAL[i]));
    TSOPVAL[i] = TSOPTEMPVAL[i];
    TSOPTEMPVAL[i] = 0;
  }
  Serial.println();
  count = 0;
  Refresh();
}

void TSOP::FilterValues(){
  //Remove Noise
  for (int i = 0; i < 12; i++) {
    #if TSOP_FILTER_NOISE
      if(TSOPVAL[i] < 5 || TSOPVAL[i] > 200){
        TEMPFILTEREDVAL[i] = 0;
      } else{
        TEMPFILTEREDVAL[i] = TSOPVAL[i];
      }
    #else
      TEMPFILTEREDVAL[i] = TSOPVAL[i];
    #endif
  }

  //Filter By Surrounding
  for (int i = 0; i < 12; i++) {
    #if TSOP_FILTER_SURROUNDING
      int temp = 0;
    #else
      int temp = 0;
    #endif

    FILTEREDVAL[i] = temp >> 4;

  }

  //Sorting TSOP Values
  for (int i = 0; i < 12; i++) {
    int maxVal = 0;
    int maxInd = 0;
    for (int j = 0; j < 12; j++) {
      if (FILTEREDVAL[j]>maxVal) {
        maxVal = FILTEREDVAL[j];
        maxInd = j;
      }
    }
    SORTEDFILTEREDVAL[i] = maxVal;
    FILTEREDVAL[maxInd] = -1;
  }


}

void TSOP::GetAngleSimple(){

}

void TSOP::GetAngle(){

}

void TSOP::GetStrengthSimple(){

}

void TSOP::GetStrength(){

}
