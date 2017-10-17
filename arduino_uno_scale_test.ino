#include "HX711.h"
#include"math.h"
#include <EEPROMex.h>
#include <EEPROMVar.h>
#include <LiquidCrystal.h>  
#define BUTTON 7 
#define LED 13 
#define TAREBUTTON 10
#define buzzer 8
// HX711.DOUT - pin #A2
// HX711.PD_SCK - pin #A3
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

HX711 scale(A2, A3); // parameter "gain" is ommited; the default value 128 is used by the library

long somma1=0;
float I=0;
int a;
float b;
float calibval1;
float calibval2;
float media2=0;
float media1=0;
long somma2=0;
float pmax= 900;
int val=0;
int val1=0; //valore del pulsante di tara
float t =0;
float g=0;
void setup() {
  scale.set_scale();
  scale.tare();
  pinMode (buzzer, OUTPUT);
  tone(buzzer,440,1000);
  delay(500);
  noTone(buzzer);
  delay(200);
  tone (buzzer,330,1000);
  delay(1000);
  noTone(buzzer);
Serial.begin (9600);
  lcd.begin(16, 2); 
  lcd.print ("Fede Bil");
  lcd.setCursor( 0,1);
  lcd.print ("ver.1.0 :)");
   for (int positionCounter = 0; positionCounter < 6; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(450);} 
     for (int positionCounter = 0; positionCounter < 6; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(450);}
  delay(3000);
  lcd.clear ();
  lcd.print ("Press Button 2");
  lcd.setCursor(0,1);
  lcd.print("to calibrate");
  delay(1500);
 pinMode(LED, OUTPUT); 
 pinMode (TAREBUTTON,OUTPUT); //IMPOSTA IL PULSANTE DI TARA
 pinMode(BUTTON, INPUT);     // imposta il pin digitale come input 
val=digitalRead (BUTTON);
if (val==HIGH){
  tone(buzzer,1047,1000);
digitalWrite(LED, HIGH);
calibrazione();}
else {
  tone(buzzer,660,500);
Serial.println (EEPROM.readFloat(10)); // restituisce il valore float memorizzato all'indirizzo indicato Ricarica calibval1
calibval2= (EEPROM.readFloat(10));
Serial.print ("calibval2=");
Serial.println (calibval2);
scale.set_scale (calibval2);
}}

void loop() {
 
pippo:  I= (scale.get_units(10));
Serial.println(I);
if (I < 1 &&I>0)
{ val1= digitalRead (TAREBUTTON);
if (val1==HIGH){
  tone(buzzer,622,1000);
  lcd.clear();
  lcd.print ("Tara");
  delay (1000);
  t= scale.get_units(10);
  g=round(t);
  scale.tare();}
  lcd.clear();
  lcd.print("d=0,5g");
  //lcd.setCursor(9,0);
 lcd.setCursor(0,1);
  lcd.print("0.00");
  lcd.setCursor(9,0);
  lcd.print ("d=0.2g");
  lcd.setCursor (9,1);
  lcd.print(I);
  delay(500);
  Serial.println ("0.00");
   val=digitalRead (BUTTON);
  if (val==HIGH){
  tone(buzzer,1047,500);
digitalWrite(LED, HIGH);
menu();}
else {
}
 goto pippo;
} 
val1= digitalRead (TAREBUTTON);
if (val1==HIGH){
  tone(buzzer,622,1000);
  lcd.clear();
  lcd.print ("Tara");
  delay (1000);
  t =scale.get_units(10);
   g=round(t);
  scale.tare();
 val=digitalRead (BUTTON); 
  if (val==HIGH){
  tone(buzzer,1047,500);
digitalWrite(LED, HIGH);
menu();}
else {
}}
  int c= (I*10);
  int e = (I*10);
 // e=round (c);
 int peso_div = (e+1)-((e+1)%2);
int  peso_div_5 = (c+2)-((c+2)%5);
  float f = (peso_div);
  float peso2 = (f/10);
   float d = (peso_div_5);
  float pesofin=(d/10);
   if (pesofin > pmax)
   {tone(buzzer,1047,2000);
     lcd.clear();
   lcd.print ("Overload");
    goto pippo;}
   lcd.clear();
   lcd.setCursor (0,0);
    lcd.print ("d=0,5g");
    lcd.setCursor(0, 1); 
    lcd.print (pesofin);
    lcd.setCursor(9,0);
    lcd.print ("d=0.2g");
    lcd.setCursor (9,1);
    lcd.print (peso2);
    delay(150);
    val=digitalRead (BUTTON);
if (val==HIGH){
  tone(buzzer,1047,500);
digitalWrite(LED, HIGH);
lcd.clear();
menu();}
else {
}
}
