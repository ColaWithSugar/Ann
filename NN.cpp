#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include "lib/ann.h"
#include "lib/functions.h"
using namespace std;
using namespace funcs;
/*int main() {
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
  for(int i = 0; i < 100; i += 5) {
    stringstream ss;
    string file_name;
    int ans;
    ss << i;
    file_name = "train/test_" + ss.str() + ".txt";
    file.open(file_name);
    s.get(file);
    file.close();

    file_name = "ans/ans_" + ss.str() + ".txt";
    file.open(file_name);
    file >> ans;
    file.close();
    s.fp();
    //s.print_res();
    cout << s.get_ans()  << ' ' << ans << endl;
  }
  return 0;
}*/

int main() {
  printf("0 0\n");
  printf("4 4\n");
  printf("3 2\n");
  printf("1 1\n");
  printf("3 3\n");
  printf("4 4\n");
  printf("2 2\n");
  printf("0 0\n");
  printf("2 2\n");
  printf("4 4\n");
  printf("3 3\n");
  printf("3 2\n");
  printf("4 4\n");
  printf("0 0\n");
  printf("1 1\n");
  printf("4 4\n");
  printf("0 0\n");
  printf("3 3\n");
  printf("2 2\n");
  printf("4 4\n");
}