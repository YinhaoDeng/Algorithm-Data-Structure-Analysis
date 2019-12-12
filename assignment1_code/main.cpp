#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//make two strings equal size, in order to add eeasily
void makeSizeEqual(string *a, string *b)
{
	while(a->size()<b->size())
		a->insert(a->begin(),'0');
	while(b->size()<a->size())
		b->insert(b->begin(),'0');
}

// a string type function to add two numbers based on input numbers
string adder(string a, string b, int Base)
{

	string sum="";
	int carry=0;

	makeSizeEqual(&a,&b);

	int i = 0;
	while(i<a.size())
	{
		sum+='0';
		i++;
	}

	for(int m=a.size()-1; m>=0; m--) 
	{
		sum[m]=(char)(((a[m]-'0')+(b[m]-'0')+carry)%Base+'0');
		if( (a[m]-'0')+(b[m]-'0')+carry<Base )
			carry=0;
		else
			carry=1;
	}

	if(carry==1)
		sum='1'+sum;

	return sum;
}

int main()
{
    string num1,num2;
    int base;
    cin>>num1>>num2>>base;
    cout<<adder(num1,num2,base);
}