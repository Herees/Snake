#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int n = 0;
    cin >> n;
    int n3 = 0;
    n3 = n*n*n;
    if (n3/n != n*n){
    cout << "Error! The cube of "<< n <<" is not "<< n3 <<"."<<endl;}
    else {
    cout << "The cube of " << n << " is " << n3 << "." << endl;
    }
}
