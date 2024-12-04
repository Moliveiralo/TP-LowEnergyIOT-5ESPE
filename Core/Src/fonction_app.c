/*
 * fonction_app.c
 *
 *  Created on: Dec 4, 2024
 *      Author: yorgo
 */
#include "fonction_app.h"


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
