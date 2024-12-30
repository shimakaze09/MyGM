//
// Created by Admin on 27/12/2024.
//

#include <iostream>

#include <MyGM/bbox.h>
#include <MyGM/transform.h>
#include <MyGM/val.h>

using namespace std;
using namespace My;

int main() {
  bboxf3 b;
  b.combine_to_self(pointf3{0, 0, 0});
  b.combine_to_self(pointf3{1, 2, 3});

  cout << "b" << b << endl;
  cout << "is_valid: " << b.is_valid() << endl;
  for (size_t i = 0; i < 8; i++)
    cout << "corner[i]: " << b.corner(i) << endl;
  cout << "center: " << b.center() << endl;
  cout << "diagonal: " << b.diagonal() << endl;
  cout << "area: " << b.area() << endl;
  cout << "volume: " << b.volume() << endl;
  cout << "max_extent: " << b.max_extent() << endl;
  cout << "lerp(valf3{0.2f}): " << b.lerp(valf3{0.2f}) << endl;
  cout << "offset(pointf3{1.f}): " << b.offset(pointf3{1.f}) << endl;

  auto c = bboxf3::minmax(pointf3{1, 1, 1}, pointf3{0, 2, 2});
  cout << "c: " << c << endl;
  cout << "intersect(b,c): " << bboxf3::intersect(b, c) << endl;

  cout << "translate(1.f):" << transformf(pointf3{1.f}) * b << endl;

  return 0;
}