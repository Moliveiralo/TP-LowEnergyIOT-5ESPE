/*Author: Alexandre Boyer
 * Date: 14 Aug. 2024
 */
/* Project L476_nRF24L01_MultiCeiver_PRX for STM32L476 mounted on Nucleo board:
 * Demo code for 6:1 Multiceiver network configuration, based on the transceiver Nordic nRF24L01+.
 * The link layer protocol Enhanced ShockBurst (ESB) is used, with automatic acknowledgment.
 * In this network, up to 6 primary transmitters (PTX) can transmit data to 1 primary receiver (PRX)
 * on the same RF channel and 6 logical channels (or data pipes) with unique addresses (known at PTX
 * and PRX side).
 * This project configures the PRX node. It is in continuous RX mode. Each time a valid packet is
 * received, the packet, the address and the number of bytes are transmitted to the host PC through USART2.
 *
 * The clock configuration is the default one (Sysclk = 80 MHz, derived from MSI and PLL).
 * Configured GPIO (even if not used in this project):
 *  > User_LED : PB13
 *  > User_Button (Blue Button) : PC13
 *  > SPI1 to communicate with transceiver nRF24L01 (data rate = 5 Mbps):
 *  	> SPI1_SCK : PA5
 *  	> SPI1_MISO : PA6
 *  	> SPI1_MOSI : PA7
 *  	> NSS not controlled by the SPI1 peripheral but software-controlled (pin nRF_CSN)
 *  > nRF_CSN : PA4 (nRF24L01 SPI Chip Select)
 *  > nRF_CE : PA8 (nRF24L01 Chip Enable pin - TX/RX mode)
 *  > nRF_IRQ : PB0 (EXTI0) (nRF24L01 interrupt pin - not used in this lab)
 *  > USART2_TX : PA2
 *  > USART2_RX : PA3
 */

/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */



#include "main.h"
#include "gpio.h"
#include "clock.h"
#include "spi.h"
#include "usart.h"
#include "RadioFunctions.h"
#include "nrf24.h"


uint8_t channel_nb = 60; //n° du canal radio utilisé (//channel 60 --> 2460 MHz)

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

  //configuration du transceiver en mode PRX
  Init_Transceiver();
  Config_RF_channel(channel_nb,nRF24_DR_250kbps,nRF24_TXPWR_12dBm);
  Config_CRC(CRC_Field_On, CRC_Field_1byte);
  Config_PRX_adress(5,nRF24_AA_ON,Default_pipe_address); //Adresse sur 5 bits
  Config_ESB_Protocol(nRF24_ARD_500us,10);
  //on sort du mode power down
  nRF24_SetPowerMode(nRF24_PWR_UP);
  Delay_ms(2); //Attente 2 ms (1.5 ms pour la sortie du mode power down).

  //Entrée en mode RX
  nRF24_SetOperationalMode(nRF24_MODE_RX);
  StartListen();
  //Ecoute continue
  Continuous_RX_Listen(500);
}


void SysTick_Handler()
{
	//do nothing ...
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
