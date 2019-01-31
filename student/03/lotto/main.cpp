#include <iostream>

using namespace std;

unsigned long int kertoma(int a)
{
    unsigned long int b = 1;
for (int i=1;i<a+1;i++){
    b=b*i;
}
return b;
}
int main()
{
cout<<"Enter the total number of lottery balls: ";
int palloja = 0;
cin >> palloja;
cout <<"Enter the number of drawn balls: ";
int veto = 0;
cin >> veto;
if (palloja <0){
    cout << "The number of balls must be a positive number."<<endl;

}
else if(veto>palloja){
    cout << "At most the total number of balls can be drawn."<<endl;
}
else{
unsigned long int pelle = kertoma(palloja);
unsigned long int pella = kertoma(veto);
unsigned long int pello = kertoma(palloja-veto);
unsigned long int todari = pelle/(pella*pello);
cout <<"The probability of guessing all "<<veto<<" balls correctly is 1/" << todari <<endl;
}}
