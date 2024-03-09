#ifndef ph_sensor_h
#define ph_sensor_h

#include <Arduino.h>

class PhSensor
{
private:
    int _analogReadPin;
    int _readingDelay = 30;
    const static int _phAverageBufferCount = 30;
    float _phAverageBuffer[_phAverageBufferCount];
    int _phAverageBufferCursor = 0;    
    const static int _readingCount = 16;
    float interpolate(float voltTointerpolate, float releavedVolt, float voltLimit, float releavedPH, float beginPH);
    float getPhInterpolated(float volt);
    void bubbleSort(int arr[], int length);
    void middleElements(int arr[], int length, int n, int result[]);
    void addPHToBuffer(float ph);

public:
    // PhSensor();
    PhSensor(int analogReadPin);
    void Init();
    float GetPH();
    float GetPHAverage();
};

#endif
