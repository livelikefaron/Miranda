
void INIT_GRAPHICS(){
 
 touchPoint = 0;
 lastTou = 0;
 
 // config layout segment offset (move the config box)
 segYOffset = -10;
 segXOffset = 0;
 
 for(char setx = 0, sety = 1; setx < 3; setx += 2, sety += 2){
  seg1a[setx] += segXOffset; seg1a[sety] += segYOffset;
  seg1b[setx] += segXOffset; seg1b[sety] += segYOffset;
  seg2a[setx] += segXOffset; seg2a[sety] += segYOffset;
  seg2b[setx] += segXOffset; seg2b[sety] += segYOffset;
  seg3a[setx] += segXOffset; seg3a[sety] += segYOffset;
  seg3b[setx] += segXOffset; seg3b[sety] += segYOffset;
  seg4a[setx] += segXOffset; seg4a[sety] += segYOffset;
  seg4b[setx] += segXOffset; seg4b[sety] += segYOffset;
  seg5a[setx] += segXOffset; seg5a[sety] += segYOffset;
  seg5b[setx] += segXOffset; seg5b[sety] += segYOffset;
 }
 
 greenLightStartX = (laneStartX + (laneWidth / 2));
 greenLightStartY = laneStartY + 50;
 redLightStartX   = greenLightStartX;
 redLightStartY   = greenLightStartY + 29;
 
 gfxResetState    = LOW;
 gfxResetTime     = millis();
 gfxResetInterval = 100;
 
 gfxBootState    = LOW;
 gfxBootTime     = millis();
 gfxBootInterval = 3000;
 
 gfxGraph = 0;
 graphBuilt = 0;
 
 touchTime = millis();
 touchInterval = 3000;
 touchState = 0;
 touchSleep = 0;
 touchMode = LOW;
 
 bootDone = 0;
 slowBoot = 1;
 slowBootDelay = 100;
 
 timeFG = 0xFFFFFF;
 timeBG = 0x0000;
 
 touchStatus = 0;
 
 //Display.txt_Xgap(timeXG);
 txtFont(2);
 
 currentPage = 0;
 reset_gfx();
}

void GRAPHICS_SERVICE(){
  
 // gfx reset pin timer
 if(gfxResetState == LOW){ if(millis() > gfxResetTime + gfxResetInterval){ gfxResetState = HIGH; }}
  digitalWrite(GFX_RESET_PIN, gfxResetState);
  
 if(gfxBootState == LOW){
  if((millis() > gfxBootTime + gfxBootInterval)){
   gfxBootState = HIGH;
   bootDone = 1;
   gfxGraph = 1;
  }
 }
 
 if(bootDone){
 
  /* 
  // settings button sensing only when screen is on
  if(gfxPowerState == HIGH){
   gfxPowerTime = millis(); // keep the screen on
   en = setTouch(0); en = setTouch(2);
   touchStatus = getCoordinate(0, 0);
      
   if(touchStatus == 2){
    deTouchHandler(getCoordinate(1, 0), getCoordinate(2, 0), currentPage, 0);
   }
   en = setTouch(1);
  }
  */
  
  if(touchMode){
   int debug = 0;
   int x;
   int y;
   en = setTouch(0);
   en = setTouch(2);
   buildConfigGlobal(currentPage);
   buildConfig(currentPage);
   formFields(currentPage);
   //touchHandler(touX[lastTou], touY[lastTou], currentPage);
   
   //************************************************************************************
   // touch screen configuration loop
   // all other processes will be stalled
  
    while(touchMode){
     
     gfxPowerTime = millis(); // keep the screen on
     touchStatus = getCoordinate(0, debug);
     
     if(touchStatus != 0){
      gfxPowerTime = millis();
      if(touchStatus == 1){ // touched
       y = getCoordinate(2, debug);
       x = getCoordinate(1, debug);
       touchHandler(x, y, currentPage);
       do{ touchStatus = getCoordinate(0, debug); } while(touchStatus != 2);
       deTouchHandler(x, y, currentPage, 1);
       if(touchStatus == 2){
        y = getCoordinate(2, debug);
        x = getCoordinate(1, debug);
        deTouchHandler(x, y, currentPage, 0);
       }
       y = 0; x = 0;
      }
      touchTime = millis();
     } else {  }
   }
  
   //************************************************************************************
   
  } else { if(gfxGraph){
    
    if(graphBuilt){
     
     txtFG(0xFFFF);
     txtBG(0x001F);
     txtW(1);
     txtH(1);
     
     gfxGraph = 0;
      
    } else {
     basicLayout();
     
     rect(5, 57, 470, 85, 0x0000, 1);
     rect(8, 60, 468, 82, 0xFFFF, 0);
     
     //menuButton(0);
     
     txtFG(0xFFFF); txtBG(0x0000);
     txtFont(0); txtW(1); txtH(2);
     moveTO(greenLightStartX + (0 * laneWidth) - 15, greenLightStartY - 55); txtPS("LN1");
     moveTO(greenLightStartX + (1 * laneWidth) - 15, greenLightStartY - 55); txtPS("LN2");
     moveTO(greenLightStartX + (2 * laneWidth) - 15, greenLightStartY - 55); txtPS("LN3");
     moveTO(greenLightStartX + (3 * laneWidth) - 15, greenLightStartY - 55); txtPS("LN4");
     
     // aa&cg header and device name
     txtFG(0xFFFF); txtBG(0x0000);
     txtFont(0); txtW(1); txtH(2);
     moveTO(5 + 8, 5 + 8);
     txtPS(randStr[5]);
     txtFont(0); txtW(1); txtH(1);
     moveTO(5 + 30, 5 + 30);
     txtPS(randStr[4]);
     
     // lane graphics layout***
     
     // lane traffic stats label boxes
     rect(
      (greenLightStartX + (0 * laneWidth)) - lightRadius - 70,
      greenLightStartY - lightRadius,
      (greenLightStartX + (0 * laneWidth)) - lightRadius - 10,
      greenLightStartY - lightRadius + 20, LABEL_BOX_1, 1);
     rect(
      (greenLightStartX + (0 * laneWidth)) - lightRadius - 70,
      greenLightStartY - lightRadius,
      (greenLightStartX + (0 * laneWidth)) - lightRadius - 10,
      greenLightStartY - lightRadius + 20, LABEL_BOX_1_BRDR, 0);
     
     rect(
      (redLightStartX + (0 * laneWidth)) - lightRadius - 70,
      redLightStartY - lightRadius + 5,
      (redLightStartX + (0 * laneWidth)) - lightRadius - 10,
      redLightStartY - lightRadius + 25, LABEL_BOX_2, 1);
     rect(
      (redLightStartX + (0 * laneWidth)) - lightRadius - 70,
      redLightStartY - lightRadius + 5,
      (redLightStartX + (0 * laneWidth)) - lightRadius - 10,
      redLightStartY - lightRadius + 25, LABEL_BOX_2_BRDR, 0);
     
     for(char g = 0, h = 1; g < 4; g++, h++){
      // lane traffic stats boxes
      rect(
       (greenLightStartX + (g * laneWidth)) + lightRadius + 10,
       greenLightStartY - lightRadius,
       (greenLightStartX + (h * laneWidth)) - lightRadius - 10,
       greenLightStartY - lightRadius + 20, STAT_BOX_1, 1);
      rect(
       (greenLightStartX + (g * laneWidth)) + lightRadius + 10,
       greenLightStartY - lightRadius,
       (greenLightStartX + (h * laneWidth)) - lightRadius - 10,
       greenLightStartY - lightRadius + 20, STAT_BOX_1_BRDR, 0);
      rect(
       (redLightStartX + (g * laneWidth)) + lightRadius + 10,
       redLightStartY - lightRadius + 5,
       (redLightStartX + (h * laneWidth)) - lightRadius - 10,
       redLightStartY - lightRadius + 25, STAT_BOX_2, 1);
      rect(
       (redLightStartX + (g * laneWidth)) + lightRadius + 10,
       redLightStartY - lightRadius + 5,
       (redLightStartX + (h * laneWidth)) - lightRadius - 10,
       redLightStartY - lightRadius + 25, STAT_BOX_2_BRDR, 0);
     }
     
     // traffic stats labels
     txtW(1);
     txtH(1);
     moveTO((greenLightStartX + (0 * laneWidth)) - lightRadius - 65, greenLightStartY - lightRadius + 6);
     txtFG(LABEL_BOX_1_TXT); txtBG(LABEL_BOX_1); txtPS(randStr[3]);
     moveTO((redLightStartX + (0 * laneWidth)) - lightRadius - 65, redLightStartY - lightRadius + 11);
     txtFG(LABEL_BOX_2_TXT); txtBG(LABEL_BOX_2);txtPS(randStr[2]);
     
     // traffic lights
     int cLane = 0;
     int cMean = 0;
     for(int g = 0, h = 1; g < 4; g++, h++){
      rect(
       (greenLightStartX + (g * laneWidth)) - lightRadius - 10,
       greenLightStartY - lightRadius - 5,
       (greenLightStartX + (g * laneWidth)) + lightRadius + 10,
       redLightStartY + lightRadius + 5, 0xFD20, 1);
      rect(
       (greenLightStartX + (g * laneWidth)) - lightRadius - 10,
       greenLightStartY - lightRadius - 5,
       (greenLightStartX + (g * laneWidth)) + lightRadius + 10,
       redLightStartY + lightRadius + 5, 0x0000, 0);
      rect(
       (greenLightStartX + (g * laneWidth)) - lightRadius - 10,
       greenLightStartY - lightRadius - 5,
       (greenLightStartX + (g * laneWidth)) - lightRadius - 5,
       redLightStartY + lightRadius + 5, 0x0000, 0);
      rect(
       (greenLightStartX + (g * laneWidth)) + lightRadius + 5,
       greenLightStartY - lightRadius - 5,
       (greenLightStartX + (g * laneWidth)) + lightRadius + 10,
       redLightStartY + lightRadius + 5, 0x0000, 0);
      
      greenLight(g, 0); // turn green light off
      redLight(g, 0); // turn red light off
      
      line(
       (greenLightStartX + (g * laneWidth)) - lightRadius,
       greenLightStartY + lightRadius + 2,
       (greenLightStartX + (g * laneWidth)) + lightRadius,
       greenLightStartY + lightRadius + 2, 0x0000);
       
      rect(
       (greenLightStartX + (g * laneWidth)) - lightRadius - 10,
       redLightStartY + lightRadius + 20,
       (greenLightStartX + (h * laneWidth)) - lightRadius - 10,
       redLightStartY + lightRadius + 40, 0x0000, 1);
      rect(
       (greenLightStartX + (g * laneWidth)) - lightRadius - 10,
       redLightStartY + lightRadius + 20,
       (greenLightStartX + (h * laneWidth)) - lightRadius - 10,
       redLightStartY + lightRadius + 40, 0xFFFF, 0);
       
      rect(
       (greenLightStartX + (h * laneWidth)) - lightRadius - 60,
       redLightStartY + lightRadius + 5,
       (greenLightStartX + (h * laneWidth)) - lightRadius - 10,
       redLightStartY + lightRadius + 20, 0x5CF4, 1);
      rect(
       (greenLightStartX + (h * laneWidth)) - lightRadius - 60,
       redLightStartY + lightRadius + 5,
       (greenLightStartX + (h * laneWidth)) - lightRadius - 10,
       redLightStartY + lightRadius + 20, 0xFFFF, 0);
      
      char yScape = 20;
      int  cHour = 0;
      do {
       rect(
        (greenLightStartX + (h * laneWidth)) - lightRadius - 45,
        redLightStartY + lightRadius + yScape,
        (greenLightStartX + (h * laneWidth)) - lightRadius - 10,
        redLightStartY + lightRadius + yScape + 20, 0x5CF4, 1);
       rect(
        (greenLightStartX + (h * laneWidth)) - lightRadius - 45,
        redLightStartY + lightRadius + yScape,
        (greenLightStartX + (h * laneWidth)) - lightRadius - 10,
        redLightStartY + lightRadius + yScape + 20, 0xFFFF, 0);
       if(yScape > 39){
        rect(
         (greenLightStartX + (g * laneWidth)) - lightRadius - 10,
         redLightStartY + lightRadius + yScape,
         (greenLightStartX + (g * laneWidth)) + lightRadius - 3,
         redLightStartY + lightRadius + yScape + 20, 0x0400, 1);
        rect(
         (greenLightStartX + (g * laneWidth)) + lightRadius - 3,
         redLightStartY + lightRadius + yScape,
         (greenLightStartX + (h * laneWidth)) - lightRadius - 45,
         redLightStartY + lightRadius + yScape + 20, 0xF800, 1);
        rect(
         (greenLightStartX + (g * laneWidth)) + lightRadius - 3,
         redLightStartY + lightRadius + yScape,
         (greenLightStartX + (h * laneWidth)) - lightRadius - 45,
         redLightStartY + lightRadius + yScape + 20, 0xFFFF, 0);
        rect(
         (greenLightStartX + (g * laneWidth)) - lightRadius - 10,
         redLightStartY + lightRadius + yScape,
         (greenLightStartX + (h * laneWidth)) - lightRadius - 10,
         redLightStartY + lightRadius + yScape + 20, 0xFFFF, 0);
         
        unsigned char dat[2];
        double average[2];
        
        dat[1] = save.readEEPROM(DISK0, ((8400 + ((hour() - cHour) * 12)) + (cLane * 2)) + 1);
        dat[0] = save.readEEPROM(DISK0, ((8400 + ((hour() - cHour) * 12)) + (cLane * 2)));
        moveTO((greenLightStartX + (g * laneWidth)) - lightRadius - 5, redLightStartY + lightRadius + yScape + 5);
        itoa(dat[1] << 8 | dat[0], holder, 10); txtW(1); txtH(1); txtFG(0x0000); txtBG(0x0400); txtPS(holder);
        average[0] = dat[1] << 8 | dat[0];
        
        dat[1] = save.readEEPROM(DISK0, ((8700 + ((hour() - cHour) * 12)) + (cLane * 2)) + 1);
        dat[0] = save.readEEPROM(DISK0, ((8700 + ((hour() - cHour) * 12)) + (cLane * 2)));
        moveTO((greenLightStartX + (g * laneWidth)) + lightRadius + 5, redLightStartY + lightRadius + yScape + 5);
        itoa(dat[1] << 8 | dat[0], holder, 10); txtW(1); txtH(1); txtFG(0x0000); txtBG(0xF800); txtPS(holder);
        average[1] = dat[1] << 8 | dat[0];
         
        moveTO((greenLightStartX + (h * laneWidth)) - lightRadius - 40, redLightStartY + lightRadius + yScape + 5);
        txtW(1); txtH(1); txtFG(0x0000); txtBG(0x5CF4);
        if(average[0] > 0){ itoa(round((average[1] / average[0]) * 100), holder, 10); } else { itoa(0, holder, 10); }
        txtPS(holder);
        
        laneMeanValues[cMean++] = round((average[1] / average[0]) * 100);
        
       }
       yScape += 20;
       cHour++;
      } while(yScape < 99);
        
      txtFG(0xFFFF); txtBG(0x0000); txtW(1); txtH(1);
      moveTO((greenLightStartX + (g * laneWidth)) - lightRadius - 5, redLightStartY + lightRadius + 27);
      itoa(save.readEEPROM(DISK0, laneStopByHourStartAddress[g]+hour()), holder, 10);
      txtPS(randStr[32]); txtPS(clrStr); txtPS(holder);
      moveTO((greenLightStartX + (h * laneWidth)) - lightRadius - 55, redLightStartY + lightRadius + 9);
      txtFG(STAT_BOX_3_TXT); txtBG(STAT_BOX_3); txtPS(randStr[1]);
      //moveTO((greenLightStartX + (h * laneWidth)) - lightRadius - 40, redLightStartY + lightRadius + 27);
      //if(trafficLane[cLane] > 0){ itoa(round((stopsLane[cLane] / trafficLane[cLane]) * 100), holder, 10); } else { itoa(0, holder, 10); } txtPS(holder);
       
      cLane++;
     }
     
     moveTO((greenLightStartX + (0 * laneWidth)) - lightRadius - 65, redLightStartY + lightRadius + 9);
     txtFG(0xFFFF); txtBG(0x001F); txtPS(randStr[0]);
     
     setTimeLabels();
     
     // end lane graphics layout****
     
     graphBuilt = 1;
    }
    
  }}
 }
}

void setTimeLabels(){
   txtFG(0xFFFF); txtBG(0x001F); 
   for(int g = 47, t = 3600; g < 97; g += 20, t += 3600){
    moveTO((greenLightStartX + (0 * laneWidth)) - lightRadius - 55, redLightStartY + lightRadius + g);
    for(int i = 0; i < 5; i++){ txtPS(clrStr); }
    moveTO((greenLightStartX + (0 * laneWidth)) - lightRadius - 55, redLightStartY + lightRadius + g);
    itoa(hourFormat12(now() - t), holder, 10);
    if(hourFormat12(now() - t) < 10){ txtPS(clrStr); }
    txtPS(holder);
    txtPS(clrStr); if(isAM(now() - t)){ txtPS(meridian[0]); } else { txtPS(meridian[1]); }
  }
}

void reset_gfx(){
 en = setTouch(1);
 delay(100);
 clr();
 delay(100);
 gfxBootTime   = millis();
 gfxPowerTime  = millis();
 gfxResetTime  = millis();
 gfxResetState = LOW;
 gfxBootState  = LOW;
 touchMode     = LOW;
 gfxPowerState = HIGH;
 bootDone      = 0;
 gfxGraph      = 1;
 graphBuilt    = 0;
}

void exitConfig(){
 en = setTouch(1);
 touchMode = LOW;
 currentPage = 0;
 heartbeats = (minute(now()) * 60) + second(now());
 saveTime(now());
 clr();
 bootDone = 1;
 basicLayout();
 updateGraph();
 inversions = save.readEEPROM(DISK0, RELAY_LOGIC);
 for(int i = 0; i < 4; i++){ interlockRelayAssoc[i] = save.readEEPROM(DISK0, INTERLOCK_1_RELAY_ASSOC + i); }
 all_visuals(LOW);
 all_relays (LOW);
 delay(500);
}

void updateGraph(){ gfxGraph = 1; graphBuilt = 0; readCurrentTraffic(); readCurrentStops(); }

int getCoordinate(int coordinate, int debug){
 int data = 0;
 do {
  DisplaySerial.flush();
  DisplaySerial.print((char)0xFF);
  DisplaySerial.print((char)0x37);
  DisplaySerial.print((char)(coordinate >> 8));
  DisplaySerial.print((char)(coordinate));
  delay(10);
  s = 0;
  while(DisplaySerial.available()){ tGet[s++] = DisplaySerial.read(); }
  if(s < 4){ delay(10); if(tGet[0] == 0x06){ data = tGet[1] << 8 | tGet[2]; break; }}
 } while(1);
 return data;
}

void buildConfigGlobal(byte page){
 clr();
 basicLayout();
 doneButton(0);
 tabButtons(page);
}

void formFields(byte page){
 DisplaySerial.flush();
 txtFG(0x0000);
 txtBG(0xFFFF);
 txtW(2);
 txtH(2);
 
 switch(page){
 case 0: // config time
  moveTO(seg1a[0], seg1a[3]+12);
  if(hour() < 10){ txtPS(randStr[6]); }
  itoa(hour(), holder, 10); txtPS(holder);
  txtPS(clrStr); txtPS(randStr[30]);
  moveTO(seg2a[0], seg2a[3]+12);
  if(minute() < 10){ txtPS(randStr[6]); }
  itoa(minute(), holder, 10); txtPS(holder);
  moveTO(seg3a[0], seg3a[3]+12);
  if(month() < 10){ txtPS(randStr[6]); }
  itoa(month(), holder, 10); txtPS(holder);
  txtPS(clrStr); txtPS(randStr[13]);
  moveTO(seg4a[0], seg4a[3]+12);
  if(day() < 10){ txtPS(randStr[6]); }
  itoa(day(), holder, 10); txtPS(holder);
  txtPS(clrStr); txtPS(randStr[13]);
  moveTO(seg5a[0], seg5a[3]+12);
  itoa(year(), holder, 10); txtPS(holder);
  break;
  
 case 1:
  //currentOption = hour();
  moveTO(seg1a[0]-5, seg1a[3]+12); for(char b = 0; b < 5; b++){ txtPS(clrStr); }
  moveTO(seg1a[0]-5, seg1a[3]+12);
  
  if(currentOption != 24){
   itoa(save.readEEPROM(DISK0, laneStopByHourStartAddress[0] + currentOption), holder, 10); txtPS(holder); txtPS(randStr[31]);
  } else {
   itoa(save.readEEPROM(DISK0, laneStopByHourStartAddress[0]), holder, 10); txtPS(holder); txtPS(randStr[31]);
  }
  
  moveTO(seg2a[0], seg2a[3]+12); for(char b = 0; b < 5; b++){ txtPS(clrStr); }
  moveTO(seg2a[0], seg2a[3]+12);
  
  if(currentOption != 24){
   itoa(save.readEEPROM(DISK0, laneStopByHourStartAddress[1] + currentOption), holder, 10); txtPS(holder); txtPS(randStr[31]);
  } else {
   itoa(save.readEEPROM(DISK0, laneStopByHourStartAddress[1]), holder, 10); txtPS(holder); txtPS(randStr[31]);
  }
  
  moveTO(seg3a[0], seg3a[3]+12); for(char b = 0; b < 5; b++){ txtPS(clrStr); }
  moveTO(seg3a[0], seg3a[3]+12);
  
  if(currentOption != 24){
   itoa(save.readEEPROM(DISK0, laneStopByHourStartAddress[2] + currentOption), holder, 10); txtPS(holder); txtPS(randStr[31]);
  } else {
   itoa(save.readEEPROM(DISK0, laneStopByHourStartAddress[2]), holder, 10); txtPS(holder); txtPS(randStr[31]);
  }
  
  moveTO(seg4a[0], seg4a[3]+12); for(char b = 0; b < 5; b++){ txtPS(clrStr); }
  moveTO(seg4a[0], seg4a[3]+12);
  
  if(currentOption != 24){
   itoa(save.readEEPROM(DISK0, laneStopByHourStartAddress[3] + currentOption), holder, 10); txtPS(holder); txtPS(randStr[31]);
  } else {
   itoa(save.readEEPROM(DISK0, laneStopByHourStartAddress[3]), holder, 10); txtPS(holder); txtPS(randStr[31]);
  }
  
  moveTO(seg5a[0], seg5a[3]+12);
  txtPS(clrStr);txtPS(clrStr);txtPS(clrStr);
  moveTO(seg5a[0], seg5a[3]+12);
  
  if(currentOption < 24){
   itoa(currentOption, holder, 10); txtPS(holder);
  } else {
   txtPS(randStr[44]);
  }
  
  break;
  
  case 2:
  moveTO(seg1a[0]-2, seg1a[3]+12);
  itoa(currentOption+1, holder, 10); txtPS(holder);
  
  
  moveTO(seg2a[0], seg2a[3]+12);
  if(save.readEEPROM(DISK0, LANE_1_START_INPUT + currentOption) < 255){
   for(char b = 0; b < 3; b++){ txtPS(clrStr); }
   moveTO(seg2a[0], seg2a[3]+12);
   itoa(save.readEEPROM(DISK0, LANE_1_START_INPUT + currentOption), holder, 10);
   if(save.readEEPROM(DISK0, LANE_1_START_INPUT + currentOption) == VIRTUAL_CRD){ txtPS(randStr[7]); } else { txtPS(holder); }
  } else { txtPS(clrStr); txtPS(randStr[13]); txtPS(clrStr); }
  
  moveTO(seg3a[0], seg3a[3]+12);
  txtPS(clrStr); txtPS(randStr[13]); txtPS(clrStr);
  
  moveTO(seg4a[0], seg4a[3]+12);
  if(save.readEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption) < 7){
   for(char b = 0; b < 3; b++){ txtPS(clrStr); }
   moveTO(seg4a[0], seg4a[3]+12);
   itoa(save.readEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption), holder, 10); txtPS(holder);
  } else { txtPS(clrStr); txtPS(randStr[13]); txtPS(clrStr); }
  
  moveTO(seg5a[0], seg5a[3]+12); txtPS(clrStr);
  moveTO(seg5a[0], seg5a[3]+12);
  if(save.readEEPROM(DISK0, 10104 + currentOption) == 1){ txtPS(randStr[42]); }
  if(save.readEEPROM(DISK0, 10104 + currentOption) == 0){ txtPS(randStr[43]); }
  break;
  
  case 3:
  moveTO(seg1a[0]-2, seg1a[3]+12);
  itoa(currentOption+1, holder, 10); txtPS(holder);
  
  moveTO(seg2a[0], seg2a[3]+12);
  if(save.readEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption) < 255){
   for(char b = 0; b < 3; b++){ txtPS(clrStr); }
   moveTO(seg2a[0], seg2a[3]+12);
   itoa(save.readEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption), holder, 10); txtPS(holder);
  } else { txtPS(clrStr); txtPS(randStr[13]); txtPS(clrStr); }
  
  moveTO(seg3a[0], seg3a[3]+12);
  if(bitRead(save.readEEPROM(DISK0, RELAY_LOGIC), currentOption) == 1){ txtPS(randStr[8]); } else { txtPS(randStr[9]); }
  
  moveTO(seg4a[0], seg4a[3]+12);
  txtPS(clrStr);txtPS(clrStr);txtPS(clrStr);
  moveTO(seg4a[0], seg4a[3]+12);
  if(save.readEEPROM(DISK0, 10100 + currentOption) < 60){
   itoa(save.readEEPROM(DISK0, 10100 + currentOption), holder, 10); txtPS(holder);
  } else { txtPS(randStr[14]); }
  break;
  
  case 4:
  break;
  
  case 5:
  moveTO(seg1a[0]-2, seg1a[3]+12);
  itoa(currentOption+1, holder, 10); txtPS(holder);
  
  moveTO(seg2a[0], seg2a[3]+12);
  switch(save.readEEPROM(DISK0, INTERLOCK_1_MODE + currentOption)){
   case RANDOMIZER_LANE_1:
    txtPS(randStr[10]); itoa(1, holder, 10); txtPS(holder);
    break;
   case RANDOMIZER_LANE_2:
    txtPS(randStr[10]); itoa(2, holder, 10); txtPS(holder);
    break; 
   case RANDOMIZER_LANE_3:
    txtPS(randStr[10]); itoa(3, holder, 10); txtPS(holder);
    break; 
   case RANDOMIZER_LANE_4:
    txtPS(randStr[10]); itoa(4, holder, 10); txtPS(holder);
    break; 
   case MANUAL_RESET:
    txtPS(randStr[11]);
    break; 
   case PULSED_RESET:
    txtPS(randStr[12]);
    break; 
   default:
    txtPS(clrStr); txtPS(randStr[13]); txtPS(clrStr);
    break; 
  }
  
  moveTO(seg3a[0]-5, seg3a[3]+12);
  if(save.readEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + currentOption) < 61){
   for(char b = 0; b < 3; b++){ txtPS(clrStr); }
   moveTO(seg3a[0]-5, seg3a[3]+12);
   itoa(save.readEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + currentOption), holder, 10); txtPS(holder);
  } else {
   txtPS(randStr[14]);
  }
  
  txtFG(0xFFFF);
  txtBG(0x18CE);
  
  byte relayAssoc = save.readEEPROM(DISK0, INTERLOCK_1_RELAY_ASSOC + currentOption);
  for(int i = 0, j = 12; i < 4; i++, j = j+20){
   moveTO(seg4a[0]-20, seg4a[3]+j);
   txtPS(randStr[15]); txtPS(clrStr);
   itoa(i+1, holder, 10); txtPS(holder);
   if(bitRead(relayAssoc, i) == 1){
    circ(seg5a[2]+25, seg4a[3]+j+5, 5, 0x0400, 1);
   } else {
    circ(seg5a[2]+25, seg4a[3]+j+5, 5, 0xF800, 1);
   }
  }
  
  break;
 }
}

void pleaseWait(byte sta){
 txtFG(0x07E0); txtBG(0x0000); txtW(2); txtH(2); moveTO(10,dateY+20);
 if(sta){ // on
  txtPS(randStr[45]);
 } else { // off
  for(char ch = 0; ch < 12; ch++){ txtPS(clrStr); } 
 }
}

void configLabels(byte page){
 txtFG(0xFFFF);
 txtBG(0x18CE);
 txtW(1);
 txtH(2);
 switch(page){
 case 0: // config time
  moveTO(seg1a[0]+5, seg1b[3]+5); txtPS(randStr[16]);
  moveTO(seg2a[0]+2, seg2b[3]+5); txtPS(randStr[17]);
  moveTO(seg3a[0]+2, seg3b[3]+5); txtPS(randStr[18]);
  moveTO(seg4a[0]+2, seg4b[3]+5); txtPS(randStr[19]);
  moveTO(seg5a[0], seg5b[3]+5); txtPS(randStr[20]);
  break;
 case 1: // config param
  moveTO(seg1a[0], seg1b[3]+5); txtPS(randStr[10]); itoa(1, holder, 10); txtPS(holder);
  moveTO(seg2a[0], seg2b[3]+5); txtPS(randStr[10]); itoa(2, holder, 10); txtPS(holder);
  moveTO(seg3a[0], seg3b[3]+5); txtPS(randStr[10]); itoa(3, holder, 10); txtPS(holder);
  moveTO(seg4a[0], seg4b[3]+5); txtPS(randStr[10]); itoa(4, holder, 10); txtPS(holder);
  moveTO(seg5a[0], seg5b[3]+5); txtPS(randStr[40]);
  break;
 case 2:
  moveTO(seg1a[0], seg1b[3]+5); txtPS(randStr[10]);
  moveTO(seg2a[0], seg2b[3]+5); txtPS(randStr[21]);
  moveTO(seg2a[0], seg2b[3]+20); txtPS(randStr[22]);
  moveTO(seg3a[0], seg3b[3]+5); txtPS(randStr[23]);
  moveTO(seg3a[0], seg3b[3]+20); txtPS(randStr[24]);
  moveTO(seg4a[0], seg4b[3]+5); txtPS(randStr[23]);
  moveTO(seg4a[0], seg4b[3]+20); txtPS(randStr[22]);
  moveTO(seg5a[0], seg5b[3]+5); txtPS(randStr[41]);
  break;
 case 3:
  moveTO(seg1a[0], seg1b[3]+5); txtPS(randStr[15]);
  moveTO(seg2a[0], seg2b[3]+5); txtPS(randStr[25]);
  moveTO(seg2a[0], seg2b[3]+20); txtPS(randStr[26]);
  moveTO(seg3a[0], seg3b[3]+5); txtPS(randStr[27]);
  moveTO(seg4a[0], seg4b[3]+5); txtPS(randStr[12]);
  break;
 case 4:
  break;
 case 5:
  moveTO(seg1a[0], seg1b[3]+5); txtPS(randStr[25]);
  moveTO(seg1a[0], seg1b[3]+20); txtPS(randStr[26]);
  moveTO(seg2a[0], seg2b[3]+5); txtPS(randStr[28]);
  moveTO(seg3a[0], seg3b[3]+5); txtPS(randStr[23]);
  moveTO(seg3a[0], seg3b[3]+20); txtPS(randStr[24]);
  moveTO(seg4a[0]-20, seg4a[1]+10); txtPS(randStr[29]);
  break;
 }
}
