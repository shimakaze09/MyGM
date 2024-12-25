//
// Created by Admin on 25/12/2024.
//

#include <iostream>

#include <MyMath/rgb.h>
#include <MyMath/scale.h>

using namespace std;
using namespace My;

int main() {
  rgbf white = {1.f, 1.f, 1.f};
  rgbf black = {0.f, 0.f, 0.f};
  scalef s = {0.4f, 0.5f, 0.6f};
  cout << white << endl;
  cout << white * black << endl;
  cout << s;
}