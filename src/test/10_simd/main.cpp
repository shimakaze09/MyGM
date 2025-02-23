//
// Created by Admin on 23/02/2025.
//

#include <MyGM/point.h>
#include <MyGM/vec.h>
#include <iostream>

// #include <MyGM/scale.h>

using namespace My;
using namespace std;

int main(int argc, char* argv[]) {
  vecf3 test;
  vecf4 a;
  vecf4 b;
  cin >> a >> b;
  cout << a + b << endl;
  cout << a.dot(b) << endl;

  pointf4 p0, p1;
  cin >> p0 >> p1;
  p0 -= a;
  cout << p0 - p1 << endl;
  // scalef4 sa;
  // scalef4 sb;
  // cin >> sa >> sb;
  // cout << sa * sb << endl;
  // cout << sa.inverse() << endl;
  // xsimd::batch<float, 4> test;

  return 0;
}
