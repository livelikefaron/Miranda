
void INIT_MEMORY(){
 
 // 3 x (256k bit EEPROM IC - 32000 byte sized storage locations each)
 
 pinMode(WP_PIN, OUTPUT);
 digitalWrite(WP_PIN, HIGH);
 
 pinMode(53, OUTPUT);
 
 lastEvent = 0;
 queueAddress = 0;
 for(int i = 0; i < 64; i++){ writeQueueAddress[i] = 0; writeQueueData[i] = 0; }
 
 for(int i = 0; i < 12; i++){ laneMeanValues[i] = 0; }
 
 unsigned char rData[4];
 
 rotateMemoryAddress(); // rotate memory addresses to save eeprom write wear
 
 for(int i = 0; i < 6; i++){ trafficLane[i] = 0; } // ram variable
 for(int i = 0; i < 6; i++){ stopsLane[i] = 0;   } // ram variable
 
 // check if time is defaulted
 for(int i = 0; i < 4; i++){ rData[i] = save.readEEPROM(DISK0, currentTimeAddress[i]); }
 
 if((rData[0] + rData[1] + rData[2] + rData[3]) == 1020){   // time is default
  if(currentTimeAddress[0] <  3){ saveTime(STARTUP_TIME); } // save start up time, initial
  if(currentTimeAddress[0] >= 3){                           // save time from last rotation
   unsigned char ti[4];
   unsigned long time = 0;
   unsigned int timeLow;
   unsigned int timeHigh;
   for(int i = 0; i < 4; i++){ ti[i] = save.readEEPROM(DISK0, currentTimeAddress[i] - 4); }
   timeLow  = ti[2] << 8 | ti[3];
   timeHigh = ti[0] << 8 | ti[1];
   time = time << 32 | timeHigh;
   time = time << 16 | timeLow;
   saveTime(time);
  }
 }
 
 // traffic stop percentage
 rData[0] = save.readEEPROM(DISK0, TRAFFIC_STOP_PERCENTAGE); // percentage
 delay(100);
 if(rData[0] == 0xFF){ // traffic stop percentage is default
  save.writeEEPROM(DISK0, TRAFFIC_STOP_PERCENTAGE, 10); // set default traffic stop percentage to 10
 }
 
 trafficStopPercentage = rData[0];
 
 // time window settings | no longer user defined
 rData[0] = save.readEEPROM(DISK0, TIME_WINDOW_SIZE); // time window size
 delay(100);
 if(rData[0] == 0xFF){ // time window location is default
  save.writeEEPROM(DISK0, TIME_WINDOW_SIZE, 60); // set default time window to 60 minutes
 }
  
 // current traffic saving offset - for saving 5 days of traffic history
 rData[0] = save.readEEPROM(DISK0, TRAFFIC_SAVE_OFFSET); // traffic save offset
 delay(100);
 if(rData[0] == 0xFF){ // traffic save offset location is default
  save.writeEEPROM(DISK0, TRAFFIC_SAVE_OFFSET, 0); // set default offset to 0
 }
 
 trafficSaveOffset = rData[0];
  
 // current stops saving offset - for saving 5 days of stops history
 rData[0] = save.readEEPROM(DISK0, STOPS_SAVE_OFFSET); // stops save offset
 delay(100);
 if(rData[0] == 0xFF){ // stops save offset location is default
  save.writeEEPROM(DISK0, STOPS_SAVE_OFFSET, 0); // set default offset to 0
 }
 
 stopsSaveOffset = rData[0];
 
 // check if current traffic and stops by lane is default, if so write 0
 for(int i = 0; i < 6; i++){
  if(save.readEEPROM(DISK0, trafficLaneMSB[i]) == 0xFF){ save.writeEEPROM(DISK0, trafficLaneMSB[i], 0x00); }
  if(save.readEEPROM(DISK0, trafficLaneLSB[i]) == 0xFF){ save.writeEEPROM(DISK0, trafficLaneLSB[i], 0x00); }
  if(save.readEEPROM(DISK0, stopsLaneMSB[i]) == 0xFF){ save.writeEEPROM(DISK0, stopsLaneMSB[i], 0x00); }
  if(save.readEEPROM(DISK0, stopsLaneLSB[i]) == 0xFF){ save.writeEEPROM(DISK0, stopsLaneLSB[i], 0x00); }
 }
 
 // check if current traffic address is saved
 rData[0] = save.readEEPROM(DISK0, currentTrafficAddress[0]);
 delay(100); 
 rData[1] = save.readEEPROM(DISK0, currentTrafficAddress[1]);
 delay(100);
 
 if((rData[0] + rData[1]) == 510){ // both locations default
  save.writeEEPROM(DISK0, currentTrafficAddress[0], 0x00);
  delay(100); 
  save.writeEEPROM(DISK0, currentTrafficAddress[1], 0x00);
  delay(100);
 }
 
 // check if current stops address is saved
 rData[0] = save.readEEPROM(DISK0, currentStopsAddress[0]);
 delay(100); 
 rData[1] = save.readEEPROM(DISK0, currentStopsAddress[1]);
 delay(100);
 
 if((rData[0] + rData[1]) == 510){ // both locations default
  save.writeEEPROM(DISK0, currentStopsAddress[0], 0x00);
  delay(100); 
  save.writeEEPROM(DISK0, currentStopsAddress[1], 0x00);
  delay(100);
 }
 
 // check if last event was saved
 rData[0] = save.readEEPROM(DISK0, LAST_EVENT_LSB);
 delay(100); 
 rData[1] = save.readEEPROM(DISK0, LAST_EVENT_MSB);
 delay(100); 
 
 if((rData[0] + rData[1]) == 510){ // both locations default
  save.writeEEPROM(DISK0, LAST_EVENT_LSB, 0x00);
  delay(100); 
  save.writeEEPROM(DISK0, LAST_EVENT_MSB, 0x00);
  delay(100); 
  rData[0] = save.readEEPROM(DISK0, LAST_EVENT_LSB);
  delay(100); 
  rData[1] = save.readEEPROM(DISK0, LAST_EVENT_MSB);
  delay(100); 
 }
  
 lastEvent = rData[1] << 8 | rData[0];
 if(lastEvent >= 8000){ lastEvent = 0; }
 
 int windowSize    = save.readEEPROM(DISK0, 0x0014);
 int highestWindow = round((hour() * 60) / windowSize);
 
 rData[0] = save.readEEPROM(DISK0, (PREVIOUS_TRAFFIC_START + highestWindow));
 delay(100); 
 rData[1] = save.readEEPROM(DISK0, (PREVIOUS_TRAFFIC_START + highestWindow + 1));
 delay(100);
 
 if((rData[0] + rData[1]) == 510){ // both locations default
  save.writeEEPROM(DISK0, (PREVIOUS_TRAFFIC_START + highestWindow), 0x00);
  delay(100); 
  save.writeEEPROM(DISK0, (PREVIOUS_TRAFFIC_START + highestWindow + 1), 0x00);
  delay(100); 
  rData[0] = save.readEEPROM(DISK0, (PREVIOUS_TRAFFIC_START + highestWindow));
  delay(100); 
  rData[1] = save.readEEPROM(DISK0, (PREVIOUS_TRAFFIC_START + highestWindow + 1));
  delay(100); 
 }
  
 // check for factory default load request
 if(save.readEEPROM(DISK0, FACTORY_DEFAULT_LOAD) == 0xFF){ loadFactoryDefaultSettings(); }
 
 readCurrentTraffic();
 readCurrentStops();
 
 // check if network information has been written
 if(save.readEEPROM(DISK0, IP_TYPE) == 0xFF){ save.writeEEPROM(DISK0, IP_TYPE, 0); } // static ip address by default
 
 for(int i = 0; i < 4; i++){ rData[i] = save.readEEPROM(DISK0, IP_1 + i); } // check ip

 if((rData[0] + rData[1] + rData[2] + rData[3]) == 1020){   // ip is unwritten
  for(int i = 0; i < 4; i++){ save.writeEEPROM(DISK0, (IP_1 + i), ipDefault[i]); }
 }
 
 for(int i = 0; i < 4; i++){ rData[i] = save.readEEPROM(DISK0, GW_1 + i); } // check gateway

 if((rData[0] + rData[1] + rData[2] + rData[3]) == 1020){   // gateway is unwritten
  for(int i = 0; i < 4; i++){ save.writeEEPROM(DISK0, (GW_1 + i), gwDefault[i]); }
 }
 
 for(int i = 0; i < 4; i++){ rData[i] = save.readEEPROM(DISK0, MAC_1 + i); } // check mac

 if((rData[0] + rData[1] + rData[2] + rData[3]) == 1020){   // mac is unwritten
  for(int i = 0; i < 6; i++){ save.writeEEPROM(DISK0, (MAC_1 + i), mac[i]); }
 }
}

void MEMORY_SERVICE(){ 
 rotateMemoryAddress();
 
 if(writeQueueAddress[queueAddress] > 0){
  save.writeEEPROM(DISK0, writeQueueAddress[queueAddress], writeQueueData[queueAddress]);
  writeQueueAddress[queueAddress] = 0;
  writeQueueData[queueAddress] = 0;
 }
 
 if(queueAddress < 63){ queueAddress++; } else { queueAddress = 0; }
}

void rotateMemoryAddress(){
 // rotate current positions of traffic and stops per lane
 int j;
 
 j = 8301;
 if(year() <  2016){ } // do nothing
 if(year() >= 2016){ j += (24*1); }
 if(year() >= 2020){ j += (24*2); }
 if(year() >= 2024){ j += (24*3); }
 for(int i = 0; i < 6; i++){ trafficLaneLSB[i] = j; trafficLaneMSB[i] = j + 1; j += 2; }
 
 j = 8325;
 if(year() <  2016){ } // do nothing
 if(year() >= 2016){ j += (24*1); }
 if(year() >= 2020){ j += (24*2); }
 if(year() >= 2024){ j += (24*3); }
 for(int i = 0; i < 6; i++){ stopsLaneLSB[i] = j; stopsLaneMSB[i] = j + 1; j += 2; }
 
 // rotate time saving addresses (save EEPROM wear)
 if(year() <  2016){ for(int i = 0;  i < 4;  i++){ currentTimeAddress[i] = i; }}
 if(year() >= 2016){ for(int i = 4;  i < 8;  i++){ currentTimeAddress[i] = i; }}
 if(year() >= 2020){ for(int i = 8;  i < 12; i++){ currentTimeAddress[i] = i; }}
 if(year() >= 2024){ for(int i = 12; i < 16; i++){ currentTimeAddress[i] = i; }}

 // rotate saving locations for current traffic & stops (save wear on EEPROM)
 currentTrafficAddress[0] = 4111;
 currentTrafficAddress[1] = 4112;
 currentStopsAddress[0]   = 4172;
 currentStopsAddress[1]   = 4173;
 if(year() >= 2015){
  currentTrafficAddress[0] += 2; currentTrafficAddress[1] += 2;
  currentStopsAddress[0]   += 2; currentStopsAddress[1]   += 2;
 }
 if(year() >= 2017){
  currentTrafficAddress[0] += 4; currentTrafficAddress[1] += 4;
  currentStopsAddress[0]   += 4; currentStopsAddress[1]   += 4;
 }
 if(year() >= 2019){
  currentTrafficAddress[0] += 6; currentTrafficAddress[1] += 6;
  currentStopsAddress[0]   += 6; currentStopsAddress[1]   += 6;
 }
 if(year() >= 2021){
  currentTrafficAddress[0] += 8; currentTrafficAddress[1] += 8;
  currentStopsAddress[0]   += 8; currentStopsAddress[1]   += 8;
 }
}

void saveCurrentTraffic(unsigned int incTraffic){
 unsigned char dat[2];
 char search = 0;
 for(int i = 0; i < 4; i++){
  if(incTraffic == 0){
   dat[1] = 0; dat[0] = 0;
  } else {
   dat[1] = trafficLane[i] >> 8; dat[0] = trafficLane[i];
  }
  do {
   if(writeQueueAddress[search] == 0){
    writeQueueAddress[search] = trafficLaneMSB[i];
    writeQueueData[search] = dat[1];
    break;
   }
  } while(search++ < 63);
  search = 0;
  do {
   if(writeQueueAddress[search] == 0){
    writeQueueAddress[search] = trafficLaneLSB[i];
    writeQueueData[search] = dat[1];
    break;
   }
  } while(search++ < 63);
 }
}

void readCurrentTraffic(){
 unsigned char dat[2];
 traffic = 0;
 for(int i = 0; i < 4; i++){
  dat[1] = save.readEEPROM(DISK0, trafficLaneMSB[i]);
  dat[0] = save.readEEPROM(DISK0, trafficLaneLSB[i]);
  trafficLane[i] = dat[1] << 8 | dat[0];
  traffic += trafficLane[i];
 }
}

void saveLaneTraffic(int lane, int traf){
 char search = 0;
  do {
   if(writeQueueAddress[search] == 0){
    writeQueueAddress[search] = trafficLaneMSB[lane];
    writeQueueData[search] = traf >> 8;;
    break;
   }
  } while(search++ < 63);
  search = 0;
  do {
   if(writeQueueAddress[search] == 0){
    writeQueueAddress[search] = trafficLaneLSB[lane];
    writeQueueData[search] = traf;
    break;
   }
  } while(search++ < 63);
}

void saveLaneStops(int lane, int sto){
 char search = 0;
  do {
   if(writeQueueAddress[search] == 0){
    writeQueueAddress[search] = stopsLaneMSB[lane];
    writeQueueData[search] = sto >> 8;
    break;
   }
  } while(search++ < 63);
  search = 0;
  do {
   if(writeQueueAddress[search] == 0){
    writeQueueAddress[search] = stopsLaneLSB[lane];
    writeQueueData[search] = sto;
    break;
   }
  } while(search++ < 63);
}

void saveCurrentStops(unsigned int incStops){
 unsigned char dat[2];
 char search = 0;
 for(int i = 0; i < 4; i++){
  if(incStops == 0){
   dat[1] = 0; dat[0] = 0;
  } else {
   dat[1] = stopsLane[i] >> 8; dat[0] = stopsLane[i];
  }
  do {
   if(writeQueueAddress[search] == 0){
    writeQueueAddress[search] = stopsLaneMSB[i];
    writeQueueData[search] = dat[1];
    break;
   }
  } while(search++ < 63);
  search = 0;
  do {
   if(writeQueueAddress[search] == 0){
    writeQueueAddress[search] = stopsLaneLSB[i];
    writeQueueData[search] = dat[1];
    break;
   }
  } while(search++ < 63);
 }
}

void readCurrentStops(){
 unsigned char dat[2];
 stops = 0;
 for(int i = 0; i < 4; i++){
  dat[1] = save.readEEPROM(DISK0, stopsLaneMSB[i]);
  dat[0] = save.readEEPROM(DISK0, stopsLaneLSB[i]);
  stopsLane[i] = dat[1] << 8 | dat[0];
  stops += stopsLane[i];
 }
}

void saveTraffic(int negativeOffset, int cl){
 unsigned char dat[2];
 char address = 0;
 char data = 0;
 for(int i = 0; i < 4; i++){
  writeQueueAddress[address++] = ((8400 + ((hour() - negativeOffset) * 12)) + (i * 2)) + 1;
  writeQueueData[data++] = save.readEEPROM(DISK0, trafficLaneMSB[i]); //writeQueueData[data++] = trafficLane[i] >> 8;
  writeQueueAddress[address++] = ((8400 + ((hour() - negativeOffset) * 12)) + (i * 2));
  writeQueueData[data++] = save.readEEPROM(DISK0, trafficLaneLSB[i]); //writeQueueData[data++] = trafficLane[i];
  writeQueueAddress[address++] = ((8700 + ((hour() - negativeOffset) * 12)) + (i * 2)) + 1;
  writeQueueData[data++] = save.readEEPROM(DISK0, stopsLaneMSB[i]); //writeQueueData[data++] = stopsLane[i] >> 8;
  writeQueueAddress[address++] = ((8700 + ((hour() - negativeOffset) * 12)) + (i * 2));
  writeQueueData[data++] = save.readEEPROM(DISK0, stopsLaneLSB[i]); //writeQueueData[data++] = stopsLane[i];
  
  if(cl == 1){ // clear?
   trafficLane[i] = 0; stopsLane[i] = 0;
   // set current values to 0
   writeQueueAddress[address++] = trafficLaneMSB[i];
   writeQueueData[data++] = 0;
   writeQueueAddress[address++] = trafficLaneLSB[i];
   writeQueueData[data++] = 0;
   writeQueueAddress[address++] = stopsLaneMSB[i];
   writeQueueData[data++] = 0;
   writeQueueAddress[address++] = stopsLaneLSB[i];
   writeQueueData[data++] = 0;
  }
 }
}

void saveTime(long time){
 unsigned char tim[4];
 tim[0] = ((time & 0xFF000000)>>24);
 tim[1] = ((time & 0x00FF0000)>>16);
 tim[2] = ((time & 0x0000FF00)>>8);
 tim[3] = (time & 0x000000FF);
 for(int i = 0; i < 4; i++){ save.writeEEPROM(DISK0, currentTimeAddress[i], tim[i]); }
 heartbeats = (minute(time) * 60) + second(time);
}

void clearMem(){
 int barWidth = 300;
 int barSlots = 0;
 int locations = 32000;
 int individual = 0;
 int barYsta = 120;
 int barYsto = 140;
 clr(); basicLayout();
 rect(3, 101,   400, 267, 0x001F, 1);
 rect(5,   5,   470,  55, 0x0000, 1); delay(10); // aa&cg header, device name, and time block
 rect(8,   8,   468,  53, 0xFFFF, 0); delay(10);
 txtFG(0x07E0); txtBG(0x0000); txtW(2); txtH(2); moveTO(10,dateY);
 txtPS(randStr[34]);
 txtFG(0x07E0); txtBG(0x001F);
 txtFont(3); txtW(1); txtH(1);
 for(int i = 0; i < 3; i++){
  rect(10, barYsta, 10+barWidth, barYsto, 0x0000, 1);
  rect(10, barYsta, 10+barWidth, barYsto, 0xFFFF, 0);
  moveTO(10+barWidth+20+40, barYsta + 5);
  txtPS(randStr[35]); txtPS(clrStr);
  itoa(i+1, holder, 10);
  txtPS(holder);
  barYsta += 40;
  barYsto += 40;
 }
 barYsta = 120;
 barYsto = 140;
 for(int d = DISK0; d < DISK0 + 3; d++){
  for(int i = 0; i < 32000; i++){
   if(save.readEEPROM(d, i) != 255){ save.writeEEPROM(d, i, 0xFF); }
   if(individual == (locations/100)){
    rect(11 + barSlots, barYsta + 1, (11 + barSlots) + (barWidth/100), barYsto - 1, 0x07E0, 1);
    barSlots += barWidth/100;
   }
   if(individual < (locations/100)){ individual++; } else { individual = 0; }
  }
  barSlots = 0;
  barYsta += 40;
  barYsto += 40;
 }
 txtFG(0x07E0); txtBG(0x0000); txtW(2); txtH(2); moveTO(10,dateY);
 txtPS(randStr[36]);
 loadFactoryDefaultSettings();
  moveTO(10,dateY); txtPS(randStr[37]);
 do {} while(1);
}

void loadFactoryDefaultSettings(){
 int j;
 for(int i = 8400; i < 8689; i++){ save.writeEEPROM(DISK0, i, 0); }
 for(int i = 8700; i < 8989; i++){ save.writeEEPROM(DISK0, i, 0); }
 for(int i = 9000; i < 9006; i++){ save.writeEEPROM(DISK0, i, 10); }
 j = 1; for(int i = 8272; i < 8272 + 4; i++){ save.writeEEPROM(DISK0, i, j++); }   // lane start inputs
 j = 1; for(int i = 8276; i < 8276 + 4; i++){ save.writeEEPROM(DISK0, i, 6); }     // lane reset inputs
 j = 1; for(int i = 8280; i < 8280 + 4; i++){ save.writeEEPROM(DISK0, i, j++); }   // lane interlocks
 save.writeEEPROM(DISK0, 8290, 0x0F);                                              // relay logic
 j = 1; for(int i = 8291; i < 8291 + 4; i++){ save.writeEEPROM(DISK0, i, j++); }   // relay interlocks
 j = 0; for(int i = 8284; i < 8284 + 4; i++){ save.writeEEPROM(DISK0, i, j++); }   // interlock mode
 j = 1; for(int i = 8266; i < 8266 + 4; i++){ save.writeEEPROM(DISK0, i, 10); }    // interlock pulse
 j = 1; for(int i = 8295; i < 8295 + 4; i++){ save.writeEEPROM(DISK0, i, j); j = j * 2; } // interlock relay assoc
 for(int i = laneStopByHourStartAddress[0]; i <= laneStopByHourStartAddress[3] + 24; i++){ save.writeEEPROM(DISK0, i, DEFAULT_PERCENTAGE); } // traffic stop % by lane
 for(int i = 10100; i < 10104; i++){ save.writeEEPROM(DISK0, i, 60); } // relay pulse times
 for(int i = 10104; i < 10108; i++){ save.writeEEPROM(DISK0, i, 0); } // lane instant triggers
 save.writeEEPROM(DISK0, FACTORY_DEFAULT_LOAD, 0x00);
}
