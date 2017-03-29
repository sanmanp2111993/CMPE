
#include<iostream>
#include<math.h>
#include<time.h>
#include<stdlib.h>


using namespace std;

// Main Function

int main()
{   int t,t1,t2,comparision,swap;
    int t3,t4,t5,t6,t7,t8;
    double time,time1;
    char ch;
    do
    {
        int n;
        cout<<"Enter the no. of elements in the array"<<endl;
        cin>>n;//Entering the total number of elements
        int a[n];
        cout<<"Loading the array with elements"<<endl;
        for(int i=1;i<=n;i++)
        {
            a[i]=rand()%10000;// Entering the elements in the array using random function
        }
        cout<<endl;
        cout<<endl;
        cout<<"Arrangement of elements before sorting "<<endl;
        
        for(int k=1;k<=n;k++)
        {
            cout<<a[k]<<"  "; // Displaying the array elements before sorting.
        }
        int l,i,j;
        t1=clock(); 
        for(j=2;j<=n;j++)
        {
            l=a[j];
            i=j-1;
            t6=clock();
            comparision++;// variable for counting total number of comparison.
            while((i>0)&&(a[i]>l))
            {
                
              
                t3=clock(); 
                a[i+1]=a[i];
                t4=clock();
                i=i-1;
                swap++;// variable for counting total number of swaps.
                t5=t4-t3;
                time=time+((double)t5/CLOCKS_PER_SEC)*1000;
                comparision++;// variable for counting the total number of comparison.
            }
           
            t7=clock();
            t8=t7-t6;
            time1=time1 + ((double)t8/CLOCKS_PER_SEC)*1000;
            a[i+1]=l;
        }
        t2=clock();
        t=t2-t1;
        double duration;
        duration=((double)t/CLOCKS_PER_SEC)*1000;// Finding the Execution time of function in Milliseconds.
	cout<<endl;
	cout<<endl;	

	cout<<"Sorting time in milliseconds: "<<duration<<endl;
       
        cout<<endl;
        cout<<endl;
        cout<<"Arrangement of elements post sorting"<<endl;
        
        for(int k=1;k<=n;k++)
        {
            cout<<a[k]<<"  ";
        }
        
        cout<<endl;
        
        
        cout<<"Number of Comparisons made: "<<comparision<<endl;
        cout<<"Number of Swaps made: "<<swap<<endl;
        cout<<"Execution time required for Swapping "<<time<<endl;
        cout<<"Execution time for Comparisons "<<time1<<endl;
        cout<<endl<<"Press 'y' or 'Y' to continue: ";
        cin>>ch;
        comparision=0;
        swap=0;
    }
	while(ch=='y'||ch=='Y');
    
    return 0;
    
}
