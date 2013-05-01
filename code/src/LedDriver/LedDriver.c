#include "RuntimeError.h"
#include "LedDriver.h"

enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};
static uint16_t *ledsAddress;
static uint16_t ledsImage;

static void updateHardware(void)
{
    *ledsAddress = ledsImage;
}

void LedDriver_Create(uint16_t *address)
{
    ledsAddress = address;
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

void LedDriver_Destroy(void)
{
}

static uint16_t convertLedNumberToBit(int ledNumber)
{
    return 1 << (ledNumber -1);
}

void LedDriver_TurnOn(int ledNumber)
{
    if(ledNumber <= 0 || ledNumber > 16) {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
        return;
    }
    ledsImage |= convertLedNumberToBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
    if(ledNumber <= 0 || ledNumber > 16) {
        RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
        return;
    }
#if 0
    if(ledNumber <= 0 || ledNumber > 16) {
        return;
    }
#endif
    ledsImage &= ~convertLedNumberToBit(ledNumber);
    updateHardware();
}

void LedDriver_TurnAllOn(void)
{
    ledsImage = ALL_LEDS_ON;
    updateHardware();
}
