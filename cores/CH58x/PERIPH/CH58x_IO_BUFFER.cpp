#include "CH58x_IO_BUFFER.h"
#include "HardwareSerial.h"
int8_t IO_Buffer::findAvailable(uint8_t Part, uint8_t Direction) {
	uint8_t Mask = (Direction << 3) | Part;
	int8_t num = 0xFF;
	for (int i = 0; i < Size_CompositeBuffer; i++)
		if (Table[i].Mask == Mask)
			num = i;
	if (num == 0xff) return -1;
	return num;
}

int8_t IO_Buffer::findEmpty() {
	int8_t num = 0xFF;
	for (int i = 0; i < Size_CompositeBuffer;i++) {
		if (Table[i].Length == 0) {
			num = i;
			break;
		}
	}
	return num;
}

int8_t IO_Buffer::getBufferIndex(uint8_t Part, uint8_t Direction, bool getEmpty) {
	int8_t target = -1;
	if (getEmpty == true) {
		target = findEmpty();
	}
	else {
		target = findAvailable(Part, Direction);
		if (target == -1) target = findEmpty();
	}
	return target;
}

IO_Buffer& IO_Buffer::push(TxSpan& span) {
	int8_t target = getBufferIndex(span.Part, span.operation);
	uint8_t Ptr = 0;
	if (target == -1) {
		span.len = 0;		
		return *this;
	}
	uint8_t len = min((MAX_PACKET_SIZE - Table[target].Length), span.len);
	span.len = len;
	
	memcpy(&Buffer[target][Table[target].Length], span.data, len);
	Table[target].Length += len;
	
	Table[target].EP = span.Part;
	Table[target].dir = span.operation;
	return *this;
}
IO_Buffer& IO_Buffer::pull(RxSpan& span) {
	int8_t target = getBufferIndex(span.Part, span.operation);
	uint8_t Ptr = 0;
	if (target == -1 || Table[target].Length == 0) {
		span.len = 0;
		return *this;
	}

	if (span.len == 0) {
		span.len = Table[target].Length;
		
		Table[target].Length = 0;
	}
	else {
		if ((Table[target].Length - Table[target].Ptr) < span.len)
			span.len = Table[target].Length - Table[target].Ptr;
		Ptr = Table[target].Ptr;
		Table[target].Ptr += span.len;

		if (Table[target].Ptr >= Table[target].Length) {
			Table[target].Ptr = 0;
			Table[target].Length = 0;
		}
	}

	memcpy(span.data, &Buffer[target][Ptr], span.len);
	Table[target].EP = span.Part;
	Table[target].dir = span.operation;
	return *this;
}

uint8_t IO_Buffer::Available(uint8_t Part) {
	int8_t target = getBufferIndex(Part, 1);
	if (target == -1) return 0;
	
	return Table[target].Length - Table[target].Ptr;
}

uint8_t IO_Buffer::AvailableWrite(uint8_t Part) {
	int8_t target = getBufferIndex(Part, 0);
	if (target == -1) return 0;
	return MAX_PACKET_SIZE - Table[target].Length;
}

uint8_t* IO_Buffer::getExtendedBuffer() {
	return &Buffer[0][0];
}
	