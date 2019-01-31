#include <iostream>
using namespace std;

int main()
{
string key;
cout<<"Enter the encryption key: ";
cin >> key;
if(key.length()!=26){
    cout<<"Error! The encryption key must contain 26 characters."<<endl;
    return EXIT_FAILURE;
}
string tarkistus="";
for (int i=0;i<26;i++){
string kirjain=key.substr(i,1);
if(!(kirjain<="z"&&kirjain>="a")){
    cout<<"Error! The encryption key must contain only lower case characters."<<endl;
    return EXIT_FAILURE;
}
for (int i=0;i<tarkistus.length();i++){
    std::string tarkistin=tarkistus.substr(i,1);
    if(tarkistin==kirjain){
        cout<<"Error! The encryption key must contain all alphabets a-z."<<endl;
        return EXIT_FAILURE;
}}
tarkistus+=kirjain;
}
string viesti;
cout<<"Enter the text to be encrypted: ";
cin>>viesti;
string salaus;
for (int i = 0; i<viesti.length();i++){
string kirj=viesti.substr(i,1);
const char *kirja=kirj.c_str();
int asc=int(*kirja);
salaus+=key.substr(asc-97,1);

}
cout<<"Encrypted text: "<<salaus<<endl;

}
