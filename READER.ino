
void READER_SERVICE(){
 if(bitCnt > 25){
  if(millis() > lastBitTime + period){
   rfidC = rfid;
   bitCntC = bitCnt;
   read_handler();
  }
 } else { if(millis() > lastBitTime + period){ bitCnt = 0; rfid = 0; }}
}
 
void read_handler(){
 
 inputOn(6); // virtual input
 
 boolean passThrough = true;
 for(int i = 0; i < 4; i++){ if(save.readEEPROM(DISK0, LANE_1_START_INPUT + i) == 7){ passThrough = false; }}
 if(passThrough){ dumpRfid(); }
 
 rfid = 0;
 bitCnt = 0;
}

void dumpRfid(){
 bitCntC--;
 do {
  digitalWrite(WD0_OUT, HIGH); digitalWrite(WD1_OUT, HIGH);
  if(bitRead(rfidC, bitCntC--) == 1){ digitalWrite(WD1_OUT, LOW); } else { digitalWrite(WD0_OUT, LOW); }
  delayMicroseconds(50);
  digitalWrite(WD0_OUT, HIGH); digitalWrite(WD1_OUT, HIGH);
  delayMicroseconds(250);
 } while(bitCntC >= 0);
 rfidC = 0;
}

void tokenize_card(int arg){
  
 int system;
 int credential;
  
 switch(arg){
  
  case 26:
  
   credential = 0;
   system = 0;
 
   for(int i = 24; i > 16; i--){ system = system << 1; system |= bitRead(rfid, i); }
   
   for(int i = 16; i > 0; i--){ credential = credential << 1; credential |= bitRead(rfid, i); }
   
   break;
   
  default: break;
 }
}
