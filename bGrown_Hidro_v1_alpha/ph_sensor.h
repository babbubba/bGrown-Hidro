#ifndef ph_sensor_h
#define ph_sensor_h

#include <Arduino.h>

class PhSensor
{
private:
    int _analogReadPin;
    int _readingDelay = 30;
    const static int _readingCount = 16;
    float interpolate(float voltTointerpolate, float releavedVolt, float voltLimit, float releavedPH, float beginPH);
    float getPhInterpolated(float volt);
    void bubbleSort(int arr[], int length);
    void middleElements(int arr[], int length, int n, int result[]);

public:
    PhSensor();
    PhSensor(int);
    void Init();
    float GetPH();
};

#endif
