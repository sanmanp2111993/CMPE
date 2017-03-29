/************************************************************
 * Program: vehicleModel.c                                  *  
 * Date: Mar 10, 2016                                       *
 * HL                       Status: debug                   *  
 * Version: x0.1;                                           * 
 * Purpose:                                                 *
 *    Buid vehicle model                                    *  
 ************************************************************/ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793238462643
#define dataSize  512  
FILE* rd;     //input data file 

/*--------------------define vehicle-------------*/  
#define vehicleLength 3.5  //meter  
#define vehicleWidth  2.5  

/*              define struct                    */ 
typedef struct
{
float WHLSTR_angle;          //wheelsteeringAngle1;   
float WHLSTR_torque;         //wheel steering torque;   
float WHLSEN_angle;          //wheelsensorAngle1;   
float VHCSPD;                //vehicle Speed;   
float VHCACC;                //vehicle acceleration;   
int   VHCSPD_index;          //vehicle speed index;  
int   VHCSTR_torqueIndex;    //vehicle speed index;  
float WHLPWM_angle;          //f_pwm1_angle;   
float WHLPWM_speed;          //f_pwm2_speed;   
float TIMSTM1;               //input action time stamp;  
float TIMSTM2;               //input completion time stamp;  
} VEHICLE_STRUCT; 

void vehicleModel( VEHICLE_STRUCT *);  // subroutine prototype 
 
int    i, j, k, kernelSize; 
float  x_buffer[dataSize];  
double sigma; 

/*------------------------------------------------*
    main program 
 *------------------------------------------------*/ 
int main(void)
{

   VEHICLE_STRUCT vehicle_struct; 

   printf("Vehicle model\n"); 

   vehicle_struct.WHLSTR_angle = 0.0;       //init wheelsteeringAngle     
   vehicle_struct.WHLSEN_angle = 0.01;      //init wheelsensorAngle      
   vehicle_struct.VHCSPD = 0.0;             //init vehicle Speed;   
   vehicle_struct.WHLPWM_angle = 0.0;       //init pwm1_angle;   
   vehicle_struct.WHLPWM_speed = 50.0;      //init pwm2_speed;   
   vehicle_struct.VHCACC = 2.1;             //vehicle acceleration;   
   vehicle_struct.TIMSTM1 = 0.0;            //init input action time stamp;  
   vehicle_struct.TIMSTM2 = 0.0;            //init input completion time stamp;  

   /*
   printf("Please enter wheel steering angle \n"); 
   scanf("%f", &vehicle_struct.WHLSTR_angle);
   printf("WHLSTR_angle = %f\n", vehicle_struct.WHLSTR_angle);
   */ 
 
   printf("Read WHLSEN_angle from LSM303 \n"); 
   // add the sensor read input here 
   vehicle_struct.WHLSEN_angle = 0.01;      // assume this value for now  

   printf("Please enter acceleration \n"); 
   printf("1. slow \n"); 
   printf("2. medium slow \n"); 
   printf("3. average \n"); 
   printf("4. fast \n"); 
   printf("5. very fast \n"); 
   scanf("%d", &vehicle_struct.VHCSPD_index);
   printf("you speed index entered : %d\n", vehicle_struct.VHCSPD_index);

   //speed index translate to PWM
   //PWM translate to torque, and torque translate to wheel speed 

   vehicle_struct.WHLPWM_speed = 500.0/vehicle_struct.VHCSPD_index;       
   vehicle_struct.TIMSTM2 = vehicle_struct.TIMSTM1 + 0.01;                    //response time 10 mSec  
   //vehicle_struct.VHCSPD =  vehicle_struct.VHCACC * vehicle_struct.TIMSTM2 
   //                           * vehicle_struct.TIMSTM2 * 0.5;  //t square time one half acceleration   
   printf("vehicle_struct.WHLPWM_speed : %f\n", vehicle_struct.WHLPWM_speed);

   printf("Please enter steering torque \n"); 
   printf("1. small \n"); 
   printf("2. medium slow \n"); 
   printf("3. average \n"); 
   printf("4. big \n"); 
   printf("5. very big \n"); 
   scanf("%d", &vehicle_struct.VHCSTR_torqueIndex);
   printf("your torque index entered : %d\n", vehicle_struct.VHCSTR_torqueIndex);
   //vehicle_struct.WHLSTR_torque = 500.0/vehicle_struct.VHCSTR_torqueIndex;         //wheel steering torque;   
   //torque translate to PWM
   //PWM translate to angle per unit time
 
  /*----------------------------------------------   
   call the vehicle module  
    ----------------------------------------------*/
   vehicleModel( &vehicle_struct );  
   
   return 0; 
} 

/*--------------------------------------------------
  Define the subroutine for the vehicle model
  -------------------------------------------------*/ 

void vehicleModel( 
                 VEHICLE_STRUCT *xx   
                 ) 
{
  /*-------------build vehicle model here-----------*/ 
   printf("In the subroutine, xx->VHCSTR_torqueIndex %d\n", xx->VHCSTR_torqueIndex);
} 
