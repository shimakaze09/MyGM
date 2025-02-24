//
// Created by Admin on 24/02/2025.
//

#include <MyGM/transform.h>
#include <iostream>

using namespace My;
using namespace std;

int main(int argc, char* argv[]) {
  pointf3 p;
  cin >> p;
  hvecf4 hv(p);
  auto hvp = hv.to_point();
  hvp += vecf3{1, 2, 3};
  cout << hvp << endl;

  return 0;
}
