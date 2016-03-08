void buildConfig(byte page){
  
 rect(3, 101,   400, 267, 0x001F, 1);
 rect(5,   5,   470,  55, 0x0000, 1); delay(10); // aa&cg header, device name, and time block
 rect(8,   8,   468,  53, 0xFFFF, 0); delay(10);
 txtFG(0x07E0); txtBG(0x0000); txtW(2); txtH(2); moveTO(10,dateY);
 txtPS(configHeaders[page]); txtPS(" Config");
 
 switch(page){
   
 case 0: // config time
  
  // config background
  rect(seg1a[0]-10, seg1a[1]-5, seg5a[2]+35, seg5b[3]+25, 0x18CE, 1);
  rect(seg1a[0]-10, seg1a[1]-5, seg5a[2]+35, seg5b[3]+25, 0xFFFF, 0);
  
  // fields input box
  rect(
   seg1a[0]-7,
   (seg1a[1]+(seg1a[3]-seg1a[1])+7),
   seg5a[2]+30,
   (seg5a[3]+(seg5a[3]-seg5a[1])+12), 0xFFFF, 1);
  rect(
   seg1a[0]-8,
   (seg1a[1]+(seg1a[3]-seg1a[1])+6),
   seg5a[2]+31,
   (seg5a[3]+(seg5a[3]-seg5a[1])+13), 0x0000, 0);
  
  dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
  dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
  
  dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
  dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
  
  dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
  dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
  
  dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
  dirButton(seg4b[0], seg4b[1], seg4b[2], seg4b[3], 0, 0);
  
  dirButton(seg5a[0], seg5a[1], seg5a[2], seg5a[3], 1, 0);
  dirButton(seg5b[0], seg5b[1], seg5b[2], seg5b[3], 0, 0);
  
  formFields(page);
  configLabels(page);
  break;
  
 case 1: // stop percentage by lane
 
  currentOption = 24;
  
  // config background
  rect(seg1a[0]-10, seg1a[1]-5, seg5a[2]+35, seg1b[3]+65, 0x18CE, 1);
  rect(seg1a[0]-10, seg1a[1]-5, seg5a[2]+35, seg1b[3]+65, 0xFFFF, 0);
  
  // fields input box
  rect(
   seg1a[0]-7,
   (seg1a[1]+(seg1a[3]-seg1a[1])+7),
   seg5a[2]+60,
   (seg5a[3]+(seg5a[3]-seg5a[1])+12), 0xFFFF, 1);
  rect(
   seg1a[0]-8,
   (seg1a[1]+(seg1a[3]-seg1a[1])+6),
   seg5a[2]+61,
   (seg5a[3]+(seg5a[3]-seg5a[1])+13), 0x0000, 0);
 
  dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
  dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
  
  dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
  dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
  
  dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
  dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
  
  dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
  dirButton(seg4b[0], seg4b[1], seg4b[2], seg4b[3], 0, 0);
  
  dirButton(seg5a[0], seg5a[1], seg5a[2], seg5a[3], 1, 0);
  dirButton(seg5b[0], seg5b[1], seg5b[2], seg5b[3], 0, 0);
  
  formFields(page);
  configLabels(page);
  break;
  
 case 2:
  
  // config background
  rect(seg1a[0]-10, seg1a[1]-5, seg5a[2]+35, seg1b[3]+65, 0x18CE, 1);
  rect(seg1a[0]-10, seg1a[1]-5, seg5a[2]+35, seg1b[3]+65, 0xFFFF, 0);
  
  // fields input box
  rect(
   seg1a[0]-7,
   (seg1a[1]+(seg1a[3]-seg1a[1])+7),
   seg5a[2]+60,
   (seg5a[3]+(seg5a[3]-seg5a[1])+12), 0xFFFF, 1);
  rect(
   seg1a[0]-8,
   (seg1a[1]+(seg1a[3]-seg1a[1])+6),
   seg5a[2]+61,
   (seg5a[3]+(seg5a[3]-seg5a[1])+13), 0x0000, 0);
 
  dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
  dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
  
  dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
  dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
  
  dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
  dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
  
  dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
  dirButton(seg4b[0], seg4b[1], seg4b[2], seg4b[3], 0, 0);
  
  dirButton(seg5a[0], seg5a[1], seg5a[2], seg5a[3], 1, 0);
  dirButton(seg5b[0], seg5b[1], seg5b[2], seg5b[3], 0, 0);
  
  formFields(page);
  configLabels(page);
  break;
  
 case 3: // config relays
  
  // config background
  rect(seg1a[0]-10, seg1a[1]-5, seg5a[2]+35, seg1b[3]+65, 0x18CE, 1);
  rect(seg1a[0]-10, seg1a[1]-5, seg5a[2]+35, seg1b[3]+65, 0xFFFF, 0);
  
  // fields input box
  rect(
   seg1a[0]-7,
   (seg1a[1]+(seg1a[3]-seg1a[1])+7),
   seg5a[2]+60,
   (seg5a[3]+(seg5a[3]-seg5a[1])+12), 0xFFFF, 1);
  rect(
   seg1a[0]-8,
   (seg1a[1]+(seg1a[3]-seg1a[1])+6),
   seg5a[2]+61,
   (seg5a[3]+(seg5a[3]-seg5a[1])+13), 0x0000, 0);
 
  dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
  dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
  
  dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
  dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
  
  dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
  dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
  
  dirButton(seg4a[0], seg4a[1], seg4a[2], seg4a[3], 1, 0);
  dirButton(seg4b[0], seg4b[1], seg4b[2], seg4b[3], 0, 0);
  
  formFields(page);
  configLabels(page);
  break;
  
 case 4: // config inputs
  
  formFields(page);
  configLabels(page);
  break;
  
 case 5: // config interlocks
  
  // config background
  rect(seg1a[0]-10, seg1a[1]-5, seg5a[2]+35, seg1b[3]+65, 0x18CE, 1);
  rect(seg1a[0]-10, seg1a[1]-5, seg5a[2]+35, seg1b[3]+65, 0xFFFF, 0);
  
  // fields input box
  rect(
   seg1a[0]-7,
   (seg1a[1]+(seg1a[3]-seg1a[1])+7),
   seg3a[2]+6,
   (seg3a[3]+(seg3a[3]-seg3a[1])+12), 0xFFFF, 1);
  rect(
   seg1a[0]-8,
   (seg1a[1]+(seg1a[3]-seg1a[1])+6),
   seg3a[2]+7,
   (seg3a[3]+(seg3a[3]-seg3a[1])+13), 0x0000, 0);
  
  dirButton(seg1a[0], seg1a[1], seg1a[2], seg1a[3], 1, 0);
  dirButton(seg1b[0], seg1b[1], seg1b[2], seg1b[3], 0, 0);
  
  dirButton(seg2a[0], seg2a[1], seg2a[2], seg2a[3], 1, 0);
  dirButton(seg2b[0], seg2b[1], seg2b[2], seg2b[3], 0, 0);
  
  dirButton(seg3a[0], seg3a[1], seg3a[2], seg3a[3], 1, 0);
  dirButton(seg3b[0], seg3b[1], seg3b[2], seg3b[3], 0, 0);
  
  formFields(page);
  configLabels(page);
  break;
 }
}

void line(int x1, int y1, int x2, int y2, int c1){
 digitalWrite(STATUS0, HIGH);
 int command = 0xFFC8;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(x1 >> 8));
 DisplaySerial.print((char)(x1));
 DisplaySerial.print((char)(y1 >> 8));
 DisplaySerial.print((char)(y1));
 DisplaySerial.print((char)(x2 >> 8));
 DisplaySerial.print((char)(x2));
 DisplaySerial.print((char)(y2 >> 8));
 DisplaySerial.print((char)(y2));
 DisplaySerial.print((char)(c1 >> 8));
 DisplaySerial.print((char)(c1));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void txtH(int multi){
 digitalWrite(STATUS0, HIGH);
 int command = 0xFFE3;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(multi >> 8));
 DisplaySerial.print((char)(multi));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void txtW(int multi){
 digitalWrite(STATUS0, HIGH);
 int command = 0xFFE4;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(multi >> 8));
 DisplaySerial.print((char)(multi));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void txtBG(int color){
 digitalWrite(STATUS0, HIGH);
 int command = 0xFFE6;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(color >> 8));
 DisplaySerial.print((char)(color));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void txtFG(int color){
 digitalWrite(STATUS0, HIGH);
 int command = 0xFFE7;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(color >> 8));
 DisplaySerial.print((char)(color));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void txtXG(int gap){
 digitalWrite(STATUS0, HIGH);
 int command = 0xFFE2;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(gap >> 8));
 DisplaySerial.print((char)(gap));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void txtFont(int id){
 digitalWrite(STATUS0, HIGH);
 int command = 0xFFE5;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(id >> 8));
 DisplaySerial.print((char)(id));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void txtPS(char str[]){
 digitalWrite(STATUS0, HIGH);
 int command = 0x0018;
 int i = 0;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 do {
  if(str[i] != 0x00){ DisplaySerial.print(str[i++]); } else {
  DisplaySerial.print((char)0x00); // null string pointer
  break;
  }
 } while(i < 50); if(i >= 49){ DisplaySerial.print((char)0x00); } // null string pointer 
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void moveTO(int x1, int y1){
 digitalWrite(STATUS0, HIGH);
 int command = 0xFFCC;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(x1 >> 8));
 DisplaySerial.print((char)(x1));
 DisplaySerial.print((char)(y1 >> 8));
 DisplaySerial.print((char)(y1));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void rect(int x1, int y1, int x2, int y2, int c1, boolean fill){
 digitalWrite(STATUS0, HIGH);
 int command; if(fill){ command = 0xFFC4; } else { command = 0xFFC5; }
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(x1 >> 8));
 DisplaySerial.print((char)(x1));
 DisplaySerial.print((char)(y1 >> 8));
 DisplaySerial.print((char)(y1));
 DisplaySerial.print((char)(x2 >> 8));
 DisplaySerial.print((char)(x2));
 DisplaySerial.print((char)(y2 >> 8));
 DisplaySerial.print((char)(y2));
 DisplaySerial.print((char)(c1 >> 8));
 DisplaySerial.print((char)(c1));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void circ(int x1, int y1, int r1, int c1, boolean fill){
 digitalWrite(STATUS0, HIGH);
 int command; if(fill){ command = 0xFFC2; } else { command = 0xFFC3; }
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(x1 >> 8));
 DisplaySerial.print((char)(x1));
 DisplaySerial.print((char)(y1 >> 8));
 DisplaySerial.print((char)(y1));
 DisplaySerial.print((char)(r1 >> 8));
 DisplaySerial.print((char)(r1));
 DisplaySerial.print((char)(c1 >> 8));
 DisplaySerial.print((char)(c1));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void tria(int x1, int y1, int x2, int y2, int x3, int y3, int c1, boolean fill){
 digitalWrite(STATUS0, HIGH);
 int command; if(fill){ command = 0xFFA9; } else { command = 0xFFBF; }
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(x1 >> 8));
 DisplaySerial.print((char)(x1));
 DisplaySerial.print((char)(y1 >> 8));
 DisplaySerial.print((char)(y1));
 DisplaySerial.print((char)(x2 >> 8));
 DisplaySerial.print((char)(x2));
 DisplaySerial.print((char)(y2 >> 8));
 DisplaySerial.print((char)(y2));
 DisplaySerial.print((char)(x3 >> 8));
 DisplaySerial.print((char)(x3));
 DisplaySerial.print((char)(y3 >> 8));
 DisplaySerial.print((char)(y3));
 DisplaySerial.print((char)(c1 >> 8));
 DisplaySerial.print((char)(c1));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

boolean setTouch(int mode){
 digitalWrite(STATUS0, HIGH);
 boolean r = false;
 int command = 0xFF38;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 DisplaySerial.print((char)(mode >> 8));
 DisplaySerial.print((char)(mode));
 s = 0;
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); tGet[s++] = DisplaySerial.read(); }
 if(tGet[0] == 0x06){ r = true; }
 for(int i = 0; i < 25; i++){ tGet[i] = 0; }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
 return r;
}

boolean setTouchRegion(){
 digitalWrite(STATUS0, HIGH);
 boolean r = false;
 int box[] = { 0, 100, 475, 260 };
 int command = 0xFF39;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 for(int i = 0; i < 4; i++){
  DisplaySerial.print((char)(box[i] >> 8));
  DisplaySerial.print((char)(box[i]));
 }
 s = 0;
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); tGet[s++] = DisplaySerial.read(); }
 if(tGet[0] == 0x06){ r = true; }
 for(int i = 0; i < 25; i++){ tGet[i] = 0; }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
 return r;
}

boolean clr(){
 digitalWrite(STATUS0, HIGH);
 int command = 0xFFCD;
 DisplaySerial.flush();
 DisplaySerial.print((char)(command >> 8));
 DisplaySerial.print((char)(command));
 while(DisplaySerial.available()){ digitalWrite(STATUS1, HIGH); DisplaySerial.read(); }
 digitalWrite(STATUS0, LOW);
 digitalWrite(STATUS1, LOW);
}

void dirButton(int x1, int y1, int x2, int y2, byte dir, int state){
 int bg;
 int tr[6];
 int xc = (((x2 - x1) / 2) + x1);  // x center
 int yc = (((y2 - y1) / 2) + y1);  // y center
 int th = ((y2 - y1) - 10);        // triangle height
 int tw = ((x2 - x1) - 10);        // triangle width
 
 if(dir){          // 1 = up
  tr[0] = xc;              // x1
  tr[1] = yc - (th/2);     // y1
  tr[2] = xc - (tw/2);     // x2
  tr[3] = yc + (th/2);     // y2
  tr[4] = xc + (tw/2);     // x3
  tr[5] = yc + (th/2);      // y3
 } else {          // 0 = down
  tr[0] = xc;              // x1
  tr[1] = yc + (th/2);     // y1
  tr[2] = xc - (tw/2);     // x2
  tr[3] = yc - (th/2);     // y2
  tr[4] = xc + (tw/2);     // x3
  tr[5] = yc - (th/2);      // y3
 }
 if(state){ bg = 0xFFFF; } else { bg = 0x8410; }
 rect(x1-2, y1-2, x2+2, y2+2, 0x0000, 1);
 rect(x1, y1, x2, y2, bg, 1);
 
 tria(tr[0], tr[1], tr[2], tr[3], tr[4], tr[5], 0x0000, 1);
}

void tabButtons(byte page){
 dirButton(segOpta[0], segOpta[1], segOpta[2], segOpta[3], 1, 0);
 dirButton(segOptb[0], segOptb[1], segOptb[2], segOptb[3], 0, 0);
}

void basicLayout(){
 rect(0, 0, 100, 20, 0x0000, 1);
 txtW(1); txtH(1);
 rect(0,   0,   475, 90,  0x001F, 1); delay(10); // header background
 rect(2,   2,   473, 88,  0x0000, 0); delay(10);
 rect(5,   5,   470, 55,  0x0000, 1); delay(10); // aa&cg header, device name, and time block
 rect(8,   8,   468, 53,  0xFFFF, 0); delay(10);
 rect(0,   92,  475, 95,  0xFFFF, 1); delay(10); // divider stripe
 rect(0,   98,  475, 270, 0x001F, 1); delay(10); // configuration / graph pane
 rect(2,   100, 473, 268, 0x0000, 0); delay(10);
}

void doneButton(int state){
 int bg;
 if(state){ bg = 0xFFFF; } else { bg = 0x8410; }
 rect(401, 103, 470, 147, 0x0000, 1);
 rect(403, 105, 468, 145, bg, 1);
 txtFG(0x0000); txtBG(bg); txtW(2); txtH(2); moveTO(407,129);
 txtPS(randStr[33]);
}

void menuButton(int state){
 int bg;
 if(state){ bg = 0xFFFF; } else { bg = 0x8410; }
 rect(menuBut[0], menuBut[1], menuBut[2], menuBut[3], bg, 1);
 rect(menuBut[0]+2, menuBut[1]+2, menuBut[2]-2, menuBut[3]-2, 0x0000, 0);
 txtFG(0x0000); txtBG(bg); txtW(1); txtH(1); txtFont(1); moveTO(menuBut[0]+5,menuBut[1]+5);
 txtPS(randStr[39]);
}

void greenLight(int lane, int func){
  switch(func){
   case 1:
     circ(greenLightStartX + (lane * laneWidth), greenLightStartY, lightRadius, GREEN_LIGHT_ON, 1);
     circ(greenLightStartX + (lane * laneWidth), greenLightStartY, lightRadius, GREEN_LIGHT_BRDR, 0);
     break;
   case 0:
     circ(greenLightStartX + (lane * laneWidth), greenLightStartY, lightRadius, GREEN_LIGHT_OFF, 1);
     circ(greenLightStartX + (lane * laneWidth), greenLightStartY, lightRadius, GREEN_LIGHT_BRDR, 0);
     break;
   default: break;
  }
}

void redLight(int lane, int func){
  switch(func){
   case 1:
       circ(redLightStartX + (lane * laneWidth), redLightStartY, lightRadius, RED_LIGHT_ON, 1);
       circ(redLightStartX + (lane * laneWidth), redLightStartY, lightRadius, RED_LIGHT_BRDR, 0);
     break;
   case 0:
       circ(redLightStartX + (lane * laneWidth), redLightStartY, lightRadius, RED_LIGHT_OFF, 1);
       circ(redLightStartX + (lane * laneWidth), redLightStartY, lightRadius, RED_LIGHT_BRDR, 0);
     break;
   default: break;
  }
}
