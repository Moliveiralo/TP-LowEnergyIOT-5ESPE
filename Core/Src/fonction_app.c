/*
 * fonction_app.c
 *
 *  Created on: Dec 4, 2024
 *      Author: yorgo
 */
#include "fonction_app.h"


void cold_start(){

	LL_PWR_EnableBkUpAccess(); // A vérifier si c'est nécessaire

	LL_RCC_ForceBackupDomainReset();
	LL_RCC_ReleaseBackupDomainReset();

	LL_RCC_LSE_Enable();
	while (LL_RCC_LSE_IsReady() != 1);

	LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);

	LL_RCC_EnableRTC();

	LL_RTC_DisableWriteProtection(RTC);
	LL_RTC_SetAsynchPrescaler(RTC, 0x7F);
	LL_RTC_SetSynchPrescaler(RTC, 0xFF);
	LL_RTC_EnableWriteProtection(RTC);
	LL_RTC_BAK_SetRegister(RTC, LL_RTC_BKP_DR0, 1);

}


void hot_start(){
	LL_PWR_EnableBkUpAccess(); // A vérifier si c'est nécessaire

	LL_RCC_EnableRTC();

	LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);

	if (LL_RCC_LSE_IsReady() != 1) {
		LL_RCC_LSE_Enable();
		while (LL_RCC_LSE_IsReady() != 1);
	}
	if (!LL_RTC_IsActiveFlag_INITS(RTC)) {
		LL_RTC_DisableWriteProtection(RTC);
		LL_RTC_SetAsynchPrescaler(RTC, 0x7F);
		LL_RTC_SetSynchPrescaler(RTC, 0xFF);
		LL_RTC_EnableWriteProtection(RTC);

	}
}

void configMsiLse(){
	//Calibration MSI vs LSE
	RCC->CR |= (1 << 2); // on met à 1 le bit MSIPLLEN de RCC_CR
}

void Sleep()
{
	//Config mode sleep
	SCB->SCR &= ~(1 << 2);  //SLEEPDEEP à 0
	SCB->SCR |= (1 << 1);	//SLEEPEXIT à 1

	//entree mode Sleep jusqua prochaine interrup
	__WFI();  //attente interruption

	//sortie du sleep mode avec le reset
}
