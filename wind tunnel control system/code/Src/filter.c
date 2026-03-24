#include "filter.h"


#define SAMPLES 20
uint16_t distance_samples[SAMPLES];
uint8_t sample_index;
uint8_t i;
uint8_t j;

uint16_t smooth(uint16_t current_distance) 
{
  uint32_t sum = 0;


  distance_samples[sample_index] = current_distance;
  sample_index = (sample_index + 1) % SAMPLES;


  for (uint8_t i = 0; i < SAMPLES; i++) {
    sum += distance_samples[i];
  }

  return (sum / SAMPLES);
}



uint16_t median(uint16_t current_distance)

{
  uint16_t sorted_samples[SAMPLES];


  distance_samples[sample_index] = current_distance;
  sample_index = (sample_index + 1) % SAMPLES;


  for (uint8_t i = 0; i < SAMPLES; i++) 
	{
    sorted_samples[i] = distance_samples[i];
  }


  for (i = 0; i < SAMPLES - 1; i++)
	{
    for ( j = 0; j < SAMPLES-i-1; j++) 
		{
      if (sorted_samples[j] > sorted_samples[j+1]) 
				{
        uint16_t temp = sorted_samples[j];
        sorted_samples[j] = sorted_samples[j+1];
        sorted_samples[j+1] = temp;
      }
    }
  }


  return sorted_samples[SAMPLES / 2];
}
	