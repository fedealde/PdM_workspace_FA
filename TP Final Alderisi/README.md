TP Final PdM - Alderisi Federico

Este proyecto se basa en la propuesta de proyecto final de la especialidad CESE UBA. 

Este primer desarrollo se enfoca en un dosificador controlado, el cual ingresamos dosis desada, sensamos nivel del tanque y activamos o desactivamos una bomba. El ingreso de datos es a través de un teclado matricial de 4x4, estos se verifican para luego mostrarlos a través de un display LCD 20x04, con el cuál se comunica a través de un códulo I2C. Además, un sensor de nivle simulado con un potenciómetro dispara una alarma por bajo nivel de líquido, activando un buzzer, apagando la bomba de dosificacion y enviando mensajes periodicos por UART respecto al estado de alarma (consta de una alarma de nivel bajo y extremadamente bajo)

El proyecto consta de los módulos API correspondientes a cada configuración de periféricos GPIO, I2C, UART, Keypad y ADC. Estos tienen su archivo port que permiten la abstracción del hardware.

Consta de una FSM que permite la funcionalidad de ingreso de datos, y sub FSM para el manejo del teclado. Además consta de la verificacion de datos, consulta de ingreso de datos, sensado automático, envío de mensaje de alarma y accionamiento de una bomba.

Se desarrolló a través de una NUCLEO 429zi de STM32, utilizando STM32 CubeIDE.

El proyecto se desarrolló utilizando MX solo para el código de ADC por lo que se debe desactivar la autogeneración de código, en caso de ser modificado.
Prototipo:

![Prototipo](https://github.com/fedealde/PdM_workspace_FA/assets/62813604/26d14371-2ef0-4478-850a-f56e7ffe8820)

Source files
![Sources](https://github.com/fedealde/PdM_workspace_FA/assets/62813604/1fffc322-ba3a-48cd-9a6d-e41747aca9e8)

API Drivers
![APIs Driver](https://github.com/fedealde/PdM_workspace_FA/assets/62813604/a8d00897-d41b-4e87-85eb-69b1ffa1fdeb)

UART
![Uart](https://github.com/fedealde/PdM_workspace_FA/assets/62813604/b0e59e98-a73d-4325-a6bb-f9aab5720114)


