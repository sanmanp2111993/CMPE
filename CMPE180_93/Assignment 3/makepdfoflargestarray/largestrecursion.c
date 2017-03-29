#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define MAX 100

using namespace std;


//function prototyping
int getMaxElement(int []);
int size;


//Main function starts here
int main(){

    int a[MAX],max,i; //Declaration of variables

    cout<<"Enter the size of the array: "<<endl;
    cin>>size;

    cout<<"Enter elements of the array: "<<size<<endl;
    for(i=0;i<size;i++)
      cin>>a[i];

    max=getMaxElement(a);

    cout<<"Largest element of the array is: "<<max<<endl;

    return 0;
}

int getMaxElement(int a[]){

    static int i=0,max =-9999;

    if(i < size){
         if(max<a[i])
           max=a[i];
      i++;
      getMaxElement(a);
    }

    return max;
}
