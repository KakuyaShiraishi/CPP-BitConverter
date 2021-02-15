#ifndef BIT_BYTE_UTIL_MEMORY_STREAM_H_
#define BIT_BYTE_UTIL_MEMORY_STREAM_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdint>

namespace BitConverter {

	enum class Origin {
		BEGIN,
		CURRENT,
		END
	};

	class MemoryStream {
	public:
		MemoryStream();
		MemoryStream(std::vector<uint8_t>& array);
		~MemoryStream();

		void seek(int offset, Origin origin);

		void writeByte(uint8_t byte);
		void write(std::vector<uint8_t>& array, int offset, int size);
		uint8_t readByte();
		uint16_t readUInt16();
		int32_t readInt32();
		uint32_t readUInt32();
		int64_t readInt64();
		uint64_t readUInt64();

	private:
		std::vector<uint8_t> _stream;
		int _pos;
	};

}
#endif
