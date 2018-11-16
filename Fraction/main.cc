#include "Fraction.hh"

using namespace std;
int main() {
	Fraction a(1,2);
	Fraction b(1,3);
	Fraction c = a + b;
	Fraction c = a - b;
	cout << c << '\n';
}
