#ifndef _CLOUD_MODE_CLOUD_H
#define _CLOUD_MODE_CLOUD_H

#include "cloud-mode.h"

class CloudLampModeCloud : public CloudLampMode {
  public:
    virtual void begin(CloudLamp* lamp);

    virtual void loop();

  protected:
    CloudLamp* lamp;
};

#endif // _CLOUD_MODE_CLOUD_H

