#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
double learning_rate = 0.005;
struct Matrix {
	int x, y;
	double **data;
	Matrix() {
	  x = 0, y = 0;
	  data = new double*[1];
	  data[0] = new double[1];
	}
	void clear() {
		for(int i = 0; i < x; ++i) {
			for(int j = 0; j < y; ++j) {
				data[i][j] = 0;
			}
		}
	}
	void resize(int nx, int ny) {
	  for(int i = 0; i < y; ++i) {
			delete[] data[i];
  	} delete[] data;
  	x = nx, y = ny;
  	data = new double*[x];
  	for(int i = 0; i < x; ++i)
  		data[i] = new double[y];
  	return;
  }
  double* operator [] (int n) {
  	return data[n];
  }
  Matrix operator + (Matrix &b) {
  	Matrix c;
  	c.resize(x, y);
  	for(int i = 0; i < x; ++i)
  		for(int j = 0; j < y; ++j)
  			c[i][j] = data[i][j] + b[i][j];
  	return c;
  }
  Matrix operator * (Matrix &b) {
  	Matrix c;
  	c.resize(x, b.y);
	  for(int k = 0; k < b.y; ++k)
		  for(int i = 0; i < b.x; ++i)
			  for(int j = 0; j < x; ++j)
				  c[j][k] += data[j][i] * b[i][k];
	  return c;	
  }
  Matrix func(double (*f)(double)) {
	  Matrix ans; ans.resize(x, y);
	  for(int i = 0; i < x; ++i)
	  	for(int j = 0; j < y; ++j)
	  		ans[i][j] = (*f)(data[i][j]);
	  return ans;
  }
};

class Ann {
	private:
		int ly, ply[21];
		Matrix target, net[21], out[21], w[21], bias[21], prop;
		Matrix Enet[21], Eout[21], Ew[21], Ebias[21];
		double (*ptr[2])(double);
	public:
		Ann() {
			ly = 0; memset(ply, 0, sizeof ply);
			ptr[0] = NULL; ptr[1] = NULL;
		}
		void set_basic(ifstream &file) {
      file >> ly;
			for(int i = 0; i < ly; ++i) file >> ply[i];
			target.resize(ply[ly - 1], 1);
			prop.resize(ply[ly - 1], 1);
			for(int i = 0; i < ly; ++i) {
				net[i].resize(ply[i], 1);
				out[i].resize(ply[i], 1);
				bias[i].resize(ply[i], 1);
				Enet[i].resize(ply[i], 1);
				Eout[i].resize(ply[i], 1);
				Ebias[i].resize(ply[i], 1);
			}
			for(int i = 1; i < ly; ++i) {
				w[i].resize(ply[i], ply[i - 1]);
				Ew[i].resize(ply[i], ply[i - 1]);
			}
    }
    void set_weight(ifstream &file) {
      for(int i = 1; i < ly; ++i)
				for(int j = 0; j < ply[i]; ++j)
					for(int k = 0; k < ply[i - 1]; ++k)
						file >> w[i][j][k];
    }
    void set_bias(ifstream &file) {
      for(int i = 1; i < ly; ++i)
				for(int j = 0; j < ply[i]; ++j)
					file >> bias[i][j][0];
    }
    void get(ifstream &file) {
      for(int i = 0; i < ply[0]; ++i)
				file >> net[0][i][0];
    }
    void set_target(ifstream &file) {
			for(int i = 0; i < ply[ly - 1]; ++i)
				target[i][0] = 0;
			int num;
			file >> num;
			target[num][0] = 1;
		}
		void set_func(double (*f1)(double), double (*f2)(double)) {
			ptr[0] = f1; ptr[1] = f2;
		}
		void fp() {
			out[0] = net[0].func(ptr[0]);
			for(int i = 1; i < ly; ++i) {
				net[i] = w[i] * out[i - 1] + bias[i];
				out[i] = net[i].func(ptr[0]);
			}
			double sum = 0;
			for(int i = 0; i < ply[ly - 1]; ++i)
				sum += out[ly - 1][i][0];
			for(int i = 0; i < ply[ly - 1]; ++i)
				prop[i][0] = out[ly - 1][i][0] / sum;
		}
		void bp() {
			Eout[ly - 1].clear();
			for(int i = 0; i < ply[ly - 1]; ++i) {
				Eout[ly - 1][i][0] = 2 * (prop[i][0] - target[i][0]);
			}
			for(int i = ly - 1; i > 0; --i) {
				Ew[i].clear();
				Enet[i].clear();
				Eout[i - 1].clear();
				Ebias[i].clear();
				for(int j = 0; j < ply[i]; ++j) {
					Ebias[i][j][0] = Enet[i][j][0] = Eout[i][j][0] * (*ptr[1])(net[i][j][0]);
					for(int k = 0; k < ply[i - 1]; ++k) {	
						Ew[i][j][k] = Enet[i][j][0] * out[i - 1][k][0];
						Eout[i - 1][k][0] += w[i][j][k] * Enet[i][j][0];
					}
				}
				for(int j = 0; j < ply[i]; ++j) {
					bias[i][j][0] -= Ebias[i][j][0] * learning_rate;
				  for(int k = 0; k < ply[i - 1]; ++k) {
						w[i][j][k] -= Ew[i][j][k] * learning_rate;
					}
				}
			}
		}
		void print_weight(ofstream &file) {
			for(int i = 1; i < ly; ++i) {
				for(int j = 0; j < ply[i]; ++j) {
					for(int k = 0; k < ply[i - 1]; ++k) {
						file << w[i][j][k] << ' ';
					} file << endl;
				} file << endl;
			}
		}
		void print_bias(ofstream &file) {
			for(int i = 1; i < ly; ++i) {
				for(int j = 0; j < ply[i]; ++j) {
					file << bias[i][j][0] << ' ';
				} file << endl;
			}
		}
		void print_res() {
			for(int i = 0; i < ply[ly - 1]; ++i) {
				cout << prop[i][0] << endl;
			}
		}
};