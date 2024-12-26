//
// Created by Admin on 25/12/2024.
//

#include <iostream>

#include <MyGM/euler.h>
#include <MyGM/quat.h>

using namespace std;
using namespace My;

int main() {
  vecf3 axis(0, 1, 0);
  float angle = 45.f;
  auto q = quatf::axis_angle(axis, to_radian(angle));
  cout << q.axis() << endl;
  cout << q.theta() << endl;
  auto x = quatf::axis_angle({1, 1, 1}, 0);
  pointf3 p(1, 0, 0);
  cout << q * p << endl;
  cout << quatf::identity() << endl;
  cout << q.theta() << endl;
  cout << q.is_identity() << endl;
  cout << quatf::rotate_with<Axis::X>(to_radian(45.f)) << endl;
  cout << eulerf(to_radian(45.f), to_radian(45.f), to_radian(45.f)).to_quat()
       << endl;
}