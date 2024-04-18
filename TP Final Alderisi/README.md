TP Final PdM - Alderisi Federico

Este proyecto se basa en la propuesta de proyecto final de la especialidad CESE UBA. 

Este primer desarrollo se enfoca en un dosificador controlado, el cual ingresamos dosis desada y sensamos nivel. El ingreso de datos es a través de un teclado matricial de 4x4, la verificación de los datos ingresados, los cuales se muestran a través de un display LCD 20x04, con el cuál se comunica a través de un códulo I2C. Además, un sensor de nivle simulado con un potenciómetro dispara una alarma por bajo nivel de líquido, activando un buzzer, apagando la bomba de dosificacion y enviando mensajes periodicos por UART respecto al estado de alarma (consta de una alarma de nivel bajo y extremadamente bajo)

El proyecto consta de los módulos API correspondientes a cada configuración de periféricos GPIO, I2C, UART, Keypad y ADC.

Consta de una FSM que permite la funcionalidad de ingreso de datos, verificacion de datos, consulta de ingreso de datos, sensado automático y accionamiento de una bomba.

Se desarrolló a través de una NUCLEO 429zi de STM32, utilizando STM32 CubeIDE.

El proyecto se desarrolló utilizando MX solo para el código de ADC por lo que se debe desactivar la autogeneración de código, en caso de ser modificado.
