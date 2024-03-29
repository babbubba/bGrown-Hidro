#include "ph_sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include "Arduino.h"

PhSensor::PhSensor(int analogReadPin)
{
  Serial.println("Setting PH analog read gpio");
  _analogReadPin = analogReadPin;
  // CircularBuffer<float, 16> _phBuffer = CircularBuffer<float, 16>();
}

void PhSensor::Init()
{
  Serial.println("Initializing PH analog read gpio");
  pinMode(_analogReadPin, INPUT);

  // TODO: Inizializza un timer per la memorizzazione di una lettura ogni tot secondi in modo da ottenere la media
}
float PhSensor::GetPH()
{
  // prendo (_readingCount) rilevazioni consecutive
  int buffer_arr[_readingCount], temp;
  for (int i = 0; i < _readingCount; i++)
  {
    buffer_arr[i] = analogRead(_analogReadPin);
    delay(_readingDelay);
  }

  int nElementi = _readingCount * 0.6;
  int risultato[_readingCount];

  middleElements(buffer_arr, _readingCount, nElementi, risultato);

  unsigned long int valuesSum = 0;
  for (int i = 0; i < nElementi; i++)
  {
    valuesSum += risultato[i];
  }

  // convertto il valore rilevato in volt considerando che 4095 è 3.3V e 0 è 0V dividendo per i campioni scelti (6)
  // TODO: Cambiare usando il convertitore anag./dig. ADS 1115 a 16 bit cosi da avere una lettura lineare e piu precisa...
  float volt = (float)valuesSum * 3.3 / 4095.0 / nElementi;
  float ph = getPhInterpolated(volt);
  Serial.print("PH: ");
  Serial.print(ph);
  Serial.println(" releaved.");
  addPHToBuffer(ph);
  return ph;
}

float PhSensor::interpolate(float voltTointerpolate, float releavedVolt, float voltLimit, float releavedPH, float beginPH)
{
  return releavedPH + (beginPH - releavedPH) * ((voltTointerpolate - releavedVolt) / (voltLimit - releavedVolt));
}

float PhSensor::getPhInterpolated(float volt)
{
  // ESP32 Analog input is not linear... so to be more realistic I will use the next rilevations
  if (volt >= 3.25)
  {
    // case measured: PH 4.8 -> raw value 4030 -> 3.25V (linear computed) -> Effective lecture 3.09V
    return interpolate(volt, 3.25, 3.3, 4.8, 0);
  }
  else if (volt >= 3.09)
  {
    return interpolate(volt, 3.09, 3.25, 5.2, 4.8);
  }
  else if (volt >= 2.69)
  {
    return interpolate(volt, 2.69, 3.09, 6.5, 5.2);
  }
  else if (volt >= 2.35)
  {
    return interpolate(volt, 2.35, 2.69, 8.5, 6.5);
  }
  else // if (volt >= 2.32)
  {
    return interpolate(volt, 2.30, 2.35, 8.7, 8.5);
  }
  // else
  // {
  //   return 14; // Gestione degli altri casi, se necessario
  // }
}

void PhSensor::bubbleSort(int arr[], int length)
{
  for (int i = 0; i < length - 1; i++)
  {
    for (int j = 0; j < length - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        // Scambia gli elementi
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void PhSensor::middleElements(int arr[], int length, int n, int result[])
{
  // Ordina la sequenza
  bubbleSort(arr, length);

  // Calcola l'indice iniziale e finale degli elementi centrali
  int indiceIniziale = (length - n) / 2;
  int indiceFinale = indiceIniziale + n;

  // Estrai gli n elementi centrali
  for (int i = 0; i < n; i++)
  {
    result[i] = arr[indiceIniziale + i];
  }
}

float PhSensor::GetPHAverage()
{
  float phValues = 0;
  for (int idx = 0; idx < _phAverageBufferCursor; idx++)
  {
    phValues += _phAverageBuffer[idx];
  }
  return phValues / _phAverageBufferCursor;
}

void PhSensor::addPHToBuffer(float ph)
{
  if (_phAverageBufferCursor < _phAverageBufferCount)
  {
    _phAverageBuffer[_phAverageBufferCursor] = ph;
    _phAverageBufferCursor++;
  }
  else
  {
    for (int idx = 0; idx < _phAverageBufferCount - 1; idx++)
    {
      _phAverageBuffer[idx] = _phAverageBuffer[idx + 1];
    }
    _phAverageBuffer[_phAverageBufferCount - 1] = ph;
  }
}
