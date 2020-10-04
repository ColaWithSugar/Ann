#include <fstream>
#include <sstream>
#include <iostream>
#include "lib/ann.h"
#include "lib/functions.h"
using namespace std;
using namespace funcs;
void settings(int x) {
  ifstream file;
  string file_name;
  stringstream ss;
  ss << x;
  file_name = "train/test_" + ss.str() + ".txt";
  file.open(file_name);
  s.get(file);
  file.close();
  file_name = "ans/ans_" + ss.str() + ".txt";
  file.open(file_name);
  s.set_target(file);
  file.close();
}
int main() {
  Ann s;
  ifstream file;
  string passwd;
  int minibatch = 10;
  while(1) {
    cout << "password: ";
    cin >> passwd;
    if(passwd == "1")
      break;
    else
      cout << "password incorrect!!!" << endl;
  }
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
  s.set_learning(0.3, 1);
  while(1) {
    for(int i = 0; i < minibatch; ++i) {
      settings(i);
      s.fp();
      s.bp();
    }
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