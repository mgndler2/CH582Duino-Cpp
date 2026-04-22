#ifndef __CH58x_I2C_H__
#define __CH58x_I2C_H__
#include "Arduino.h"
#include "CH58x_I2C_SFR.h"
#include "CH58x_SYS.h"
class I2C_Base {
public:

	I2C_Base(volatile I2C_Module_t& mod) :
		_I2C(mod) {
	}
	I2C_Base(volatile I2C_Module_t& mod, uint16_t addr, uint8_t is10BitAddr = 0) {

		I2C_OADDR1_t OAddr;
		OAddr.MUST1 = 1;
		OAddr.ADDMODE = is10BitAddr;
		
	}
	uint8_t writeTo(uint16_t address, uint8_t is10BitAddr, wait) {
		_I2C.CTRL1.STOP = 0;
		_I2C.CTRL1.START = 1;
		if (is10BitAddr) {
			b10AddrCode header;
			header.Header = 0b11110;
			header.Addr9_8 = (address >> 8) & 0x03;
			header.Operation = 0;
			
			while (_I2C.STAR1.SB == 0);
			_I2C.DATAR.DATAR = header.byte;
			while (_I2C.STAR1.ADD10 == 0);
			_I2C.DATAR.DATAR = address & 0xFF;
		}
		else {
			while (_I2C.STAR1.SB == 0);
			_I2C.DATAR.DATAR = address << 1 | 0;			
		}
		while (_I2C.STAR1.ADDR == 0);
		_I2C.STAR2.MSL;
		return 0;
	}
	void writeTobuffer(void* data, int len) {
		uint8_t writeIndex = (table[0].Index + table[0].Length) % 32;
		uint8_t writelen = min(32 - writeIndex, len);
		memcpy(&Buffer[0][writeIndex], data, writelen);
		if (len > writelen) {
			memcpy(&Buffer[0][0], (uint8_t*)data + writelen, len - writelen);
		}
		table[0].Length += len;
	}
	inline void sendFrombuffer() {
		while (!_I2C.STAR1.TxE);
		_I2C.DATAR.DATAR = Buffer[0][table[0].Index];
		table[0].Index = (table[0].Index + 1) & 31;
		table[0].Length--;
	}
	void recvTobuffer() {
		uint8_t writeIndex = (table[1].Index + table[1].Length) & 31;
		if (_I2C.STAR1.RxNE) {
			Buffer[1][writeIndex] = _I2C.DATAR.DATAR;
			table[1].Length++;
		}
	}
	void readFromBuffer(void* data, int len) {
		//uint8_t readEnd = table[1].Index + len;
		len = min(table[1].Length, len);
		uint8_t readlen = min(32 - table[1].Index, len);
		memcpy(data, &Buffer[1][table[1].Index], readlen);
		if (len > readlen) {
			memcpy((uint8_t*)data + readlen, &Buffer[1][0], len - readlen);
		}
		table[1].Index = (table[1].Index + len) & 31;
		table[1].Length -= len;
	}
	uint8_t availableWrite() {
		return 32 - table[0].Length;
	}
	uint8_t available() {
		return table[1].Length;
	}
private:
	volatile I2C_Module_t& _I2C;
	void setClock(uint16_t Clock) {
		uint32_t SysClock = CPU_CLK.GetSysClock();
		uint16_t _PE = _I2C.CTRL1.PE;
		_I2C.CTRL2.FREQ = SysClock / 1000000;
		_I2C.CTRL1.PE = 0;
		if (Clock < 10000) Clock = 10000;
		if (Clock <= 100000) {
			_I2C.CKCFGR.byte = sysClock / (Clock << 1);
			if (_I2C.CKCFGR.CCR < 0x04) _I2C.CKCFGR.CCR = 0x04;
			_I2C.RTR.TRISE = ((_I2C.CTRL2.FREQ + 1) > 0x3F) ? 0x3F : _I2C.CTRL2.FREQ + 1;
		}
		else {
			_I2C.CKCFGR.F_S = 1;
			if (Clock >= 200000) {
				_I2C.CKCFGR.DUTY = 1;
				_I2C.CKCFGR.CCR = (SysClock / (Clock * 25)) < 1 ? 1 : (SysClock / (Clock * 25));
			}
			else {
				_I2C.CKCFGR.DUTY = 0;
				_I2C.CKCFGR.CCR = (SysClock / (Clock * 3)) < 1 ? 1 : (SysClock / (Clock * 3));
			}
			_I2C.RTR.TRISE = _I2C.CTRL2.FREQ * 300 / 1000 + 1;
		}
		_I2C.CTRL1.PE = _PE;
	}
	inline void SoftWareReset() {
		_I2C.CTRL1.SWRST = 1;
		_nop();
		_I2C.CTRL1.SWRST = 0;
	}
	struct BufTable {
		uint8_t Length;
		uint8_t Index;
	};
	BufTable volatile table[2];
	union b10AddrCode {
		struct {
			uint8_t Operation : 1;
			uint8_t Addr9_8 : 2;
			uint8_t Header : 5;
		};
		uint8_t byte;
	};
	__aligned_four__ volatile uint8_t Buffer[2][32];
	__aligned_four__ volatile uint8_t MasterBuf[32];
};


#endif // !__CH58x_I2C_H__
