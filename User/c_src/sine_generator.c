#include "sine_generator.h"

uint16_t sine_wave[SAMPLES];

#define SINE_FREQUENCY 10 // 10 Hz
#define SAMPLE_RATE 1000 // 1 kHz
#define PI 3.14159265358979

static void generate_sinewave(void)
{
    for (int i = 0; i < SAMPLES; i++)
    {
        sine_wave[i] = (uint16_t)((DAC_MAX / 2) * (sin(2 * M_PI * i / SAMPLES) + 1));
    }
}

void start_sinwave(void)
{
    generate_sinewave();
    HAL_DAC_Start_DMA(DAC_GetHandle(), DAC_CHANNEL_1, (uint32_t*)sine_wave, SAMPLES, DAC_ALIGN_12B_R);
}


float sine_value;
void sine_gen_test()
{
    float angle = 0.0f;
    float angle_increment = 2 * PI * SINE_FREQUENCY / SAMPLE_RATE;
    while(1)
    {
        sine_value = sinf(angle);
        angle += angle_increment;
        if (angle >= 2 * PI)
        {
            angle -= 2 * PI; // Zapewnij, że kąt mieści się w przedziale [0, 2*PI)
        }
        HAL_Delay(1);

    }
}