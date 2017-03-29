// selection sorting


#include<iostream>
#include<cstdlib>
#include<time.h>


using namespace std ;

int count,count1;
double dur6,dur9,dur50,dur75;
void printArray(int array[], int size); // print function declaration
void sortDescending ( int array[], int size ); // ascending order function declaration
void sortAscending ( int array[], int size ); // descending order function declaration
int n;

int main ()  // main function
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
    cout <<"The elements in the list are ";
    printArray(array, n);
    cout<< "Enter 'A'/'a' for ascending order or 'D'/'d' for descending order: ";
    char ans;
    cin >> ans;

if ( (ans == 'a')|| (ans == 'A'))
{
	cout <<"Sorting in Ascending order.......... " << endl;
	cout <<"Original array: "<<endl;
	printArray(array, n);	
	int t1 = clock();
	sortAscending(array, n);// call to ascending function
	int t2=clock(); //
	double timetaken= t2-t1; // time calculation for ascending sorting
	double dur2 = ((double)timetaken/CLOCKS_PER_SEC)*1000; 
	cout <<"The time taken is: "<<dur2<<" Milliseconds"<<endl;
	cout <<"Sorted array: "<<endl;
	printArray(array, n);
	cout<<"Number of comparisions made: "<<count++<<endl;
	cout<<"Execution Time taken for Ascending Order comparisions: "<<endl;
	cout<<dur9<<endl;
	cout<<"Number of swaps made: "<<count1++<<endl;
	cout<<"Time taken for Ascending Order swaps: "<<endl;
	cout<<dur50<<endl;

}
else if (( ans == 'd')||( ans == 'D'))
{
	cout <<"Sorting in descending order: " << endl;
	cout <<"Original array:\t";
	printArray(array, n);
	int t3=clock();
	sortDescending(array, n); // call to descending function
	int t4=clock();
	double timetaken1= t4-t3; // time calculation for descending fuction.
	double dur1 = dur1 + ((double)timetaken1/CLOCKS_PER_SEC)*1000;
	cout<<"The time taken is: "<<dur1<<" Milliseconds"<<endl;
	cout <<"Sorted array: ";
	printArray(array, n);
	cout<<"Number of comparisions made: "<<count++<<endl;
        cout<<"Time taken for Descending comparisions: "<<endl;
	cout<<dur6<<endl;
	cout<<"Number of swaps made: "<<count1++<<endl;
	cout<<"Time taken for Descending swaps: "<<endl;
	cout<<dur75<<endl;

}
else
{
	cout<<"Invalid input"<< endl;
}
    return 0;
}


void printArray(int array[], int size) // print array function definition 
    {
    for ( int i = 0; i < size; i++ ) {
        cout << array[i] << ' ';
    }
    cout<<endl;
}

void sortAscending ( int array[], int size ) // ascending order function definition
    {
    int maxIndx = 0, temp = 0, indx = 0;
 for ( indx = maxIndx; indx < size; indx++ ) 
	{       int t7=clock();
        	if ( array[indx] > array[maxIndx] ) 
	{       
		 
	        count++;
            	maxIndx = indx;
		continue;
		
        }
	 count++;
       	 int t8=clock();
	 double timetaken4 = t8-t7; // time calculation for descending fuction.
	 double dur9 = dur9 + ((double)timetaken4/CLOCKS_PER_SEC)*1000;
    }
	
    int t20=clock();
    temp = array[size-1];
    array[size-1] = array[maxIndx];
    array[maxIndx] = temp;
    int t30=clock();
    double timetaken15 = t30-t20; // time calculation for descending fuction.
    double dur50 = dur50 + ((double)timetaken15/CLOCKS_PER_SEC)*1000;
	
    if ( size > 1 ) {
        sortAscending ( array, --size ) ;
	count1++;
    }

}

void sortDescending ( int array[], int size ) // descending order function definition 
    {
    int maxIndx = 0, temp = 0, indx = 0;
    for ( indx = maxIndx; indx < size; indx++ ) 
	{ int t10=clock();
        if ( array[indx] < array[maxIndx] )
	 {
	    count++;
            maxIndx = indx;
	    continue;
        }
	count++;
	int t11=clock();
	double timetaken5 = t11-t10; // time calculation for descending fuction.
	double dur6 = dur6 + ((double)timetaken5/CLOCKS_PER_SEC)*1000;
    }
    int t60=clock();
    temp = array[size-1];
    array[size-1] = array[maxIndx];
    array[maxIndx] = temp;
    int t70=clock();
    double timetaken18 = t70-t60; // time calculation for descending fuction.
    double dur75 = dur75 + ((double)timetaken18/CLOCKS_PER_SEC)*1000;
    if ( size > 1 ) 
    {
        sortDescending ( array, --size ) ;
	count1++;
    }

}

