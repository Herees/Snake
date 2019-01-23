#include <iostream>

// Write here a function counting the mean value

int main()
{
  std::cout << "From how many integer numbers you want to count the mean value? ";
  float n = 0;
  float sum = 0;
  std::cin >> n;
  if (n <= 0) {
  std::cout << "Cannot count mean value from " << n << " numbers" << std::endl;}
                else
      {
  for(int i = 1; i < n + 1; i++)
  {std::cout << "Input " << i << ". number:";
  int luku = 0;
  std::cin >> luku;
  sum+=luku;
      }}
  if(n>=1){
  float mean = sum / n;
  std::cout << "Mean value of the given numbers is " << mean << std::endl;}



}
