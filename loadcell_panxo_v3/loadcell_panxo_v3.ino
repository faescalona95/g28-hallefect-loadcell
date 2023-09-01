

#include <Joystick.h>
#include <Q2HX711.h>

int incomingByte = 0; // for incoming serial data

const byte hx711_data_pin = 14;
const byte hx711_clock_pin = 16;

float y1 = 10000.0; // calibrated mass to be added

float x0;
float avg_size = 1.0; // amount of averages for each mass measurement
float accel;
////////////////////////////////////////////////////
///////CALIBRACION Y LA CONCHUDA //////////////////
/////////////////////////////////////////////////
//
//⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
//⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
//⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀ 
//⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀ 
//⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆ 
//⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿ 
//⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀ 
//⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
//⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
//⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀ 
//⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀ 
//⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀ 
//⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀ 
//⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀ 
//⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉

float x2 = 7700000.0;
float x1 = 6640000.0; 

float acc_inf = 201.0;
float acc_sup = 630.0;

float clut_inf = 219.0;
float clut_sup = 282.0;
String instruccion;


Q2HX711 hx711(hx711_data_pin, hx711_clock_pin); // prep hx711
 
Joystick_ Joystick(0x06, JOYSTICK_TYPE_JOYSTICK, 2, 0,  false, false, true, false, false, false,  true, true, false, true, false);

const byte pin_accel_analog = A0;
const byte pin_embr_analog = A3;

void setup() {

Joystick.begin();

Joystick.setBrakeRange(0, 1023);




Serial.begin(500000);
//while(!Serial);

float x2 = 7700000.0;
float x1 = 6640000.0; 

//float m = (1023.0)/(x2-x1) ;

float m2 = -0.3;
float n2 = 0.0;
}

void loop() {
  // averaging reading
  float reading = hx711.read();
  float accel = analogRead(pin_accel_analog);
  float embr = analogRead(pin_embr_analog);

digitalWrite(2,HIGH);


if (Serial.available() != 0) {
// read the incoming byte:
instruccion = Serial.readString();
instruccion.trim();
}
  
float m = (1023.)/(x2-x1);
float y1 = 0.0;
float masita = m * reading - m*x1 + y1;

Serial.print("frenoraw:");
Serial.print(masita);
Serial.print(",");


  if (masita < 0.){
    masita = 0.;
  }
  else if (masita >1023.){
    masita = 1023.;
  }


//  float accel2 = pow( ( (accel - acc_inf)*(0.-1023.0)/(acc_inf - acc_sup)+0.0 )/1023.0, 0.60) * 1023.0;

float accel2 = 1023./(acc_sup-acc_inf) * accel - 1023./(acc_sup-acc_inf)*acc_inf ;

  if (accel2 < 0.){
    accel2 = 0.;
  }
  if (accel2 >1023.){
    accel2 = 1023.;
  }

 float embr2 = pow( ( (embr-clut_inf)*(0.-1023.0)/(clut_inf-clut_sup)+0.0 )/1023.0    , 0.75) * 1023.0;  
  
  if (embr2 < 0.){
    embr2 = 0.0;
  }
  if (embr2 >1023.){
    embr2 = 1023.;
  }


//Serial.print("freno:");
//Serial.print(masita/1023*100);
//Serial.print(",");
//Serial.print("accel:");
//Serial.print(accel2/1023*100);
//Serial.print(",");
//Serial.print("embr:");
//Serial.println(embr2/1023*100);
//Serial.print(",");
Serial.print("accelraw:");
Serial.print(accel);
Serial.print(",");
Serial.print("embrraw:");
Serial.println(embr2);
Joystick.setBrake(masita);
Joystick.setThrottle(accel2);
Joystick.setZAxis(embr2);
//Joystick.send_now();
}




