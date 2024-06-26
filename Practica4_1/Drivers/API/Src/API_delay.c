
#include "API_delay.h"

/*Recibe el puntero a la estructura delay correspondiente para ser inicializada, junto a la
 * duración deseada. No retorna nada*/
void delayInit(delay_t *delay, tick_t duration) {

	if (delay == NULL || duration == 0)
	Error_Handler();

	delay->startTime = 0;
	delay->duration = duration;
	delay->running = false;

}

/*Recibe el puntero a la estructura delay correspondiente para consultar si el tiempo
 * de delay a concluido o inicia el delay si no ha sido iniciado. Retorna un bool con
 * true si cumplió el tiempo o false si aún no*/
bool_t delayRead(delay_t *delay) {

	if (delay == NULL)
		Error_Handler();
	/*Inicializa si este aún no lo estaba*/
	if (delay->running == false) {

		delay->startTime = HAL_GetTick();
		delay->running = true;
		return false;

	} else {
		/*Verifica si se cumplio el tiempo*/
		if ((HAL_GetTick() - delay->startTime) >= delay->duration) {
			delay->running = false;
			return true;
		}

	}

	return false;

}

/*Recibe la duración y el puntero a la estructura delay, para ingresar en este
 * el valor de la duración. No retorna nada.*/
void delayWrite(delay_t *delay, tick_t duration) {

	if (delay == NULL || duration == 0)
		Error_Handler();

	delay->duration = duration;

}



static void Error_Handler(void) {
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1) {
	}
}
