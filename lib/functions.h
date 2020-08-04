#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
namespace funcs {
	double relu(double x) {
		return x > 0 ? x : 0;
	}
	double _relu(double x) {
		return x > 0 ? 1 : 0;
	}

	double sigmoid(double x) {
		return 1 / (1 + pow(2.718281828, -x));
	}
	double _sigmoid(double x) {
		return sigmoid(x) * (1 - sigmoid(x));
	}
	
	double prelu(double x) {
		return x > 0 ? x : 0.01 * x;
	}
	double _prelu(double x) {
		return x >= 0 ? 1 : 0.01;
	}
}
