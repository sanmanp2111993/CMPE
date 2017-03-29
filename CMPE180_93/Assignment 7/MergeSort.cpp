#include<stdio.h>
#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>


using namespace std;

int a[10000];       // array to be sorted
int count;


void merge(int a[],int l,int m,int h)
{
  int a1[10000],a2[10000];        // Two temporary arrays to hold the two arrays to be merged
  int n1,n2,i,j,k;
  n1=m-l+1;
  n2=h-m;

  for(i=0; i<n1; i++)
    a1[i]=a[l+i];

  for(j=0; j<n2; j++)
    a2[j]=a[m+j+1];
	

  a1[i]=99999;  
  a2[j]=99999;

  i=0;
  j=0;
  for(k=l; k<=h; k++) 
{ 
    if(a1[i]<=a2[j])
      {
      a[k]=a1[i++];
       count++;}
    else{
      a[k]=a2[j++];
       //count++;
}
  }

    
}

void merge_sort(int a[],int left,int right)
{
  int centre;
  if(left<right) 
{
    centre=(left+right)/2;
    merge_sort(a,left,centre);
    merge_sort(a,centre+1,right);
    merge(a,left,centre,right);
  }

 
}


int main()
{
  int n,i,t1,t2,t;

  cout<<"Enter the size of array: ";  // input the elements
  cin>>n;
  for(i=0; i<n; i++)
 {
     a[i]=rand()%1000;
  } 
  cout<<endl;
  cout<<"Unsorted array: ";  
  for(i=0; i<n; i++)
 {
  cout<<" "<<a[i];
 }
  t1=clock();
  merge_sort(a,0,n-1);  // sort the array
  t2=clock();
  t=(double)(t2-t1)/CLOCKS_PER_SEC*1000000.0;
  cout<<endl;
  cout<<endl;
  cout<<"Sorted array: ";  // print sorted array
  for(i=0; i<n; i++)
    cout<<" "<<a[i];
    cout<<endl;
    cout<<endl;
    cout<<"Execution time in Microseconds: "<<t<<endl;
    cout<<endl;
    cout<<"Number of swaps made: "<<count<<endl;
    cout<<endl; 



  return 0;
}



