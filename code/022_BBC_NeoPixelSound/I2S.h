#ifndef _I2S_H
#define _I2S_H

//https://www.arduino.cc/en/Reference/I2S

#include "Arduino.h"
#include <i2s.h>
#include <i2s_reg.h>

typedef enum 
{
  I2S_PHILIPS_MODE,
  I2S_RIGHT_JUSTIFIED_MODE, // PT8211 DAC uses this mode
  I2S_LEFT_JUSTIFIED_MODE,
  I2S_PDM_MODE // pulse density mode for direct RC-low pass connection at pin
} i2s_mode_t;

class I2SClass 
{
  public:

    uint8_t  begin(i2s_mode_t mode, uint32_t sampleRate, uint8_t bitsPerSample);
    void     end();

    uint32_t availableForWrite();

    void     write(int16_t data);
    void     write(int16_t leftData, int16_t rightData);

    void     write(int16_t *data, size_t size);

    void     onTransmit(void (*callback) (void)); // call back shall have "void ICACHE_RAM_ATTR" attribute 
    
    i2s_mode_t i2sMode;

};

#endif
