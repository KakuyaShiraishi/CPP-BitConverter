#include <iostream>

#include "bit_converter.h"

void bitArrayCopyTest() {
	unsigned char c1 = 0x15;
	unsigned char c2 = 0x22;
	unsigned char c3 = 0x33;
	unsigned char c4 = 0x44;
	unsigned char c5 = 0x55;
	unsigned char c6 = 0x66;
	unsigned char c7 = 0x77;
	unsigned char c8 = 0x88;

	auto bitset1 = std::bitset<8>(c1);
	auto bitset2 = std::bitset<8>(c2);
	std::vector<unsigned char> byteArray = { c1, c2, c3, c4, c5, c6, c7, c8 };


	std::vector<unsigned char> copy = BitConverter::BitArrayCopy(byteArray, 3, 20);


	std::bitset<8> b1(c1);
	unsigned char outc = (unsigned char)b1.to_ulong();


	std::bitset<8> temp;

	for (auto& iter : byteArray) {
		temp = std::bitset<8>(iter);
	}

	for (auto& iter : copy) {
		temp = std::bitset<8>(iter);
	}
}


void bitConverterTest() {
	unsigned char c1 = 0x15;
	unsigned char c2 = 0x22;
	unsigned char c3 = 0x33;
	unsigned char c4 = 0x44;
	unsigned char c5 = 0x55;
	unsigned char c6 = 0x66;
	unsigned char c7 = 0x77;
	unsigned char c8 = 0x88;

	std::vector<unsigned char> byteArray = { c1, c2, c3, c4, c5, c6, c7, c8 };

	short _short;
	unsigned short _unsigned_short;
	int _int;
	unsigned int _unsigned_int;
	long long _long_long;
	unsigned long long _unsigned_long_long;

	_short = BitConverter::BytesToInt16(byteArray, 0);
	_unsigned_short = BitConverter::BytesToUInt16(byteArray, 0);
	_int = BitConverter::BytesToInt32(byteArray, 1);
	_unsigned_int = BitConverter::BytesToUInt32(byteArray, 1);
	_long_long = BitConverter::BytesToInt64(byteArray, 0);
	_unsigned_long_long = BitConverter::BytesToUInt64(byteArray, 0);


	std::bitset<8> temp;
	std::bitset<8> b1(c1);
	unsigned char outc = (unsigned char)b1.to_ulong();

	for (auto& iter : byteArray) {
		temp = std::bitset<8>(iter);
	}
	std::vector<unsigned char> ret = BitConverter::GetBytes(_unsigned_int);
	for (auto iter : ret) {
		temp = std::bitset<8>(iter);
	}

}

void vectorInitialization() {
	unsigned char a = 0x51;
	unsigned char b = 0x3A;
	std::vector<unsigned char> temp;

	temp = { a, b };

	for (auto iter : temp) {
		std::cout << std::hex << (unsigned int)iter << std::endl;
	}

	temp.clear();
	temp = { b, a };

	for (auto iter : temp) {
		std::cout << std::hex << (unsigned int)iter << std::endl;
	}
}

int main(int argc, char* argv[]) {

	vectorInitialization();
	//  bitConverterTest();
	//  bitArrayCopyTest();

	return 0;
}
