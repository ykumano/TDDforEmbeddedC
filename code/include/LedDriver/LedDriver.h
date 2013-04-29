#include <stdint.h>

void LedDriver_Create(uint16_t * ledsAddress);
void LedDriver_Destroy(void);

void LedDriver_TurnOn(int ledNumber);
void LedDriver_TurnOff(int ledNumber);
