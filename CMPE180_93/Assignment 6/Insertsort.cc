 
 
// insertion sorting .
#include <cstdlib>
#include <iostream>
#include<ctime>
#include<unistd.h>
//#include<time.h>
//#include<dos>
#include<stdlib.h>

using namespace std;


void print_array(int array[], int size);
void insertion_sort(int array[], int length);


double dur75,dur1,dur20;
int n,count1,count;

int main()
{

	int num;  
	cout<<"Enter '1' for 100 element array "<<endl;
	cout<<"Enter '2' for 1000 element array"<<endl;
	cout<<"Enter '3' for 10000 element array"<<endl;
	cout<<"Enter Option: "; 
	cin >> num;
	cout<<"You entered: "<<num<< endl;



switch(num)
{
	case 1:
    	n=100;
    	break;
	
	case 2:
    	n=1000;
    	break;
	
	case 3:
    	n=10000;
    	break;
	
	default :
  	n=10;
}
int array[n];
for (int i=0; i<n;i++)
    {
    	array[i]=rand()%n+1;
    }
    cout<<"The elements in the list are: ";
    print_array(array, n);

	int t1=clock();
	insertion_sort(array,n);
	int t2=clock();
	double timetaken =t2-t1;
	double dur1 = dur1 + ((double)timetaken/CLOCKS_PER_SEC)*1000;
	cout<<"The time taken is: " <<dur1<<" Milliseconds"<<endl;
	cout<<"Number of comparisions made: "<<count++<<endl;
	cout<<"Execution time for comparison "<<endl;
        cout<<dur75<<endl;
	cout<<"Number of swaps made: "<<count1++<<endl;
	cout<<"Execution time for swapping "<<endl;
       	cout<<dur20<<endl;
	

 
 return 0;
}//end of main


void insertion_sort(int array[], int length)
 {
 	int i, j ,temp;
 	for (i = 1; i < length; i++) 
	{
		 j = i;
		 int t60=clock();
             
	 	 while (j > 0 && array[j - 1] > array[j]) 
	{        int t70=clock();
   		 double timetaken18 = t70-t60; // time calculation for descending fuction.
   		 double dur75 = dur75 + ((double)timetaken18/CLOCKS_PER_SEC)*1000;  
                
           
                 count++;

		 int t8 = clock();
		 temp = array[j];
		 array[j] = array[j - 1];
		 array[j - 1] = temp;
		 j--;
		 int t9=clock();
   		 double timetaken11 = t9-t8; // time calculation for descending fuction.
   		 double dur20 = dur20 + ((double)timetaken11/CLOCKS_PER_SEC)*1000;
                 
		 count1++;
	 }
	count++;	//end of while loop

      
 }//end of for loop
	cout<<"Sorted Elements: "<<endl;
	print_array(array,n);
 }//end of insertion_sort.

void print_array(int array[], int size)
{
	 int j;
	 for (j=0; j<size;j++)
	 for (j=0; j<size;j++)
	 cout <<" "<< array[j];
	 cout << endl;
 }//end of print_array
