/*Author: Alexandre Boyer
 * Date: 14 Aug. 2024
 */
/* Project L476_LoPoSo_LEDBlink_2043 for STM32L476 mounted on Nucleo board:
 * Starting project for Low Power Software lab (5ESPE) - Version 2024-25.
 * tThe user LED (mounted on pin PB13) is flashed every 2 seconds for 50 ms.
 * The time base is provided by Systick (100 ticks per second), which generates ISR every 10 ms.
 * The clock configuration is the default one (Sysclk = 80 MHz, derived from MSI and PLL).
 * All the GPIO used in the Low Power Software lab has been configures (even if not used in this project):
 *  > User_LED : PB13
 *  > User_Button (Blue Button) : PC13
 *  > Clock_monitor (to monitor bus clock deviation) : PC10
 *  > SPI1 to communicate with transceiver nRF24L01 (data rate = 5 Mbps):
 *  	> SPI1_SCK : PA5
 *  	> SPI1_MISO : PA6
 *  	> SPI1_MOSI : PA7
 *  	> NSS not controlled by the SPI1 peripheral but software-controlled (pin nRF_CSN)
 *  > nRF_CSN : PA4 (nRF24L01 SPI Chip Select)
 *  > nRF_CE : PA8 (nRF24L01 Chip Enable pin - TX/RX mode)
 *  > nRF_IRQ : PB0 (EXTI0) (nRF24L01 interrupt pin - not used in this lab)
 *  > optional: PA2 and PA3 (USART2_TX and USART2_RX) for RF transceiver debug
 *
 */



#include "main.h"
#include "gpio.h"
#include "clock.h"
#include "spi.h"
#include "usart.h"
#include "nrf24.h"
#include "RadioFunctions.h"
#include <stdio.h>


volatile unsigned int ticks = 0; //pour la gestion des intervalles de temps. 1 tick = 10 ms.
volatile int blue_mode = 0; //pour savoir si on est dans le mode "Blue mode"
volatile int old_blue = 0;
volatile int expe = 0; //pour la sauvegarde du numéro de l'expérience
uint32_t testing ;
int status;
LL_RTC_InitTypeDef RTC_InitStruct;

uint8_t channel_nb = 60; //n° du canal radio utilisé (//channel 60 --> 2460 MHz)
uint8_t adr_data_pipe_used = 1; //numéro du data pipe utilisé pour la transmission (de 0 à 5)

int main(void)
{

	/*clock domains activation*/
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// config GPIO
	GPIO_init();
	//config clock
	SystemClock_Config_80M();
	//config bus SPI1 (pour la communication avec le transceiver nRF24L01)
	SPI1_Init();
	//config USART2
	USART2_Init();
	//Init to RTC
	LL_RTC_StructInit(&RTC_InitStruct);
	LL_RTC_Init(RTC, &RTC_InitStruct);
	// config systick avec interrupt
	mySystick( SystemCoreClock / 100 );	// 100 Hz --> 10 ms
	LL_RTC_BAK_SetRegister(RTC, 3, expe);
	testing = LL_RTC_BAK_GetRegister(RTC, 3);
	expe = LL_RTC_BAK_GetRegister(RTC, 3);
	// config systick avec interrupt
	mySystick( SystemCoreClock / 100 );	// 100 Hz --> 10 ms
	while (expe < 7)
	{
		status = BLUE_BUTTON();
		if ( 1 == status)
		{
			LL_mDelay(100);
			expe++;
			LL_RTC_BAK_SetRegister(RTC, 3, expe);
			testing = LL_RTC_BAK_GetRegister(RTC, 3);
		}
	}

//	//// ----------------------------------------------------------------------------
//	//// 									PTX
//	//// 					ENVOI DE MESSAGES VIA LE TRANCEIVER RF
//	//// ----------------------------------------------------------------------------
//	//configuration du transceiver en mode PTX
//	Init_Transceiver();
//	Config_RF_channel(channel_nb,nRF24_DR_250kbps,nRF24_TXPWR_18dBm);
//	Config_CRC(CRC_Field_On, CRC_Field_1byte);
//	//Adresse sur 5 bits. Transmission sur le data pipe adr_data_pipe_used.
//	Config_PTX_adress(5,Default_pipe_address,adr_data_pipe_used,nRF24_AA_ON);
//	Config_ESB_Protocol(nRF24_ARD_1000us,10);
//	//on sort du mode power down
//	nRF24_SetPowerMode(nRF24_PWR_UP);
//	Delay_ms(2); //Attente 2 ms (1.5 ms pour la sortie du mode power down).
//
//	//Entrée en mode TX
//	nRF24_SetOperationalMode(nRF24_MODE_TX);
//	StopListen();
//
//	//configuration interruption Systick (attention, il n'y a quue 23 bits dans le registre load ...
//	//mySystick( SystemCoreClock * 2 );	// 0.5 Hz --> 2 s
//	//on va partir sur une période de 100 ms
//	mySystick( SystemCoreClock /10 ); //10 Hz --> 0.1 s
//
//	int expNumber = 0;
//	int packetNumber = 0;
//
//	// 1 char = 1 octet, donc chaque message a une taille max de 32 char
//	char messageToSend[33];  // 32 char + caractère de fin de chaîne
//
//	// Création du message à envoyer			    |   NOMS DU BINOME   | EXPN | NBPAQUET |
//	snprintf(messageToSend, sizeof(messageToSend), "O-LOPES_TETAZ_CHALHOUB_EXP%d_%d   ", expNumber, packetNumber);
//
//	// Appel de la fonction Transmit_Message (exemple d'appel)
//	Transmit_Message((uint8_t *)messageToSend, 32);



//	//// ----------------------------------------------------------------------------
//	//// 									PRX
//	//// 				RECEPTION DE MESSAGES VIA LE TRANCEIVER RF
//	//// ----------------------------------------------------------------------------
//	//configuration du transceiver en mode PRX
//	Init_Transceiver();
//	Config_RF_channel(channel_nb,nRF24_DR_250kbps,nRF24_TXPWR_12dBm);
//	Config_CRC(CRC_Field_On, CRC_Field_1byte);
//	Config_PRX_adress(5,nRF24_AA_ON,Default_pipe_address); //Adresse sur 5 bits
//	Config_ESB_Protocol(nRF24_ARD_500us,10);
//	//on sort du mode power down
//	nRF24_SetPowerMode(nRF24_PWR_UP);
//	Delay_ms(2); //Attente 2 ms (1.5 ms pour la sortie du mode power down).
//
//	//Entrée en mode RX
//	nRF24_SetOperationalMode(nRF24_MODE_RX);
//	StartListen();
//
//	//Ecoute continue
//	Continuous_RX_Listen(500);

	while (1)
	{

	}
}

// systick interrupt handler --> allumage LED toutes les 2 s pendant 50 ms.
//Scrutation de l'état du bouton bleu  (pas d'action à ce stade).
void SysTick_Handler()
{
	unsigned int subticks;

	//scrutation bouton bleu
	ticks += 1;
	if	( BLUE_BUTTON() )
	{
		if	( old_blue == 0 )
			blue_mode = 1;
		old_blue = 1;
	}
	else 	old_blue = 0;

	//gestion de l'allumage de la LED
	subticks = ticks % 200;
	if	( subticks == 0 )
		LED_GREEN(1);
	else if	( subticks == 5 )
		LED_GREEN(0);
}



/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
