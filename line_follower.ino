
#include<Servo.h> 

const int vel=58;     //adjust here
const int lift=65;
const float turn=0.35;
int flag=1;
int k=vel,a,b,c;
Servo escr;
Servo escl;
Servo escm; 

void setup() 
{
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A0,INPUT); 
  pinMode(A5,INPUT);  
 
  escr.attach(11,1000,2000);
  escl.attach(9,1000,2000);
  escm.attach(10,1000,2000);
  
  for (int i=40;i>0;i--)
  { escr.write(i);
    escl.write(i);
    escm.write(i);}
    delay(10000);
  
  int j=15;
  while (j<lift)
{  
  escm.write(j);
  delay(200); 
  j++;
}
  escr.write(k);//needed because initially if all sens are on then it wont start
  escl.write(k);
}

void off()
{ escr.write(0);escl.write(0);
  while(analogRead(A4)>30){;}
  if(flag==1){ escr.write(k);escl.write(k); }
  if(flag==2){ escr.write(k-turn*k);escl.write(k+turn*k);}
  if(flag==3){ escl.write(k-turn*k);escr.write(k+turn*k);}     } 


void loop() 
{ 
  if(analogRead(A4)>30) off();
 
  a=digitalRead(A0);// Serial.println('a');Serial.println(a);//right side
  b=digitalRead(A1);// Serial.println('b');Serial.println(b);//middle sensor
  c=digitalRead(A2);// Serial.println('c');Serial.println(c);//left side
 
  //if(b||d) { b=1;} else {b=0;} Serial.println('b');Serial.println(b);
  if(a&&!b&&c) { flag=1; escr.write(k);escl.write(k);// Serial.println("going straight");
                } 
  if(!a&&b&&c) { flag=2; escr.write(k-turn*k);escl.write(k+turn*k);// Serial.println("turning right");
                } 
  if(a&&b&&!c) { flag=3; escr.write(k+turn*k);escl.write(k-turn*k);// Serial.println("turning left");
                } 
}
