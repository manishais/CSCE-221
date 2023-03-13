#include<iostream>

using namespace

void Recur_fun(int n) { 
   if(n > 0) { 
      Recur_fun(n-1); 
      cout << n << endl; 
      Recur_fun(n-1);
   }
}

int main()
{

}