#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include <unistd.h>
int main()
{ 
	int freq = 50;
	int m=0;
	m = accread();   
	if (m < 0)
	{
		printf("accread failed\n");
	}
	
	m = magread(); 
	if (m < 0)
	{
		printf("magread failed\n");
	}
	
	open_buzzer();
	set_buzzer_freq(freq);
	 sleep(10);
	    return 0;
         
}
