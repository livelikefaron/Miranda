void INIT_POWER(){
 
 inputPower = LOW;
 
 pinMode(GFX_POWER, OUTPUT);
 
 gfxPowerState = HIGH;
 
 //analogReference(EXTERNAL);
}

void POWER_SERVICE(){
 digitalWrite(GFX_POWER, gfxPowerState);
 if(analogInputValue[POWER_PIN] < 100){
  if(inputPower == LOW){
   gfxBootTime   = millis();
   gfxPowerTime  = millis();
   gfxResetTime  = millis();
   gfxResetState = LOW;
   gfxBootState  = LOW;
   gfxPowerState = HIGH;
   bootDone      = 0;
   gfxGraph      = 0;
   graphBuilt    = 0;
  }
  inputPower = HIGH;
 } else {
  inputPower = LOW;
 }
 //if(inputPower == HIGH){ greenOneState = LOW; } else { greenOneState = HIGH; }
}
