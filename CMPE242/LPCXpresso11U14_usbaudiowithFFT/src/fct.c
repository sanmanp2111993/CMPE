/*----------------------------------------------------------------------------
 * Name:    fct.c
 * Purpose: Fast Cosine Transform (FCT) Processing - 64 points
 * Author : A Surya Cahyadi (Cahyadi.Surya@FotisInc.com)
 * Version: V1.00
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC microcontroller devices only. Nothing else
 *      gives you the right to use this software.
 *
 * Copyright (c) 2011 Fotis Inc - Engineering Technology.  All rights reserved.
 *---------------------------------------------------------------------------*/

#define COS_PREC 7
#define COM_PREC 0
#define DATA_PREC  2
#define N 64
#define M 6 // M=log2N

extern signed int ct[];
signed int temp[N];

void pre_align_f(signed int *);
void P_FCT_f(void);
void post_add_f(signed int *);
int bit_reserve_f(int ip);

void FCT_fixed(int * x, int *y)
{
	pre_align_f(x);
	P_FCT_f();
    post_add_f(y);
}



int bit_reserve_f(int ip)
{
	int op = 0;
	int i;

	for (i=0;i<M;i++)
	{
		if (((ip>>i)&0x1)==0x1) 
			op |= (1 <<(M-i-1)); 
	}
	
	return op;

}

void pre_align_f(int * x)
{
	int i;
	signed int idx;
	signed int work[N];
	
	// even and odd order mapping
	for (i=0;i<N/2;i++)
	{
		work[i] = x[2*i] >> DATA_PREC;
		work[N-i-1] = x[2*i+1] >> DATA_PREC;
	}

	//bit-reversal mapping
	
	for (i=0;i<N;i++)
	{
		idx = bit_reserve_f(i);
		temp[i] = (work[idx] <<COM_PREC);
	}		
}


void P_FCT_f()
{
	/* Input parameters: N. NO, m, xu, ctU */
	/* Output parameters: xu */
	unsigned int i,j,k,l,p,Bs,bB,bls,ble;
	signed int a,c;

	Bs = N; bB = bls = 1; p = 0;
	
	for(k=0; k<M; k++) /* Go through all stages */
	{
		Bs=Bs>>1;  ble=0; bls=bls<<1;

		for(j=0; j<Bs; j++) /* Go through all blocks of butteflies */
		{
			l=ble; c=ct[p]; p++;
			for(i=0; i<bB; i++) // Calculate the complete butterflies 
			{
				a=temp[l];
				temp[l]   += temp[l+bB];
				temp[l+bB] =((a-temp[l+bB])*c )>>COS_PREC;
				l++;
			}
			ble +=bls;
		}
		bB=bB<<1;
	}
}

void post_add_f(signed int * y)
{
	/* Input parameters: N, NO, m. XI]*/
	/* Output parameters: xu */

	unsigned int i, j, k, l, s, ep, loops;

	s=N; loops=1;


	for (k=1; k<M; k++) /* Go through the m-1 stages */
	{
		s=s>>1; ep=s>>1; loops=loops<<1;
		for(j=0; j<(s>>1); j++ ) /* Groups per stage */
		{
			l = ep;
			for(i=1; i<loops; i++) /* Required additions per group */
			{
				temp[l+s] -= temp[l];
				l +=s;
			}
			ep++;
		}
	}

	y[0] = temp[0]>>COM_PREC;

	for (j=1; j<N; j++) 
	{
		y[j] = temp[j]>>(COM_PREC+1);
	}

}
