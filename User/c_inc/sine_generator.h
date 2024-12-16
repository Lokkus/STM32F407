#ifndef SINE_GENERATOR_H
#define SINE_GENERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "math.h"

#define SAMPLES 200          // Liczba próbek na okres
#define DAC_MAX 4095         // Maksymalna wartość DAC (12-bit)
//#define SIN_FREQ 10          // Częstotliwość wyjściowej fali (Hz)

void start_sinwave(void);
// void DAC_Init(void);
// void TIM6_Init(void);
// void DMA_Init(void);
void sine_gen_test();

#ifdef __cplusplus
}
#endif

#endif /* SINE_GENERATOR_H */