/**********************************************************************
* Filename    : rotaryEncoder.c
* Description : make a rotaryEncoder work.
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Date        : 2014/08/27
**********************************************************************/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>

int RoAPin = 0;
int RoBPin = 1;
int RoSPin = 2;

static volatile int globalCounter = 0 ;
volatile int lastEncoded_left = 0;

unsigned char flag;
unsigned char Last_RoB_Status;
unsigned char Current_RoB_Status;

void rotaryDeal(void)
{
  printf("\n inside rotarydeal \n");
  int MSB_left = digitalRead(RoAPin); //MSB = most significant bit
  int LSB_left = digitalRead(RoBPin); //LSB = least significant bit

  printf("\n msb is %d and lsb is %d \n", MSB_left, LSB_left);

  int encoded_left = (MSB_left << 1) |LSB_left; //converting the 2 pin value to single number
  int sum_left  = (lastEncoded_left << 2) | encoded_left; //adding it to the previous encoded value
  
  printf("\n encoded is %d and sum is %d \n", encoded_left, sum_left);

  if(sum_left == 0b1101 || sum_left == 0b0100 || sum_left == 0b0010 || sum_left == 0b1011) globalCounter ++;
  if(sum_left == 0b1110 || sum_left == 0b0111 || sum_left == 0b0001 || sum_left == 0b1000) globalCounter --;
  printf("\n globalCounter : %d\n",globalCounter);
 
  lastEncoded_left = encoded_left;
  //store this value for next time
}

void rotaryClear(void)
{
	if(digitalRead(RoSPin) == 0)
	{
		globalCounter = 0;
		printf("globalCounter : %d\n",globalCounter);
		delay(1000);
	}
}

int main(void)
{
  	printf("\n inside main \n");
	if(wiringPiSetup() < 0){
		fprintf(stderr, "Unable to setup wiringPi:%s\n",strerror(errno));
		return 1;
	}

	pinMode(RoAPin, INPUT);
	pinMode(RoBPin, INPUT);
	pinMode(RoSPin, INPUT);

	pullUpDnControl(RoSPin, PUD_UP);

	while(1){

       		printf("\n inside while loop in main loop \n");
		rotaryDeal();
		rotaryClear();
		delay(1);
	}

	return 0;
}