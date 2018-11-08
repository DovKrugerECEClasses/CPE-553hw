#include "Image.hh"
#include <iostream>

using namespace std;

int main() {
	Image img(800,600, 0x000000);
	image.Load("DOWN.png");
  const uint32_t cols = image.Width();
  const uint32_t rows = image.Height();
  const uint32_t size = rows*cols*3;
 
  cout << "Image rows=" << rows << " cols=" << cols << '\n';
  const char* bytes = image.getPixels();
  cout << hex;
  for (int i = 0 ; i < size; i += rows) {
    for (int j = 0; j < cols; ++j) {
      cout << bytes[i+j] << ' ';
    }
    cout << '\n';
  }
}
