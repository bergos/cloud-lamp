#ifndef _CLOUD_MODE_H
#define _CLOUD_MODE_H

class CloudLampMode {
  public:
    virtual void begin(CloudLamp* lamp);

    virtual void loop();
};

#endif // _CLOUD_MODE_H
