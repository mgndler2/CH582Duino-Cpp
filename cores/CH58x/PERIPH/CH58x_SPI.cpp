#include "CH58x_SPI.h"

template<int SPI_NUM>
void SPI_Base<SPI_NUM>::transfer(void* data, uint32_t len) {
	uint8_t* p = (uint8_t*)data;
	_SPI.SPI_MOD.SPI_FIFO_DIR = 0;
	
	for (int i = 0; i < len;i++) {
		_SPI.SPI_BUFFER.data = p[i];
		while (!(_SPI.SPI_INT_FLAG.SPI_FREE));
		p[i] = _SPI.SPI_BUFFER.data;
	}
}
template<int SPI_NUM>
void SPI_Base<SPI_NUM>::sendViaFIFO(void* data, uint16_t len) {
	uint8_t* p = (uint8_t*)data;
	_SPI.SPI_MOD.SPI_FIFO_DIR = 0;
	_SPI.SPI_TOTAL_CNT.length = len;
	_SPI.SPI_INT_FLAG.SPI_IF_CNT_END = 1;
	for (int i = 0;i < len;i++) {
		_SPI.FIFO.data = p[i];
		while (_SPI.FIFO_COUNT.length >= 8);
	}
}
template<int SPI_NUM>
void SPI_Base<SPI_NUM>::recvViaFIFO(void* data, uint16_t len) {
	uint8_t* p = (uint8_t*)data;
	_SPI.SPI_MOD.SPI_FIFO_DIR = 1;
	_SPI.SPI_TOTAL_CNT.length = len;
	_SPI.SPI_INT_FLAG.SPI_IF_CNT_END = 1;
	for (int i = 0;i < len;i++) {
		while (_SPI.FIFO_COUNT.length == 0);
		p[i] = _SPI.FIFO.data;
	}
}
template<int SPI_NUM>
void SPI_Base<SPI_NUM>::sendViaDMA(void* data, uint16_t len) {
	uint8_t* p = (uint8_t*)data;
	_SPI.SPI_MOD.SPI_FIFO_DIR = 0;
	_SPI.SPI_DMA_BEG.addr = (uintptr_t)p;
	_SPI.SPI_DMA_END.addr = (uintptr_t)(p + len);
	_SPI.SPI_TOTAL_CNT.length = len;
	_SPI.SPI_INT_FLAG.byte = 0b00001001; //IF_DMA_END, IF_CNT_END
	_SPI.SPI_CFG.SPI_DMA_ENABLE = 1;
}
template<int SPI_NUM>
void SPI_Base<SPI_NUM>::recvViaDMA(void* data, uint16_t len) {
	uint8_t* p = (uint8_t*)data;
	_SPI.SPI_MOD.SPI_FIFO_DIR = 1;
	_SPI.SPI_DMA_BEG.addr = (uintptr_t)p;
	_SPI.SPI_DMA_END.addr = (uintptr_t)(p + len);
	_SPI.SPI_TOTAL_CNT.length = len;
	_SPI.SPI_INT_FLAG.byte = 0b00001001; //IF_DMA_END, IF_CNT_END
	_SPI.SPI_CFG.SPI_DMA_ENABLE = 1;
}

