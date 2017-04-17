#ifndef _CLOUD_MODE_FLASH_H
#define _CLOUD_MODE_FLASH_H

#include "cloud-mode.h"

class CloudLampModeFlash : public CloudLampMode {
  public:
    virtual void begin(CloudLamp* lamp);

    virtual void loop();

  protected:
    CloudLamp* lamp;
};

#endif // _CLOUD_MODE_FLASH_H
