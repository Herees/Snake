#include <iostream>

using namespace std;


int main()
{
    int count,upperBound;
    cout << "Enter an upper bound: ";
    cin >> upperBound;
    cout << "Prime numbers smaller than " << upperBound << ":" << endl;
    for(int a = 1;a<=upperBound;a++){
        count = 0;
        for(int i=2;i<=a/2;i++){
            if(a%i==0){
                count++;
                break;
            }
        }

        if(count==0 and a != 1)
            cout << a << " ";
    }
    cout << endl;
}
