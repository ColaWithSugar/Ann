#include <fstream>
#include <sstream>
#include <iostream>
#include "lib/ann.h"
#include "lib/functions.h"
using namespace std;
using namespace funcs;
int main() {
  Matrix W;
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
  s.set_func(lrelu, _lrelu);

	for(int i = 0; i < 4000; ++i) {
    stringstream ss;
    ss << i;

    string file_name = "train/test_" + ss.str() + ".txt";
    file.open(file_name);
    s.get(file);
    file.close();

    file_name = "ans/ans_" + ss.str() + ".txt";
    file.open(file_name);
    s.set_target(file);
    file.close();
    s.fp();
    s.bp();
  }
  ofstream output;
  output.open("data/ann_bias.conf");
  s.print_bias(output);
  output.close();
  output.open("data/ann_weight.conf");
  s.print_weight(output);
  output.close();
  return 0;
}