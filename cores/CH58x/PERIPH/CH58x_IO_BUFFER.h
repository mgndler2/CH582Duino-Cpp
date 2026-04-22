#pragma once

#ifndef CH58x_IO_BUFFER__H__
#define CH58x_IO_BUFFER__H__
#include "CH58x_USB_SFR.h"
#include <cstring>
//#include "Arduino.h"
#ifndef Size_CompositeBuffer
#define Size_CompositeBuffer		4
#endif // !Size_CompositeBuffer
struct TxSpan {
	uint8_t Part;
	const uint8_t* data;
	int8_t& len;
	uint8_t operation;
};
inline TxSpan push_data(uint8_t Part, const uint8_t* data, int8_t& len, uint8_t operation) {
	return { Part, data, len, operation };
}

struct RxSpan {
	uint8_t Part;
	uint8_t* data;
	int8_t& len;
	uint8_t operation;
};
inline RxSpan pull_data(uint8_t Part, uint8_t* data, int8_t& len, uint8_t operation) {
	return { Part, data, len, operation };
}

class IO_Buffer {
public:
	uint8_t* ptr = nullptr;
	IO_Buffer& operator<<(TxSpan span) {
		
		return push(span);
	}
	IO_Buffer& operator>>(RxSpan span) {
		
		return pull(span);
	}
	uint8_t* getExtendedBuffer();
	uint8_t Available(uint8_t Part);
	uint8_t AvailableWrite(uint8_t Part);
private:
	IO_Buffer& push(TxSpan& span);
	IO_Buffer& pull(RxSpan& span);
	int8_t getBufferIndex(uint8_t Part, uint8_t Direction, bool getEmpty = false);
	int8_t findAvailable(uint8_t Part, uint8_t Direction);
	int8_t findEmpty();
	typedef struct data_table {
		union {
			struct {
				uint8_t EP : 3;
				uint8_t dir : 1;
				uint8_t : 4;
			};
			struct {
				uint8_t Mask : 4;
				uint8_t : 4;  // padding
			};
		};
		uint8_t Length;
		uint8_t Ptr;
	}data_table_t;
	data_table_t Table[Size_CompositeBuffer];
	__aligned_four__ uint8_t Buffer[Size_CompositeBuffer][MAX_PACKET_SIZE];
};

#endif // !CH58x_IO_BUFFER__H__