
void INIT_TIME(){
  
 unsigned char ti[4];
 unsigned long time = 0;
 unsigned int timeLow;
 unsigned int timeHigh;
 
 for(int i = 0; i < 4; i++){ ti[i] = save.readEEPROM(DISK0, currentTimeAddress[i]); }
 
 timeLow  = ti[2] << 8 | ti[3];
 timeHigh = ti[0] << 8 | ti[1];
 
 time = time << 32 | timeHigh;
 time = time << 16 | timeLow;
 
 setTime(time);
 
 heartbeatTime = millis();
 heartbeatInterval = 1000;
 heartbeats = (minute(now()) * 60) + second(now());
 
 readCurrentTraffic();
 readCurrentStops();
 
 gfxPowerTime = millis();
 gfxPowerInterval = 240000;
}


void TIME_SERVICE(){
  
 if(millis() > gfxPowerTime + gfxPowerInterval){ gfxPowerState = LOW; }
 
 if(bootDone){
  timeFG = 0xFFFF;
  timeBG = 0x0000;
  
  if(millis() > heartbeatTime + heartbeatInterval){
   
   if(gfxPowerState == HIGH){
    
    updating = true;
    
    readCurrentTraffic();
    readCurrentStops();
    
    txtFG(timeFG);
    txtBG(timeBG);
    txtXG(timeXG);
    txtFont(timeF);
    txtW(timeM);
    txtH(timeM);
  
    // show date
    moveTO(dateX,dateY);
    txtW(timeM-1);
    txtH(timeM);
    txtPS(weekdays[weekday()]);
    txtPS(clrStr);
    itoa(month(), holder, 10);
    txtPS(holder);
    txtPS(randStr[38]);
    itoa(day(), holder, 10);
    txtPS(holder);
    txtPS(randStr[38]);
    itoa(year(), holder, 10);
    txtPS(holder);
  
    // show time
    txtW(timeM);
    txtH(timeM);
    moveTO(timeX,timeY);
    itoa(hourFormat12(now()), holder, 10);
    if(hourFormat12(now()) < 10){ txtPS(randStr[6]); }
    txtPS(holder);
    txtPS(randStr[30]);
    itoa(minute(now()), holder, 10);
    if(minute(now()) < 10){ txtPS(randStr[6]); }
    txtPS(holder);
    txtPS(randStr[30]);
    itoa(second(now()), holder, 10);
    if(second(now()) < 10){ txtPS(randStr[6]); }
    txtPS(holder);
    txtPS(clrStr);
    if(isAM()){ txtPS(meridian[0]); } else { txtPS(meridian[1]); }
    
    // show lane stats
    txtFG(0xFFFF);
    txtW(2);
    txtH(1);
    for(int i = 0; i < 4; i++){
     moveTO((greenLightStartX + (i * laneWidth)) + lightRadius + 15, greenLightStartY - lightRadius + 6);
     txtFG(STAT_BOX_1_TXT); txtBG(STAT_BOX_1);
     if(trafficLane[i] < 1){
      for(int c = 0; c < 3; c++){ txtPS(clrStr); }
      moveTO((greenLightStartX + (i * laneWidth)) + lightRadius + 15, greenLightStartY - lightRadius + 6);
     }
     if(trafficLane[i] < 1000){ itoa(trafficLane[i], holder, 10); txtPS(holder); }
     moveTO((redLightStartX + (i * laneWidth)) + lightRadius + 15, redLightStartY - lightRadius + 11);
     txtFG(STAT_BOX_2_TXT); txtBG(STAT_BOX_2);
     if(stopsLane[i] < 1){
      for(int c = 0; c < 3; c++){ txtPS(clrStr); }
      moveTO((redLightStartX + (i * laneWidth)) + lightRadius + 15, redLightStartY - lightRadius + 11);
     }
     if(stopsLane[i] < 1000){ itoa(stopsLane[i], holder, 10); txtPS(holder); }
    }
    
    for(char g = 0; g < 4; g++){
     if(interlockOn[g]){
       greenLight(g, 0); // turn off green light
       redLight(g, 1); // turn on red light
     } else {
       redLight(g, 0); // turn off red light
     }
    }
    
    for(char g = 1; g < 5; g++){
     // show current stops percentage
     //Serial.print(stopsLane[g - 1]);
     //Serial.print(" / ");
     //Serial.println(trafficLane[g - 1]);
     txtW(1); txtH(1);
     txtFG(STAT_BOX_3_TXT); txtBG(STAT_BOX_3);
     moveTO((greenLightStartX + (g * laneWidth)) - lightRadius - 40, redLightStartY + lightRadius + 27);
     if(trafficLane[g - 1] > 0){ itoa(round(((stopsLane[g - 1] * 100) / trafficLane[g - 1])), holder, 10); } else { itoa(0, holder, 10); }
     txtPS(holder);
    }
    
    if(second(now()) == 10 && minute(now()) == 0){
     int cLane = 0;
     int cMean = 0;
     for(int g = 0, h = 1; g < 4; g++, h++){
      char yScape = 20;
      int  cHour = 0;
      do {
       if(yScape > 39){
        unsigned char dat[2];
        double average[2];
        
        dat[1] = save.readEEPROM(DISK0, ((8400 + ((hour() - cHour) * 12)) + (cLane * 2)) + 1);
        dat[0] = save.readEEPROM(DISK0, ((8400 + ((hour() - cHour) * 12)) + (cLane * 2)));
        moveTO((greenLightStartX + (g * laneWidth)) - lightRadius - 5, redLightStartY + lightRadius + yScape + 5);
        txtW(1); txtH(1); txtFG(0x0000); txtBG(0x0400);
        for(char b = 0; b < 3; b++){ txtPS(clrStr); }
        moveTO((greenLightStartX + (g * laneWidth)) - lightRadius - 5, redLightStartY + lightRadius + yScape + 5);
        itoa(dat[1] << 8 | dat[0], holder, 10);  txtPS(holder);
        average[0] = dat[1] << 8 | dat[0];
        
        dat[1] = save.readEEPROM(DISK0, ((8700 + ((hour() - cHour) * 12)) + (cLane * 2)) + 1);
        dat[0] = save.readEEPROM(DISK0, ((8700 + ((hour() - cHour) * 12)) + (cLane * 2)));
        moveTO((greenLightStartX + (g * laneWidth)) + lightRadius + 5, redLightStartY + lightRadius + yScape + 5);
        txtW(1); txtH(1); txtFG(0x0000); txtBG(0xF800);
        for(char b = 0; b < 3; b++){ txtPS(clrStr); }
        moveTO((greenLightStartX + (g * laneWidth)) + lightRadius + 5, redLightStartY + lightRadius + yScape + 5);
        itoa(dat[1] << 8 | dat[0], holder, 10); txtPS(holder);
        average[1] = dat[1] << 8 | dat[0];
         
        moveTO((greenLightStartX + (h * laneWidth)) - lightRadius - 40, redLightStartY + lightRadius + yScape + 5);
        txtW(1); txtH(1); txtFG(0x0000); txtBG(0x5CF4);
        for(char b = 0; b < 3; b++){ txtPS(clrStr); }
        moveTO((greenLightStartX + (h * laneWidth)) - lightRadius - 40, redLightStartY + lightRadius + yScape + 5);
        if(average[0] > 0){ itoa(round((average[1] / average[0]) * 100), holder, 10); } else { itoa(0, holder, 10); }
        txtPS(holder);
        
        laneMeanValues[cMean++] = round((average[1] / average[0]) * 100);
        
       }
       yScape += 20;
       cHour++;
      } while(yScape < 99);cLane++;
     }
     setTimeLabels();
     do {} while(second(now()) == 10);
    }
   }
    
   if(heartbeats == 3600){ readCurrentTraffic(); saveTraffic(1, 1); saveTime(now()); heartbeats = 0; } else { heartbeats++; }
    
   if(greenZerState == 0){ greenZerState = 1; } else { greenZerState = 0; }
    
   heartbeatTime = millis();
   updating = false;
  }
 } else {
  if(millis() > heartbeatTime + heartbeatInterval){ heartbeatTime = millis(); }
 }
}

