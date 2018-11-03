#include <iostream>
using namespace std;

class IllegalSize {
};

class Matrix {
private:
	uint32_t rows,cols;
	double* m;
  Matrix(uint32_t rows, uint32_t cols) : rows(rows), cols(cols),
																				 m(         ) {		//TODO:
	}
public:
  Matrix(uint32_t rows, uint32_t cols, double v) : Matrix(rows,cols) {
		for (uint32_t i = 0; i < rows*cols; i++) {
			m[i] = v;
		}
	}
	Matrix(const Matrix& orig) : rows(orig.rows), cols(orig.cols),
															 m(      ) {
		//TODO:
		
	}

	// add move constructor for 20% bonus
	
	Matrix& operator =(const Matrix& orig) {
		Matrix copy(orig);
		rows = orig.rows;
		cols = orig.cols;
		swap(m, copy.m);
		return *this;
	}

	~Matrix() {
		delete [] m;
	}

	//C++ order in memory for static-sized arrays
	// int x[5][2]; // x[0][0] x[0][1] x[1][0] x[1][1] ....
	
  double operator()(uint32_t r, uint32_t c) const {
		return m[r * cols + c ];
	}
  double& operator()(uint32_t r, uint32_t c) { 
		return m[r * cols + c ];
	}

	friend  Matrix operator +(const Matrix& a, const Matrix& b) {
		if (a.rows != b.rows || a.cols != b.cols)
			throw IllegalSize();
		Matrix ans(a.rows, a.cols);

		//TODO:

		return ans;
	}

	friend Matrix operator *(const Matrix& a, const Matrix& b) {
		if (a.cols != b.rows)
			throw IllegalSize();
		Matrix ans(a.rows, b.cols, 0.0);
		for (uint32_t i = 0; i < a.rows; i++)
			for (uint32_t j = 0; j < b.cols ; j++) {
				double dot = 0;
				for (uint32_t k = 0; k < a.cols; k++)
					// linearize so this is about 30% faster
					dot += a(i,k) * b(k,j); //TODO: replace (i,j) by indexing
				ans(i,j) = dot; //TODO: make this faster
			}

		return ans;
	}
	friend ostream& operator<<(ostream& s, const Matrix& m) {
		for (uint32_t i = 0, c = 0; i < m.rows; i++) {
			for (uint32_t j = 0; j < m.cols; j++, c++) {
				s << m.m[c] << '\t';
			}
			s << '\n';
		}
		return s;
	}
};


int main() {
	try {
		Matrix a(4, 3, 0.0);
		cout << a(2,2);
		a(2,2) = 1.5;
		a[2][1] = 2.5;
		Matrix b(4, 3, 0.0);
		b(1,2) = 1.2;
		b(0,0) = -1.1;
		Matrix c = a + b;
		cout << c << '\n';
		
		Matrix d(3,2,1.0);   // 4x3   x 3x2 = 4x2 matrix
		Matrix e = a * d;
		cout<< e << '\n';
		b = d;
		cout << d << '\n';
		d = e + d;
	} catch(IllegalSize e) {
		cout << "Illegal size -- throw this one back!";
	}
}
