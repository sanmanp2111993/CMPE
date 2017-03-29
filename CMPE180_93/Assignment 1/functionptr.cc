#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

void Asc(int a[],int n );
void Dsc(int a[],int n );
void sort(void (*ptr)(int a[],int n),int a[],int n)
{

	cout<<"Enter Asc for ascended list or Dsc for descended list"<< endl;
	string s;
	cin>>s;

if(s =="Asc")
{
	ptr = Asc;
	Asc(a,n);
}
if(s =="Dsc")
{
	ptr = Dsc;
	Dsc(a,n);
}

}

/*void Array(int *k, string t)
{int n;
    cout << "\n\nThe value of the array is:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << ": " << k[i] << endl;
    }
    cout << endl;
}*/

//int showArray(int a[], int numElements);
int main()
{
   int n=0;
   int a[100];
//    int numberOfValues;
   void (*ptr)(int a[],int n) = 0;

	int integerValue,ln;
    while(integerValue<100)
    {

        int integerValue;
        cout << "Enter next number: ";
        cin  >> integerValue;
        a[n] = integerValue;
        ln++;
        if (integerValue < 0)
        {
            break;
        }
        n++;
    }
  //  cout<<"Elements in the array are: "<<endl;
    sort(ptr,a,ln);
    /*string f;
	cout<<"Enter 'Asc' if you want sorting the element in the ascending order or 'Dsc' for sorting the elements in descending order"<<endl;

    cin>>f;
    if(f =="Asc"){
       Asc(a,n);
	}
    Array(a,f);*/

    return 0;
}

  /*  switch(f)
    {
    	case 'A':
		int *r = Asc(a,n);
		int *r1;
		cout<<"Ascending Order elements:";
		for(int m=0;m<n;m++)
	  {
			int r1=&r[i];
		cout<<*r1<<endl;
       }
    	   break;
    	case 'D':
		int *q = Dsc(a,n);
		int *q1;
		cout<<"Descending Order elements:";
		for(int k=0;k<n;k++)
	  {
			int q1=&q[i];
		cout<<*q1<<endl;
       }
		   break;
    	default:
		   break;
	}*/
	/*
    cout << "This program sums values entered "
         << "by the user\n";
    cout << "Terminate the loop by entering "
         << "a negative number\n";
    cout << endl;

    int inputValues[100];
    int numberOfValues = Array(inputValues, 100);
    cout<<"\nNo of values = " << numberOfValues;



    int d,d1;
	int (*p) (int[], int);
	p = &showArray;
	d =(*p)(inputValues,numberOfValues);


	int (*p1) (int[], int);
	p1 = &Array;
	d1 =(*p1)(inputValues,numberOfValues);




    cout << "Press Enter to continue..." << endl;
    cin.ignore(10, '\n');
    cin.get();

    string s;
    cin>>s;

     if(s=="Asc"){
	 Asc(a,d1)
         }
else

{
	Dsc(a,int n)
}
*/
   // Asc(inputValues,n);
    //Dsc(inputValues,n);
 //   return 0;
//}
/*
int Array(int a[], int maxNumElements)
{   int n=0;
    int numberOfValues;
    for(numberOfValues = 0; numberOfValues < maxNumElements; numberOfValues++)
    {

        int integerValue;
        cout << "Enter next number: ";
        cin  >> integerValue;
        n++;

        if (integerValue < 0)
        {
            break;
        }

        a[numberOfValues] = integerValue;
    }

    return n;
 }

*/

   /* int temp;
        for(int i=0; i < numElements; i++){

            for(int j=1; j < (numElements - i); j++){
                if(a[j-1] > a[j]){
                    temp=a[j-1];
                    a[j-1] = a[j];
                    a[j] = temp;
                }
            }
    */

/*
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
*/



void Asc(int a[],int n)
{
	cout<<"Signature of Function: void Asc(int a[],int n);"<<endl;
	int temp; //cout<< n<< endl;
        for(int i=0; i < n; i++){

            for(int j=1; j < (n - i); j++){
                if(a[j-1] > a[j]){
                    temp=a[j-1];
                    a[j-1] = a[j];
                    a[j] = temp;
                }
            }
}
for(int i=0; i<n; i++){
	cout<<a[i]<<",";
}
}



void Dsc(int a[],int n)
{
	cout<<"Signature of Function: void Dsc(int a[],int n);"<<endl;
	 int temp;
        for(int i=0; i < n; i++)
		{

            for(int j=1; j < (n - i); j++){
                if(a[j-1] < a[j]){
                    temp=a[j-1];
                    a[j-1] = a[j];
                    a[j] = temp;
                }
            }
}
for(int i=0; i<n; i++){
	cout<<a[i]<<",";
}
}

