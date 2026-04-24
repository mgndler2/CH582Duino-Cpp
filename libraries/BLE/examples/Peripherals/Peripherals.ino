#include "peripheral.h"
__aligned(4) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

void setup() {
    pinMode(20, OUTPUT);

    CH58X_BLEInit();
    HAL_Init();
    GAPRole_PeripheralInit();
    Peripheral_Init();
}

bool toggle = 0;

void loop() {
    digitalWrite(20, LOW);
    delay(50);
    //Serial.println("Hellow");
    Serial.println("Good!");
    digitalWrite(20, HIGH);
    if (Serial1.available()) {
        Serial.print((char)Serial1.read());
    }
    //
    //Serial1.println("Good!");
    delay(500);

    TMOS_SystemProcess();
}