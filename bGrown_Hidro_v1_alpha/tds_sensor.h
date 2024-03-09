#ifndef tds_sensor_h
#define tds_sensor_h
#include <Arduino.h>

class TDSSensor
{
private:
    const static int TDS_READING_COUNT = 30;
    int copyIndex = 0;
    int analogBufferIndex = 0;
    int analogBuffer[TDS_READING_COUNT]; // store the analog value in the array, read from ADC
    int analogBufferTemp[TDS_READING_COUNT];
    float averageVoltage = 0;
    float temperature = 25;
    int TdsSensorPin = 0;

    int getMedianNum(int bArray[], int iFilterLen);

public:
    void Init(int analogInputGpio);
    float loop();
};

#endif
