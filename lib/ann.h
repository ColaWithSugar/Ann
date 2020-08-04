#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
double learning_rate = 0.1;
struct Matrix {
	int x, y;
	double **data;
	Matrix() {
	  x = 0, y = 0;
	  data = new double*[2];
	  data[1] = new double[1];
	}
	void resize(int nx, int ny) {
	  for(int i = 1; i <= y; ++i) {
			delete[] data[i];
  	} delete[] data;
  	x = nx, y = ny;
  	data = new double*[x + 1];
  	for(int i = 1; i <= x; ++i)
  		data[i] = new double[y + 1];
  	return;
  }
  double* operator [] (int n) {
  	return data[n];
  }
  Matrix operator + (Matrix &b) {
  	Matrix c;
  	c.resize(x, y);
  	for(int i = 1; i <= x; ++i)
  		for(int j = 1; j <= y; ++j)
  			c[i][j] = data[i][j] + b[i][j];
  	return c;
  }
  Matrix operator * (Matrix &b) {
  	Matrix c;
  	c.resize(x, b.y);
	  for(int k = 1; k <= b.y; ++k)
		  for(int i = 1; i <= b.x; ++i)
			  for(int j = 1; j <= x; ++j)
				  c[j][k] += data[j][i] * b[i][k];
	  return c;	
  }
  Matrix func(double (*f)(double)) {
	  Matrix ans; ans.resize(x, y);
	  for(int i = 1; i <= x; ++i)
	  	for(int j = 1; j <= y; ++j)
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
			for(int i = 1; i <= ly; ++i) file >> ply[i];
			target.resize(ply[ly], 1);
			prop.resize(ply[ly], 1);
			for(int i = 1; i <= ly; ++i) {
				net[i].resize(ply[i], 1);
				out[i].resize(ply[i], 1);
				bias[i].resize(ply[i], 1);
			}
			for(int i = 2; i <= ly; ++i)
				w[i].resize(ply[i], ply[i - 1]);
    }
    void set_weight(ifstream &file) {
      for(int i = 2; i <= ly; ++i)
				for(int j = 1; j <= ply[i]; ++j)
					for(int k = 1; k <= ply[i - 1]; ++k)
						file >> w[i][j][k];
    }
    void set_bias(ifstream &file) {
      for(int i = 1; i <= ly; ++i)
				for(int j = 1; j <= ply[i]; ++j)
					file >> bias[i][j][1];
    }
    void get(ifstream &file) {
      for(int i = 1; i <= ply[1]; ++i)
				file >> net[1][i][1];
    }
    void set_target(ifstream &file) {
			for(int i = 1; i <= ply[ly]; ++i)
				file >> target[i][1];
		}
		void set_func(double (*f1)(double), double (*f2)(double)) {
			ptr[0] = f1; ptr[1] = f2;
		}
		void fp() {
			out[1] = net[1].func(ptr[0]);
			for(int i = 2; i <= ly; ++i) {
				net[i] = w[i] * out[i - 1] + bias[i];
				out[i] = net[i].func(ptr[0]);
			}
			double sum = 0;
			for(int i = 1; i <= ply[ly]; ++i)
				sum += out[ly][i][1];
			for(int i = 1; i <= ply[ly]; ++i)
				prop[i][1] = out[ly][i][1] / sum;
		}
		void bp() {
			Eout[ly].resize(out[ly].x, out[ly].y);
			for(int i = 1; i <= ply[ly]; ++i) {
				Eout[ly][i][1] = 2 * (prop[i][1] - target[i][1]);
			}
			for(int i = ly; i >= 2; --i) {
				Ew[i].resize(w[i].x, w[i].y);
				Enet[i].resize(net[i].x, net[i].y);
				Eout[i - 1].resize(out[i - 1].x, out[i - 1].y);
				Ebias[i].resize(bias[i].x, bias[i].y);
				for(int j = 1; j <= ply[i]; ++j) {
					Ebias[i][j][1] = Enet[i][j][1] = Eout[i][j][1] * (*ptr[1])(net[i][j][1]);
					for(int k = 1; k <= ply[i - 1]; ++k) {	
						Ew[i][j][k] = Enet[i][j][1] * out[i - 1][k][1];
						Eout[i - 1][k][1] += w[i][j][k] * Enet[i][j][1];
					}
				}
				for(int j = 1; j <= ply[i]; ++j) {
					bias[i][j][1] -= Ebias[i][j][1] * learning_rate;
				  for(int k = 1; k <= ply[i - 1]; ++k) {
						w[i][j][k] -= Ew[i][j][k] * learning_rate;
					}
				}
			}
		}
		void print_weight(ofstream &file) {
			for(int i = 2; i <= ly; ++i) {
				for(int j = 1; j <= ply[i]; ++j) {
					for(int k = 1; k <= ply[i - 1]; ++k) {
						file << w[i][j][k] << ' ';
					} file << endl;
				} file << endl;
			}
		}
		void print_bias(ofstream &file) {
			for(int i = 1; i <= ly; ++i) {
				for(int j = 1; j <= ply[i]; ++j) {
					file << bias[i][j][1] << ' ';
				} file << endl;
			}
		}
		void print_res() {
			for(int i = 1; i <= ply[ly]; ++i) {
				cout << prop[i][1] << endl;
			}
		}
};