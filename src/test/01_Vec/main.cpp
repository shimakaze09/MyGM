//
// Created by Admin on 25/12/2024.
//

#include <iostream>

#include <MyMath/Vec.h>

using namespace std;
using namespace My;

int main() {
  vecf3 v(1, 2, 3);
  vecf3 u = {0, 2, 3};
  cout << sizeof(vecf3) << endl;

  // add
  cout << -v << endl;
  cout << v + u << endl;
  cout << v - u << endl;
  v += u;
  cout << v << endl;
  v -= u;
  cout << v << endl;
  cout << v * 5 << endl;
  cout << 5 * v << endl;

  // mul
  cout << v * 3.f << endl;
  cout << 4.f * v << endl;
  v *= 5.f;
  cout << v << endl;
  cout << v / 3.f << endl;
  v /= 5.f;
  cout << v << endl;

  // inner product
  cout << v.dot(u) << endl;
  cout << vecf3::dot(v, u) << endl;

  // norm
  cout << v.norm2() << endl;
  cout << v.norm() << endl;
  cout << v.normalize() << endl;
  v.normalize_self();
  cout << v[2] << endl;

  // angle
  cout << vecf3::cos_theta(v, u) << endl;
  cout << v.cos_theta(u) << endl;

  // cross
  cout << vecf3::cross(v, u) << endl;
  cout << v.cross(u) << endl;

  vecf3 vs[4];

  for (size_t i = 0; i < 4; i++)
    std::cin >> vs[i];

  std::cout << vs[2] + vs[3];
  std::cout << vecf3(vs[0][0] + vs[1][0], vs[0][1] + vs[1][1],
                     vs[0][2] + vs[1][2]);
}