#ifndef _CLOUD_MODE_SOLID_H
#define _CLOUD_MODE_SOLID_H

#include "cloud-mode.h"

class CloudLampModeSolid : public CloudLampMode {
  public:
    virtual void begin(CloudLamp* lamp);

    virtual void loop();

  protected:
    CloudLamp* lamp;
};

#endif // _CLOUD_MODE_SOLID_H
