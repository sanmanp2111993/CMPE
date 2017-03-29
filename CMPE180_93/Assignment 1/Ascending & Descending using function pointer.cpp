#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
// prototype declarations
int Array(int a[], int maxNumElements);

int showArray(int a[], int numElements);
int main(int nNumberofArgs, char* pszArgs[])
{
    // input the loop count
    cout << "This program sums values entered "
         << "by the user\n";
    cout << "Terminate the loop by entering "
         << "a negative number\n";
    cout << endl;
    // read numbers to be summed from the user into a
    // local array
    int inputValues[100];
    int numberOfValues = Array(inputValues, 100);
    cout<<"\nNo of values = " << numberOfValues; 
    // now output the values and the sum of the values
    //showArray(inputValues, numberOfValues);
    
    
    int d;
	int (*p) (int[], int);
	p = &showArray;
	d =(*p)(inputValues,numberOfValues);
	    
    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();
    return 0;
}
// Array - read integers from the operator into
//             'a' until operator enters neg.
//             Return the number of elements stored.
int Array(int a[], int maxNumElements)
{
    int numberOfValues;
    for(numberOfValues = 0;
        numberOfValues < maxNumElements;
        numberOfValues++)
    {
        // fetch another number
        int integerValue;
        cout << "Enter next number: ";
        cin  >> integerValue;
        // if it's negative...
        if (integerValue < 0)
        {
            // ...then exit
            break;
        }
        // ... otherwise store the number
        // into the  storage array
        a[numberOfValues] = integerValue;
    }
    // return the number of elements read
    return numberOfValues;
 }
// showArray - display the members of an
//                array of length sizeOfloatArray
int showArray(int a[], int numElements)
{
    cout << "\n\nThe value of the array is:" << endl;
    for (int i = 0; i < numElements; i++)
    {
        cout << i << ": " << a[i] << endl;
    }
    cout << endl;
    
    int temp;
        for(int i=0; i < numElements; i++){
 
            for(int j=1; j < (numElements - i); j++){
                if(a[j-1] > a[j]){
                    temp=a[j-1];
                    a[j-1] = a[j];
                    a[j] = temp;
                }
            }
    
}
int x = 0;
cout<<"Enter whether the numbers should be displayed in (1) Ascending Order or (2) Descending Order: "<<endl;
cin>> x;
if ( x == 1)
{
	
	for (int i = 0; i < numElements; i++)
    {
        cout << i << ": " << a[i] << endl;
    }
    cout << endl;
}


else

{

cout << "The value of the array is:" << endl;
    for (int i = numElements - 1; i >= 0; i--)
    {
        cout << i << ": " << a[i] << endl;
    }
    cout << endl;
}
return (0);
}
