//
// Created by Admin on 23/12/2024.
//

#include <MyMath/Val.h>
#include <iostream>

using namespace std;
using namespace My;

int main() {
  Valf3 v(1, 2, 3);
  Valf3 u = {0, 2, 3};
  cout << sizeof(Valf3) << endl;
  cout << (u == v ? "u==v" : "u!=v") << endl;
  cout << (u < v ? "u<v" : "u>=v") << endl;
  cout << v << endl;
  cin >> v;
  cout << v << endl;
  cout << u << endl;
  cout << v.Abs() << endl;
  cout << Valf3(abs(v[0]), abs(v[1]), abs(v[2])) << endl;
  cout << v.MaxDim() << endl;
}