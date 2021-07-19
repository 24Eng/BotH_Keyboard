void screenName(String funScreenFunctions, String funScreenName){
  u8g2.clearBuffer();
  if(currentLayer == 0){
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0,20);
    // Print statuses below the setting name
    // Vibrator bit setting
    if(vibrationSetting){
      u8g2.print("   | ");
    }else{
      u8g2.print("   0 ");
    }
    u8g2.print("        ");
    
    // Piezeo bit setting
    if(audioSetting){
      u8g2.print(" | ");
    }else{
      u8g2.print(" 0 ");
    }
    u8g2.print("       ");
    
    // Screen off timer
    u8g2.print(screenTimeout);
    u8g2.print("        ");
    
    // Volume multiplier
    u8g2.print(volumeAdjustmentFactor);
  }
  
  if(currentLayer == 1){
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0,20);
    // Print statuses below the setting name
    // Bluetooth off
    if(!BTStatus){
      u8g2.print("Off        ");
    }else{
      u8g2.print("On         ");
    }
    // Serial diagnostic print bit status
    if(diagnosticPrintBit){
      u8g2.print("|");
    }else{
      u8g2.print("0");
    }
    u8g2.print("          ");
    if(AppleProducts){
      u8g2.print("Apl   ");
    }else{
      u8g2.print("Win");
    }
    u8g2.print("   --");
  }
  if(currentLayer == 7){
    if(diagnosticPrintBit){
      Serial.print("Interval in mS: ");
      Serial.print(repeatingIntervalMillis);
      Serial.print("\n");
    }
    u8g2.setCursor(0,20);
    // Print statuses below the setting name
    if(repeatingKeySequence == 3){
      u8g2.print(repeatingIntervalMillis/1000);
      u8g2.print(" S");
    }else{
      u8g2.print("        ");
    }
    if(repeatingKeySequence == 2){
      u8g2.print(repeatingIntervalMillis/60000);
      u8g2.print(" M");
    }else{
      u8g2.print("           ");
    }
    if(repeatingKeySequence == 1){
      u8g2.print(repeatingIntervalMillis/60000);
      u8g2.print(" M");
    }else{
      u8g2.print("           ");
    }
    if(repeatingKeySequence == 0){
      u8g2.print(repeatingIntervalMillis/1000);
      u8g2.print(" S");
    }
  }
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(0,10);
  u8g2.print(funScreenFunctions);
  
  u8g2.setFont(u8g2_font_cu12_tr);
  u8g2.setCursor(0,45);
  u8g2.print(funScreenName);
  
  u8g2.sendBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
}

void blankScreen(){
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}
