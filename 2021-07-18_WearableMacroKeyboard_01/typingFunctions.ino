void layerTyping(){
  switch (currentLayer){
    case 0:
      // Settings, page 1
      if (risingEdge[3] == 1){
        vibrationSetting = !vibrationSetting;
        EEPROM.write(0, vibrationSetting);
        EEPROM.commit();
        if(diagnosticPrintBit){
          Serial.print("Vibration: ");
          Serial.print(vibrationSetting);
          Serial.print("\n");
        }
      }
      if (risingEdge[2] == 1){
        audioSetting = !audioSetting;
        EEPROM.write(1, audioSetting);
        EEPROM.commit();
        if(diagnosticPrintBit){
          Serial.print("Sound: ");
          Serial.print(audioSetting);
          Serial.print("\n");
        }
      }
      if (risingEdge[1] == 1){
        screenTimeout = screenTimeout + 5;
        if (screenTimeout > 30){
          screenTimeout = 10;
        }
        EEPROM.write(2, screenTimeout);
        EEPROM.commit();
      }
      if (risingEdge[0] == 1){
        volumeAdjustmentFactor++;
        if (volumeAdjustmentFactor > 5){
          volumeAdjustmentFactor = 1;
        }
        EEPROM.write(3, volumeAdjustmentFactor);
        EEPROM.commit();
        if(diagnosticPrintBit){
          Serial.print("Volume adjustment factor: ");
          Serial.print(volumeAdjustmentFactor);
          Serial.print("\n");
        }
      }
      screenName(layerKeys[currentLayer], layerNames[currentLayer]);
      break;
    case 1:
      // Settings, page 1
      if (risingEdge[3] == 1){
        btStop();
        BTStatus = LOW;
      }
      if (risingEdge[2] == 1){
        diagnosticPrintBit = !diagnosticPrintBit;
        EEPROM.write(4, diagnosticPrintBit);
        EEPROM.commit();
        Serial.print("Diagnostic print statements: ");
        Serial.print(diagnosticPrintBit);
        Serial.print("\n");
      }
      if (risingEdge[1] == 1){
        AppleProducts = !AppleProducts;
        EEPROM.write(5, AppleProducts);
        EEPROM.commit();
      }
      if (risingEdge[0] == 1){
        screenName(layerKeys[currentLayer], layerNames[currentLayer]);
      }
      screenName(layerKeys[currentLayer], layerNames[currentLayer]);
      break;
    case 2:
      // Media control mode
      if (risingEdge[3] == HIGH){
        sensors_event_t event;
        lis.getEvent(&event);
        newAccelerometerPosition = (event.acceleration.y);
        oldAccelerometerPosition = newAccelerometerPosition;
        suppressBuzzer = HIGH;
      }
      if(currentState[3] && (millis() > cooldownTimer[4])){
        cooldownTimer[4] = millis() + 10;
        sensors_event_t event;
        lis.getEvent(&event);
        
        newAccelerometerPosition = (event.acceleration.y);
        if(newAccelerometerPosition < oldAccelerometerPosition){
          for(int i=0; i<volumeAdjustmentFactor; i++){
            bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
          }
        }
        if(newAccelerometerPosition > oldAccelerometerPosition){
          for(int i=0; i<volumeAdjustmentFactor; i++){
            bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
          }
        }
        oldAccelerometerPosition = newAccelerometerPosition;
      }
      if(fallingEdge[3] == HIGH){
        suppressBuzzer = LOW;
      }
      if (risingEdge[2] == 1){
        bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
      }
      if (risingEdge[1] == 1){
        bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
      }
      if (risingEdge[0] == 1){
        bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      }
      screenName(layerKeys[currentLayer], layerNames[currentLayer]);
      break;
    case 3:
      // Work macros mode
      if (risingEdge[3] == 1){
        bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
      }
      if (risingEdge[2] == 1){
        bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
      }
      if (risingEdge[1] == 1){
        bleKeyboard.write(KEY_F24);
      }
      if (risingEdge[0] == 1){
        bleKeyboard.write(KEY_RETURN);
      }
      screenName(layerKeys[currentLayer], layerNames[currentLayer]);
      break;
    case 4:
      // Function keys F21 - F24
      if (risingEdge[3] == 1){
        bleKeyboard.write(KEY_F21);
      }
      if (risingEdge[2] == 1){
        bleKeyboard.write(KEY_F22);
      }
      if (risingEdge[1] == 1){
        bleKeyboard.write(KEY_F23);
      }
      if (risingEdge[0] == 1){
        bleKeyboard.write(KEY_F24);
      }
      screenName(layerKeys[currentLayer], layerNames[currentLayer]);
      break;
    case 5:
      // Function keys F17 - F20
      if (risingEdge[3] == 1){
        bleKeyboard.write(KEY_F17);
      }
      if (risingEdge[2] == 1){
        bleKeyboard.write(KEY_F18);
      }
      if (risingEdge[1] == 1){
        bleKeyboard.write(KEY_F19);
      }
      if (risingEdge[0] == 1){
        bleKeyboard.write(KEY_F20);
      }
      screenName(layerKeys[currentLayer], layerNames[currentLayer]);
      break;
    case 6:
      // Pokémon Go but shown on the screen as "Pokemon Go" without the accent mark
      if (risingEdge[3] == HIGH){
        sensors_event_t event;
        lis.getEvent(&event);
        newAccelerometerPosition = (event.acceleration.y);
        oldAccelerometerPosition = newAccelerometerPosition;
        suppressBuzzer = HIGH;
      }
      if(currentState[3] && (millis() > cooldownTimer[4])){
        cooldownTimer[4] = millis() + 10;
        sensors_event_t event;
        lis.getEvent(&event);
        
        newAccelerometerPosition = (event.acceleration.y);
        if(newAccelerometerPosition < oldAccelerometerPosition){
          for(int i=0; i<volumeAdjustmentFactor; i++){
            bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
          }
        }
        if(newAccelerometerPosition > oldAccelerometerPosition){
          for(int i=0; i<volumeAdjustmentFactor; i++){
            bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
          }
        }
        oldAccelerometerPosition = newAccelerometerPosition;
      }
      if(fallingEdge[3] == HIGH){
        suppressBuzzer = LOW;
      }
      if (risingEdge[2] == 1){
        bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
      }
      if (risingEdge[1] == 1){
        if(AppleProducts){
          bleKeyboard.press(KEY_LEFT_GUI);
        }else{
          bleKeyboard.press(KEY_LEFT_CTRL);
        }
        bleKeyboard.print("a");
        delay(75);
        bleKeyboard.releaseAll();
        bleKeyboard.print("OK");
      }
      if (risingEdge[0] == 1){
        if(AppleProducts){
          bleKeyboard.press(KEY_LEFT_GUI);
        }else{
          bleKeyboard.press(KEY_LEFT_CTRL);
        }
        bleKeyboard.print("a");
        delay(75);
        bleKeyboard.releaseAll();
        bleKeyboard.print("0*,1*,2*");
        delay(75);
        bleKeyboard.print("|!costume");
        delay(75);
        bleKeyboard.print("|!legendary");
        delay(75);
        bleKeyboard.print("|!mythical");
        delay(75);
        bleKeyboard.print("|!shiny");
        delay(75);
        bleKeyboard.print("|!traded");
        delay(75);
        bleKeyboard.print("|!shadow");
        delay(75);
        bleKeyboard.print("|age0");
      }
      screenName(layerKeys[currentLayer], layerNames[currentLayer]);
      break;
    case 7:
      // Repeating keystrokes
      // Pressing the left-most button will repeat the F5 key every 5 to 25 seconds
      if (risingEdge[3] == HIGH){
        if(repeatingKeySequence == 3){
          repeatingIntervalMultiplier++;
        }else{
          repeatingKeySequence = 3;
          repeatingIntervalMultiplier = 1;
        }
        if(repeatingIntervalMultiplier > 5){
          repeatingIntervalMultiplier = 1;
        }
        repeatingIntervalMillis = repeatingIntervalMultiplier*5000;
//        repeatingCooldownTimeout = millis() + repeatingIntervalMillis;
      }
      
      // Pressing the second-from-the-left button will periodically send "//"
      if (risingEdge[2] == HIGH){
        if(repeatingKeySequence == 2){
          repeatingIntervalMultiplier++;
        }else{
          repeatingKeySequence = 2;
          repeatingIntervalMultiplier = 1;
        }
        if(repeatingIntervalMultiplier > 5){
          repeatingIntervalMultiplier = 1;
        }
        repeatingIntervalMillis = repeatingIntervalMultiplier*180000;
        repeatingCooldownTimeout = millis() + repeatingIntervalMillis;
      }
      
      // Pressing the third button will press the control button, mostly to keep a screen awake
      if (risingEdge[1] == HIGH){
        if(repeatingKeySequence == 1){
          repeatingIntervalMultiplier++;
        }else{
          repeatingKeySequence = 1;
          repeatingIntervalMultiplier = 1;
        }
        if(repeatingIntervalMultiplier > 5){
          repeatingIntervalMultiplier = 1;
        }
        repeatingIntervalMillis = repeatingIntervalMultiplier*300000;
        repeatingCooldownTimeout = millis() + repeatingIntervalMillis;
      }
      
      // Pressing the rightmost button will psuedo-randomly press play. This would be useful as a gag where
      // you load an obnoxious sound, like a cricket chirping, and hide the phone by a coworker
      if (risingEdge[0] == HIGH){
        if(repeatingKeySequence == 0){
          repeatingIntervalMultiplier++;
        }else{
          repeatingKeySequence = 0;
          repeatingIntervalMultiplier = 1;
        }
        if(repeatingIntervalMultiplier > 5){
          repeatingIntervalMultiplier = 1;
        }
        repeatingIntervalMillis = random(0, (repeatingIntervalMultiplier*300000));
        repeatingCooldownTimeout = millis() + repeatingIntervalMillis;
      }
      screenName(layerKeys[currentLayer], layerNames[currentLayer]);
      break;
    default:
      if(diagnosticPrintBit){
        Serial.print("Unknown layer operation");
      }
      screenName(layerKeys[currentLayer], layerNames[currentLayer]);
      break;
  }
}

void repeatingKeystrokes(){
  if (((millis() > repeatingCooldownTimeout) || risingEdge[3]) && repeatingKeySequence==3){
    bleKeyboard.write(KEY_F5);
    repeatingCooldownTimeout = millis() + repeatingIntervalMillis;
  }
  if (((millis() > repeatingCooldownTimeout) || risingEdge[2]) && repeatingKeySequence==2){
    bleKeyboard.print("//");
    repeatingCooldownTimeout = millis() + repeatingIntervalMillis;
  }
  if (((millis() > repeatingCooldownTimeout) || risingEdge[1]) && repeatingKeySequence==1){
    bleKeyboard.write(KEY_LEFT_CTRL);
    repeatingCooldownTimeout = millis() + repeatingIntervalMillis;
  }
  if (((millis() > repeatingCooldownTimeout)) && repeatingKeySequence==0){
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    repeatingIntervalMillis = random(0, (repeatingIntervalMultiplier*300000));
    repeatingCooldownTimeout = millis() + repeatingIntervalMillis;
    screenName(layerKeys[currentLayer], layerNames[currentLayer]);
  }
}
