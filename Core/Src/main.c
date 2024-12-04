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

void expe_counter() {

	if (BLUE_BUTTON()) {
		expe = LL_RTC_BAK_GetRegister(RTC, LL_RTC_BKP_DR0);
		if (9 == expe){ expe = 1; }
		LL_RTC_BAK_SetRegister(RTC, LL_RTC_BKP_DR0, expe);
	}
}


int main(void)
{

	/*clock domains activation*/
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	// config GPIO
	GPIO_init();
	//config clock
	SystemClock_Config_80M();
	//config bus SPI1 (pour la communication avec le transceiver nRF24L01)
	SPI1_Init();
	//config USART2
	USART2_Init();

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	if (LL_RCC_LSE_IsReady() == 1) {
		hot_start();
	} else {
		cold_start();
	}
	expe_counter();

	// config systick avec interrupt
	mySystick( SystemCoreClock / 100 );	// 100 Hz --> 10 ms

	if (expe == 1) {
		SystemClock_Config_80M();
	}
	if (expe == 2) {
		SystemClock_Config_Expe2();
	}
	if (expe == 3) {
		SystemClock_Config_ExpeReste();

	}
	if (expe ==4){ //expe3 bis car non realise
		SystemClock_Config_ExpeReste();

	}
	if (expe == 5) {
		SystemClock_Config_ExpeReste();

	}
	if (expe == 6) {
		SystemClock_Config_ExpeReste();

	}
	if (expe == 7) {
		SystemClock_Config_ExpeReste();

	}
	if (expe == 8) {
		SystemClock_Config_ExpeReste();

	}

	while (1)
	{
		if (expe == 1) {
			if (blue_mode){
				Sleep();
			}
		}
		if (expe == 2) {
			if (blue_mode){
				configMsiLse();
			}
		}
		if (expe == 3) {
			if (blue_mode){
				Sleep();
			}
		}
		if (expe ==4){
			if (blue_mode){
				configMsiLse();
			}
		}
		if (expe == 5) {
			if (blue_mode){
				null;
			}
		}
		if (expe == 6) {
			if (blue_mode){
				null;
			}
		}
		if (expe == 7) {
			if (blue_mode){
				null;
			}
		}
		if (expe == 8) {
			if (blue_mode){
				null;
			}
		}
	}
}
// systick interrupt handler --> allumage LED toutes les 2 s pendant 50 ms.
//Scrutation de l'état du bouton bleu  (pas d'action à ce stade).
void SysTick_Handler()
{
	//unsigned int subticks;

	//scrutation bouton bleu
	ticks += 1;
	if	( BLUE_BUTTON() )
	{
		if	( old_blue == 0 )
			blue_mode = 1;

	}
	else 	old_blue = 0;
}


//_______________________________FONCTIONS DES EXPERIENCES______________________________________//
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






void cold_start(){

	    LL_PWR_EnableBkUpAccess();

	    // 3. Effectuer un reset du backup domain (réinitialisation des registres de sauvegarde)
	    LL_RCC_ForceBackupDomainReset();
	    LL_RCC_ReleaseBackupDomainReset();

	    // 4. Démarrer l'oscillateur LSE (Low Speed External)
	    LL_RCC_LSE_Enable();
	    while (LL_RCC_LSE_IsReady() != 1);  // Attendre que l'oscillateur LSE soit prêt

	    // 5. Configurer les prescalers du RTC (asynchrone et synchrone)
	    // Désactiver la protection en écriture des registres RTC
	    LL_RTC_DisableWriteProtection(RTC);

	    // Configurer les prescalers
	    LL_RTC_SetAsynchPrescaler(RTC, 0x7F);  // Valeur de prescaler asynchrone (à ajuster selon votre besoin)
	    LL_RTC_SetSynchPrescaler(RTC, 0xFF);   // Valeur de prescaler synchrone (à ajuster selon votre besoin)

	    // 6. Réactiver la protection en écriture des registres RTC
	    LL_RTC_EnableWriteProtection(RTC);
}


void hot_start(){
	 LL_PWR_EnableBkUpAccess();

	    // 3. Initialiser l'interface RTC-MPU avant d'accéder aux backup-registers
	    // L'interface RTC-MPU est automatiquement désactivée au démarrage, donc on l'active ici
	    LL_RCC_EnableRTC();

	    // 4. Vérifier si l'oscillateur LSE est prêt, sinon attendre
	    if (LL_RCC_LSE_IsReady() != 1) {
	        LL_RCC_LSE_Enable();
	        while (LL_RCC_LSE_IsReady() != 1);  // Attendre que l'oscillateur LSE soit prêt
	    }

	    // 5. Si nécessaire, configurer les prescalers RTC à ce moment-là
	    // (Cela peut ne pas être nécessaire à chaque démarrage "à chaud")
	    // Si vous avez besoin de reconfigurer les prescalers, il faut désactiver la protection et les reconfigurer.
	    if (!LL_RTC_IsActiveFlag_INITS(RTC)) {
	        LL_RTC_DisableWriteProtection(RTC);  // Désactiver la protection en écriture
	        LL_RTC_SetAsynchPrescaler(RTC, 0x7F); // Configurer les prescalers (exemple)
	        LL_RTC_SetSynchPrescaler(RTC, 0xFF);  // Configurer les prescalers (exemple)
	        LL_RTC_EnableWriteProtection(RTC);   // Réactiver la protection

	    }
}

//_____________________________________________________________________________________________//



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


// partie commune a toutes les utilisations du wakeup timer
void RTC_wakeup_init( int delay )
{
LL_RTC_DisableWriteProtection( RTC );
LL_RTC_WAKEUP_Disable( RTC );
while	( !LL_RTC_IsActiveFlag_WUTW( RTC ) )
	{ }
// connecter le timer a l'horloge 1Hz de la RTC
LL_RTC_WAKEUP_SetClock( RTC, LL_RTC_WAKEUPCLOCK_CKSPRE );
// fixer la duree de temporisation
LL_RTC_WAKEUP_SetAutoReload( RTC, delay );	// 16 bits
LL_RTC_ClearFlag_WUT(RTC);
LL_RTC_EnableIT_WUT(RTC);
LL_RTC_WAKEUP_Enable(RTC);
LL_RTC_EnableWriteProtection(RTC);
}

// Dans le cas des modes STANDBY et SHUTDOWN, le MPU sera reveille par reset
// causé par 1 wakeup line (interne ou externe) (le NVIC n'est plus alimenté)
void RTC_wakeup_init_from_standby_or_shutdown( int delay )
{
RTC_wakeup_init( delay );
// enable the Internal Wake-up line
LL_PWR_EnableInternWU();	// ceci ne concerne que Standby et Shutdown, pas STOPx
}

// Dans le cas des modes STOPx, le MPU sera reveille par interruption
// le module EXTI et une partie du NVIC sont encore alimentes
// le contenu de la RAM et des registres étant préservé, le MPU
// reprend l'execution après l'instruction WFI
void RTC_wakeup_init_from_stop( int delay )
{
RTC_wakeup_init( delay );
// valider l'interrupt par la ligne 20 du module EXTI, qui est réservée au wakeup timer
LL_EXTI_EnableIT_0_31( LL_EXTI_LINE_20 );
LL_EXTI_EnableRisingTrig_0_31( LL_EXTI_LINE_20 );
// valider l'interrupt chez NVIC
NVIC_SetPriority( RTC_WKUP_IRQn, 1 );
NVIC_EnableIRQ( RTC_WKUP_IRQn );
}

// wakeup timer interrupt Handler (inutile mais doit etre defini)
void RTC_WKUP_IRQHandler() {
	LL_EXTI_ClearFlag_0_31( LL_EXTI_LINE_20);
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



//	RTC AVEC REGISTER
//	//Init to RTC
//	RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN; //Enable GRP1_CLOCK
//	PWR->CR1 |= PWR_CR1_DBP; //Enable BkUpAccess
//	RCC->BDCR |= RCC_BDCR_LSEON; //Enable RCC_LSE
//	RCC->BDCR &= ~RCC_BDCR_RTCSEL; //Set RTCClockSource
//	RCC->BDCR |= RCC_BDCR_RTCSEL_0;
//	RCC->BDCR |= RCC_BDCR_RTCEN; // Enable RTC
//
//	 expe= RTC->BKP0R;
//	 if ( 1 == RTC->BKP1R)
//	 	{
//		 	 expe++;
//	 	}
//	 if ( 8 < expe)
//		{
//		 	 expe++;
//		}
//	RTC->BKP0R = expe;



// LL_RTC_BAK_SetRegister(RTC, 3, expe);
// testing = LL_RTC_BAK_GetRegister(RTC, 3);
// expe = LL_RTC_BAK_GetRegister(RTC, 3);
// // config systick avec interrupt
// mySystick( SystemCoreClock / 100 );	// 100 Hz --> 10 ms
// while (expe < 7)
// {
// 	status = BLUE_BUTTON();
// 	if ( 1 == status)
// 	{
// 		LL_mDelay(100);
// 		expe++;
// 		LL_RTC_BAK_SetRegister(RTC, 3, expe);
// 		testing = LL_RTC_BAK_GetRegister(RTC, 3);
// 	}
// }


//void Expe1()
//{
//    //Config clock deja faite
//	//Mode sleep
//	Sleep();
//}
//
//void Expe2(){
//	//Config clock
//	SystemClock_Config_Expe2();
//
//	//Config MSI
//	configMsiLse();
//}
//
//void Expe3()
//{
//	Sleep();
//}
//
//
//void Expe4(){
//	//Config clock
//	SystemClock_Config_ExpeReste();
//
//	//Config MSI
//	configMsiLse();
//}
//
//void Expe5()
//{
//	//Config clock
//	SystemClock_Config_ExpeReste();
//	//Config mode sleep
//	SCB->SCR |= (1 << 2);	//SLEEPDEEP à 1
//
//	//Mode STOP0
//	PWR->CR &= ~(1 << 2);
//
//	__WFI();
//}






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
