/*Algorithm:
1.This program takes n number of elements from user and stores it in array a[]. 
2.To find the largest element, the first two elements of array are checked and largest of these two element is placed in a[0].
3.Then, the first and third elements are checked and largest of these two element is placed in a[0]. 
4.This process continues until and first and last elements are checked. 
5.After this process, the largest element of an array will be in a[0] position.
*/

#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;
int main()
{
    int i,n;
    float a[100];
    cout << "Enter total number of elements: ";
    cin >> n;
    cout << endl;
    while (n>100 || n<=0)
    {
        cout << "Error! number should in range of (1 to 100)." << endl;
        cout << "Enter the number again: ";
        cin >> n;
    }
    for(i=0;i<n;++i)  /* Stores number entered by user. */
    {
       cout << "Enter Number " << i+1 << " : ";
       cin >> a[i];
    }
    for(i=1;i<n;++i)  /* Loop to store largest number to a[0] */
    {
       if(a[0]<a[i]) /* Change < to > if you want to find smallest element*/
           a[0]=a[i];
    }
    cout << "Largest element = " << a[0];
    return 0;
}
