#include <MyGM/transform.hpp>
#include <iostream>

using namespace Smkz;
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
