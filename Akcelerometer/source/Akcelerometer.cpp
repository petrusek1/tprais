/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Akcelerometer.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <stdint-gcc.h>
#include <tgmath.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_pit.h"


#include "MMA8451Q/MMA8451Q.h"
#include "Timer/Timer.h"

#define ACCELL_ADDRESS 0x1DU

#define PI 		(float)		3.1415
#define Fc 		(float)		5
#define DELTA_T (float)		0.1

static const float alfa = (2*PI*DELTA_T*Fc)/((2*PI*DELTA_T*Fc) + 1) ; // low pass

// ** Predefinitions **

#if defined(__cplusplus)
extern "C" {
#endif
	volatile int flagIRQ = 0;
	//surove dáta
	float zakladneData[3]= {0, 0, 0};
	//filter na dáta
	float odfiltrovaneData[3] = {0,0,0};
	//filter na stare dáta
	static float stareodfiltrovaneData[3] = {0,0,0};
	// pre uhly
	float allfa, beta, gama = 0;
	void PIT_IRQHandler();
} //extern C



//inicializacia
void BOARD_INIT();
//filter jednej osi
float filterOneAxis(float input, float oldOutput);
//filter
void filter(float* zakladneData, float *stareData, float* noveData);
//ulhy
float uhly(float* data, uint8_t axis);

MMA8451Q* accel;



// *** Main function *** inicializacia
int main(void)
{

    BOARD_INIT();
    Timer timer;
    accel = new MMA8451Q(ACCELL_ADDRESS);
    accel->init();

    timer.setTime((uint64_t)DELTA_T * 100);
    timer.starTimer();

    while(1)
    {}

    return 0 ;
}


//inicializacia dosky, ...
void BOARD_INIT()
{
	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
}



void PIT_IRQHandler(){
	//vyčistenie
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);

	accel->getAccAllAxis(zakladneData);
	filter(zakladneData, stareodfiltrovaneData, odfiltrovaneData);


	/* Vypis gravitacne sily */
	//	PRINTF("x: %.3f,y: %.3f,z: %.3f \n\r",odfiltrovaneData[0] , odfiltrovaneData[1], odfiltrovaneData[2]);

	/*Vypis zrychlenie na jednolivych osiach*/
	PRINTF("x: %.3f y: %.3f z: %.3f \n\r",stareodfiltrovaneData[0] , stareodfiltrovaneData[1], stareodfiltrovaneData[2]);



    allfa = uhly(stareodfiltrovaneData, 1);
	beta = uhly(stareodfiltrovaneData, 2);
	gama = uhly(stareodfiltrovaneData, 3);

	/*Vypis uhol naklonu*/
	//PRINTF("a: %.1f° b: %.1f° g:  %.1f° \n\r",allfa, beta, gama);
}

//filter pre jednu os
float filterOneAxis(float input, float oldOutput)
{
		return ((1 -alfa) * oldOutput + alfa * input);
}


//metoda na filtrovanie dát

void filter(float* pZakladneData, float *pStareData, float* pNoveData)
{
	for(int i = 0; i < 3; i++)
	{
		pNoveData[i] = (((1 -alfa) * pStareData[i]) + (alfa * pZakladneData[i]));  //LOW
		pStareData[i] = pNoveData[i];
		pNoveData[i] = pStareData[i] - pNoveData[i];
	}

}


//metoda na určenie uhlov náklonu
float uhly(float* data, uint8_t axis){
	if(axis == 1){
		return (180/PI) * atanf(data[0]/(sqrtf( powf(data[1],2) + powf(data[2],2) )));
	} else if(axis == 2){
		return (180/PI) * atanf(data[1]/(sqrtf( powf(data[0],2) + powf(data[2],2) )));
	} else {
		return (180/PI) * atanf(data[2]/(sqrtf( powf(data[1],2) + powf(data[0],2) )));
	}
}
