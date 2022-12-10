#include <iostream>
#include "Binaryim.h"
#include <cstdio>
using namespace std;

int main() {

	binaryimage<bool, true, false> bimage(3, 3);
	bimage(0, 0) = true;
	bimage(1, 1) = false;
	cout << "bimage:\n" << bimage << endl;

	binaryimage<int, 7, 3> bimage1(3, 3);
	bimage1(0, 0) = 3;
	bimage1(1, 1) = 7;
	cout << "bimage1:\n" << bimage1 << endl;

	binaryimage<int, 7, 3> bimage0(3, 3);
	bimage0(0, 0) = 4;
	bimage0(1, 1) = 1;
	cout << "bimage0:\n" << bimage0 << endl;

	cout << bimage1 + bimage0 << endl;
	cout << bimage1 * bimage0 << endl;

	binaryimage<short, 7, 3> bimage2(3, 3);
	bimage2(0, 0) = 5;
	bimage2(1, 1) = 7;
	cout << "bimage2:\n" << bimage2 << endl;

	binaryimage<char, 's', 'a'> bimage3(3, 3);
	bimage3(0, 0) = 's';
	bimage3(1, 1) = 'a';
	cout << "bimage3:\n" << bimage3 << endl;

	binaryimage<float, 7.1, 3.1> bimage4(3, 3);
	bimage4(0, 0) = 7.1;
	bimage4(1, 1) = 7.2;
	cout << "bimage4:\n" << bimage4 << endl;

	cout << (bimage0 == bimage1) << endl;	
	bimage = !bimage;
	cout << "!bimage:\n" << bimage << endl;	

	
	
}