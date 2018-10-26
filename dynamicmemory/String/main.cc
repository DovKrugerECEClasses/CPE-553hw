#include "String.hh"
using namespace std;


int main() {
	String s;
	cout << s << '\n'; // print blank line
	
	String s2 = "abc"; // a b c '\0'  control-@ (ASCII NUL)
	cout << s2 << "\n"; // prints abc
	s2 += "def";
	cout << s2 << '\n'; // prints abcdef
	String copy(s2);
	String copy2 = s2;
	String x = "qqq";
	copy2 = copy = x; // this is why we need to return String& in operator =
	cout << copy << '\n'; // prints qqq
  copy = copy; // for a single = it would not matter
	cout << copy << '\n'; // prints qqq
	
	String s3("xyz", 5); // xyzxyzxyzxyzxyz
	cout << s3 << '\n';
	String s4 = s3.substring(3, 2); // from position 3 length 2
	cout << s4 << '\n'; // "xy"
	char c  = s3[3];
	cout << "c=" << c << '\n'; // x
	s3[4] = 'a';
	cout << s3 << '\n';// xyzxazxyzxyzxyz
	s3.replace('x', 'q');
	const String hello = "hello";

	cout << hello.length() << '\n';
	s3.insert(5, hello);
	cout << s3 << "\n";
	String s5 = s2 + s3;
	cout << s5 << '\n';
}
