#include <iostream>
#include <cstring>
using namespace std;

class String {
private:
	uint32_t capacity;
	uint32_t len;
	char* s;
	void checkGrow(uint32_t newLen) {
		if (newLen > capacity) {
      //grow  allocate double the size of newLen
			const char* old = s;
			s = 
		}
	}
public:
	void operator += (const char str[]) {
		
	}
	void operator +=(const String& s) {
		checkGrow(len + s.len);
    // write the code to append s to the end of your string
	}
};

int main() {
	String s; // must create an empty string
	String s2 = "abc"; // a b c '\0'  control-@ (ASCII NUL)
	String s3("abc", 30000010);

	for (int i = 0; i < 1000000; i++)
		s2 += "def"; // overload operator += (const char str[])
	
	String copy(s2);   // copy constructor
	String copy2 = s2; // copy constructor
	String x = "qqq";
	copy2 = copy = x; // this is why we need to return String& in operator =
  copy = copy; // for a single = it would not matter
	
	String s3("xyz", 5); // xyzxyzxyzxyzxyz
	//	String s4 = s3.substring(3, 2); // from position 3 length 2
	//	cout << s4 << '\n';
	char c  = s3[3];
	s3[4] = 'a';
	cout << s3;
	//	s3.replace('x', 'q');
	const String hello = "hello";

	//cout << hello.length() << '\n';
	//s3.insert(5, hello);
	//	String s5 = s2 + s3;
	//	cout << s5 << '\n';
	
}
