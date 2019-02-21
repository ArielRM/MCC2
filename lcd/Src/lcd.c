#include "lcd.h"

static inline void lcd_pulse_enable()
{
	HAL_GPIO_WritePin(LCD_GPIO_E, LCD_PIN_E, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(LCD_GPIO_E, LCD_PIN_E, GPIO_PIN_RESET);
	HAL_Delay(1);
}

static inline GPIO_PinState lcd_get_state(uint32_t data)
{
	if (data)
			return GPIO_PIN_SET;
	else
			return GPIO_PIN_RESET;
}

static void lcd_write_data_pins(uint32_t data)
{
#ifdef LCD_8_BITS
	HAL_GPIO_WritePin(LCD_GPIO_D0, LCD_PIN_D0, lcd_get_state(data & 0x00000001));
	HAL_GPIO_WritePin(LCD_GPIO_D1, LCD_PIN_D1, lcd_get_state(data & 0x00000002));
	HAL_GPIO_WritePin(LCD_GPIO_D2, LCD_PIN_D2, lcd_get_state(data & 0x00000004));
	HAL_GPIO_WritePin(LCD_GPIO_D3, LCD_PIN_D3, lcd_get_state(data & 0x00000008));
	HAL_GPIO_WritePin(LCD_GPIO_D4, LCD_PIN_D4, lcd_get_state(data & 0x00000010));
	HAL_GPIO_WritePin(LCD_GPIO_D5, LCD_PIN_D5, lcd_get_state(data & 0x00000020));
	HAL_GPIO_WritePin(LCD_GPIO_D6, LCD_PIN_D6, lcd_get_state(data & 0x00000040));
	HAL_GPIO_WritePin(LCD_GPIO_D7, LCD_PIN_D7, lcd_get_state(data & 0x00000080));
#else
	HAL_GPIO_WritePin(LCD_GPIO_D4, LCD_PIN_D4, lcd_get_state(data & 0x00000001));
	HAL_GPIO_WritePin(LCD_GPIO_D5, LCD_PIN_D5, lcd_get_state(data & 0x00000002));
	HAL_GPIO_WritePin(LCD_GPIO_D6, LCD_PIN_D6, lcd_get_state(data & 0x00000004));
	HAL_GPIO_WritePin(LCD_GPIO_D7, LCD_PIN_D7, lcd_get_state(data & 0x00000008));
#endif
}

static void lcd_send_byte(uint32_t byte)
{
	#ifndef LCD_8_BITS
		lcd_write_data_pins(byte >> 4);
		lcd_pulse_enable();
	#endif

	lcd_write_data_pins(byte);
	lcd_pulse_enable();
}


void lcd_send_command(uint32_t cmd)
{
	HAL_GPIO_WritePin(LCD_GPIO_RS, LCD_PIN_RS, GPIO_PIN_RESET);
	lcd_send_byte(cmd);
}

void lcd_init(void)
{
	// inicialização comum para interfaces de 4 e 8 bits
	HAL_GPIO_WritePin(LCD_GPIO_E, LCD_PIN_E, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_GPIO_RS, LCD_PIN_RS, GPIO_PIN_RESET);

	// Wait for more than 15 ms after VCC rises to 4.5 V
	HAL_Delay(20);

	// sends instruction 0b0011XXXX
	lcd_write_data_pins(0x03);
	lcd_pulse_enable();

	// Wait for more than 4.1 ms
	HAL_Delay(5);

	// sends instruction 0b0011XXXX
	lcd_pulse_enable();

	//Wait for more than 100 us
    HAL_Delay(1);

    // sends instruction 0b0011XXXX
    lcd_pulse_enable();

#ifndef LCD_8_BITS
    // Set interface to be 4 bits long.
	lcd_write_data_pins(0x02);
	lcd_pulse_enable();

	//interface de 4 bits 2 linhas
	lcd_send_command(0x00000028);
#else
	//interface de 8 bits 2 linhas
	lcd_send_command(0x00000038);
#endif

    //desliga o display
	lcd_send_command(0x08);
    //limpa todo o display
	lcd_send_command(0x01);
    //mensagem aparente cursor inativo não piscando
	lcd_send_command(0x0C);
    //inicializa cursor na primeira posição a esquerda - 1a linha
	lcd_send_command(0x80);

}

void lcd_write(const char *txt)
{
	HAL_GPIO_WritePin(LCD_GPIO_RS, LCD_PIN_RS, GPIO_PIN_SET);
	uint32_t i;
	for (i = 0; txt[i] != '\0'; i++)
	{
		lcd_send_byte(txt[i]);
	}
}
