//
// Created by Admin on 25/12/2024.
//

#include <MyMath/mat.h>
#include <iostream>

using namespace std;
using namespace My;

int main() {
  vecf3 c0 = {1, 2, 3};
  vecf3 c1 = {4, 5, 6};
  vecf3 c2 = {7, 8, 9};
  matf3 m0(c0, c1, c2);
  matf3 m1(c1, c2, c0);
  cout << m0 << endl;
  cout << m0 + m1 << endl;
  cout << m0 - m1 << endl;
  cout << 3 * m0 << endl;
  cout << m0 * m1 << endl;
  cin >> m0;
  cout << m0;
}