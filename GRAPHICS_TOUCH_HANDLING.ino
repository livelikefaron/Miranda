void deTouchHandler(int x, int y, byte page, byte skip){
 // done button
 if((x > 405) && (x < 470)){ if((y > 105) && (y < 145)){ doneButton(0); if(!skip){ exitConfig(); }}} else {}
 
 // seg1a
 if((x > seg1a[0]) && (x < seg1a[2])){ if((y > seg1a[1]) && (y < seg1a[3])){
  pleaseWait(1);
  switch(page){
    
   case 0: // config time
    if(!skip){ if(hour() == 59){ setTime(0,minute(),second(),day(),month(),year()); } else {
     setTime(hour()+1,minute(),second(),day(),month(),year()); }}
    dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
    break;
    
   case 1: // cofig param
    if(!skip){
      
     int addr;
     char per;
     
     if(currentOption == 24){ // set percentage for every hour
       
       addr = laneStopByHourStartAddress[0];
       per = save.readEEPROM(DISK0, addr);
       
       for(int ix = 0; ix < 24; ix++){
        if(per > 98){ save.writeEEPROM(DISK0, addr + ix, 0); } else { save.writeEEPROM(DISK0, addr + ix, per+1); }
       }
       
     } else {
       
      addr = laneStopByHourStartAddress[0] + currentOption;
      per = save.readEEPROM(DISK0, addr);
      if(per > 98){ save.writeEEPROM(DISK0, addr, 0); } else { save.writeEEPROM(DISK0, addr, per+1); }
     }
     
    }
    dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
    break;
    
   case 2: // cofig lane
    if(!skip){ if(currentOption == 3){ currentOption = 0; } else { currentOption++; }
    }
    dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
    break;
    
   case 3: // config relays
    if(!skip){ if(currentOption == 3){ currentOption = 0; } else { currentOption++; }
    }
    dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
    break;
    
   case 4: // config inputs
    if(!skip){}
    dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
    break;
    
   case 5: // config interlocks
    if(!skip){ if(currentOption == 3){ currentOption = 0; } else { currentOption++; }
    }
    dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
    break;
  }
  pleaseWait(0);
  formFields(page);
 }}
 
 // seg1b
 if((x > seg1b[0]) && (x < seg1b[2])){ if((y > seg1b[1]) && (y < seg1b[3])){
  pleaseWait(1);
  switch(page){
    
   case 0: // config time
    if(!skip){ if(hour() == 0){ setTime(59,minute(),second(),day(),month(),year()); } else {
     setTime(hour()-1,minute(),second(),day(),month(),year()); }}
    dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
    break;
    
   case 1: // cofig param
    if(!skip){
      
     int addr;
     char per;
     
     if(currentOption == 24){ // set percentage for every hour
       
       addr = laneStopByHourStartAddress[0];
       per = save.readEEPROM(DISK0, addr);
       
       for(int ix = 0; ix < 24; ix++){
        if(per == 0){ save.writeEEPROM(DISK0, addr + ix, 99); } else { save.writeEEPROM(DISK0, addr + ix, per-1); }
       }
       
     } else { 
       
      addr = laneStopByHourStartAddress[0] + currentOption;
      per = save.readEEPROM(DISK0, addr);
      if(per == 0){ save.writeEEPROM(DISK0, addr, 99); } else { save.writeEEPROM(DISK0, addr, per-1); }
     }
     
    }
    dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
    break;
    
   case 2: // cofig lane
    if(!skip){ if(currentOption == 0){ currentOption = 3; } else { currentOption--; }
    }
    dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
    break;
    
   case 3: // config relays
    if(!skip){ if(currentOption == 0){ currentOption = 3; } else { currentOption--; }
    }
    dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
    break;
    
   case 4: // config inputs
    if(!skip){}
    dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
    break;
    
   case 5: // config interlocks
    if(!skip){ if(currentOption == 0){ currentOption = 3; } else { currentOption--; }
    }
    dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
    break;
  }
  pleaseWait(0);
  formFields(page);
 }}
 
 // seg2a
 if((x > seg2a[0]) && (x < seg2a[2])){ if((y > seg2a[1]) && (y < seg2a[3])){
  pleaseWait(1);
  switch(page){
    
   case 0: // config time
    if(!skip){ if(minute() == 59){ setTime(hour(),0,second(),day(),month(),year()); } else {
     setTime(hour(),minute()+1,second(),day(),month(),year()); }}
    dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
    break;
    
   case 1: // config param
    if(!skip){
      
     int addr;
     char per;
     
     if(currentOption == 24){ // set percentage for every hour
       
       addr = laneStopByHourStartAddress[1];
       per = save.readEEPROM(DISK0, addr);
       
       for(int ix = 0; ix < 24; ix++){
        if(per > 98){ save.writeEEPROM(DISK0, addr + ix, 0); } else { save.writeEEPROM(DISK0, addr + ix, per+1); }
       }
       
     } else {
       
      addr = laneStopByHourStartAddress[1] + currentOption;
      per = save.readEEPROM(DISK0, addr);
      if(per > 98){ save.writeEEPROM(DISK0, addr, 0); } else { save.writeEEPROM(DISK0, addr, per+1); }
     }
     
    }
    dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
    break;
    
   case 2: // config lane
    if(!skip){
     char option = save.readEEPROM(DISK0, LANE_1_START_INPUT + currentOption);
     if(option >= 7){
       save.writeEEPROM(DISK0, LANE_1_START_INPUT + currentOption, 1); 
      } else {
       save.writeEEPROM(DISK0, LANE_1_START_INPUT + currentOption, option + 1);
     }}
    dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
    break;
    
   case 3: // config relays
    if(!skip){
     if(save.readEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption) >= 4){
      save.writeEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption, 1);
     } else {
      save.writeEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption, save.readEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption) + 1);
     }
     byte inter = save.readEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption) - 1;
     byte assoc = save.readEEPROM(DISK0, INTERLOCK_1_RELAY_ASSOC + inter);
     for(int i = INTERLOCK_1_RELAY_ASSOC; i < INTERLOCK_1_RELAY_ASSOC + 4; i++){
      byte clrBit = save.readEEPROM(DISK0, i);
      save.writeEEPROM(DISK0, i, bitWrite(clrBit, currentOption, 0));
     }
     save.writeEEPROM(DISK0, INTERLOCK_1_RELAY_ASSOC + inter, bitWrite(assoc, currentOption, 1));
    }
    dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
    break;
    
   case 4: // config inputs
    if(!skip){}
    dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
    break;
    
   case 5: // config interlocks
    if(!skip){}
    dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
    break;
  }
  pleaseWait(0);
  formFields(page);
 }}
 
 // seg2b
 if((x > seg2b[0]) && (x < seg2b[2])){ if((y > seg2b[1]) && (y < seg2b[3])){
  pleaseWait(1);
  switch(page){
    
   case 0: // config time
    if(!skip){ if(minute() == 0){ setTime(hour(),59,second(),day(),month(),year()); } else {
     setTime(hour(),minute()-1,second(),day(),month(),year()); }}
    dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
    break;
    
   case 1: // config param
    if(!skip){
      
     int addr;
     char per;
     
     if(currentOption == 24){ // set percentage for every hour
       
       addr = laneStopByHourStartAddress[1];
       per = save.readEEPROM(DISK0, addr);
       
       for(int ix = 0; ix < 24; ix++){
        if(per == 0){ save.writeEEPROM(DISK0, addr + ix, 99); } else { save.writeEEPROM(DISK0, addr + ix, per-1); }
       }
       
     } else { 
       
      addr = laneStopByHourStartAddress[1] + currentOption;
      per = save.readEEPROM(DISK0, addr);
      if(per == 0){ save.writeEEPROM(DISK0, addr, 99); } else { save.writeEEPROM(DISK0, addr, per-1); }
     }
     
    }
    dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
    break;
    
   case 2: // config lane
    if(!skip){
     char option = save.readEEPROM(DISK0, LANE_1_START_INPUT + currentOption);
     if(option == 1){
       save.writeEEPROM(DISK0, LANE_1_START_INPUT + currentOption, 7); 
      } else {
       save.writeEEPROM(DISK0, LANE_1_START_INPUT + currentOption, option - 1);
     }}
    dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
    break;
    
   case 3: // config relays
    if(!skip){
     if(save.readEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption) == 1){
      save.writeEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption, 4);
     } else {
      save.writeEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption, save.readEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption) - 1);
     }
     byte inter = save.readEEPROM(DISK0, RELAY_1_INTERLOCK + currentOption) - 1;
     byte assoc = save.readEEPROM(DISK0, INTERLOCK_1_RELAY_ASSOC + inter);
     for(int i = INTERLOCK_1_RELAY_ASSOC; i < INTERLOCK_1_RELAY_ASSOC + 4; i++){
      byte clrBit = save.readEEPROM(DISK0, i);
      save.writeEEPROM(DISK0, i, bitWrite(clrBit, currentOption, 0));
     }
     save.writeEEPROM(DISK0, INTERLOCK_1_RELAY_ASSOC + inter, bitWrite(assoc, currentOption, 1));
    }
    dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
    break;
    
   case 4: // config inputs
    if(!skip){}
    dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
    break;
    
   case 5: // config interlocks
    if(!skip){}
    dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
    break;
  }
  pleaseWait(0);
  formFields(page);
 }}
 
 // seg3a
 if((x > seg3a[0]) && (x < seg3a[2])){ if((y > seg3a[1]) && (y < seg3a[3])){
  pleaseWait(1);
  switch(page){
    
   case 0: // config time
    if(!skip){ if(month() == 12){ setTime(hour(),59,second(),day(),1,year()); } else {
     setTime(hour(),minute(),second(),day(),month()+1,year()); }}
    dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
    break;
    
   case 1: // config param
    if(!skip){
      
     int addr;
     char per;
     
     if(currentOption == 24){ // set percentage for every hour
       
       addr = laneStopByHourStartAddress[2];
       per = save.readEEPROM(DISK0, addr);
       
       for(int ix = 0; ix < 24; ix++){
        if(per > 98){ save.writeEEPROM(DISK0, addr + ix, 0); } else { save.writeEEPROM(DISK0, addr + ix, per+1); }
       }
       
     } else {
       
      addr = laneStopByHourStartAddress[2] + currentOption;
      per = save.readEEPROM(DISK0, addr);
      if(per > 98){ save.writeEEPROM(DISK0, addr, 0); } else { save.writeEEPROM(DISK0, addr, per+1); }
     }
     
    }
    dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
    break;
    
   case 2: // config lane
    if(!skip){}
    dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
    break;
    
   case 3: // config relays
    if(!skip){
     byte thisData = save.readEEPROM(DISK0, RELAY_LOGIC);
     byte thisBit;
     if(bitRead(thisData, currentOption) == 1){ thisBit = 0; } else { thisBit = 1; }
     bitWrite(thisData, currentOption, thisBit);
     save.writeEEPROM(DISK0, RELAY_LOGIC, thisData);
     for(int i = INTERLOCK_1_RELAY_ASSOC; i < INTERLOCK_1_RELAY_ASSOC + 6; i++){
      thisData = save.readEEPROM(DISK0, i);
      if(bitRead(thisData, currentOption) == 1){
       bitWrite(thisData, currentOption + 4, thisBit);
       save.writeEEPROM(DISK0, i, thisData);
      }
     }
    }
    dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
    break;
    
   case 4: // config inputs
    if(!skip){}
    dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
    break;
    
   case 5: // config interlocks
    if(!skip){
     if(save.readEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + currentOption) >= 61){
      save.writeEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + currentOption, 1);
     } else {
      save.writeEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + currentOption, save.readEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + currentOption) + 1);
     }}
    dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
    break;
  }
  pleaseWait(0);
  formFields(page);
 }}
 
 // seg3b
 if((x > seg3b[0]) && (x < seg3b[2])){ if((y > seg3b[1]) && (y < seg3b[3])){
  pleaseWait(1);
  switch(page){
    
   case 0: // config time
    if(!skip){ if(month() == 1){ setTime(hour(),59,second(),day(),12,year()); } else {
     setTime(hour(),minute(),second(),day(),month()-1,year()); }}
    dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
    break;
    
   case 1: // config param
    if(!skip){
      
     int addr;
     char per;
     
     if(currentOption == 24){ // set percentage for every hour
       
       addr = laneStopByHourStartAddress[2];
       per = save.readEEPROM(DISK0, addr);
       
       for(int ix = 0; ix < 24; ix++){
        if(per == 0){ save.writeEEPROM(DISK0, addr + ix, 99); } else { save.writeEEPROM(DISK0, addr + ix, per-1); }
       }
       
     } else { 
       
      addr = laneStopByHourStartAddress[2] + currentOption;
      per = save.readEEPROM(DISK0, addr);
      if(per == 0){ save.writeEEPROM(DISK0, addr, 99); } else { save.writeEEPROM(DISK0, addr, per-1); }
     }
     
    }
    dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
    break;
    
   case 2: // config lane
    if(!skip){}
    dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
    break;
    
   case 3: // config relays
    if(!skip){
     byte thisData = save.readEEPROM(DISK0, RELAY_LOGIC);
     byte thisBit;
     if(bitRead(thisData, currentOption) == 1){ thisBit = 0; } else { thisBit = 1; }
     bitWrite(thisData, currentOption, thisBit);
     save.writeEEPROM(DISK0, RELAY_LOGIC, thisData);
     for(int i = INTERLOCK_1_RELAY_ASSOC; i < INTERLOCK_1_RELAY_ASSOC + 6; i++){
      thisData = save.readEEPROM(DISK0, i);
      if(bitRead(thisData, currentOption) == 1){
       bitWrite(thisData, currentOption + 4, thisBit);
       save.writeEEPROM(DISK0, i, thisData);
      }
     }
    }
    dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
    break;
    
   case 4: // config inputs
    if(!skip){}
    dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
    break;
    
   case 5: // config interlocks
    if(!skip){
     if(save.readEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + currentOption) == 1){
      save.writeEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + currentOption, 61);
     } else {
      save.writeEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + currentOption, save.readEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + currentOption) - 1);
     }}
    dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
    break;
  }
  pleaseWait(0);
  formFields(page);
 }}
 
 // seg4a
 if((x > seg4a[0]) && (x < seg4a[2])){ if((y > seg4a[1]) && (y < seg4a[3])){
  pleaseWait(1);
  switch(page){
    
   case 0: // config time
    if(!skip){
     char thirtyOneDayMonths[] = { 1, 3, 5, 7, 8, 10, 12 };
     char thisDay = day(now());
     char thisMon = month(now());
     char maxDays = 30; if(month(now()) == 2){ maxDays = 29; }
     for(int d = 0; d < 7; d++){ if(month(now()) == thirtyOneDayMonths[d]){ maxDays = 31; }}
     if(thisDay < maxDays){ thisDay++; } else { thisDay = 0; }
     setTime(hour(),minute(),second(),thisDay,thisMon,year());
    }
    dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
    break;
    
   case 1: // cofig param
    if(!skip){
      
     int addr;
     char per;
     
     if(currentOption == 24){ // set percentage for every hour
       
       addr = laneStopByHourStartAddress[3];
       per = save.readEEPROM(DISK0, addr);
       
       for(int ix = 0; ix < 24; ix++){
        if(per > 98){ save.writeEEPROM(DISK0, addr + ix, 0); } else { save.writeEEPROM(DISK0, addr + ix, per+1); }
       }
       
     } else {
       
      addr = laneStopByHourStartAddress[3] + currentOption;
      per = save.readEEPROM(DISK0, addr);
      if(per > 98){ save.writeEEPROM(DISK0, addr, 0); } else { save.writeEEPROM(DISK0, addr, per+1); }
     }
     
    }
    dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
    break;
    
   case 2: // cofig lane
    if(!skip){
     if(
      save.readEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption) == 6
       ||
      save.readEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption) > 60
     ){ save.writeEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption, 1); 
      } else {
       save.writeEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption, save.readEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption)+1);
     }}
    dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
    break;
    
   case 3: // config relays
    if(!skip){
     char pulse = save.readEEPROM(DISK0, 10100 + currentOption);
     if(pulse < 59){ pulse++; } else { pulse = 1; } save.writeEEPROM(DISK0, 10100 + currentOption, pulse);
    }
    dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
    break;
    
   case 4: // config inputs
    if(!skip){}
    dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
    break;
    
   case 5: // config interlocks
    if(!skip){}
    dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
    break;
  }
  pleaseWait(0);
  formFields(page);
 }}
 
 // seg4b
 if((x > seg4b[0]) && (x < seg4b[2])){ if((y > seg4b[1]) && (y < seg4b[3])){
  pleaseWait(1);
  switch(page){
    
   case 0: // config time
    if(!skip){
     char thirtyOneDayMonths[] = { 1, 3, 5, 7, 8, 10, 12 };
     char thisDay = day(now());
     char thisMon = month(now());
     char maxDays = 30; if(month(now()) == 2){ maxDays = 29; }
     for(int d = 0; d < 7; d++){ if(month(now()) == thirtyOneDayMonths[d]){ maxDays = 31; }}
     if(thisDay > 1){ thisDay--; } else { thisDay = maxDays; }
     setTime(hour(),minute(),second(),thisDay,thisMon,year());
    }
    dirButton(seg4b[0], seg4b[1], seg4b[2], seg4b[3], 0, 0);
    break;
    
   case 1: // cofig param
    if(!skip){
      
     int addr;
     char per;
     
     if(currentOption == 24){ // set percentage for every hour
       
       addr = laneStopByHourStartAddress[3];
       per = save.readEEPROM(DISK0, addr);
       
       for(int ix = 0; ix < 24; ix++){
        if(per == 0){ save.writeEEPROM(DISK0, addr + ix, 99); } else { save.writeEEPROM(DISK0, addr + ix, per-1); }
       }
       
     } else { 
       
      addr = laneStopByHourStartAddress[3] + currentOption;
      per = save.readEEPROM(DISK0, addr);
      if(per == 0){ save.writeEEPROM(DISK0, addr, 99); } else { save.writeEEPROM(DISK0, addr, per-1); }
     }
     
    }
    dirButton(seg4b[0], seg4b[1], seg4b[2], seg4b[3], 0, 0);
    break;
    
   case 2: // cofig lane
    if(!skip){
     if(
      save.readEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption) == 1
       ||
      save.readEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption) > 60
     ){ save.writeEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption, 6); 
      } else {
       save.writeEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption, save.readEEPROM(DISK0, LANE_1_STOP_INPUT + currentOption)-1);
     }}
    dirButton(seg4b[0], seg4b[1], seg4b[2], seg4b[3], 0, 0);
    break;
    
   case 3: // config relays
    if(!skip){
     char pulse = save.readEEPROM(DISK0, 10100 + currentOption);
     if(pulse > 1){ pulse--; } else { pulse = 60; } save.writeEEPROM(DISK0, 10100 + currentOption, pulse);
    }
    dirButton(seg4b[0], seg4b[1], seg4b[2], seg4b[3], 0, 0);
    break;
    
   case 4: // config inputs
    if(!skip){}
    dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
    break;
    
   case 5: // config interlocks
    if(!skip){}
    dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
    break;
  }
  pleaseWait(0);
  formFields(page);
 }}
 
 // seg5a
 if((x > seg5a[0]) && (x < seg5a[2])){ if((y > seg5a[1]) && (y < seg5a[3])){
  pleaseWait(1);
  switch(page){
    
   case 0: // config time
    if(!skip){ setTime(hour(),minute(),second(),day(),month(),year()+1); }
    dirButton(seg5a[0], seg5a[1], seg5a[2], seg5a[3], 1, 0);
    break;
    
   case 1: // cofig param
    if(!skip){
     if(currentOption < 24){ currentOption++; } else { currentOption = 0; }
    }
    dirButton(seg5a[0], seg5a[1], seg5a[2], seg5a[3], 1, 0);
    break;
    
   case 2: // cofig lane
    if(!skip){
     if(save.readEEPROM(DISK0, 10104 + currentOption) != 1){ save.writeEEPROM(DISK0, 10104 + currentOption, 1); }
    }
    dirButton(seg5a[0], seg5a[1], seg5a[2], seg5a[3], 1, 0);
    break;
  }
  pleaseWait(0);
  formFields(page);
 }}
 
 // seg5b
 if((x > seg5b[0]) && (x < seg5b[2])){ if((y > seg5b[1]) && (y < seg5b[3])){
  pleaseWait(1);
  switch(page){
    
   case 0: // config time
    if(!skip){ setTime(hour(),minute(),second(),day(),month(),year()-1); }
    dirButton(seg5b[0], seg5b[1], seg5b[2], seg5b[3], 0, 0);
    break;
    
   case 1: // cofig param
    if(!skip){
     if(currentOption > 0){ currentOption--; } else { currentOption = 24; }
    }
    dirButton(seg5b[0], seg5b[1], seg5b[2], seg5b[3], 0, 0);
    break;
    
   case 2: // cofig lane
    if(!skip){
     if(save.readEEPROM(DISK0, 10104 + currentOption) != 0){ save.writeEEPROM(DISK0, 10104 + currentOption, 0); }
    }
    dirButton(seg5b[0], seg5b[1], seg5b[2], seg5b[3], 0, 0);
    break;
  }
  pleaseWait(0);
  formFields(page);
 }}
 
 // segOpta
 if((x > segOpta[0]) && (x < segOpta[2])){ if((y > segOpta[1]) && (y < segOpta[3])){
  dirButton(segOpta[0], segOpta[1], segOpta[2], segOpta[3], 1, 0);
  if(!skip){
   currentOption = 0;
   if(currentPage == numberOfPages - 1){ currentPage = 0; } else { currentPage++; }
   buildConfig(currentPage);
  }
 }}
 
 // segOptb
 if((x > segOptb[0]) && (x < segOptb[2])){ if((y > segOptb[1]) && (y < segOptb[3])){
  dirButton(segOptb[0], segOptb[1], segOptb[2], segOptb[3], 0, 0);
  if(!skip){
   currentOption = 0;
   if(currentPage == 0){ currentPage = numberOfPages - 1; } else { currentPage--; }
   buildConfig(currentPage);
  }
 }}
 
 // menuBut
 if((x > menuBut[0]) && (x < menuBut[2])){ if((y > menuBut[1]) && (y < menuBut[3])){ touchMode = 1; }}
}

void touchHandler(int x, int y, byte page){
 // done button
 if((x > 405) && (x < 470)){ if((y > 105) && (y < 145)){ doneButton(1); }}
 
 // seg1a
 if((x > seg1a[0]) && (x < seg1a[2])){ if((y > seg1a[1]) && (y < seg1a[3])){
  dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 1);
 }}
 
 // seg1b
 if((x > seg1b[0]) && (x < seg1b[2])){ if((y > seg1b[1]) && (y < seg1b[3])){
  dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 1);
 }} 
 
 // seg2a
 if((x > seg2a[0]) && (x < seg2a[2])){ if((y > seg2a[1]) && (y < seg2a[3])){
  dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 1);
 }}
 
 // seg2b
 if((x > seg2b[0]) && (x < seg2b[2])){ if((y > seg2b[1]) && (y < seg2b[3])){
  dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 1);
 }}
 
 // seg3a
 if((x > seg3a[0]) && (x < seg3a[2])){ if((y > seg3a[1]) && (y < seg3a[3])){
  dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 1);
 }}
 
 // seg3b
 if((x > seg3b[0]) && (x < seg3b[2])){ if((y > seg3b[1]) && (y < seg3b[3])){
  dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 1);
 }}
 
 // seg4a
 if((x > seg4a[0]) && (x < seg4a[2])){ if((y > seg4a[1]) && (y < seg4a[3])){
  dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 1);
 }}
 
 // seg4b
 if((x > seg4b[0]) && (x < seg4b[2])){ if((y > seg4b[1]) && (y < seg4b[3])){
  dirButton(seg4b[0], seg4b[1], seg4b[2], seg4b[3], 0, 1);
 }}
 
 // seg5a
 if((x > seg5a[0]) && (x < seg5a[2])){ if((y > seg5a[1]) && (y < seg5a[3])){
  dirButton(seg5a[0], seg5a[1], seg5a[2], seg5a[3], 1, 1);
 }}
 
 // seg5b
 if((x > seg5b[0]) && (x < seg5b[2])){ if((y > seg5b[1]) && (y < seg5b[3])){
  dirButton(seg5b[0], seg5b[1], seg5b[2], seg5b[3], 0, 1);
 }}
 
 // segOpta
 if((x > segOpta[0]) && (x < segOpta[2])){ if((y > segOpta[1]) && (y < segOpta[3])){
  dirButton(segOpta[0], segOpta[1], segOpta[2], segOpta[3], 1, 1);
 }}
 
 // segOptb
 if((x > segOptb[0]) && (x < segOptb[2])){ if((y > segOptb[1]) && (y < segOptb[3])){
  dirButton(segOptb[0], segOptb[1], segOptb[2], segOptb[3], 0, 1);
 }}
 
 // menuBut
 if((x > menuBut[0]) && (x < menuBut[2])){ if((y > menuBut[1]) && (y < menuBut[3])){
  menuButton(1);
 }}
}
