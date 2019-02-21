# LCD

- Uso com LM016;
- Padrão 4 bits, para usar com 8 bits deve-se definir LCD_8_BITS em ./Inc/lcd.h.

``` c
.
.
.
#include "stm32f1xx_hal.h"

#ifndef LCD_H_
#define LCD_H_

#define LCD_8_BITS

#define LCD_PIN_E        GPIO_PIN_0
#define LCD_GPIO_E        GPIOA
.
.
.
#endif
.
.
.
```