

void INIT_VISUALS(){
  
 pinMode(GREEN_0, OUTPUT);
 pinMode(GREEN_1, OUTPUT);
 pinMode(STATUS0, OUTPUT);
 pinMode(STATUS1, OUTPUT);
 pinMode(STATUS2, OUTPUT);
 
 pinMode(GFX_RESET_PIN, OUTPUT);
 gfxResetInterval = 100;
}


void VISUALS_SERVICE(){
 digitalWrite(GREEN_0, greenZerState);
 digitalWrite(GREEN_1, greenOneState);
 digitalWrite(STATUS0, statusZerState);
 digitalWrite(STATUS1, statusOneState);
 digitalWrite(STATUS2, statusTwoState);
}

void all_visuals(int state){
 greenZerState  = state;
 greenOneState  = state;
 statusZerState = state;
 statusOneState = state;
 statusTwoState = state;
}
