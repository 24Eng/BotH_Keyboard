bool scanKeyswitches(){
  bool funReturn = LOW;
  for(int i=0; i<4; i++){
    int funCurrentReading = analogRead(keyswitchLocations[i]);
    if (funCurrentReading<1){
      funCurrentReading = HIGH;
      currentState[i] = HIGH;
      funReturn = HIGH;
    }else{
      funCurrentReading = LOW;
      currentState[i] = LOW;
    }
    if(millis() < cooldownTimer[i]){
      funCurrentReading = oldReading[i];
    }
    if (funCurrentReading > oldReading[i]){
      risingEdge[i] = HIGH;
      cooldownTimer[i] = millis() + cooldownWait;
//      if(audioSetting){
//        mySerial.print("Hello, world?");
//      }
      if(diagnosticPrintBit){
        Serial.print("Input ");
        Serial.print(i);
        Serial.print(" high\n");
      }
    }else{
      risingEdge[i] = LOW;
    }
    if (funCurrentReading < oldReading[i]){
      fallingEdge[i] = HIGH;
      funReturn = HIGH;
      cooldownTimer[i] = millis() + cooldownWait;
      if(diagnosticPrintBit){
        Serial.print("Input ");
        Serial.print(i);
        Serial.print(" low\n");
      }
    }else{
      fallingEdge[i] = LOW;
    }
    oldReading[i] = funCurrentReading;
  }
  if(!suppressBuzzer && vibrationSetting){
    digitalWrite(vibratorPin, funReturn);
  }
  if(suppressBuzzer || !vibrationSetting){
    digitalWrite(vibratorPin, LOW);
  }
  return(funReturn);
}


bool scanEncoder(){
  bool funReturn = LOW;
  for(int i=0; i<3; i++){
    encoderPinLevels[i] = analogRead(encoderPinLocations[i]);
    if(encoderPinLevels[i] < 1){
      encoderPinStates[i] = HIGH;
      funReturn = HIGH;
    }else{
      encoderPinStates[i] = LOW;
    }
  }
  if(encoderUntriggered &&(encoderPinStates[0] < encoderPinStates[1])){
    encoderUntriggered = LOW;
    currentLayer++;
    if(currentLayer > totalLayers){
      currentLayer = 0;
    }
    screenName(layerKeys[currentLayer], layerNames[currentLayer]);
    suppressBuzzer = LOW;
    if(diagnosticPrintBit){
      Serial.print("Clockwise\t\t");
      Serial.print(layerNames[currentLayer]);
      Serial.print("\n");
    }
  }
  if(encoderUntriggered &&(encoderPinStates[0] > encoderPinStates[1])){
    encoderUntriggered = LOW;
    currentLayer--;
    if(currentLayer < 0){
      currentLayer = totalLayers;
    }
    screenName(layerKeys[currentLayer], layerNames[currentLayer]);
    suppressBuzzer = LOW;
    if(diagnosticPrintBit){
      Serial.print("Counter clockwise\t");
      Serial.print(layerNames[currentLayer]);
      Serial.print("\n");
    }
  }
  if((!encoderPinStates[0]) && (!encoderPinStates[1]) && (!encoderUntriggered)){
    encoderUntriggered = HIGH;
  }
  return funReturn;
}

void scanAccelerometerI(){
  lis.read();      // get X Y and Z data at once
  sensors_event_t event;
  lis.getEvent(&event);
}
