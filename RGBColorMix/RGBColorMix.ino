#define falante A0
int R = 9;
int G = 10;
int B = 11;   //pin for rgb pins (gnd = on) PWM NEEDED
int colorState[3] = {1,0,0};
int rgb[3] = {9, 10, 11};
int lastRead[5];
int audioIntensity;
int audioPeak;
int prevTime;

void setup() {
  Serial.begin(115200);
  pinMode(falante, INPUT);
  //led_test();
  
  analogWrite(R, 123);
  delay(1000);
}

void loop() {
  sequence();
  /*
  if((millis()+3000)>prevTime){
    for(int cont=0; cont<5; cont++){
      lastRead[cont] = analogRead(falante);
      delay(50);
    }
  }
  
  for(int cont=0; cont<5; cont++){
    int media = 0;
    media += lastRead[cont];

    if(cont==4)
      media = media/5;
    
    if (analogRead(falante) > media)
      peak_change_color();

    pulses();
    Serial.println(prevTime = millis());
  }*/
}

//desejamos que em caso de atingir pico temporario, mude o estado, pegamos pico de 1 segundo da intensidade de audio
void peak_change_color(){
  prevTime = millis();
  change_color();
}

void change_color(){
  ledOff();
  for(int n=0; n<3; n++){
    if(colorState[n]==0){
      analogWrite(colorState[n], random(0, 123));
      colorState[n] = 1;
    }
    else{
      analogWrite(colorState[1], random(0, 123));
      colorState[n] = 0;
    }
  }

}

void led_test(){
  Serial.println("Testing RED");
  analogWrite(R, 0);
  delay(500);
  analogWrite(R, 255);

  Serial.println("Testing GREEN");
  analogWrite(G, 0);
  delay(500);
  analogWrite(G, 255);

  Serial.println("Testing BLUE");
  analogWrite(B, 0);
  delay(500);
  analogWrite(B, 255);

  Serial.println("Testing color intensity");
  for (int pin=0; pin<3; pin++){
    for (int n=0; n<256; n++){
      analogWrite(rgb[pin], n);
      delay(50);
    }
  }
  
  Serial.println("Shuting down led test ");
  analogWrite(R, 255);
  delay(500);
  analogWrite(G, 255);
  delay(500);
  analogWrite(B, 255);
  delay(500);
}

void ledOff(){
  for(int n=0; n<3; n++){
      analogWrite(colorState[n], 0);
  }
}

void pulses(){
  for ( int led=0; led<3; led++){
    if(colorState[led]==1)
        analogWrite((9+led), random(0, 230));
        delay(100);      
  }
}

void doidao() {
  analogWrite( (9+random(0, 3)), random(0,254));
  delay(random(10,2000));
}

void sequence(){
  ledOff();
  for (int led=9; led<12; led++)
    for(int power= 255; power>0; power--){
      analogWrite(led, power);
      delay(10);
    }
  
}