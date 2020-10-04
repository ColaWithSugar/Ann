#include <ctime>
#include <fstream>
#include <random>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
  default_random_engine e;
	uniform_real_distribution<double> u(0, 1);
  srand((unsigned)time(NULL));
  ifstream in_file;
  ofstream out_file;
  while(1) {
    string passwd;
    cout << "password: ";
    cin >> passwd;
    if(passwd == "123456789")
      break;
    else
      cout << "password incorrect!!!" << endl;
  }
  in_file.open("data/ann_basic_settings.conf");
  int ly, ply[1000];
  in_file >> ly;
  cout << ly << endl;
  for(int i = 0; i < ly; ++i) {
    in_file >> ply[i];
    cout << ply[i] << ' ';
  }
  in_file.close();
  out_file.open("data/ann_weight.conf");
  for(int k = 1; k < ly; ++k) {
    for(int i = 0; i < ply[k]; ++i) {
      for(int j = 0; j < ply[k - 1]; ++j) {
        out_file << 1.0 * (rand() % 1000) / 10000 << ' ';
      } out_file << endl;
    } out_file << endl;
  }
  out_file.close();
  out_file.open("data/ann_bias.conf");
  for(int i = 1; i < ly; ++i) {
    for(int j = 0; j < ply[i]; ++j) {
      out_file << 1.0 * (rand() % 100) / 100 << ' ';
    } out_file << endl; 
  }
  out_file.close();
}