//
// Created by Admin on 25/12/2024.
//

#include <MyGM/quat.h>
#include <iostream>

using namespace std;
using namespace My;

int main() {
  vecf3 axis(0, 1, 0);
  float angle = 45.f;
  quatf q(axis, angle / 180 * 3.1415926);
  quatf x(0, {1, 1, 1});
  pointf3 p(1, 0, 0);
  cout << q * p << endl;
  cout << quatf::identity() << endl;
  cout << q.theta() << endl;
  cout << q.is_identity() << endl;
}