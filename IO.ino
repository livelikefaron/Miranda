

void INIT_IO(){
  
 // wiegand interrupts
 for(int i = 2; i < 4; i++){ pinMode(i, OUTPUT); digitalWrite(i, HIGH); digitalWrite(i, LOW); pinMode(i, INPUT); digitalWrite(i, HIGH); }
 
 attachInterrupt(0, DATA0, FALLING); // pin 2
 attachInterrupt(1, DATA1, FALLING); // pin 3
 
 pinMode(WD0_OUT, OUTPUT); digitalWrite(WD0_OUT, HIGH);
 pinMode(WD1_OUT, OUTPUT); digitalWrite(WD1_OUT, HIGH);
 
 // init digital inputs - write high to disable internal pullup
 for(int i = 0; i < 6; i++){ set_input(digitalInput[i]); }
 // init dry relays
 for(int i = 0; i < 4; i++){ set_output(dryOutput[i]); }
 // init digital outputs
 for(int i = 0; i < 4; i++){ set_output(digitalOutput[i]); }
 
 bitCnt  = 0;
 rfidC   = 0;
 bitCntC = 0;
 
 buttonSenseInterval1 = 0;
 buttonSenseInterval2 = 0;
 
 instantInputInterval = 0;
 
 resetDefaultTime = 0;
 resetDefaultTrip = 10000;
 
 for(int i = 0; i < 6; i++){ inputSenseInterval[i] = 0; }
 
 lastInput   = 0;
 lastDeInput = 0;
 
 inversions = save.readEEPROM(DISK0, RELAY_LOGIC);
 for(int i = 0; i < 4; i++){ interlockRelayAssoc[i] = save.readEEPROM(DISK0, INTERLOCK_1_RELAY_ASSOC + i); }
}

void IO_SERVICE(){
 // set digital inputs
 for(int i = 0; i < 6; i++){ digitalInputState[i] = digitalRead(digitalInput[i]); }
 
 // set dry relays
 for(int i = 0; i < 4; i++){ digitalWrite(dryOutput[i], dryOutputState[i]); }
 
 // set digital outputs
 for(int i = 0; i < 4; i++){ digitalWrite(digitalOutput[i], digitalOutputState[i]); }
 // read analog values
 for(int i = 0; i < 3; i++){ analogInputValue[i] = analogRead(analogInput[i]); }
 // read function buttons
 for(int i = 0; i < 2; i++){ funcButtonValue[i] = analogRead(funcButton[i]); }
 
 //instant input
 if(analogInputValue[0] < 450){ instantInputInterval++; } else { instantInputInterval = 0; }
 if(instantInputInterval == 8){ instantOn(); }
 
 if(funcButtonValue[0] < 450 && funcButtonValue[1] > 450){
  if(resetDefaultTime == 0){ resetDefaultTime = millis(); }
  if(millis() - resetDefaultTime > resetDefaultTrip){ clearMem(); }
  buttonSenseInterval1++;
 } else { resetDefaultTime = 0; buttonSenseInterval1 = 0; }
  if(buttonSenseInterval1 == 8){ button1On();  }
  if(buttonSenseInterval1 == 0){ button1Off(); }
  
 if(funcButtonValue[1] < 450 && funcButtonValue[0] > 450){ if(!updating) { buttonSenseInterval2++; }} else { buttonSenseInterval2 = 0; }
  if(buttonSenseInterval2 == 8){ button2On();  }
  if(buttonSenseInterval2 == 0){ button2Off(); }
 
 if(resetDefaultTime > 0){ statusTwoState = HIGH; } else { statusTwoState = LOW; }
 
 for(int i = 0; i < 6; i++){
  if(digitalInputState[i] == LOW){ inputSenseInterval[i]++; } else { inputSenseInterval[i] = 0; }
   if(inputSenseInterval[i] == 8){ inputOn(i);  }
   if(inputSenseInterval[i] == 0){ inputOff(i); }
 }
}

void DATA0(void){ rfid = rfid << 1; rfid |= 0; bitCnt++; lastBitTime = millis(); }
void DATA1(void){ rfid = rfid << 1; rfid |= 1; bitCnt++; lastBitTime = millis(); }

void inputOn(int in){
 doMaths(in);
 lastInput = in;
}

void inputOff(int in){
 if(lastInput == in){ lastDeInput = in; }
}

void button1On(){ saveTime(now()); saveTraffic(0, 0); }

void button1Off(){ }

void button2On(){
 if(gfxPowerState == LOW){
  reset_gfx();
  all_visuals(LOW);
  all_relays (LOW);
 } else { touchMode = HIGH; }
}

void button2Off(){
}

void instantOn(){
 for(int i = 0; i < 4; i++){
  char inst = save.readEEPROM(DISK0, 10104 + i); // is instant input selected on by lane
  if(inst){ // if so, inc the traffic total for that lane and initiate the interlock
   trafficLane[i]++;
   saveLaneTraffic(i, trafficLane[i]);
   selected(i);
  }
 }
}

void all_relays(int state){ for(int i = 0; i < 4; i++){ dryOutputState[i] = state; }}
void set_output(int pin){ pinMode(pin, OUTPUT); }
void set_input(int pin) { pinMode(pin, INPUT); digitalWrite(pin, LOW); }
