#include "stm32f10x_conf.h"

//define pins
#define RS_Pin GPIO_Pin_13
#define RS_Gate GPIOC
#define RW_Pin GPIO_Pin_11
#define EN_Pin GPIO_Pin_0
#define EN_Gate GPIOD
#define D4_Pin GPIO_Pin_6
#define D5_Pin GPIO_Pin_5
#define D6_Pin GPIO_Pin_4
#define D7_Pin GPIO_Pin_3
#define D_Gate GPIOE

int cursor_pos = 0;

void delay(unsigned long i)
{
	i = i*168;
	while(i--); //wait i microseconds
}

void lcd_init_8(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef LCD_Pins;
	LCD_Pins.GPIO_Mode = GPIO_Mode_Out_PP;
	LCD_Pins.GPIO_Speed = GPIO_Speed_50MHz;
	LCD_Pins.GPIO_Pin = RS_Pin | RW_Pin;
	GPIO_Init(GPIOC, &LCD_Pins); //initialize pins PC13 and PC11;

	LCD_Pins.GPIO_Pin = EN_Pin;
	GPIO_Init(GPIOD, &LCD_Pins); //initialize pin PD0;

	LCD_Pins.GPIO_Pin = D4_Pin | D5_Pin | D6_Pin | D7_Pin;
	GPIO_Init(GPIOE, &LCD_Pins); //initialize pins PE3 to PE6;

	//initialization steps, page 42 of HD44780 datasheet
	//Step 2: function set 4-bit (0 0 0 0 1 0)
	GPIO_ResetBits(GPIOC, RS_Pin);
	GPIO_ResetBits(GPIOC, RW_Pin);
	GPIO_ResetBits(GPIOE, D7_Pin);
	GPIO_ResetBits(GPIOE, D6_Pin);
	GPIO_SetBits(GPIOE, D5_Pin);
	GPIO_ResetBits(GPIOE, D4_Pin);

	GPIO_SetBits(GPIOD, EN_Pin);
	delay(10);
	GPIO_ResetBits(GPIOD, EN_Pin);

	//Step 3: function set 4-bit + 1-line display
	//(0 0 0 0 1 0)
	GPIO_ResetBits(GPIOC, RS_Pin);
	GPIO_ResetBits(GPIOC, RW_Pin);
	GPIO_ResetBits(GPIOE, D7_Pin);
	GPIO_ResetBits(GPIOE, D6_Pin);
	GPIO_SetBits(GPIOE, D5_Pin);
	GPIO_ResetBits(GPIOE, D4_Pin);

	GPIO_SetBits(GPIOD, EN_Pin);
	delay(10);
	GPIO_ResetBits(GPIOD, EN_Pin);

	//(0 0 0 0 * *) * = don't care
	GPIO_ResetBits(GPIOC, RS_Pin);
	GPIO_ResetBits(GPIOC, RW_Pin);
	GPIO_ResetBits(GPIOE, D7_Pin);
	GPIO_ResetBits(GPIOE, D6_Pin);
	GPIO_ResetBits(GPIOE, D5_Pin);
	GPIO_ResetBits(GPIOE, D4_Pin);

	GPIO_SetBits(GPIOD, EN_Pin);
	delay(10);
	GPIO_ResetBits(GPIOD, EN_Pin);

	//Step 4: function set turn on display and cursor
	//(0 0 0 0 0 0)
	GPIO_ResetBits(GPIOC, RS_Pin);
	GPIO_ResetBits(GPIOC, RW_Pin);
	GPIO_ResetBits(GPIOE, D7_Pin);
	GPIO_ResetBits(GPIOE, D6_Pin);
	GPIO_ResetBits(GPIOE, D5_Pin);
	GPIO_ResetBits(GPIOE, D4_Pin);

	GPIO_SetBits(GPIOD, EN_Pin);
	delay(10);
	GPIO_ResetBits(GPIOD, EN_Pin);

	//(0 0 1 1 1 0)
	GPIO_ResetBits(GPIOC, RS_Pin);
	GPIO_ResetBits(GPIOC, RW_Pin);
	GPIO_SetBits(GPIOE, D7_Pin);
	GPIO_SetBits(GPIOE, D6_Pin);
	GPIO_SetBits(GPIOE, D5_Pin);
	//GPIO_ResetBits(GPIOE, D5_Pin);
	GPIO_ResetBits(GPIOE, D4_Pin);

	GPIO_SetBits(GPIOD, EN_Pin);
	delay(10);
	GPIO_ResetBits(GPIOD, EN_Pin);

	//Step 5: function set entry mode + cursor shift right after input
	//(0 0 0 0 0 0)
	GPIO_ResetBits(GPIOC, RS_Pin);
	GPIO_ResetBits(GPIOC, RW_Pin);
	GPIO_ResetBits(GPIOE, D7_Pin);
	GPIO_ResetBits(GPIOE, D6_Pin);
	GPIO_ResetBits(GPIOE, D5_Pin);
	GPIO_ResetBits(GPIOE, D4_Pin);

	GPIO_SetBits(GPIOD, EN_Pin);
	delay(10);
	GPIO_ResetBits(GPIOD, EN_Pin);

	//(0 0 0 1 1 0)
	GPIO_ResetBits(GPIOC, RS_Pin);
	GPIO_ResetBits(GPIOC, RW_Pin);
	GPIO_ResetBits(GPIOE, D7_Pin);
	GPIO_SetBits(GPIOE, D6_Pin);
	GPIO_SetBits(GPIOE, D5_Pin);
	GPIO_ResetBits(GPIOE, D4_Pin);

	GPIO_SetBits(GPIOD, EN_Pin);
	delay(10);
	GPIO_ResetBits(GPIOD, EN_Pin);

	//Step 6: write A
	//(1 0 0 1 0 0)
	GPIO_SetBits(GPIOC, RS_Pin);
	GPIO_ResetBits(GPIOC, RW_Pin);
	GPIO_ResetBits(GPIOE, D7_Pin);
	GPIO_SetBits(GPIOE, D6_Pin);
	GPIO_ResetBits(GPIOE, D5_Pin);
	GPIO_ResetBits(GPIOE, D4_Pin);

	GPIO_SetBits(GPIOD, EN_Pin);
	delay(10);
	GPIO_ResetBits(GPIOD, EN_Pin);

	//(0 0 0 0 0 1)
	GPIO_ResetBits(GPIOC, RS_Pin);
	GPIO_ResetBits(GPIOC, RW_Pin);
	GPIO_ResetBits(GPIOE, D7_Pin);
	GPIO_ResetBits(GPIOE, D6_Pin);
	GPIO_ResetBits(GPIOE, D5_Pin);
	GPIO_SetBits(GPIOE, D4_Pin);

	GPIO_SetBits(GPIOD, EN_Pin);
	delay(10);
	GPIO_ResetBits(GPIOD, EN_Pin);
}

void lcd_init_16(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef LCD_Pins;
	LCD_Pins.GPIO_Mode = GPIO_Mode_Out_PP;
	LCD_Pins.GPIO_Speed = GPIO_Speed_50MHz;
	LCD_Pins.GPIO_Pin = RS_Pin | RW_Pin;
	GPIO_Init(RS_Gate, &LCD_Pins); //initialize pins PC13 and PC11;

	LCD_Pins.GPIO_Pin = EN_Pin;
	GPIO_Init(EN_Gate, &LCD_Pins); //initialize pin PD0;

	LCD_Pins.GPIO_Pin = D4_Pin | D5_Pin | D6_Pin | D7_Pin;
	GPIO_Init(D_Gate, &LCD_Pins); //initialize pins PE3 to PE6;

	delay(15000);
	//initialization steps, page 42 of HD44780 datasheet
	//Step 2: function set 4-bit (0 0 0 0 1 0)
	GPIO_ResetBits(RS_Gate, RS_Pin);
	GPIO_ResetBits(RS_Gate, RW_Pin);
	GPIO_ResetBits(D_Gate, D7_Pin | D6_Pin | D4_Pin);
	GPIO_SetBits(D_Gate, D5_Pin);

	delay(5000);
	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(1000);
	GPIO_ResetBits(EN_Gate, EN_Pin);

	//Step 3: function set 4-bit + 2-line display
	//(0 0 0 0 1 0)
	delay(5000);
	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(1000);
	GPIO_ResetBits(EN_Gate, EN_Pin);

	//(0 0 1 0 * *) * = don't care
	GPIO_SetBits(D_Gate, D7_Pin);
	GPIO_ResetBits(D_Gate, D5_Pin);

	delay(5000);
	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(1000);
	GPIO_ResetBits(EN_Gate, EN_Pin);

	//Step 4: function set turn on display and cursor
	//(0 0 0 0 0 0)
	GPIO_ResetBits(D_Gate, D7_Pin);
	delay(5000);

	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(1000);
	GPIO_ResetBits(EN_Gate, EN_Pin);

	//(0 0 1 1 0 0)
	GPIO_SetBits(D_Gate, D7_Pin | D6_Pin);

	delay(5000);
	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(1000);
	GPIO_ResetBits(EN_Gate, EN_Pin);

	//Step 5: function set entry mode + cursor shift right after input
	//(0 0 0 0 0 0)
	GPIO_ResetBits(D_Gate, D7_Pin | D6_Pin);

	delay(5000);
	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(1000);
	GPIO_ResetBits(EN_Gate, EN_Pin);

	//(0 0 0 1 1 0)
	GPIO_SetBits(D_Gate, D6_Pin | D5_Pin);

	delay(5000);
	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(1000);
	GPIO_ResetBits(EN_Gate, EN_Pin);

	//Step 6: write A
	//(1 0 0 1 0 0)
	GPIO_SetBits(RS_Gate, RS_Pin);
	GPIO_ResetBits(RS_Gate, RW_Pin);
	GPIO_ResetBits(D_Gate, D7_Pin);
	GPIO_SetBits(D_Gate, D6_Pin);
	GPIO_ResetBits(D_Gate, D5_Pin);
	GPIO_ResetBits(D_Gate, D4_Pin);

	delay(5000);
	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(1000);
	GPIO_ResetBits(EN_Gate, EN_Pin);

	//(0 0 0 0 0 1)
	GPIO_ResetBits(RS_Gate, RS_Pin);
	GPIO_ResetBits(RS_Gate, RW_Pin);
	GPIO_ResetBits(D_Gate, D7_Pin);
	GPIO_ResetBits(D_Gate, D6_Pin);
	GPIO_ResetBits(D_Gate, D5_Pin);
	GPIO_SetBits(D_Gate, D4_Pin);

	delay(5000);
	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(1000);
	GPIO_ResetBits(EN_Gate, EN_Pin);
}

void lcd_setCursor(int pos)
{
	int i;

	GPIO_ResetBits(RS_Gate, RS_Pin);
	GPIO_ResetBits(RS_Gate, RW_Pin);
	GPIO_ResetBits(D_Gate, D7_Pin | D6_Pin | D5_Pin | D4_Pin);

	if(pos>=8)
	{
		//set position 8 = 0 0 1 0 1 0  0 0 0 0
		GPIO_SetBits(D_Gate, D7_Pin | D5_Pin);
		delay(500);
		GPIO_SetBits(EN_Gate, EN_Pin);
		delay(100);
		GPIO_ResetBits(EN_Gate, EN_Pin);
		delay(500);
		GPIO_ResetBits(D_Gate, D7_Pin | D5_Pin);
		GPIO_SetBits(EN_Gate, EN_Pin);
		delay(100);
		GPIO_ResetBits(EN_Gate, EN_Pin);
	}
	else
	{
		//return cursor home
		delay(500);
		GPIO_SetBits(EN_Gate, EN_Pin);
		delay(100);
		GPIO_ResetBits(EN_Gate, EN_Pin);

		GPIO_SetBits(D_Gate, D5_Pin);

		delay(500);
		GPIO_SetBits(EN_Gate, EN_Pin);
		delay(100);
		GPIO_ResetBits(EN_Gate, EN_Pin);

		GPIO_ResetBits(D_Gate, D5_Pin);
	}

	for(i=1; i<=pos; i++)
	{
		//shift cursor 1 position to the right
		GPIO_ResetBits(D_Gate, D7_Pin | D6_Pin | D5_Pin);
		GPIO_SetBits(D_Gate, D4_Pin);
		delay(500);
		GPIO_SetBits(EN_Gate, EN_Pin);
		delay(100);
		GPIO_ResetBits(EN_Gate, EN_Pin);

		GPIO_SetBits(D_Gate, D6_Pin);
		delay(500);
		GPIO_SetBits(EN_Gate, EN_Pin);
		delay(100);
		GPIO_ResetBits(EN_Gate, EN_Pin);
	}

	cursor_pos = pos;
}

void lcd_clear(void)
{
	//clear display 0 0 0 0 0 0 0 0 0 1
	GPIO_ResetBits(RS_Gate, RS_Pin);
	GPIO_ResetBits(RS_Gate, RW_Pin);
	GPIO_ResetBits(D_Gate, D7_Pin | D6_Pin | D5_Pin | D4_Pin);

	delay(500);
	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(100);
	GPIO_ResetBits(EN_Gate, EN_Pin);

	GPIO_ResetBits(RS_Gate, RS_Pin);
	GPIO_ResetBits(RS_Gate, RW_Pin);
	GPIO_ResetBits(D_Gate, D7_Pin);
	GPIO_ResetBits(D_Gate, D6_Pin);
	GPIO_ResetBits(D_Gate, D5_Pin);
	GPIO_SetBits(D_Gate, D4_Pin);

	delay(500);
	GPIO_SetBits(EN_Gate, EN_Pin);
	delay(100);
	GPIO_ResetBits(EN_Gate, EN_Pin);

	lcd_setCursor(0);
}

void lcd_print(char text[17])
{
	int i;
	char output;

	for(i=0; i<16; i++)
	{
		if(cursor_pos==8) lcd_setCursor(8);

		if(text[i]=='\0') break;

		GPIO_SetBits(RS_Gate, RS_Pin); //Set Clock high to receive bits
		GPIO_ResetBits(RS_Gate, RW_Pin);
		output = text[i];

		//first set all bits low
		GPIO_ResetBits(D_Gate, D7_Pin | D6_Pin | D5_Pin | D4_Pin);

		//first 4 bits:
		if(output & 0b10000000) GPIO_SetBits(D_Gate, D7_Pin);
		if(output & 0b01000000) GPIO_SetBits(D_Gate, D6_Pin);
		if(output & 0b00100000) GPIO_SetBits(D_Gate, D5_Pin);
		if(output & 0b00010000) GPIO_SetBits(D_Gate, D4_Pin);

		//insert bits
		delay(500);
		GPIO_SetBits(EN_Gate, EN_Pin);
		delay(100);
		GPIO_ResetBits(EN_Gate, EN_Pin);

		//first reset all bits again
		GPIO_ResetBits(D_Gate, D7_Pin | D6_Pin | D5_Pin | D4_Pin);

		//second 4 bits
		if(output & 0b00001000) GPIO_SetBits(D_Gate, D7_Pin);
		if(output & 0b00000100) GPIO_SetBits(D_Gate, D6_Pin);
		if(output & 0b00000010) GPIO_SetBits(D_Gate, D5_Pin);
		if(output & 0b00000001) GPIO_SetBits(D_Gate, D4_Pin);

		delay(500);
		GPIO_SetBits(EN_Gate, EN_Pin);
		delay(100);
		GPIO_ResetBits(EN_Gate, EN_Pin);

		cursor_pos++;
	}
}
