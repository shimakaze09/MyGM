//
// Created by Admin on 23/12/2024.
//

#include <MyMath/Val.h>
#include <iostream>

using namespace std;
using namespace My;

int main() {
  Valf3 v(1, 2, 3);
  Valf3 u = {4, 5, 6};
  // Valf3 w = { 1,2 }; // error
  cout << v << endl;
  cin >> v;
  cout << v << endl;
  cout << u << endl;
}