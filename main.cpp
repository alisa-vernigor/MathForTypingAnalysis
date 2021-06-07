#include <iostream>

#include <MathModule.h>

#include <vector>
#include <string>
#include <cmath>
#include <fstream>

#include <Tests/tests.h>

using namespace std;

int main() {
   NSTests::CTests t(2500, "results.txt");
   t.test_all();
   return 0;
}
