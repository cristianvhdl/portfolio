/*
 * main.c
 *
 *  Created on: Apr 19, 2016
 *      Author: Kyle Tingey
 *      		Reuben Fishback
 */

#define stub (uint16_t)0x0000; // my stub. You should not end up with any of these!

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f0xx.h"
#include "delay.h"

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


uint8_t SendOperationReady;  //flag condition for ir interupt
uint8_t BitsSentCounter = 0; //number of bit the ir interupt has sent
uint8_t SendOperationCompleted; //flag condition for ir send completion
//sony IR code
uint64_t ManchesterCodedMsg = 0b000000011011011011010101011011011010110101011010110110101101111;//1,0,1,1,0,1,0,0,1,0,1,1,1,0,0,0,1,1,1,1
uint8_t startManchester = 1;


/*
 * Initialize IR_OUT on PB9 for Sony IR
 *
 * The following configuration is for RC5 standard
 * TIM16 is used for the envelope while TIM17 is used for the carrier
 */
void initSonyIR(){
#define TIM_ENV TIM16
#define TIM_CAR TIM17

	/* Configure peripheral clocks and GPIO*/
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN | RCC_APB2ENR_TIM17EN | RCC_APB2ENR_SYSCFGCOMPEN; /* (1) Enable the peripheral clocks of Timer 16 and 17 and SYSCFG*/
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; /* (2) Enable the peripheral clock of GPIOB*/
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODER9)| GPIO_MODER_MODER9_1; /* (3) Select alternate function mode on GPIOB pin 9*/
	GPIOB->AFR[1] &= ~(0x0F << ((9 - 8) * 4)); /* (4) Select AF0 on PB9 in AFRH for IR_OUT (reset value)*/
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C_FMP_PB9; /* (5) Enable the high sink driver capability by setting I2C_PB9_FM+ bit in SYSCFG_CFGR1*/


	/* Configure TIM_CAR as carrier signal */
	TIM_CAR->PSC = 0; /* (1) Set prescaler to 1, so APBCLK i.e 48MHz*/
	TIM_CAR->ARR = 1200; /* (2) Set ARR = 1200, as timer clock is 48MHz the frequency is 40kHz*/
	TIM_CAR->CCR1 = (uint16_t)(1200 / 2); /* (3) Set CCRx = 1200/2, , the signal will have a 50% duty cycle*/
	TIM_CAR->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; /* (4) Select PWM mode 1 on OC1 (OC1M = 110), enable preload register on OC1 (OC1PE = 1)*/
	TIM_CAR->CCER |= TIM_CCER_CC1E; /* (5) Select active high polarity on OC1 (CC1P = 0, reset value), enable the output on OC1 (CC1E = 1)*/
	TIM_CAR->BDTR |= TIM_BDTR_MOE; /* (6) Enable output (MOE = 1)*/

	/* Configure TIM_ENV is the modulation envelope */
	TIM_ENV->PSC = 0; /* (1) Set prescaler to 1, so APBCLK i.e 48MHz*/
	TIM_ENV->ARR = 28800; /* (2) Set ARR = 28800, as timer clock is 48MHz the period is 600 us*/
	TIM_ENV->CCMR1 |= TIM_CCMR1_OC1M_2; /* (3) Select Forced inactive on OC1 (OC1M = 100)*/
	TIM_ENV->CCER |= TIM_CCER_CC1E; /* (4) Select active high polarity on OC1 (CC1P = 0, reset value), enable the output on OC1 (CC1E = 1)*/
	TIM_ENV->BDTR |= TIM_BDTR_MOE; /* (5) Enable output (MOE = 1)*/
	TIM_ENV->DIER |= TIM_DIER_UIE; /* (6) Enable Update interrupt (UIE = 1)*/

	/* Enable and reset TIM_CAR only */
	TIM_ENV->CR1 |= TIM_CR1_CEN;
	TIM_CAR->CR1 |= TIM_CR1_CEN; /* (1) Enable counter (CEN = 1), select edge aligned mode (CMS = 00, reset value), select direction as upcounter (DIR = 0, reset value)*/
	TIM_CAR->EGR |= TIM_EGR_UG; /* (2) Force update generation (UG = 1)*/

	/* Configure TIM_ENV interrupt */
	NVIC_EnableIRQ(TIM16_IRQn); /* (1) Enable Interrupt on TIM_ENV*/
	NVIC_SetPriority(TIM16_IRQn,0); /* (2) Set priority for TIM_ENV*/

	SendOperationReady = 1;
}


/*
 * Initialize IR_OUT on PB9 for Nikon
 *
 * The following configuration is for RC5 standard
 * TIM16 is used for the envelope while TIM17 is used for the carrier
 */
void initNikonIR(){
#define TIM_ENV TIM16
#define TIM_CAR TIM17

	/* Configure peripheral clocks and GPIO*/
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN | RCC_APB2ENR_TIM17EN | RCC_APB2ENR_SYSCFGCOMPEN; /* (1) Enable the peripheral clocks of Timer 16 and 17 and SYSCFG*/
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; /* (2) Enable the peripheral clock of GPIOB*/
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODER9)| GPIO_MODER_MODER9_1; /* (3) Select alternate function mode on GPIOB pin 9*/
	GPIOB->AFR[1] &= ~(0x0F << ((9 - 8) * 4)); /* (4) Select AF0 on PB9 in AFRH for IR_OUT (reset value)*/
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_I2C_FMP_PB9; /* (5) Enable the high sink driver capability by setting I2C_PB9_FM+ bit in SYSCFG_CFGR1*/


	/* Configure TIM_CAR as carrier signal */
	TIM_CAR->PSC = 0; /* (1) Set prescaler to 1, so APBCLK i.e 48MHz*/
	TIM_CAR->ARR = 1200; /* (2) Set ARR = 1200, as timer clock is 48MHz the frequency is 40kHz*/
	TIM_CAR->CCR1 = (uint16_t)(1200 / 2); /* (3) Set CCRx = 1200/2, , the signal will have a 50% duty cycle*/
	TIM_CAR->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE; /* (4) Select PWM mode 1 on OC1 (OC1M = 110), enable preload register on OC1 (OC1PE = 1)*/
	TIM_CAR->CCER |= TIM_CCER_CC1E; /* (5) Select active high polarity on OC1 (CC1P = 0, reset value), enable the output on OC1 (CC1E = 1)*/
	TIM_CAR->BDTR |= TIM_BDTR_MOE; /* (6) Enable output (MOE = 1)*/

	/* Configure TIM_ENV is the modulation envelope */
	TIM_ENV->PSC = 0; /* (1) Set prescaler to 1, so APBCLK i.e 48MHz*/
	TIM_ENV->ARR = 28800; /* (2) Set ARR = 28800, as timer clock is 48MHz the period is 600 us*/
	TIM_ENV->CCMR1 |= TIM_CCMR1_OC1M_2; /* (3) Select Forced inactive on OC1 (OC1M = 100)*/
	//	TIM_ENV->CCER |= TIM_CCER_CC1E; /* (4) Select active high polarity on OC1 (CC1P = 0, reset value), enable the output on OC1 (CC1E = 1)*/
	TIM_ENV->BDTR |= TIM_BDTR_MOE; /* (5) Enable output (MOE = 1)*/
	TIM_ENV->DIER |= TIM_DIER_UIE; /* (6) Enable Update interrupt (UIE = 1)*/

	/* Enable and reset TIM_CAR only */
	TIM_ENV->CR1 |= TIM_CR1_CEN;
	TIM_CAR->CR1 |= TIM_CR1_CEN; /* (1) Enable counter (CEN = 1), select edge aligned mode (CMS = 00, reset value), select direction as upcounter (DIR = 0, reset value)*/
	TIM_CAR->EGR |= TIM_EGR_UG; /* (2) Force update generation (UG = 1)*/

	/* Configure TIM_ENV interrupt */
	NVIC_EnableIRQ(TIM16_IRQn); /* (1) Enable Interrupt on TIM_ENV*/
	NVIC_SetPriority(TIM16_IRQn,1); /* (2) Set priority for TIM_ENV*/

	//SendOperationReady = 1;
}



//TODO
/**
 * Description: This function handles TIM_16 interrupt request.
 * This interrupt subroutine computes the laps between 2
 * rising edges on T1IC.
 * This laps is stored in the "Counter" variable.
 */
void TIM16_IRQHandler(void)
{
	startManchester = 1;
	uint8_t bit_msg = 0;
	if (startManchester == 1)
	{
		if ((SendOperationReady == 1)
				&& (BitsSentCounter < 65))
		{
			if (BitsSentCounter < 64)
			{
				SendOperationCompleted = 0x00;
				bit_msg = (uint8_t)((ManchesterCodedMsg >> BitsSentCounter)& 1);
				if (bit_msg== 1)
				{
					/* Force active level - OC1REF is forced high */
					TIM_ENV->CCMR1 |= TIM_CCMR1_OC1M_0;
				}
				else
				{
					/* Force inactive level - OC1REF is forced low */
					TIM_ENV->CCMR1 &= (uint16_t)(~TIM_CCMR1_OC1M_0);
				}
				BitsSentCounter++;
			}
			else{
				BitsSentCounter=0;
			}

		}
		else
		{

			SendOperationCompleted = 0x01;
			SendOperationReady = 0;
			BitsSentCounter = 0;
		}
	}
	startManchester = 0;
	/* Clear TIM_ENV update interrupt */
	TIM_ENV->SR &= (uint16_t)(~TIM_SR_UIF);
}

void sonySnapshot()
{
	NVIC_EnableIRQ(TIM16_IRQn);
	delay_ms(150);
	NVIC_DisableIRQ(TIM16_IRQn);
	delay_ms(150);

}

/*
 * Initializes tilt servo on PB4 using TIM3_CH1.
 * Uses PWM: frequency is 100KHz, period of 20ms
 */
void initTiltServo(){

	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;  /* Enable GPIO */
	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN; /* Enable TIM3_CH1 */

	GPIOB -> MODER |= 0b10 << 8; /* Set alternate function mode */
	GPIOB -> AFR[0] |= 0b0001<<16; /* Select alternate function 1 for TIM3_CH1 */

	/* TODO: Enable UEV interrupt */
	//TIM3 -> DIER |= TIM_DIER_UIE;

	TIM3 -> PSC |= 479;//sets frequency to 100KHz
	TIM3 -> ARR = 2000; //threshold value sets period to 20ms

	TIM3->CCR1 = 150; /* (3) Set CCRx = 150, the signal will be high during 1.5ms*/
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1
			| TIM_CCMR1_OC1PE; /* (4) Select PWM mode 1 on OC1 (OC1M = 110), enable preload register on OC1 (OC1PE = 1)*/
	TIM3->CCER |= TIM_CCER_CC1E; /* (5) Select active high polarity on OC1 (CC1P = 0, reset value), enable the output on OC1 (CC1E = 1)*/
	TIM3->BDTR |= TIM_BDTR_MOE; /* (6) Enable output (MOE = 1)*/
	TIM3->CR1 |= TIM_CR1_CEN; /* (7) Enable counter (CEN = 1) select edge aligned mode (CMS = 00, reset value) select direction as upcounter (DIR = 0, reset value)*/
	TIM3->EGR |= TIM_EGR_UG; /* (8) Force update generation (UG = 1)*/
}

/*
 * Initializes pan servo on PB3 using TIM2_CH2.
 * Uses PWM: frequency is 100KHz, period of 20ms
 */
void initPanServo(){

	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;  /* Enable GPIO */
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN; /* Enable TIM2_CH2 */

	GPIOB -> MODER |= 0b10 << 6; /* Set alternate function mode */
	GPIOB -> AFR[0] |= 0b0010<<12; /* Select alternate function 2 for TIM2_CH2 */

	TIM2 -> PSC |= 479;//sets frequency to 100KHz
	TIM2 -> ARR = 2000; //threshold value sets period to 20ms

	TIM2->CCR2 = 150; /* (3) Set CCRx = 150, the signal will be high during 1.5ms*/
	TIM2->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1
			| TIM_CCMR1_OC2PE; /* (4) Select PWM mode 1 on OC1 (OC1M = 110), enable preload register on OC1 (OC1PE = 1)*/
	TIM2->CCER |= TIM_CCER_CC2E; /* (5) Select active high polarity on OC1 (CC1P = 0, reset value), enable the output on OC1 (CC1E = 1)*/
	TIM2->BDTR |= TIM_BDTR_MOE; /* (6) Enable output (MOE = 1)*/
	TIM2->CR1 |= TIM_CR1_CEN; /* (7) Enable counter (CEN = 1) select edge aligned mode (CMS = 00, reset value) select direction as upcounter (DIR = 0, reset value)*/
	TIM2->EGR |= TIM_EGR_UG; /* (8) Force update generation (UG = 1)*/
}


void tiltServo(uint32_t value){

	TIM3 -> CCR1 = value;
	delay_ms(100);
	TIM3 -> CCR1 = 0;
}

void panServo(int toggle){
	int cw = 128; // 15 degree change clockwise
	int ccw = 172;
	int off = 0;

	if (toggle == 1)
	{
		TIM2-> CCR2 = cw;
		delay_ms(100);
		TIM2-> CCR2 = 0;
	}


}
//x is the number of photos taken in the left to right or x direction
//for each x position the camera will take two photos.
void panoXby2(int _x)
{
	int tilt[] = {154, 185}; //154  15 degree up, 185 down
	int pan = 0;

	for(int x = 0; x < _x; x++)
	{
		panServo(pan);
		pan = 1;
		for (int y = 0; y < 2; y++)
		{
			delay_ms(1000);
			tiltServo(tilt[y]);
			delay_ms(1000);
			sonySnapshot();
			delay_ms(1000);

		}
	}
}


int main(void){
	initSonyIR();
	initTiltServo();
	initPanServo();
	delay_init();

    // pan indefintely with two horzontal photos
	panoXby2(4);

	//to take a picture set the SendOperationReady bit high
	while(1){
		__NOP();

	} // loop indefinitely
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
