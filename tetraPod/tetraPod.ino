
//2020.03.28
#include <Servo.h>
#include <IBusBM.h>

Servo myservoRodillas[4];
Servo myservoPatitas[4];
Servo myservoHombritos[4];

IBusBM IBus;

int hombritos[4]={90,90,90,90};
int rodillas[4]={160,20,160,20};
int patitas[4]={160,20,160,20};

int hombritosP[4]={90,90,90,90};
int rodillasP[4]={160,20,160,20};
int patitasP[4]={175,5,175,5};

void setup(){
  delay(5000);
  
  myservoHombritos[0].attach(10);
  myservoHombritos[0].write(hombritos[0]);
  myservoHombritos[1].attach(11);
  myservoHombritos[1].write(hombritos[1]);
  myservoHombritos[2].attach(12);
  myservoHombritos[2].write(hombritos[2]);
  myservoHombritos[3].attach(13);
  myservoHombritos[3].write(hombritos[3]);
  
  myservoRodillas[0].attach(2);
  myservoRodillas[0].write(rodillas[0]);
  myservoRodillas[1].attach(3);
  myservoRodillas[1].write(rodillas[1]);
  myservoRodillas[2].attach(4);
  myservoRodillas[2].write(rodillas[2]);
  myservoRodillas[3].attach(5);
  myservoRodillas[3].write(rodillas[3]);

  myservoPatitas[0].attach(6);
  myservoPatitas[0].write(patitas[0]);
  myservoPatitas[1].attach(7);
  myservoPatitas[1].write(patitas[1]);
  myservoPatitas[2].attach(8);
  myservoPatitas[2].write(patitas[2]);
  myservoPatitas[3].attach(9);
  myservoPatitas[3].write(patitas[3]);
  delay(5000);
  
  //Serial.begin(115200);
  IBus.begin(Serial);
} 

void loop(){
  int channel0 = IBus.readChannel(0);
  int channel2 = IBus.readChannel(2);
  
  if (channel0==0 && channel2==0) {
    controlAutomatico();
  }else {
    controlRemoto(channel2,channel0);
  }
  
}

void controlRemoto(int valUD, int valLR){
  
  if (valLR>1600) {
    rotarDer(8);
  } else if (valLR<1400) {
    rotarIzq(8);
  } else if (valUD>1600) {
    andar(8);
  } else if (valUD<1400) {
    retroceder(8);
  } else {
    reposo();
    /*Serial.print("LR: ");
    Serial.println(valLR);
    Serial.print("UD: ");
    Serial.println(valUD);*/
    delay(100);
  }
}

void controlAutomatico() {
  if (analogRead(7)>1020) {
    andar(8);
    //Serial.print("AVANZAR");Serial.print(analogRead(7));Serial.print(", ");
  } else {
    //Serial.print("ROTANDO DERECHA");Serial.print(", ");
    retroceder(8);
    retroceder(8);
    retroceder(8);
    rotarDer(7);
    rotarDer(7);
    rotarDer(7);
    if (random(2)==0){
      rotarDer(7);
    }
  }
}

void smothPositioning(Servo servo, int pos) {
  int start = servo.read();
  while(start<pos) {
    servo.write(start++);
    delay(10);
  }
  while(start>pos) {
    servo.write(start--);
    delay(10);
  }
}

void andar(int velocidad) {
  int fps=0;
  int incremento=0;
  int incrementoPat=0;
  int incrementoRod=-25;
  int incremento2=25;
  int incrementoPat2=20;
  int incrementoRod2=0;

  while (++fps<100) {
    if(fps<50){
      incremento++; if (++incrementoPat>20){ incrementoPat=20; } if (++incrementoRod>0){ incrementoRod=0; } 
      myservoHombritos[0].write(hombritos[0]+incremento);
      myservoPatitas[0].write(patitas[0]-incrementoPat);
      myservoRodillas[0].write(rodillas[0]+incrementoRod);

      myservoHombritos[2].write(hombritos[2]-incremento);
      myservoPatitas[2].write(patitas[2]-incrementoPat);
      myservoRodillas[2].write(rodillas[2]+incrementoRod);
    }
    if(fps>=50){
      incremento--; if (--incrementoPat<0){ incrementoPat=0; } if (--incrementoRod<-25){ incrementoRod=-25; }
      myservoHombritos[0].write(hombritos[0]+incremento);
      myservoPatitas[0].write(patitas[0]-incrementoPat);
      myservoRodillas[0].write(rodillas[0]+incrementoRod);

      myservoHombritos[2].write(hombritos[2]-incremento);
      myservoPatitas[2].write(patitas[2]-incrementoPat);
      myservoRodillas[2].write(rodillas[2]+incrementoRod);
    }
    if(fps>=50){
      incremento2++; if (++incrementoPat2>20){ incrementoPat2=20; } if (++incrementoRod2>0){ incrementoRod2=0; } 
      myservoHombritos[3].write(hombritos[3]-incremento2);
      myservoPatitas[3].write(patitas[3]+incrementoPat2);
      myservoRodillas[3].write(rodillas[3]-incrementoRod2);

      myservoHombritos[1].write(hombritos[1]+incremento2);
      myservoPatitas[1].write(patitas[1]+incrementoPat2);
      myservoRodillas[1].write(rodillas[1]-incrementoRod2);
    }
    if(fps<50){
      incremento2--; if (--incrementoPat2<0){ incrementoPat2=0; } if (--incrementoRod2<-25){ incrementoRod2=-25; }
      myservoHombritos[3].write(hombritos[3]-incremento2);
      myservoPatitas[3].write(patitas[3]+incrementoPat2);
      myservoRodillas[3].write(rodillas[3]-incrementoRod2);

      myservoHombritos[1].write(hombritos[1]+incremento2);
      myservoPatitas[1].write(patitas[1]+incrementoPat2);
      myservoRodillas[1].write(rodillas[1]-incrementoRod2);
    }
    delay(velocidad);
  } 
}

void retroceder(int velocidad) {
  int fps=0;
  int incremento=50;
  int incrementoPat=0;
  int incrementoRod=-25;
  int incremento2=-25;
  int incrementoPat2=20;
  int incrementoRod2=0;

  while (++fps<100) {
    if(fps<50){
      incremento--; if (++incrementoPat>20){ incrementoPat=20; } if (++incrementoRod>0){ incrementoRod=0; } 
      myservoHombritos[0].write(hombritos[0]+incremento);
      myservoPatitas[0].write(patitas[0]-incrementoPat);
      myservoRodillas[0].write(rodillas[0]+incrementoRod);

      myservoHombritos[2].write(hombritos[2]-incremento);
      myservoPatitas[2].write(patitas[2]-incrementoPat);
      myservoRodillas[2].write(rodillas[2]+incrementoRod);
    }
    if(fps>=50){
      incremento++; if (--incrementoPat<0){ incrementoPat=0; } if (--incrementoRod<-25){ incrementoRod=-25; }
      myservoHombritos[0].write(hombritos[0]+incremento);
      myservoPatitas[0].write(patitas[0]-incrementoPat);
      myservoRodillas[0].write(rodillas[0]+incrementoRod);

      myservoHombritos[2].write(hombritos[2]-incremento);
      myservoPatitas[2].write(patitas[2]-incrementoPat);
      myservoRodillas[2].write(rodillas[2]+incrementoRod);
    }
    if(fps>=50){
      incremento2--; if (++incrementoPat2>20){ incrementoPat2=20; } if (++incrementoRod2>0){ incrementoRod2=0; } 
      myservoHombritos[3].write(hombritos[3]-incremento2);
      myservoPatitas[3].write(patitas[3]+incrementoPat2);
      myservoRodillas[3].write(rodillas[3]-incrementoRod2);

      myservoHombritos[1].write(hombritos[1]+incremento2);
      myservoPatitas[1].write(patitas[1]+incrementoPat2);
      myservoRodillas[1].write(rodillas[1]-incrementoRod2);
    }
    if(fps<50){
      incremento2++; if (--incrementoPat2<0){ incrementoPat2=0; } if (--incrementoRod2<-25){ incrementoRod2=-25; }
      myservoHombritos[3].write(hombritos[3]-incremento2);
      myservoPatitas[3].write(patitas[3]+incrementoPat2);
      myservoRodillas[3].write(rodillas[3]-incrementoRod2);

      myservoHombritos[1].write(hombritos[1]+incremento2);
      myservoPatitas[1].write(patitas[1]+incrementoPat2);
      myservoRodillas[1].write(rodillas[1]-incrementoRod2);
    }
    delay(velocidad);
  } 
}

void rotarDer(int velocidad) {
  int fps=0;
  int incremento=0;
  int incremento2=0;
  int incremento3=0;
  int incremento4=0;
  int incremento5=0;

  while (++fps<150) {
    if(fps<70){
      incremento++;
      myservoHombritos[0].write(hombritos[0]+incremento-20);
      myservoHombritos[2].write(hombritos[2]+incremento-50);
      myservoHombritos[3].write(hombritos[3]+incremento-50);
      myservoHombritos[1].write(hombritos[1]+incremento-20);     
    }
    if(fps>=70 && fps<90){
      if (++incremento2>10){ incremento2=10; }
      myservoHombritos[0].write(hombritos[0]+70-(incremento2*7)-20);
      myservoPatitas[0].write(patitas[0]-incremento2);
      myservoRodillas[0].write(rodillas[0]+incremento2*2);
    }
    if(fps>=90 && fps<110){
      if (--incremento2<0){ incremento2=0; } 
      myservoPatitas[0].write(patitas[0]-incremento2);
      myservoRodillas[0].write(rodillas[0]+incremento2*2);
      if (++incremento3>10){ incremento3=10; }
      myservoHombritos[2].write(hombritos[2]+70-(incremento3*7)-50);
      myservoPatitas[2].write(patitas[2]-incremento3);
      myservoRodillas[2].write(rodillas[2]+incremento3*2);
      }
    if(fps>=110 && fps<130){
      if (--incremento3<0){ incremento3=0; }  
      myservoPatitas[2].write(patitas[2]-incremento3);
      myservoRodillas[2].write(rodillas[2]+incremento3*2);
      if (++incremento4>10){ incremento4=10; }
      myservoHombritos[3].write(hombritos[3]+70-(incremento4*7)-50);
      myservoPatitas[3].write(patitas[3]+incremento4);
      myservoRodillas[3].write(rodillas[3]-incremento4*2);
     }
    if(fps>=130){
      if (--incremento4<0){ incremento4=0; }
      myservoPatitas[3].write(patitas[3]+incremento4);
      myservoRodillas[3].write(rodillas[3]-incremento4*2);
      if (++incremento5>10){ incremento5=10; }
      myservoHombritos[1].write(hombritos[1]+70-(incremento5*7)-20); 
      myservoPatitas[1].write(patitas[1]+incremento5);
      myservoRodillas[1].write(rodillas[1]-incremento5*2);    
    }
    if(fps==149){
      if (--incremento5<0){ incremento5=0; }
       myservoPatitas[1].write(patitas[1]+incremento5);
       myservoRodillas[1].write(rodillas[1]-incremento5*2); 
    }
    delay(velocidad);
  } 
}

void rotarIzq(int velocidad) {
  int fps=0;
  int incremento=70;
  int incremento2=0;
  int incremento3=0;
  int incremento4=0;
  int incremento5=0;

  while (++fps<150) {
    if(fps<70){
      incremento++;
      myservoHombritos[0].write(hombritos[0]-incremento+90);
      myservoHombritos[2].write(hombritos[2]-incremento+120);
      myservoHombritos[3].write(hombritos[3]-incremento+120);
      myservoHombritos[1].write(hombritos[1]-incremento+90);     
    }
    if(fps>=70 && fps<90){
      /*if (++incremento2>10){ incremento2=10; }
      myservoHombritos[0].write(hombritos[0]+(incremento2*7)+90);
      myservoPatitas[0].write(patitas[0]-incremento2);
      myservoRodillas[0].write(rodillas[0]+incremento2*2);*/

      if (++incremento5>10){ incremento5=10; }
      myservoHombritos[1].write(hombritos[1]+(incremento5*7)-50); 
      myservoPatitas[1].write(patitas[1]+incremento5);
      myservoRodillas[1].write(rodillas[1]-incremento5*2);
      
    }
    if(fps>=90 && fps<110){
      /*if (--incremento2<0){ incremento2=0; } 
      myservoPatitas[0].write(patitas[0]-incremento2);
      myservoRodillas[0].write(rodillas[0]+incremento2*2);
      if (++incremento3>10){ incremento3=10; }
      myservoHombritos[2].write(hombritos[2]+(incremento3*7)+120);
      myservoPatitas[2].write(patitas[2]-incremento3);
      myservoRodillas[2].write(rodillas[2]+incremento3*2);*/

      if (--incremento5<0){ incremento5=0; }
      myservoPatitas[1].write(patitas[1]+incremento5);
      myservoRodillas[1].write(rodillas[1]-incremento5*2); 
      if (++incremento4>10){ incremento4=10; }
      myservoHombritos[3].write(hombritos[3]+(incremento4*7)-20);
      myservoPatitas[3].write(patitas[3]+incremento4+20);
      myservoRodillas[3].write(rodillas[3]-incremento4*2);
      
      
    }
    if(fps>=110 && fps<130){
      /*if (--incremento3<0){ incremento3=0; }  
      myservoPatitas[2].write(patitas[2]-incremento3);
      myservoRodillas[2].write(rodillas[2]+incremento3*2);
      if (++incremento4>10){ incremento4=10; }
      myservoHombritos[3].write(hombritos[3]+(incremento4*7)+120);
      myservoPatitas[3].write(patitas[3]+incremento4);
      myservoRodillas[3].write(rodillas[3]-incremento4*2);*/

      if (--incremento4<0){ incremento4=0; }
      myservoPatitas[3].write(patitas[3]+incremento4+20);
      myservoRodillas[3].write(rodillas[3]-incremento4*2);
      if (++incremento3>10){ incremento3=10; }
      myservoHombritos[2].write(hombritos[2]+(incremento3*7)-20);
      myservoPatitas[2].write(patitas[2]-incremento3);
      myservoRodillas[2].write(rodillas[2]+incremento3*2);
      
     }
    if(fps>=130){
      /*if (--incremento4<0){ incremento4=0; }
      myservoPatitas[3].write(patitas[3]+incremento4);
      myservoRodillas[3].write(rodillas[3]-incremento4*2);
      if (++incremento5>10){ incremento5=10; }
      myservoHombritos[1].write(hombritos[1]+(incremento5*7)+90); 
      myservoPatitas[1].write(patitas[1]+incremento5);
      myservoRodillas[1].write(rodillas[1]-incremento5*2); */

      if (--incremento3<0){ incremento3=0; }  
      myservoPatitas[2].write(patitas[2]-incremento3);
      myservoRodillas[2].write(rodillas[2]+incremento3*2);
      if (++incremento2>10){ incremento2=10; }
      myservoHombritos[0].write(hombritos[0]+(incremento2*7)-50);
      myservoPatitas[0].write(patitas[0]+incremento2-20);
      myservoRodillas[0].write(rodillas[0]-incremento2*2);
         
    }
    if(fps==149){
      /*if (--incremento5<0){ incremento5=0; }
       myservoPatitas[1].write(patitas[1]+incremento5);
       myservoRodillas[1].write(rodillas[1]-incremento5*2); */

      if (--incremento2<0){ incremento2=0; } 
      myservoPatitas[0].write(patitas[0]+incremento2-20);
      myservoRodillas[0].write(rodillas[0]-incremento2*2);
      
    }
    delay(velocidad);
  } 
}

void reposo() {
  myservoHombritos[0].attach(10);
  myservoHombritos[0].write(hombritos[0]);
  myservoHombritos[1].attach(11);
  myservoHombritos[1].write(hombritos[1]);
  myservoHombritos[2].attach(12);
  myservoHombritos[2].write(hombritos[2]);
  myservoHombritos[3].attach(13);
  myservoHombritos[3].write(hombritos[3]);
  
  myservoRodillas[0].attach(2);
  myservoRodillas[0].write(rodillas[0]);
  myservoRodillas[1].attach(3);
  myservoRodillas[1].write(rodillas[1]);
  myservoRodillas[2].attach(4);
  myservoRodillas[2].write(rodillas[2]);
  myservoRodillas[3].attach(5);
  myservoRodillas[3].write(rodillas[3]);

  myservoPatitas[0].attach(6);
  myservoPatitas[0].write(patitas[0]);
  myservoPatitas[1].attach(7);
  myservoPatitas[1].write(patitas[1]);
  myservoPatitas[2].attach(8);
  myservoPatitas[2].write(patitas[2]);
  myservoPatitas[3].attach(9);
  myservoPatitas[3].write(patitas[3]);
}
