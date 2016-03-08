/* [START BYTE] [COMMAND] [PARAMS] [END BYTE] */
/* */

void INIT_COMM(){
  
 Serial.begin(9600);
 SlaveSerial.begin(RATE);
 DisplaySerial.begin(115200);
 
 slaveBufferSize = 0;
 
 startByte = 0x0B;
 endByte = 0xFF;
 statusByte = 0x01;
 streamOn  = 0;
 statusWaiting = 0x00;
 slaveOnline = 0;
 
 statusTime = millis();
 statusInterval = 1000;
}


void COMM_SERVICE(){
  
 if(slaveOnline == 1){ greenOneState = HIGH; } else { greenOneState = LOW; }
  
 if(millis() > statusTime + statusInterval){
  sendStatus();
  statusTime = millis();
  if(statusWaiting > 1){ slaveOnline = 0; }
 }
 
 if(SlaveSerial.available() > 0){ 
   
  while(SlaveSerial.available() > 0){
   slaveBuffer[slaveBufferSize++] = SlaveSerial.read();
   digitalWrite(STATUS1, HIGH);
  } 
  
 } else {
   
  if(slaveBufferSize > 0){
   parseSlaveMessage();
   slaveBufferSize = 0;
  }
  
  statusOneState = LOW;
 }
}


void sendStatus(){
 digitalWrite(STATUS0, HIGH);
 SlaveSerial.write(startByte);
 SlaveSerial.write(statusByte);
 SlaveSerial.write(endByte);
 statusWaiting++;
 digitalWrite(STATUS0, LOW);
}

void parseSlaveMessage(){
 
 for(int i = 0; i < slaveBufferSize; i++){
  if(slaveBuffer[i] == startByte){ streamOn = 1; }
  if(streamOn == 1){
   if(slaveBuffer[i] == endByte){ streamOn = 0; } else {
    if(slaveBuffer[i] == statusByte){ statusReturn(); }
  }}
 }
 slaveBufferSize = 0;
}

void sendTimeSync(long time){
 unsigned char tim[4];
 digitalWrite(STATUS0, HIGH);
 SlaveSerial.write(startByte);
 SlaveSerial.write(TIME_SYNC);
 tim[0] = ((time & 0xFF000000)>>24);
 tim[1] = ((time & 0x00FF0000)>>16);
 tim[2] = ((time & 0x0000FF00)>>8);
 tim[3] = (time & 0x000000FF);
 for(int i = 0; i < 4; i++){ SlaveSerial.write(tim[i]); }
 SlaveSerial.write(endByte);
 digitalWrite(STATUS0, LOW);
}

void statusReturn(){
 if(statusWaiting > 0){
  slaveOnline = 1;
  statusWaiting = 0;
 }
 if(slaveOnline == 1){ sendTimeSync(now()); }
}
