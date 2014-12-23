#include <LiquidCrystal.h>
char in=0;
int i=0;
int z=0;

//setting up LCD using the LiquidCrystal library
LiquidCrystal lcd(2,3,4,5,6,7);

//motor pins
int m1=8;
int m2=9;
int m3=10;
int m4=11;

void setup()
{
//setting up motor pins as output
pinMode(m1,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(m3,OUTPUT);
pinMode(m4,OUTPUT);

//defining an lcd of 16*2
lcd.begin(16, 2);

//starting serial link
Serial.begin(115200);
}

/*the wires might have gotten interchanged a little so fiddle around with which pin goes high when to get the
proper code for movement in any direction*/
//function for forward movement
void forward()
{
digitalWrite(m1,HIGH);
digitalWrite(m4,HIGH);
digitalWrite(m2,LOW);
digitalWrite(m3,LOW);
}

//function for backward movement
void backward()
{
digitalWrite(m1,LOW);
digitalWrite(m4,LOW);
digitalWrite(m2,HIGH);
digitalWrite(m3,HIGH);
}

//function for turning left on its axis
void left()
{
digitalWrite(m1,LOW);
digitalWrite(m4,HIGH);
digitalWrite(m2,HIGH);
digitalWrite(m3,LOW);
}

//function for turning right on its axis
void right()
{
digitalWrite(m1,HIGH);
digitalWrite(m4,LOW);
digitalWrite(m2,LOW);
digitalWrite(m3,HIGH);
}

//function for stopping all motion
void stop1()
{
digitalWrite(m1,LOW);
digitalWrite(m4,LOW);
digitalWrite(m2,LOW);
digitalWrite(m3,LOW);
}

void move_code(char x)
{
if(x=='w')
forward();
else if(x=='x')
backward();
else if(x=='a')
left();
else if(x=='d')
right();
else if(x=='s')
stop1();
}

//function for displaying message while in motion and controlling the movement of bot
void display_move()
{
if(z==0)
{
lcd.clear();
lcd.print("Moving....");
z++;
}
if(Serial.available())
{
in=Serial.read();
if(in=='w'||in=='s'||in=='a'||in=='d'||in=='x')
move_code(in);
else if(in=='%')
lcd_display();
else
{
lcd.clear();
lcd.print("You typed shit..");
delay(3000);
z=0;
}
}
}

//function for displaying message typed
void lcd_display()
{
lcd.clear();
stop1();
in=0;
i=0;
lcd.cursor();
while(in!='%')
{
if(i>32)
{
lcd.clear();
i=0;
}

if (Serial.available())
{
char in=Serial.read();
i++;
if(i>16&&i<=32&&in!='%')
{
lcd.setCursor((i-17),1);
lcd.print(in);
}
else if(in=='%')
{
z=0;
in=0;
break;
}
else
lcd.print(in);
}
}
}

//main function
void loop()
{
display_move();
}
