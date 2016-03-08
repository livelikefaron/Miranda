//#include <avr/pgmspace.h>
//#include <SD.h>
#include <Time.h>
#include <Wire.h>
#include <AthenaSave.h>

#define STARTUP_TIME 1262347200  //noon Jan 1 2010

#define DEFAULT_PERCENTAGE 20

#define DisplaySerial Serial3
#define SlaveSerial Serial2
#define RATE 9600

// logical definitions

//#define LOW  0
#define OFF  0
//#define HIGH 1
#define ON   1

// EEPROM addresses
#define DISK0 0x50
#define DISK1 0x51
#define DISK2 0x52

// memory addresses (EEPROM)
#define LAST_EVENT_LSB              0x1008
#define LAST_EVENT_MSB              0x1009
#define CURRENT_TRAFFIC_ADDRESS_LSB 0x100F
#define CURRENT_TRAFFIC_ADDRESS_MSB 0x1010
#define CURRENT_STOPS_ADDRESS_LSB   4142
#define CURRENT_STOPS_ADDRESS_MSB   4172
#define TRAFFIC_STOP_PERCENTAGE     0x0015
#define TIME_WINDOW_SIZE            0x0014
#define PREVIOUS_TRAFFIC_START	    21
#define PREVIOUS_STOPS_START        7775
#define TRAFFIC_SAVE_OFFSET	    0x100A
#define STOPS_SAVE_OFFSET	    7774

#define LANE_1_RESET_TIME           8256
#define LANE_2_RESET_TIME           8257
#define LANE_3_RESET_TIME           8258
#define LANE_4_RESET_TIME           8259
#define DIGITAL_INPUT_1_MODE        8260
#define DIGITAL_INPUT_2_MODE        8261
#define DIGITAL_INPUT_3_MODE        8262
#define DIGITAL_INPUT_4_MODE        8263
#define DIGITAL_INPUT_5_MODE        8264
#define DIGITAL_INPUT_6_MODE        8265
#define INTERLOCK_1_PULSE_TIME      8266
#define INTERLOCK_2_PULSE_TIME      8267
#define INTERLOCK_3_PULSE_TIME      8268
#define INTERLOCK_4_PULSE_TIME      8269
#define INTERLOCK_5_PULSE_TIME      8270
#define INTERLOCK_6_PULSE_TIME      8271
#define LANE_1_START_INPUT          8272
#define LANE_2_START_INPUT          8273
#define LANE_3_START_INPUT          8274
#define LANE_4_START_INPUT          8275
#define LANE_1_STOP_INPUT           8276
#define LANE_2_STOP_INPUT           8277
#define LANE_3_STOP_INPUT           8278
#define LANE_4_STOP_INPUT           8279
#define LANE_1_INTERLOCK            8280
#define LANE_2_INTERLOCK            8281
#define LANE_3_INTERLOCK            8282
#define LANE_4_INTERLOCK            8283
#define INTERLOCK_1_MODE            8284
#define INTERLOCK_2_MODE            8285
#define INTERLOCK_3_MODE            8286
#define INTERLOCK_4_MODE            8287
#define INTERLOCK_5_MODE            8288
#define INTERLOCK_6_MODE            8289
#define RELAY_LOGIC                 8290
#define RELAY_1_INTERLOCK           8291
#define RELAY_2_INTERLOCK           8292
#define RELAY_3_INTERLOCK           8293
#define RELAY_4_INTERLOCK           8294
#define INTERLOCK_1_RELAY_ASSOC     8295
#define INTERLOCK_2_RELAY_ASSOC     8296
#define INTERLOCK_3_RELAY_ASSOC     8297
#define INTERLOCK_4_RELAY_ASSOC     8298
#define INTERLOCK_5_RELAY_ASSOC     8299
#define INTERLOCK_6_RELAY_ASSOC     8300

#define FACTORY_DEFAULT_LOAD        8301

#define IP_1                        10200
#define IP_2                        10201
#define IP_3                        10202
#define IP_4                        10203
#define GW_1                        10204
#define GW_2                        10205
#define GW_3                        10206
#define GW_4                        10207
#define MAC_1                       10208
#define MAC_2                       10209
#define MAC_3                       10210
#define MAC_4                       10211
#define MAC_5                       10212
#define MAC_6                       10213
#define IP_TYPE                     10214

// mode values
#define RANDOMIZER_LANE_1   0x00
#define RANDOMIZER_LANE_2   0x01
#define RANDOMIZER_LANE_3   0x02
#define RANDOMIZER_LANE_4   0x03
#define MANUAL_RESET        0x04
#define PULSED_RESET        0x05

// log types
//#define CONFIG_SAVE 0;

// log priorities
//#define PRIORITY0 0;

// pins
#define SD_CS            4
#define WP_PIN           5
#define GFX_RESET_PIN    6
#define GFX_POWER        9
#define GREEN_0          36
#define GREEN_1          37
#define STATUS0          39
#define STATUS1          38
#define STATUS2          40
#define ANALOG_1         0
#define ANALOG_2         1
#define POWER_PIN        2
#define FUNC_1           8
#define FUNC_2           9
#define DIGITAL_INPUT_1  22
#define DIGITAL_INPUT_2  23
#define DIGITAL_INPUT_3  24
#define DIGITAL_INPUT_4  25
#define DIGITAL_INPUT_5  26
#define DIGITAL_INPUT_6  27
#define DIGITAL_INPUT_7  2
#define DIGITAL_INPUT_8  3
#define WD0_OUT          30
#define WD1_OUT          31
#define DIGITAL_OUTPUT_1 32
#define DIGITAL_OUTPUT_2 33
#define DIGITAL_OUTPUT_3 34
#define DIGITAL_OUTPUT_4 35
#define DRY_OUTPUT_1     42
#define DRY_OUTPUT_2     43
#define DRY_OUTPUT_3     44
#define DRY_OUTPUT_4     45

// virtual inputs
#define VIRTUAL_CRD      7

// graphics colors
#define GREEN_LIGHT_ON   0x07E0
#define GREEN_LIGHT_OFF  0x0400
#define GREEN_LIGHT_BRDR 0x0000

#define RED_LIGHT_ON     0xFB08
#define RED_LIGHT_OFF    0xF800
#define RED_LIGHT_BRDR   0x0000

#define STAT_BOX_1          0xFFFF
#define STAT_BOX_1_BRDR     0x0000
#define STAT_BOX_1_TXT      0x0000

#define STAT_BOX_2          0xFFFF
#define STAT_BOX_2_BRDR     0x0000
#define STAT_BOX_2_TXT      0x0000

#define STAT_BOX_3          0x5CF4
#define STAT_BOX_3_BRDR     0x0000
#define STAT_BOX_3_TXT      0x0000

#define LABEL_BOX_1         0xFFFF
#define LABEL_BOX_1_BRDR    0x0000
#define LABEL_BOX_1_TXT     0x0000

#define LABEL_BOX_2         0xFFFF
#define LABEL_BOX_2_BRDR    0x0000
#define LABEL_BOX_2_TXT     0x0000

#define LABEL_BOX_3         0xFFFF
#define LABEL_BOX_3_BRDR    0x0000
#define LABEL_BOX_3_TXT     0x0000

// slave serial commands*******************
// start byte - 0x0B | status byte 0x01 | end byte - 0xFF

#define TIME_SYNC 0x10

// ****************************************

// memory var******************************
int laneResetTimeAddress[] = { 8256, 8257, 8258, 8259 };
int laneStopByHourStartAddress[] = { 10000, 10024, 10048, 10072 };

int lastEvent;
int trafficSaveOffset;
int stopsSaveOffset;
int currentTrafficAddress[2];
int currentStopsAddress[2];
int currentTimeAddress[4];
int trafficStopPercentage;
byte lastMillis;

int trafficLaneMSB[6];
int trafficLaneLSB[6];
int trafficLane[6];

int stopsLaneMSB[6];
int stopsLaneLSB[6];
int stopsLane[6];

int laneMeanValues[12];

int writeQueueAddress[64];
unsigned char writeQueueData[64];
char queueAddress;

unsigned int traffic;
unsigned int stops;


// ****************************************

// gfx pins & var**************************

int lightRadius = 12;
int laneStartX = 40;
int laneStartY = 70;
int laneWidth  = 100;
int greenLightStartX;
int greenLightStartY;
int redLightStartX;
int redLightStartY;

long greenLightTime = 0;
long redLightTime   = 0;
int greenLightInterval = 1000;
int redLightInterval   = 1000;
int greenLightStatus   = LOW;
int redLightStatus     = LOW;

int greenLightOn = 0;
int redLightOn   = 0;

int s;

boolean en;
boolean re;

boolean updating = false;

int gfxGraph;
int graphBuilt;

int gfxResetState;
unsigned long gfxResetTime;
int gfxResetInterval;

int gfxBootState;
unsigned long gfxBootTime;
int gfxBootInterval;

unsigned long touchTime;
int touchSleep;
int touchInterval;

int touchState;
int touchMode;
int touchX;
int touchY;

int touchStatus;

int tGet[25];

int bootDone;
int slowBoot;
int slowBootDelay;

int timeF = 3;
int timeX = 300;
int timeY = 5+30;
int dateX = 330;
int dateY = 5+8;
int timeFG = 0x000000;
int timeBG = 0x000000;
int timeM = 2;
int timeXG = 5;

// ****************************************

// led pins & var **************************

int greenZerState = LOW;
int greenOneState = LOW;

int statusZerState = LOW;
int statusOneState = LOW;
int statusTwoState = LOW;


// ****************************************

// IO pins & var **************************

int buttonSenseInterval1;
int buttonSenseInterval2;

int instantInputInterval;

unsigned long resetButtons = 0;
int resetThreshold = 10000;

int inputSenseInterval[6];

byte lastInput;
byte lastDeInput;

byte dryOutput[]          = { DRY_OUTPUT_1,     DRY_OUTPUT_2,     DRY_OUTPUT_3,     DRY_OUTPUT_4 };
byte dryOutputState[]     = { LOW,              LOW,              LOW,              LOW };
byte relaylastStatus[]    = { 0,                0,                0,                0 };
byte digitalOutput[]      = { DIGITAL_OUTPUT_1, DIGITAL_OUTPUT_2, DIGITAL_OUTPUT_3, DIGITAL_OUTPUT_4 };
byte digitalOutputState[] = { LOW,              LOW,              LOW,              LOW };
byte digitalInput[]       = { DIGITAL_INPUT_1,  DIGITAL_INPUT_2,  DIGITAL_INPUT_3,  DIGITAL_INPUT_4,
                              DIGITAL_INPUT_5,  DIGITAL_INPUT_6,  DIGITAL_INPUT_7,  DIGITAL_INPUT_8 };
byte analogInput[]        = { ANALOG_1,         ANALOG_2,         POWER_PIN };
byte funcButton[]         = { FUNC_1,           FUNC_2 };

int digitalInputState[8];
int analogInputValue[3];
int funcButtonValue[2];

byte inversions;

unsigned long interlockStartTime[6];
int interlockOn[] = { 0, 0, 0, 0, 0, 0 };
long interlockTimer[6];
byte interlockRelayAssoc[6];

byte laneSecondChance[] = { 0, 0, 0, 0 };

// ****************************************

// time var *******************************

unsigned long gfxPowerTime;
long gfxPowerInterval;

unsigned long heartbeatTime;
int heartbeatInterval;
int heartbeats;

unsigned long resetDefaultTime;
int resetDefaultTrip;

char relayPulse[] = { 0, 0, 0, 0 };

// ****************************************

// power var ******************************

int inputPower;
int gfxPowerState;
// ****************************************

// reader var******************************

int period = 4;

volatile int bitCnt = 0;
volatile int bitCntC;
volatile long lastBitTime = 0;

volatile long rfid = 0;
volatile long rfidC;
// ****************************************

// comm var********************************

int slaveBuffer[256];
int slaveBufferSize;

int  startByte, endByte, statusByte, statusWaiting, slaveOnline;
char streamOn;

unsigned long statusTime;
int statusInterval;

int ipDefault[] = { 192, 168, 1, 169 };
int gwDefault[] = { 192, 168, 1, 1 };
int mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xA5, 0x61 };

// ****************************************

// button coordinates**********************

volatile int seg1a[] = { 20, 130, 50, 150 };
volatile int seg1b[] = { 20, 190, 50, 210 };

volatile int seg2a[] = { 80, 130, 110, 150 };
volatile int seg2b[] = { 80, 190, 110, 210 };

volatile int seg3a[] = { 140, 130, 170, 150 };
volatile int seg3b[] = { 140, 190, 170, 210 };

volatile int seg4a[] = { 200, 130, 230, 150 };
volatile int seg4b[] = { 200, 190, 230, 210 };

volatile int seg5a[] = { 260, 130, 290, 150 };
volatile int seg5b[] = { 260, 190, 290, 210 };

volatile int segOpta[] = { 403, 155, 468, 175 };
volatile int segOptb[] = { 403, 185, 468, 205 };

volatile int menuBut[] = { 400, 61, 467, 81 };

volatile int currentPage;
volatile int segYOffset;
volatile int segXOffset;

int numberOfPages = 6;
volatile int currentOption = 0;

volatile int touchPoint;

int lastTou;

// ****************************************

char holder[6];

char* clrStr = " ";
char* meridian[] = { "AM", "PM" };
char* randStr[] = {
 /*0*/"History", /*1*/"Actual", /*2*/"Stops", /*3*/"Traffic", /*4*/"Traffic Flow Inspection Server",
 /*5*/"Access Automation & Controls Group, Inc", /*6*/"0", /*7*/"CRD", /*8*/"STR", /*9*/"INV",
 /*10*/"LN", /*11*/"MAN", /*12*/"PUL", /*13*/"-", /*14*/"LAT", /*15*/"Relay",
 /*16*/"HR", /*17*/"MIN", /*18*/"MON", /*19*/"DAY", /*20*/"YEAR", /*21*/"Start", /*22*/"Input",
 /*23*/"Reset", /*24*/"Time", /*25*/"Inter", /*26*/"lock", /*27*/"Logic", /*28*/"Action",
 /*29*/"Assoc Relays:", /*30*/":", /*31*/"%", /*32*/"Insp%", /*33*/"Done",
 /*34*/"Clearing Memory!", /*35*/"Disk", /*36*/"Loading Factory Default Config",
 /*37*/"Done! Please touch reset button", /*38*/"/", /*39*/"Settings", /*40*/"BY HR", /*41*/"INST", /*42*/"Y", /*43*/"N",
 /*44*/"ALL", /*45*/"Please wait"
};

char* weekdays[] = {
 " ", "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"
};

char* configHeaders[] = {
 "Time (24 HR)",
 "Inspection %",
 "Lane",
 "Relay",
 "Future",
 "Interlock"
};

AthenaSave save(WP_PIN, STATUS2); // Initialize custom EEPROM library with write protect pin

void setup(){
 INIT_COMM();
 INIT_GRAPHICS();
 INIT_MEMORY();
 INIT_TIME();
 INIT_POWER();
 INIT_VISUALS();
 INIT_IO();
 INIT_SD();
}

void loop(){
 POWER_SERVICE();
 TIME_SERVICE();
 COMM_SERVICE();
 RANDOMIZER_SERVICE();
 MEMORY_SERVICE();
 IO_SERVICE();
 VISUALS_SERVICE();
 GRAPHICS_SERVICE();
 READER_SERVICE();
}


