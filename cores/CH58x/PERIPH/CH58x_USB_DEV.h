#pragma once

#ifndef __CH58x_USB_DEV_H__
#define __CH58x_USB_DEV_H__
#include "CH58x_USB_SFR.h"
//#include "RVMSIS/core_riscv.h"
#include <cstring>

#include "CH58x_IO_BUFFER.h"


namespace USB_MASK {
	enum response_Mask
	{
		ACK,
		No_Response,
		NAK,
		STALL
	};
	enum Token_PID
	{
		OUT_PACK,
		SOF_PACK,
		IN_PACK,
		IDLE
	};
}



class EP_Setting {
public:
	EP_Setting(uint8_t num, volatile USB_Module_t* USB_Module)
		: _num(num), Mod(USB_Module) {
		switch (num) {
		case 0:
			_CTRL = &Mod->UEP0_CTRL;
			_TLEN = &Mod->UEP0_T_LEN;
			break;
		case 1:
			_CTRL = &Mod->UEP1_CTRL;
			_TLEN = &Mod->UEP1_T_LEN;
			break;
		case 2:
			_CTRL = &Mod->UEP2_CTRL;
			_TLEN = &Mod->UEP2_T_LEN;
			break;
		case 3:
			_CTRL = &Mod->UEP3_CTRL;
			_TLEN = &Mod->UEP3_T_LEN;
			break;
		case 4:
			_CTRL = &Mod->UEP4_CTRL;
			_TLEN = &Mod->UEP4_T_LEN;
			break;
		case 5:
			_CTRL = &Mod->UEP5_CTRL;
			_TLEN = &Mod->UEP5_T_LEN;
			break;
		case 6:
			_CTRL = &Mod->UEP6_CTRL;
			_TLEN = &Mod->UEP6_T_LEN;
			break;
		case 7:
			_CTRL = &Mod->UEP7_CTRL;
			_TLEN = &Mod->UEP7_T_LEN;
			break;
		}
	}
	struct ContentProxy {
	public:
		ContentProxy(EP_Setting* p, uint8_t idx)
			: parent(p), index(idx) {
		}
		ContentProxy& operator= (uint8_t v) {
			parent->setVal(index, v);
			return *this;
		}
		operator uint8_t() const {
			parent->getVal();
			uint8_t val;
			if (index == 0) {
				val = parent->_set.NUM;
			}
			else if (index == 1) {
				val = parent->_set.dir;
			}
			else if (index == 2) {
				val = parent->_set.dualBuffer;
			}
			return val;
		}
	private:
		EP_Setting* parent;
		uint8_t index;
	};

	ContentProxy Num{ this,0 };
	ContentProxy dir{ this,1 };
	ContentProxy dualBuffer{ this,2 };
	//uint8_t RX_Length;
	uint8_t* EpBuffer;
	volatile UEPn_CTRL_t* _CTRL;
	volatile UEPn_T_LEN_t* _TLEN;
private:
	typedef union __PACKED EP_SET_t {
		struct __PACKED {
			uint8_t NUM : 3;
			uint8_t dir : 2;			//rx_tx
			uint8_t dualBuffer : 1;		//Can be set if EP = 1, 2, 3;
			uint8_t : 2;
		};
		struct __PACKED {
			uint8_t : 3;
			uint8_t rx : 1;
			uint8_t tx : 1;
			uint8_t : 3;
		};
		uint8_t byte;
	}EP_SET;
	EP_SET _set;
	enum lookupIndex {
		lk_num, lk_dir, lk_dualBuffer
	};
	volatile USB_Module* Mod;
	uint8_t _num;

	void getVal() {
		_set.NUM = _num;
		switch (_num) {
		case 0:
			_set.dir = 0x03; _set.dualBuffer = 0;
			break;
		case 1:
			_set.dir = Mod->UEP4_1_MOD.UEP1.RX_TX;
			_set.dualBuffer = Mod->UEP4_1_MOD.UEP1.BUF_MOD;
			break;
		case 2:
			_set.dir = Mod->UEP2_3_MOD.UEP2.RX_TX;
			_set.dualBuffer = Mod->UEP2_3_MOD.UEP2.BUF_MOD;
			break;
		case 3:
			_set.dir = Mod->UEP2_3_MOD.UEP3.RX_TX;
			_set.dualBuffer = Mod->UEP2_3_MOD.UEP3.BUF_MOD;
			break;
		case 4:
			_set.dir = Mod->UEP4_1_MOD.UEP4.RX_TX;
			_set.dualBuffer = 0;
			break;
		case 5:
			_set.dir = Mod->UEP567_MOD.UEP5.RX_TX;
			_set.dualBuffer = 0;
			break;
		case 6:
			_set.dir = Mod->UEP567_MOD.UEP6.RX_TX;
			_set.dualBuffer = 0;
			break;
		case 7:
			_set.dir = Mod->UEP567_MOD.UEP7.RX_TX;
			_set.dualBuffer = 0;
			break;
		default:
			_set.byte = 0;
			break;
		}
	}
	void setVal(uint8_t idx, uint8_t val) {
		if (idx == lk_dir) {
			switch (_num) {
			case 1:
				Mod->UEP4_1_MOD.UEP1.RX_TX = val;
				break;
			case 2:
				Mod->UEP2_3_MOD.UEP2.RX_TX = val;
				break;
			case 3:
				Mod->UEP2_3_MOD.UEP3.RX_TX = val;
				break;
			case 4:
				Mod->UEP4_1_MOD.UEP4.RX_TX = val;
				break;
			case 5:
				Mod->UEP567_MOD.UEP5.RX_TX = val;
				break;
			case 6:
				Mod->UEP567_MOD.UEP6.RX_TX = val;
				break;
			case 7:
				Mod->UEP567_MOD.UEP7.RX_TX = val;
				break;
			default:
				break;
			}
		}
		else if (idx == lk_dualBuffer) {
			switch (_num) {
			case 1:
				Mod->UEP4_1_MOD.UEP1.BUF_MOD = val;
				break;
			case 2:
				Mod->UEP2_3_MOD.UEP2.BUF_MOD = val;
				break;
			case 3:
				Mod->UEP2_3_MOD.UEP3.BUF_MOD = val;
			default:
				break;
			}
		}
	}
	void fun() {

	}
};

typedef char _usb_errType_t;
enum BasicUSB_err_Type_ {
	It_is_Okay = -1,
	EP_Not_set,
	Does_Not_Support_Bulk
};

class USB_Base {
public:
	USB_Base(volatile USB_Module_t& eUSB);
	~USB_Base();
	uint8_t* getEpBuffer(uint8_t num);
	void ResetDevEP();
	void AttachDevice();
	_usb_errType_t InitialDevEP(int EP, uint8_t Type);
	bool assignBuffer(int EP, uint8_t Buffer[]);

	uint8_t Available(uint8_t ep) { return Buffer.Available(ep); }
	uint8_t AvailableWrite(uint8_t ep) { return Buffer.AvailableWrite(ep); }
	uint8_t* getExtendedBuffer(int8_t motion);
	int Send(uint8_t ep, const void* data, int8_t len);
	int IN(uint8_t ep);
	int Recv(uint8_t ep, void* data, int8_t len);
	int OUT(uint8_t ep, int8_t len);
	EP_Setting EndPoint[8] = {
		{0,&USB}, {1,&USB}, {2,&USB}, {3,&USB}, {4,&USB}, {5,&USB}, {6,&USB}, {7,&USB}
	};
	
protected:
	volatile USB_Module_t& Module;
	IO_Buffer Buffer;
private:	
	volatile __aligned_four__ uint8_t Ep0Buffer[3 * MAX_PACKET_SIZE];
};


#endif // !__CH58x_USB_DEV_H__
