#include "hd44780_driver.h"
#include "system_stm32f10x.h"

void lcd_delay(void) {
  volatile uint32_t tmpvar;
  for (tmpvar = 8000; tmpvar != 0; tmpvar--)
    ;
}

void lcd_init() {
  LCD_PORT->CRH |= LCD_PORT_CRH_S;
  LCD_PORT->CRL |= LCD_PORT_CRL_S;
  LCD_PORT->CRH &= ~(LCD_PORT_CRH_C);
  LCD_PORT->CRL &= ~(LCD_PORT_CRL_C);
  lcd_set_4bit_mode();
  lcd_set_state(LCD_ENABLE, CURSOR_ENABLE, NO_BLINK);
  lcd_clear();
  lcd_send(0x06, COMMAND);
}

void lcd_set_user_char(uint8_t char_num, uint8_t *char_data) {
  uint8_t i;
  lcd_send(((1 << 6) | (char_num * 8)), COMMAND);
  for (i = 0; i <= 7; i++) {
    lcd_send(char_data[i], DATA);
  }
  lcd_send((1 << 7), COMMAND);
}

void lcd_set_xy(uint8_t x, uint8_t y) {
  if (y == 0) {
    lcd_send(((1 << 7) | (x)), COMMAND);
  } else {
    lcd_send(((3 << 6) | (x)), COMMAND);
  }
}

void lcd_out(char *txt) {
  while (*txt) {
    lcd_send(*txt, DATA);
    txt++;
  }
}

void lcd_clear(void) { lcd_send(0x01, COMMAND); }

void lcd_set_state(lcd_state state, cursor_state cur_state,
                   cursor_mode cur_mode) {
  if (state == LCD_DISABLE) {
    lcd_send(0x08, COMMAND);
  } else {
    if (cur_state == CURSOR_DISABLE) {
      if (cur_mode == NO_BLINK) {
        lcd_send(0x0C, COMMAND);
      } else {
        lcd_send(0x0D, COMMAND);
      }
    } else {
      if (cur_mode == NO_BLINK) {
        lcd_send(0x0E, COMMAND);
      } else {
        lcd_send(0x0F, COMMAND);
      }
    }
  }
}

void lcd_set_4bit_mode(void) {

  LCD_PORT->BSRR = (LCD_DB7_BC | LCD_DB6_BC | LCD_DB5_BC | LCD_DB4_BC |
                    LCD_CD_BC | LCD_EN_BC);
  LCD_PORT->BSRR = (LCD_DB5_BS);

  LCD_PORT->BSRR = LCD_EN_BS;
  lcd_delay();
  LCD_PORT->BSRR = LCD_EN_BC;
  lcd_delay();

  LCD_PORT->BSRR = (LCD_DB7_BC | LCD_DB6_BC | LCD_DB5_BC | LCD_DB4_BC |
                    LCD_CD_BC | LCD_EN_BC);
  LCD_PORT->BSRR = (LCD_DB5_BS);

  LCD_PORT->BSRR = LCD_EN_BS;
  lcd_delay();
  LCD_PORT->BSRR = LCD_EN_BC;
  lcd_delay();

  LCD_PORT->BSRR = (LCD_DB7_BC | LCD_DB6_BC | LCD_DB5_BC | LCD_DB4_BC |
                    LCD_CD_BC | LCD_EN_BC);
  LCD_PORT->BSRR = (LCD_DB7_BS);

  LCD_PORT->BSRR = LCD_EN_BS;
  lcd_delay();
  LCD_PORT->BSRR = LCD_EN_BC;
  lcd_delay();
}

void lcd_send(uint8_t byte, dat_or_comm dc) {

  LCD_PORT->BSRR = (LCD_DB7_BC | LCD_DB6_BC | LCD_DB5_BC | LCD_DB4_BC |
                    LCD_CD_BC | LCD_EN_BC);

  if (dc) {
    LCD_PORT->BSRR = LCD_CD_BS;
  }

  if (byte & 0x10) {
    LCD_PORT->BSRR = LCD_DB4_BS;
  }
  if (byte & 0x20) {
    LCD_PORT->BSRR = LCD_DB5_BS;
  }
  if (byte & 0x40) {
    LCD_PORT->BSRR = LCD_DB6_BS;
  }
  if (byte & 0x80) {
    LCD_PORT->BSRR = LCD_DB7_BS;
  }

  LCD_PORT->BSRR = LCD_EN_BS;
  lcd_delay();
  LCD_PORT->BSRR = LCD_EN_BC;
  lcd_delay();

  LCD_PORT->BSRR = (LCD_DB7_BC | LCD_DB6_BC | LCD_DB5_BC | LCD_DB4_BC);

  if (byte & 0x01) {
    LCD_PORT->BSRR = LCD_DB4_BS;
  }
  if (byte & 0x02) {
    LCD_PORT->BSRR = LCD_DB5_BS;
  }
  if (byte & 0x04) {
    LCD_PORT->BSRR = LCD_DB6_BS;
  }
  if (byte & 0x08) {
    LCD_PORT->BSRR = LCD_DB7_BS;
  }

  LCD_PORT->BSRR = LCD_EN_BS;
  lcd_delay();
  LCD_PORT->BSRR = LCD_EN_BC;
  lcd_delay();
}
void lcd_out_char(char *txt) { lcd_out(txt); }

void lcd_out_number(uint32_t number) {
  char lcd_massiv_out[16];
  uint32_t div_remainder = 1;
  uint8_t flag = 0;
  uint8_t index_mass_lcd;
  index_mass_lcd = long_int_size(number) - 1;
  lcd_massiv_out[index_mass_lcd + 1] = '\0';

  while (number > 0 && index_mass_lcd >= 0) {
    div_remainder = number % 10;
    lcd_massiv_out[index_mass_lcd--] = div_remainder + 48;
    number = number / 10;
    flag = 1;
  }

  if (number == 0 && flag == 0) {
    lcd_massiv_out[index_mass_lcd] = 48;
    lcd_out(lcd_massiv_out);
  } else
    lcd_out(lcd_massiv_out);
  return;
}

uint8_t long_int_size(uint32_t number) {
  uint8_t decimal = 0;
  if (number == 0) {
    return 1;
  }
  while (number > 0) {
    number = number / 10;
    decimal++;
  }
  return decimal;
}