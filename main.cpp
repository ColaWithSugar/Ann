#include <fstream>
#include <iostream>
#include "lib/ann.h"
#include "lib/functions.h"
using namespace std;
using namespace funcs;
int main() {
  Matrix W;
  Ann s;
  ifstream file;
  file.open("data/ann_basic_settings.conf");
  s.set_basic(file);
  file.close();
  file.open("data/ann_target.conf");
  s.set_target(file);
  file.close();
  file.open("data/ann_weight.conf");
  s.set_weight(file);
  file.close();
  file.open("data/ann_in.conf");
  s.get(file);
  file.close();
  file.open("data/ann_bias.conf");
  s.set_bias(file);
  file.close();
  s.set_func(prelu, _prelu);
  s.fp();
	for(int i = 1; i <= 12650; ++i) {
	  s.bp(); s.fp();
	}
  s.print_res();
  return 0;
}