#include "mode.h"
#include "hd44780_driver.h"
#include "match.h"
#include "menu.h"

uint8_t push_mode = 0;

#define STM32F103C8T6 // STM32F103C8T6/STM32F103ZET6
#define no_OUT_UART   // no_OUT_UART/OUT_UART

void config_chanal_arm();


void mode_open(uint8_t number_repetitions_regime_open) {
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("JAMMERS");
  lcd_set_xy(0, 1);
  lcd_out_char("WORK");

  double cyr_fraquent = 1000;
  uint32_t registr_32_bit;
  registr_32_bit = calc_registr(cyr_fraquent);
  config_port_dds();
  set_serial_mode();
  send_data_serial_mode(registr_32_bit);
  lcd_set_xy(0,0);
  lcd_out_char("Fraquent = ");
  lcd_set_xy(0,1);
  lcd_out_number(cyr_fraquent);
  while(!GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE))
  {

  };
}


void mode_short() {
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("BROADBANS");
  lcd_set_xy(0, 1);
  lcd_out_char("WORK");
  while(!GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE));
}



void adjust() {
  uint8_t push_up_down = 0;
  uint8_t push_enter = 0;
  uint8_t push_mode = 0;

  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("OPTIONS");
  lcd_set_xy(0, 1);
  lcd_out_char("PUSH CAP UP/DOWN");

  while (push_mode == 0) {
    push_up_down = 0;
    push_enter = 0;

    while (push_up_down == 0 && push_mode == 0) {
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char("Repetitions_OPEN");
      lcd_set_xy(0, 1);
      if (push_enter == 1) {
        if (number_repetitions_regime_open == 0)
          number_repetitions_regime_open = 1;
        else
          number_repetitions_regime_open = 0;
      }
      if (number_repetitions_regime_open == 0)
        lcd_out_char("State:infinitely");
      else
        lcd_out_char("State:Once");
      while (1) {
        push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
        push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
        push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
        if ((push_up_down == 1) || (push_enter == 1) || (push_mode == 1))
          break;
      }
      delay_us(500);
    }

    push_up_down = 0;
    push_enter = 0;

    while (push_up_down == 0 && push_mode == 0) {
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char("matrix_for_validation");
      lcd_set_xy(0, 1);
      if (push_enter == 1)
        matrix_for_validation = ~matrix_for_validation;
      if (matrix_for_validation == 0)
        lcd_out_char("infinitely");
      else
        lcd_out_char("Once");
      while (1) {
        push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
        push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
        push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
        if ((push_up_down == 1) || (push_enter == 1) || (push_mode == 1))
          break;
      }
      delay_us(300);
    }

    push_up_down = 0;
    push_enter = 0;

    while (push_up_down == 0 && push_mode == 0) {
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char("NUMB_BITS_SWITCH");
      lcd_set_xy(0, 1);
      if (push_enter == 1)
        numb_bits = ++numb_bits;
      if (numb_bits == MAX_CHANAL)
        numb_bits = 0;
      lcd_out_number(numb_bits);

      while (1) {
        push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
        push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
        push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
        if ((push_up_down == 1) || (push_enter == 1) || (push_mode == 1))
          break;
      }
      delay_us(300);
    }

    push_up_down = 0;
    push_enter = 0;

    while (push_up_down == 0 && push_mode == 0) {
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char("adc_level_add");
      lcd_set_xy(0, 1);
      if (push_enter == 1)
        adc_level_add = adc_level_add + 50;
      if (adc_level_add == 2000)
        adc_level_add = 0;
      lcd_out_number(adc_level_add);

      while (1) {
        push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
        push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
        push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
        if ((push_up_down == 1) || (push_enter == 1) || (push_mode == 1))
          break;
      }
      delay_us(300);
    }

    push_up_down = 0;
    push_enter = 0;

    while (push_up_down == 0 && push_mode == 0) {
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char("set_option_push");
      lcd_set_xy(0, 1);
      if (push_enter == 1)
        set_option_push = ++set_option_push;
      if (numb_bits == 3)
        set_option_push = 0;
      lcd_out_number(set_option_push);

      while (1) {
        push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
        push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
        push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
        if ((push_up_down == 1) || (push_enter == 1) || (push_mode == 1))
          break;
      }
      delay_us(300);
    }

    push_up_down = 0;
    push_enter = 0;

    while (push_up_down == 0 && push_mode == 0) {
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char("type_test_signal");
      lcd_set_xy(0, 1);
      if (push_enter == 1) {
        if (type_test_signal == 0) {
          type_test_signal = 1;
        } else {
          if (type_test_signal == 1) {
            type_test_signal = 0;
          }
        }
      }

      if (type_test_signal == 0)
        lcd_out_char("digit");
      else
        lcd_out_char("analog");
      while (1) {
        push_enter = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
        push_up_down = GPIO_ReadInputDataBit(PORT_CAP, CAP_UP_DOWN);
        push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
        if ((push_up_down == 1) || (push_enter == 1) || (push_mode == 1))
          break;
      }
      delay_us(300);
    }
  }

  options[0] = number_repetitions_regime_open;
  options[1] = matrix_for_validation;
  options[2] = number_of_channels;
  options[3] = pin_null;
  options[4] = numb_bits;
  options[5] = adc_level_add;
  options[6] = adc_level_add;
}
