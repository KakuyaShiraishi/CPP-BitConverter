#ifndef BIT_BYTE_UTIL_BIT_CONVERTER_H_
#define BIT_BYTE_UTIL_BIT_CONVERTER_H_

#include <iostream>
#include <vector>
#include <memory>
#include <bitset>

namespace BitConverter {

	static bool isLittleEndian = true;


	bool IsLittleEndian();

	std::vector<unsigned char> BitArrayCopy(
		std::vector<unsigned char>& source, int sourceIndex, int copyCount);

	std::vector<unsigned char> GetBytes(bool value);
	std::vector<unsigned char> GetBytes(short value);
	std::vector<unsigned char> GetBytes(unsigned short value);
	std::vector<unsigned char> GetBytes(int value);
	std::vector<unsigned char> GetBytes(unsigned int value);
	std::vector<unsigned char> GetBytes(long long value);
	std::vector<unsigned char> GetBytes(unsigned long long value);
	short BytesToInt16(std::vector<unsigned char>& input, int startOffset);
	unsigned short BytesToUInt16(std::vector<unsigned char>& input, int startOffset);
	int BytesToInt32(std::vector<unsigned char>& input, int startOffset);
	unsigned int BytesToUInt32(std::vector<unsigned char>& input, int startOffset);
	long long BytesToInt64(std::vector<unsigned char>& input, int startOffset);
	unsigned long long BytesToUInt64(std::vector<unsigned char>& input, int startOffset);


}
#endif
