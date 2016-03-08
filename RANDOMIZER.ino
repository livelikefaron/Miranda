
 void RANDOMIZER_SERVICE(){
 
 // interlock execution
 for(int i = 0; i < 6; i++){
  if(interlockOn[i]){
   if(millis() > interlockStartTime[i] + interlockTimer[i]){
    if(interlockTimer[i] <= 60000){ interlockOn[i] = 0; if(rfidC > 0){ dumpRfid(); }}
   } else {
    for(int j = 0; j < 4; j++){
     if(bitRead(interlockRelayAssoc[i], j) == 1){
      char pulse = relayPulse[j];
      if(bitRead(inversions, j) == 1){
       if(millis() > interlockStartTime[i] + (pulse * 1000) && pulse < 60){ 
        dryOutputState[j] = LOW;
       } else {
        dryOutputState[j] = HIGH;
       }
      } else {
       if(millis() > interlockStartTime[i] + (pulse * 1000) && pulse < 60){
        dryOutputState[j] = HIGH;
       } else {
        dryOutputState[j] = LOW;
       }
      }
     }
    }
   }
  } else {
   for(int j = 0; j < 4; j++){
    if(bitRead(interlockRelayAssoc[i], j) == 1){
     if(bitRead(inversions, j) == 0){ dryOutputState[j] = HIGH; } else { dryOutputState[j] = LOW; }
    }
   }
  }
 }
}
 

void doMaths(int in){
 int input = in + 1;
 int interlock;
 int laneStartInputs[4];
 int laneStart[4]; for(int i = 0; i < 4; i++){ laneStart[i] = 0; }
 
 // load array with lane initiators
 int j = 0;
 for(int i = LANE_1_START_INPUT; i < LANE_1_START_INPUT + 4; i++){
  laneStartInputs[j++] = save.readEEPROM(DISK0, i);
 }
 
 // check array for signaled input
 j = 0;
 for(int i = 0; i < 4; i++){ if(laneStartInputs[i] == input){
  int m = 0;
  do {
   if(save.readEEPROM(DISK0, INTERLOCK_1_MODE + m) == RANDOMIZER_LANE_1 + i){
    interlock = m;
    break;
   }
   m++;
  } while(m < 6);
  if(interlockOn[interlock]){
   if(save.readEEPROM(DISK0, LANE_1_STOP_INPUT + i) == input){
    interlockOn[interlock] = 0;
   } else { laneStart[i] = 1; }
  } else { laneStart[i] = 1; }
 }}
 
 // check for resets
 for(int i = 0; i < 4; i++){
  if(interlockOn[i]){
   
   if(laneStartInputs[i] == input){
    // stop the possibility of another inspection event while the interlock is on
    laneStart[i] = 0;
    // but increase the total traffic count
    trafficLane[i]++; saveLaneTraffic(i, trafficLane[i]);
    // and tally up future rolls for the accounted traffic
    laneSecondChance[i]++;
   }
   
   if(save.readEEPROM(DISK0, LANE_1_STOP_INPUT + i) == input){
    
    interlockOn[i] = 0;
    laneStart[i] = 0;
    if(rfidC > 0){ dumpRfid(); }
   }
  }
 }
 
 // do maths
 for(int i = 0; i < 4; i++){
  if(laneStart[i] == 1){
   int gotcha = 0;
   trafficLane[i]++;
   saveLaneTraffic(i, trafficLane[i]);
   if(rollWithIt(laneStopByHourStartAddress[i]) == 1){
    selected(i); 
   } else {
    if(laneSecondChance[i] > 0){
     do {
      laneSecondChance[i]--;
      if(rollWithIt(laneStopByHourStartAddress[i]) == 1){
       selected(i);
       gotcha = 1;
       break;
      }
     } while(laneSecondChance[i] > 0);
     if(gotcha == 0){
      if(rfidC > 0){ dumpRfid(); }
      greenLight(i, 1);
     }
    } else {
     if(rfidC > 0){ dumpRfid(); }
     greenLight(i, 1);
    }
   }
   laneStart[i] = 0;
  }
 }
}

int rollWithIt(int addr){
 int insp = 0;
 int roll = random(1, 100);
 if(roll <= save.readEEPROM(DISK0, addr + hour())){ insp = 1; }
 return insp;
}

void selected(int lane){
 int j = 0;
 int m = 0;
 int interlock;
 do {
  if(save.readEEPROM(DISK0, INTERLOCK_1_MODE + m) == RANDOMIZER_LANE_1 + lane){
   interlock = m;
   break;
  }
  m++;
 } while(m < 6);
 interlockTimer[interlock] = (unsigned int)(save.readEEPROM(DISK0, INTERLOCK_1_PULSE_TIME + lane) * 1000);
 stopsLane[lane]++;
 saveLaneStops(lane, stopsLane[lane]);
 activateInterlock(interlock);
}

void activateInterlock(int interlock){
 interlockStartTime[interlock] = millis();
 interlockOn[interlock] = 1;
 for(int j = 0; j < 4; j++){ if(bitRead(interlockRelayAssoc[interlock], j) == 1){ relayPulse[j] = save.readEEPROM(DISK0, 10100 + j); }}
}

