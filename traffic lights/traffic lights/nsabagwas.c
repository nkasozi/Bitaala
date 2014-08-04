/*
Group members
Nsubuga Kasozi 	        10/u/1246		210000261
Kinyera Kenneth Douglas 10/u/9280/PS		210009102
Kasoma Fredrick 	10/u/9252/PS		210019190
Ahimbisibwe Dan 	10/u/9174/PS		210012141 

*/


#include <reg52.h>

//traffic light 1 pins
sbit red_light_1=P2^3;
sbit orange_light_1=P2^4;
sbit green_light_1=P2^5;

//traffic light 2 pins
sbit red_light_2=P2^6;
sbit orange_light_2=P2^7;
sbit green_light_2=P3^0;

//traffic light 3 pins
sbit red_light_3=P3^4;
sbit orange_light_3=P3^5;
sbit green_light_3=P3^6;

//keypad variables
sbit keypad_number1=P1^1;
sbit keypad_number2=P1^2;
sbit keypad_number3=P1^3;
sbit keypad_row1=P1^0;
sbit keypad_row2=P1^4;

//LCD variables
sbit rw=P2^1;
sbit rs=P2^0;
sbit en=P2^2;

//LDR variables
sbit ldr_pin=P1^4;

//indicates whose turn it is
int number_representing_whose_turn_it_is=1;
int number1_pressed= 0;
int number2_pressed= 0;
int number3_pressed= 0;
int number4_pressed= 0;
int number5_pressed= 0;
int number6_pressed= 0;
int returning_from_interrupt=0;
int it_is_first_time=1;


//creates a millis second delay
void delay()
{
   int i;
   for(i=0;i<=2000;i++);
}


//sets lcd enable bit  low then high
void toggleEnablePin()
{
 en=0;
 delay();
 en=1;
 delay();
}

//sets the line to which lcd writes
void setline()
{
    rs=0;
    rw=0;
    P0=0x80;
    toggleEnablePin();
    rs=1;
}
//tells user that interrupt has been recieved
void sendInterruptMessage()
{
  int j;
   char msg []="SWITCHING...";
   char *msg_address;
   setline();
   msg_address=&msg;
   for(j=1;j<=16;j++)
   {
     P0=*msg_address++;
     toggleEnablePin();
   }
}
//sends data to lcd
void sendData2Lcd()
{
  if(it_is_first_time==1)
  {
   int j;
   char msg []="Kisobookaahh!!! software";
   char *msg_address;
   setline();
   msg_address=&msg;
   for(j=1;j<=32;j++)
   {
     P0=*msg_address++;
     toggleEnablePin();
   }
  }
  else
  {
    if(number_representing_whose_turn_it_is==1)
    {
      int j;
      char msg []="Rd 1 and 2 GO!!";
      char *msg_address;
      setline();
      msg_address=&msg;
      for(j=1;j<=16;j++)
      {
       P0=*msg_address++;
       toggleEnablePin();
      }
    }
     else if(number_representing_whose_turn_it_is==2)
    {
      int j;
      char msg []="Rd 3 and 4 GO!!";
      char *msg_address;
      setline();
      msg_address=&msg;
      for(j=1;j<=16;j++)
      {
       P0=*msg_address++;
       toggleEnablePin();
      }
    }
    else if(number_representing_whose_turn_it_is==3)
    {
      int j;
      char msg []="Rd 5 and 6 GO!!";
      char *msg_address;
      setline();
      msg_address=&msg;
      for(j=1;j<=16;j++)
      {
       P0=*msg_address++;
       toggleEnablePin();
      }
  } 
  }

}

 //creates a delay 4 the given number of seconds
void delay4TheseSeconds(int number_of_seconds)
{
     int i,j;
     int number_of_times_to_loop=number_of_seconds*2*10;
     for(i=0;i<=number_of_times_to_loop;i++)
     {
        if(returning_from_interrupt==1) 
        {
            break;
        }
        for(j=0;j<=10000;j++);   
     }
     return;
    
}

//changes whose turn it is to move to point to the next road in sequence to move
void point2NextRoadToMove()
{
 if(number_representing_whose_turn_it_is==1) 
 {
   number_representing_whose_turn_it_is=2;
   return;
 }
 if(number_representing_whose_turn_it_is==2) 
 {
   number_representing_whose_turn_it_is=3;
   return;
 }
 if(number_representing_whose_turn_it_is==3) 
 {
   number_representing_whose_turn_it_is=1;
   return;
 }
}


//checks to see if number 1 is pressed on keypad
int checkIf1IsPressed()
{
  keypad_row1=0;
  keypad_row2=1;
  if(keypad_number1==0) 
  {
   delay4TheseSeconds(1);
   return 1;
  }
  return 0;
}
//checks to see if number 2 is pressed on keypad
int checkIf2IsPressed()
{
  keypad_row1=0;
  keypad_row2=1;
  if(keypad_number2==0) 
  {
   delay4TheseSeconds(1);
   return 2;
  }
  return 0;
}


//sees if number 3 is pressed on keypad
int checkIf3IsPressed()
{
  keypad_row1=0;
  keypad_row2=1;
  if(keypad_number3==0) 
  {
   delay4TheseSeconds(1);
   return 3;
  }
  return 0;
}


//sees if number 4 is pressed on keypad
int checkIf4IsPressed()
{
  keypad_row1=1;
  keypad_row2=0;
  if(keypad_number1==0) 
  {
   delay4TheseSeconds(1);
   return 4;
  }
  return 0;
}


//sees if number 5 is pressed on keypad
int checkIf5IsPressed()
{
  keypad_row1=1;
  keypad_row2=0;
  if(keypad_number2==0) 
  {
   delay4TheseSeconds(1);
   return 5;
  }
  return 0;
}


//sees if number 6 is pressed on keypad
int checkIf6IsPressed()
{
  keypad_row1=1;
  keypad_row2=0;
  if(keypad_number3==0) 
  {
   delay4TheseSeconds(1);
   return 6;
  }
  return 0;
}


//turns traffic light orange 4 4secs and then red 4 1 sec immediately
void turnLight2Orange()
{
 red_light_2=0;
 orange_light_2=1;
 green_light_2=0;
 delay4TheseSeconds(4);
 red_light_2=1;
 orange_light_2=0;
 green_light_2=0;
 delay4TheseSeconds(1);
}


//turns traffic light 1 orange 4 4secs and then red 4 1 sec immediately
void turnLight1Orange()
{
 red_light_1=0;
 orange_light_1=1;
 green_light_1=0;
 delay4TheseSeconds(4);
 red_light_1=1;
 orange_light_1=0;
 green_light_1=0;
 delay4TheseSeconds(1);
}

//turns traffic light  3 orange 4 4secs and then red 4 1 sec immediately
void turnLight3Orange()
{
 red_light_3=0;
 orange_light_3=1;
 green_light_3=0;
 delay4TheseSeconds(4);
 red_light_3=1;
 orange_light_3=0;
 green_light_3=0;
 delay4TheseSeconds(1);
}

//makes the currently lighting traffic light go orange then red
void makeCurrentLightGoToOrange()
{
 if(number_representing_whose_turn_it_is==1)
 {
    turnLight1Orange();
    return;
 }
 else if(number_representing_whose_turn_it_is==2) 
 {
    turnLight2Orange();
    return;
 }
 else if(number_representing_whose_turn_it_is==3) 
 {
    turnLight3Orange();
    return;
 }

}

//turns on traffic light 1 to green orange and then red
void TurnOnTrafficLightOne()
{
  number_representing_whose_turn_it_is=1;
  sendData2Lcd();
  red_light_1=0;
  orange_light_1=0;
  green_light_1=1;
  delay4TheseSeconds(10);
  
  red_light_1=0;
  orange_light_1=1;
  green_light_1=0;
  delay4TheseSeconds(3);
   
  red_light_1=1;
  orange_light_1=0;
  green_light_1=0;
  delay4TheseSeconds(1);
   

}

//turns on traffic light 2 to green orange and then red
void TurnOnTrafficLightTwo()
{
  number_representing_whose_turn_it_is=2;
  sendData2Lcd();
  red_light_2=0;
  orange_light_2=0;
  green_light_2=1;
  delay4TheseSeconds(10);
   
  red_light_2=0;
  orange_light_2=1;
  green_light_2=0;
  delay4TheseSeconds(3);
   
  red_light_2=1;
  orange_light_2=0;
  green_light_2=0;
  delay4TheseSeconds(1);
   

}

 //turns on traffic light 3 to green orange and then red
void TurnOnTrafficLightThree()
{
  number_representing_whose_turn_it_is=3;
  sendData2Lcd();
  red_light_3=0;
  orange_light_3=0;
  green_light_3=1;
  delay4TheseSeconds(10);
    
  red_light_3=0;
  orange_light_3=1;
  green_light_3=0;
  delay4TheseSeconds(3);
   
  red_light_3=1;
  orange_light_3=0;
  green_light_3=0;
  delay4TheseSeconds(1);
    

}

//interrupt handler for external interrupt 0
void externalInterrupt0(void) interrupt 0 
{
  EA=0; //disable  interrupts and then handle this one
  EX0=0;
  
  
  number1_pressed=checkIf1IsPressed();
  number2_pressed=checkIf2IsPressed();
  number3_pressed=checkIf3IsPressed();
  number4_pressed=checkIf4IsPressed();
  number5_pressed=checkIf5IsPressed();
  number6_pressed=checkIf6IsPressed();
  sendInterruptMessage();
  makeCurrentLightGoToOrange();

  if(number1_pressed==1||number2_pressed==2)
  {
      TurnOnTrafficLightOne();
  }
  else if(number3_pressed==3||number4_pressed==4)
  {
    TurnOnTrafficLightTwo();
  }
  else 
  {
    TurnOnTrafficLightThree();
  }
  returning_from_interrupt=1;//inform main that an interrupt occured
  initializeKeypad();//return keypad to original function  
  EA=1;   //enable external interrupt again
  EX0=1;
}

//initializes all traffic lights to be red 
void initializeTrafficLights()
{
   red_light_1=1;
   orange_light_1=0;
   green_light_1=0;

   red_light_2=1;
   orange_light_2=0;
   green_light_2=0;

   red_light_3=1;
   orange_light_3=0;
   green_light_3=0;
}

//sets all key pad to 1 
void initializeKeyPad()
{
 keypad_number1=1;
 keypad_number2=1;
 keypad_number3=1;
 keypad_row1=0;
 keypad_row2=0;

}

//initializes lcd and prepares it to recieve data
void initializeLCD()
{
   delay();
   rs=0;
   rw=0;
   en=0;
   P0 = 0x38;
   toggleEnablePin();
   P0= 0x0F;
   toggleEnablePin();
   toggleEnablePin();
   P0= 0x1c;
   toggleEnablePin();
   toggleEnablePin();
   P0= 0x01;
   toggleEnablePin();

}

 
void main()
{
  

 int power_is_on=1;
 
 EA=1; 
 EX0=1;  //Interrupt enable for ext0
 initializeTrafficLights();
 initializeKeyPad(); 
 initializeLCD();
 
 

 while(power_is_on)
 {
   if(it_is_first_time==1)
   {
     //char msg[16]="MADE by SNK";
     sendData2Lcd();
     delay4TheseSeconds(5);
     it_is_first_time=0;
   }

   if(number_representing_whose_turn_it_is==1)
   {
    TurnOnTrafficLightOne();
    point2NextRoadToMove();
    if(returning_from_interrupt==1)
    {
      returning_from_interrupt=0;  //clear interrupt flag
    }
   }
   if(number_representing_whose_turn_it_is==2)
   {
    TurnOnTrafficLightTwo();
    point2NextRoadToMove();
     if(returning_from_interrupt==1)
    {
      returning_from_interrupt=0;
    }
   }
   if(number_representing_whose_turn_it_is==3)
   {
    TurnOnTrafficLightThree();
    point2NextRoadToMove();
     if(returning_from_interrupt==1)
    {
      returning_from_interrupt=0;
    }
   }

 }

}