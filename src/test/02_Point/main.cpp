//
// Created by Admin on 25/12/2024.
//

#include <iostream>

#include <MyMath/Point.h>

using namespace std;
using namespace My;

int main() {
  pointf3 o(1, 1, 1);
  pointf3 p(2, 2, 2);
  vecf3 v(1, 2, 3);
  cout << o << endl;
  cout << p + v << endl;
  cout << p - v << endl;
  o += v;
  cout << o << endl;
  o -= v;
  cout << o << endl;
  cout << p - o << endl;
}
