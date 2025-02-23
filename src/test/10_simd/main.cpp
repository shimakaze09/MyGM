//
// Created by Admin on 23/02/2025.
//

#include <MyGM/mat.h>
#include <MyGM/point.h>
#include <MyGM/vec.h>
#include <iostream>

// #include <MyGM/scale.h>

using namespace My;
using namespace std;

int main(int argc, char* argv[]) {
  // {  // vecf4
  //   vecf4 a;
  //   vecf4 b;
  //   cin >> a >> b;
  //   cout << a + b << endl;
  //   cout << a.dot(b) << endl;
  // }

  // {  // pointf4
  //   pointf4 p0, p1;
  //   cin >> p0 >> p1;
  //   p0 -= vecf4{1, 1, 1, 1};
  //   cout << p0 - p1 << endl;
  // }

  // {  // matrix mul
  //   matf4 m1, m2;
  //   cin >> m1 >> m2;
  //   auto m1m2 = m1 * m2;
  //   cout << m1m2 << endl;
  // }

  {  // matrix inverse
    matf4 m;
    cin >> m;
    (m * m.inverse()).print();
  }

  return 0;
}
