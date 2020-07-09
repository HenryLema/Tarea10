#include<LiquidCrystal.h>
#include<TimerOne.h>
#include<MsTimer2.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
volatile byte state = LOW;
int minutero;
const int led1=4;
const int led2=5;
const int led3=6;
const int led4=7;
const int interrupcion = 2;
volatile long int reloj=0;
volatile long int minuto=0;
int cont=0;
int on;
int estado2= 0;
int conversor;
int hora;
int conversor2;

void setup() {
  lcd.begin(16,2);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(interrupcion, INPUT_PULLUP);
  attachInterrupt(0, activar, RISING);
  attachInterrupt(1, modos, LOW);
  Timer1.initialize(1000000); //1 seg
  Timer1.attachInterrupt(tiempo); //
  Serial.begin(9600);
  MsTimer2::set(1000,modos1);
  MsTimer2::start();
}
 void loop() {
}
void activar() {
  state = !state;
  if (state == 1) {
  lcd.setCursor(0,0);
  lcd.println("off");  
  lcd.noDisplay();
  
  }
  else{
  lcd.setCursor(0,0);
  lcd.println("ON");
  lcd.display();
  
  }
}


void tiempo(){
 
 reloj++;
 if(reloj>59){
  reloj=0;
  minuto++;
 }
  if(estado2==0){
 lcd.setCursor(0,1);
 lcd.println("Hora: ");
 if(minuto<10)
 lcd.setCursor(6,0);
 lcd.println("0");
 lcd.setCursor(7,0);
 lcd.println(minuto);
 lcd.setCursor(8,0);
 lcd.println(":");
 if(reloj<10){
  lcd.setCursor(9,0);
  lcd.println("0");
 //lcd.clear();
 }
 lcd.setCursor(10,0);
 lcd.println(reloj);
 if(minuto>=12){
 lcd.setCursor(0,1);
 lcd.print("Estado:PM");
 }else {
  lcd.setCursor(0,1);
  lcd.print("Estado:AM");
 }
}else if(estado2==1){
  lcd.clear();
    conversor=analogRead(0);
    conversor2=analogRead(1);
    lcd.setCursor(0,0);
    lcd.print("Hora:");
    lcd.setCursor(0,1);
    hora=map(conversor, 0, 1023, 0, 24);
    lcd.println(hora);
    lcd.setCursor(2,1);
    lcd.println(":");
    minutero=map(conversor2, 0, 1023, 0,60);
    lcd.setCursor(4,1);
    lcd.println(minutero);
  
}
}
void modos(){
 switch(estado2){
    case 0:
 lcd.setCursor(0,1);
 lcd.print("H");
      modos1();
      estado2++;
     break;
     case 1:
     lcd.setCursor(0,1);
     lcd.print("H22");
    lcd.clear();
    conversor=analogRead(0);
    conversor2=analogRead(1);
    lcd.setCursor(0,0);
   lcd.print("Hora:");
    lcd.setCursor(7,0);
    hora=map(conversor, 0, 1023, 0, 24);
    lcd.println(hora);
    lcd.setCursor(9,0);
    lcd.println(":");
    minutero=map(conversor2, 0, 1023, 0,60);
    lcd.setCursor(10,0);
    lcd.println(minutero);

    on=0;
    estado2=0;
    break;

 
    
  }
  
  conversor=analogRead(0);
  hora=minuto;
  hora=map(conversor, 0, 1023, 0, 24);
  lcd.setCursor(7,0);
  lcd.println(hora);

  
 
  
}
void modos1(){
  if(cont<20){
    cont++;
    switch(cont){
      case 2:
        digitalWrite(led3,HIGH);
      break;
      case 5:
        digitalWrite(led1,HIGH);
      break;
      case 7:
        digitalWrite(led3,LOW);
      break;
      case 9:
        digitalWrite(led2,HIGH);
      break;
      case 11:
        digitalWrite(led4,HIGH);
      break;
      case 13:
        digitalWrite(led2,LOW);
      break;
      case 15:
        digitalWrite(led4,LOW);
      break;
      case 18:
        digitalWrite(led1,LOW);
      break;
      case 20:
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        digitalWrite(led3,LOW);
        digitalWrite(led4,LOW);
    }
    if(reloj>20){
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        digitalWrite(led3,LOW);
        digitalWrite(led4,LOW);
    }
  }
  else
  cont=0;
  
}
