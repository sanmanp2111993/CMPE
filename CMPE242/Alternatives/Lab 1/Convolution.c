#include<math.h>
#include<stdio.h>
#include<stdlib.h>

int d[25]={1.1,1.1,1.1,3.9,4.12,5.13,4.03,3.2,4.75,6.3,11.42,1.5,-1.3,2.2,-1.35,-1.78,-3.2,-4.38,0.22,1.23,1.23,1.23,1.3,1.5,1.77};

float ComputeGaussianKernel(const int sigma, const float inWeight)
{
    //float* gkernel = (float*)malloc(mem_amount*sizeof(float));
    float c,y;
	int x,j;
    float gkernel[3];
    float a = (2.0 * sigma * sigma);
    float sqrtTwoPiTimesRadius = 1.0 / (sqrt(2.0 *M_PI) * sigma);
    float radiusModifier = inWeight;

    // Create Gaussian Kernel
    for (x = -1; x <= 1; x++)
    {
		y = x*x;
		gkernel[x+1] = sqrtTwoPiTimesRadius*(exp(-y/(a)));
		printf("Kernel is : %0.2f\n",gkernel[x+1]);
    }
    
    for(j=0; j < (25-1) ; j++)
    {
		c = gkernel[0]*d[j] + gkernel[1]*d[j+1] + gkernel[2]*d[j+2];
		printf("\n%f", c);
	}	
    
    return (0);
}

int main(){
               
          int sigma = 1.8;
          int inWeight;
           ComputeGaussianKernel(sigma,inWeight);
}
