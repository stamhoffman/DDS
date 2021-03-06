#include "menu.h"
#include "hd44780_driver.h"

uint8_t menu_1(void) {

  uint8_t mode = 0;
  uint8_t push_up_down = 0;
  uint8_t count_up_down = 0;
  uint8_t push_enter = 0;

  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("SET_INTERFERENCE");
  lcd_set_xy(0, 1);
  lcd_out_char("PUSH CAP UP/DOWN");

  while (mode == 0) {

    switch (count_up_down) {
    case 0:
      while ((push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN)) == 0);
      count_up_down = 1;
      push_up_down = 0;
      delay_us(400);
      break;

    case 1:
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char("JAMMERS");
      lcd_set_xy(0, 1);
      lcd_out_char("SET -> ENTER");

      while (push_up_down == 0 && push_enter == 0) {
        push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
        push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
        delay_us(150);
      }
      if (push_up_down == 1)
        count_up_down = 2;
      if (push_enter == 1)
        mode = 1;

      push_enter = 0;
      push_up_down = 0;
      break;

    case 2:
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char("BROADBANS");
      lcd_set_xy(0, 1);
      lcd_out_char("SET -> ENTER");

      while (push_up_down == 0 && push_enter == 0) {
        push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
        push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
        delay_us(150);
      }
      if (push_up_down == 1)
        count_up_down = 3;
      if (push_enter == 1)
        mode = 2;

      push_enter = 0;
      push_up_down = 0;
      break;

    case 3:
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char("OPTIONS");
      lcd_set_xy(0, 1);
      lcd_out_char("SET -> ENTER");

      while (push_up_down == 0 && push_enter == 0) {
        push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
        push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
        delay_us(150);
      }

      if (push_up_down == 1)
        count_up_down = 0;
      if (push_enter == 1)
        mode = 3;

      push_enter = 0;
      push_up_down = 0;

      break;
    }

    if (mode != 0)
      return mode;
  }
  return 1;
}
