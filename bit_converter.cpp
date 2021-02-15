#include "bit_converter.h"

namespace BitConverter {

	bool IsLittleEndian() {
		return isLittleEndian;
	}

	std::vector<unsigned char> BitArrayCopy(
		std::vector<unsigned char>& source, int sourceIndex, int copyCount) {
		const int firstChunkIdx = sourceIndex / 8;
		const int firstChunkOffset = sourceIndex % 8;
		const int lastIndex = sourceIndex + copyCount - 1;
		const int lastChunkIdx = lastIndex / 8;
		const int lastChunkOffset = lastIndex % 8;
		const int chunkNum = lastChunkIdx - firstChunkIdx + 1;

		std::vector<unsigned char> ret(chunkNum);
		std::vector<bool> retBits(chunkNum * 8);

		if (copyCount <= 0) {
			return ret;
		}

		int i, j;
		int k;
		std::bitset<8> tempBits;
		if (1 == chunkNum) {
			k = 0;
			tempBits = std::bitset<8>(source[firstChunkIdx]);

			for (int i = firstChunkOffset; i < lastChunkOffset + 1; i++) {
				if (tempBits[i]) {
					retBits[k++] = true;
				} else {
					retBits[k++] = false;
				}
			}
		} else {
			k = 0;

			for (i = firstChunkIdx; i < lastChunkIdx + 1; i++) {
				tempBits = std::bitset<8>(source[i]);

				if (firstChunkIdx == i) {
					for (j = firstChunkOffset; j < 8; j++) {
						if (tempBits[j]) {
							retBits[k++] = true;
						} else {
							retBits[k++] = false;
						}
					}
				} else if (lastChunkIdx == i) {
					for (j = 0; j < lastChunkOffset + 1; j++) {
						if (tempBits[j]) {
							retBits[k++] = true;
						} else {
							retBits[k++] = false;
						}
					}
				} else {
					for (j = 0; j < 8; j++) {

						if (tempBits[j]) {
							retBits[k++] = true;
						} else {
							retBits[k++] = false;
						}
					}
				}
			}
		}

		unsigned char temp;
		k = 0;

		for (i = 0; i < chunkNum - 1; i++) {
			temp = 0x00;
			tempBits = std::bitset<8>();

			for (j = 0; j < 8; j++) {
				if (true == retBits[8 * i + j]) {
					tempBits.set(j);
				} else {
					tempBits.reset(j);
				}
			}
			temp = (unsigned char)tempBits.to_ulong();
			ret[k++] = temp;
		}


		tempBits = std::bitset<8>();
		for (j = 0; j < (copyCount % 8) + 1; j++) {
			if (retBits[8 * (chunkNum - 1) + j]) {
				tempBits.set(j);
			} else {
				tempBits.reset(j);
			}
		}

		temp = (unsigned char)tempBits.to_ulong();
		ret[k++] = temp;

		for (auto& iter : ret) {
			auto print = std::bitset<8>(iter);
		}

		return ret;

	}


	std::vector<unsigned char> GetBytes(bool value) {
		std::vector<unsigned char> ret;
		ret.reserve(1);
		ret[0] = (value ? (unsigned char)true : (unsigned char)false);

		return ret;
	}

	std::vector<unsigned char> GetBytes(short value) {
		std::vector<unsigned char> ret;
		ret.reserve(2);

		int i;
		unsigned char temp = 0x00;
		if (isLittleEndian) {
			for (i = 0; i < 2; i++) {
				temp = value >> 8 * i;
				ret.push_back(temp);
			}
		} else {

			for (i = 1; i >= 0; i++) {
				temp = value >> 8 * i;
				ret.push_back(temp);
			}
		}


		return ret;
	}

	std::vector<unsigned char> GetBytes(unsigned short value) {
		return GetBytes((short)value);
	}

	std::vector<unsigned char> GetBytes(int value) {
		std::vector<unsigned char> ret;
		ret.reserve(4);

		int i;
		unsigned char temp = 0x00;
		if (isLittleEndian) {
			for (i = 0; i < 4; i++) {
				temp = value >> 8 * i;
				ret.push_back(temp);
			}
		} else {
			for (i = 3; i >= 0; i++) {
				temp = value >> 8 * i;
				ret.push_back(temp);
			}
		}


		return ret;
	}

	std::vector<unsigned char> GetBytes(unsigned int value) {
		return GetBytes((int)value);
	}

	std::vector<unsigned char> GetBytes(long long value) {
		std::vector<unsigned char> ret;
		ret.reserve(8);

		int i;
		unsigned char temp = 0x00;
		if (isLittleEndian) {
			for (i = 0; i < 8; i++) {
				temp = value >> 8 * i;
				ret.push_back(temp);
			}
		} else {
			for (i = 7; i >= 0; i++) {
				temp = value >> 8 * i;
				ret.push_back(temp);
			}
		}

		return ret;
	}

	std::vector<unsigned char> GetBytes(unsigned long long value) {
		return GetBytes((long long)value);
	}

	short BytesToInt16(std::vector<unsigned char>& input, int startOffset) {
		if (input.empty()) {
			return 0;
		}
		if ((unsigned int)startOffset >= input.size()) {
			return 0;
		}
		if (startOffset > input.size() - 2) {
			return 0;
		}


		if (isLittleEndian) {
			return (input[startOffset]) | (input[startOffset + 1] << 8);
		} else {
			return (input[startOffset] << 8) | (input[startOffset]);
		}
	}

	unsigned short BytesToUInt16(std::vector<unsigned char>& input, int startOffset) {
		if (input.empty()) {
			return 0;
		}
		if ((unsigned int)startOffset >= input.size()) {
			return 0;
		}
		if (startOffset > input.size() - 2) {
			return 0;
		}

		return (unsigned short)BytesToInt16(input, startOffset);
	}

	int BytesToInt32(std::vector<unsigned char>& input, int startOffset) {
		if (input.empty()) {
			return 0;
		}
		if ((unsigned int)startOffset >= input.size()) {
			return 0;
		}
		if (startOffset > input.size() - 4) {
			return 0;
		}

		if (isLittleEndian) {
			return (input[startOffset]) | (input[startOffset + 1] << 8) |
				(input[startOffset + 2] << 16) | (input[startOffset + 3] << 24);
		} else {
			return (input[startOffset] << 24) | (input[startOffset] << 16) |
				(input[startOffset] << 8) | (input[startOffset]);
		}
	}

	unsigned int BytesToUInt32(std::vector<unsigned char>& input, int startOffset) {
		if (input.empty()) {
			return 0;
		}
		if ((unsigned int)startOffset >= input.size()) {
			return 0;
		}
		if (startOffset > input.size() - 4) {
			return 0;
		}

		return (unsigned int)BytesToInt32(input, startOffset);
	}

	long long BytesToInt64(std::vector<unsigned char>& input, int startOffset) {
		if (input.empty()) {
			return 0;
		}
		if ((unsigned int)startOffset >= input.size()) {
			return 0;
		}
		if (startOffset > input.size() - 8) {
			return 0;
		}

		int first, second;
		if (isLittleEndian) {
			first = (input[startOffset]) | (input[startOffset + 1] << 8) |
				(input[startOffset + 2] << 16) | (input[startOffset + 3] << 24);
			second = (input[startOffset + 4]) | (input[startOffset + 5] << 8) |
				(input[startOffset + 6] << 16) | (input[startOffset + 7] << 24);
			return (long long)((unsigned int)first | ((unsigned long long) second << 32));
		} else {
			first = (input[startOffset] << 24) | (input[startOffset + 1] << 16) |
				(input[startOffset + 2] << 8) | (input[startOffset + 3]);
			second = (input[startOffset + 4] << 24) | (input[startOffset + 5] << 16) |
				(input[startOffset + 6] << 8) | (input[startOffset + 7]);
			return (long long)((unsigned int)second | (unsigned long long) first << 32);
		}
	}

	unsigned long long BytesToUInt64(std::vector<unsigned char>& input, int startOffset) {
		if (input.empty()) {
			return 0;
		}
		if ((unsigned int)startOffset >= input.size()) {

			return 0;
		}
		if (startOffset > input.size() - 8) {

			return 0;
		}
		return (unsigned long long) BytesToInt64(input, startOffset);
	}

}
