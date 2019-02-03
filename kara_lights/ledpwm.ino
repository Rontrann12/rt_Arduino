/* 

  Karaoke/ living room lighting 

  todo:
  - add more patterns (inverted colours 
  - clean up the code 
  - add 5V regulator to power arduino 
  - toggle white light brightness? 
  - find appropriate power supply (12v, ~ 3amp)
  - solder up the final project 

*/

// give variable name to the pin
 int blue = 6;
 int green = 5;
 int red = 3; 
 int aPin = 0;
 int interruptPin = 2;
 volatile byte mode = 0; 
 int i;
 int val = 0;

void setup() {

  Serial.begin(9600);
  // Initialize the IO pins
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(interruptPin, INPUT);
  
  digitalWrite(13,HIGH);
  attachInterrupt(digitalPinToInterrupt(interruptPin), swap, RISING);

}


void warmWhite(){
  analogWrite(blue, 10);
  analogWrite(green, 65);
  analogWrite(red, 255);

}

void white(){
  analogWrite(blue, 200);
  analogWrite(green, 210);
  analogWrite(red, 255);
}

void flash() {
  analogWrite(blue,0);  // reset leds 
  analogWrite(green,0);
  analogWrite(red,0); 

  if (mode == 2){
    analogWrite(blue, 255);
    delay(792);
    analogWrite(blue, 0);
    delay(792);
  }

  if (mode == 2){
    analogWrite(green, 255);
    delay(792);
    analogWrite(green, 0);
    delay(792);
  }



  if (mode == 2){
    analogWrite(red, 255);
    delay(792);
    analogWrite(red, 0);
    delay(792);
  }

  if (mode == 2){
    analogWrite(blue,255);
    analogWrite(red, 255);
    delay(792);
    analogWrite(red, 0);
    analogWrite(blue,0);
    delay(792);
  }
  if (mode == 2){
    analogWrite(green, 255);
    analogWrite(red, 255);
    delay(792);
    analogWrite(red, 0);
    analogWrite(green, 0);
    delay(792);
  }
  
  
}

void cycle(){
  analogWrite(blue, 0);
  analogWrite(green, 0);
  analogWrite(red, 0);
  
  for(i = 0 ; i<=255 ; i = i+1){ //cycle green 
    analogWrite(green,i);
    delay(20);
    if(mode != 0) {i = 255;}
  } 

  if(mode == 0){
    for( i = 255 ; i >= 0; i = i-1){
      analogWrite(green, i );
      delay(20);  
      if(mode != 0 ){ i = 0;}
    }
  }

  if(mode == 0){
    for( i = 0 ; i<=255 ; i = i+1){ //cycle red 
      analogWrite(red,i);
      delay(20);
      if(mode != 0) {i = 255;}  
    }  
  }
  if(mode == 0){
    for ( i = 255 ; i >= 0 ; i = i-1){
      analogWrite(red,i);
      delay(20);
      if(mode != 0) {i = 0;}       
    }
  }
  if(mode == 0){
    for( i = 0 ; i<=255 ; i = i+1){ //cycle blue  
      analogWrite(blue,i);
      delay(20);
      if(mode != 0) {i = 255;}  
    }  
  }
  if(mode == 0){
    for ( i = 255 ; i >= 0 ; i = i-1){
      analogWrite(blue,i);
      delay(20);
      if(mode != 0) {i = 0;}       
    }
  }
}


int forPWM( double val){

  val = (int) (val * 255);
  val = abs(val);
  return val;
}

void alternate(){
  //reset leds 
  analogWrite(blue, 0); 
  analogWrite(green,0);
  analogWrite(red, 0);
  float angle = 0.0; //in radians 
  delay(1000);

  while (mode == 4){

    //create pwm signal (there should be phase shift between the led colours)
    analogWrite(red, 6);
    delay(20);

    //adjust the angle 
    angle = angle + 0.1;

    //makes sure that pi loops around 
    if ( angle >= 2*(3.14)){
      angle = 0; //reset te value for angle 
    }
  }
  
}

void strobe(){
  
  val = analogRead(aPin);
  float rate;
  analogWrite(blue,0);
  analogWrite(red,0);
  analogWrite(green,0);

  rate = 80. + (35./1023.)*val;
  val = (int) ((1./rate)*30000.);

  delay( val);

  analogWrite(blue,255);
  analogWrite(red,255);
  analogWrite(green,255);

  delay( val);


  
  
}


void pattern(int mode) {
  if (mode == 0) {
    cycle();
  }
  
  if(mode == 1){
    warmWhite();
  }

  if( mode == 2){
    flash();
  }
  if( mode == 3){
    white();
  }

  if(mode == 4){
    strobe();
  }

}

void loop() {
  pattern(mode);

}

void swap(){
  mode = mode + 1; //swap the value for mode 
  if( mode == 5){ mode = 0;} //cycle through all the patterns again 
}

