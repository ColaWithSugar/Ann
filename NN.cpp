
#include <fstream>
#include <sstream>
#include <iostream>
#include "lib/ann.h"
#include "lib/functions.h"
using namespace std;
using namespace funcs;
int main() {
  Ann s;
  ifstream file;
  //basic
  file.open("data/ann_basic_settings.conf");
  s.set_basic(file);
  file.close();
  //weight
  file.open("data/ann_weight.conf");
  s.set_weight(file);
  file.close();
  //bias
  file.open("data/ann_bias.conf");
  s.set_bias(file);
  file.close();
  //function
  s.set_func(sigmoid, _sigmoid);
  file.open("exam/test.txt");
  s.get(file);
  file.close();
  s.fp();
  s.print_res();
  return 0;
}