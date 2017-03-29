// quick sort program
#include <iostream>
#include<cstdlib>
#include<ctime>
using namespace std;


	 

void printArray(int* arr, int n); // function declaration 
void qckSort(int* arr, int startIndex, int endIndex);  // function declaration
int divideArray(int* arr, int pivotValue, int startIndex, int endIndex);  // function declaration
void swap(int &a, int &b);  // function declaration

	 
int n,count;
int main(void)   // main function 

{
int num,t1,t2,t; 
    cout<<"Enter '1' for sorting 100 elements"<<endl;
    cout<<"Enter '2' for sorting 1000 elements"<<endl;
    cout<<"Enter '3' for sorting 10000 elements"<<endl;
    cout<<"Enter Option: ";
    cin >> num;
    cout<<"You entered: "<<num<< endl;

switch(num)      // switch case 
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
int arr[n];            // array declaration with random input 
for (int i=0; i<n;i++)
{
arr[i]=rand()%n+1;
}
cout <<"The elements in the list are: "<<endl;
printArray(arr, n);
cout<<endl;
t1=clock();	   
qckSort(arr,0,n-1);
t2=clock();
t=(double)(t2-t1)/CLOCKS_PER_SEC*1000000.0;    
cout<<endl;
cout<<"Sorted list  : "<<endl;

printArray(arr, n);
cout<<endl;
cout<<"Execution time in Microseconds: "<<t<<endl;
cout<<"Number of swaps made: "<<count<<endl; 
 return 0;
}

	 

	
void swap(int &p, int &q)        // swap function 
{
int temp;
temp = p;
p = q;
q = temp;
}

	 

	

void printArray(int* arr, int n)  // print function 
{
int i;
for( i = 0; i < n; i++)
{
cout<<arr[i] << " ";
}
}

	 
void qckSort(int* arr, int startIndex, int endIndex) // sort function
{
int pivot = arr[startIndex];                  
int divPoint;
if(endIndex > startIndex)                      	                                                      
{
divPoint = divideArray(arr, pivot, startIndex, endIndex);                                            
arr[divPoint] = pivot;
qckSort(arr, startIndex, divPoint-1);   
qckSort(arr, divPoint+1, endIndex);    
}	
}

	 
int divideArray(int* arr, int pivot, int startIndex, int endIndex) /* function for splitting the list from the pivot point */
{
int left = startIndex;
int right = endIndex;
while(left < right)             
{
while( pivot < arr[right] && right > left) 
{
right--;               
}
count++;
swap(arr[left], arr[right]);
while( pivot >= arr[left] && left < right)  
 {
left++;                       
 }


 swap(arr[right], arr[left]);
     
}
count++;
return left;  

                           
	}
