#include "mode.h"
#include "hd44780_driver.h"
#include "match.h"
#include "menu.h"

uint8_t push_mode = 0;

#define STM32F103C8T6 // STM32F103C8T6/STM32F103ZET6
#define no_OUT_UART   // no_OUT_UART/OUT_UART

void config_chanal_arm() {

#ifdef STM32F103C8T6

  CHANAL[0] = GPIO_Pin_0;
  CHANAL[1] = GPIO_Pin_1;   // A
  CHANAL[2] = GPIO_Pin_2;   // A
  CHANAL[3] = GPIO_Pin_3;   // A
  CHANAL[4] = GPIO_Pin_4;   // A
  CHANAL[5] = GPIO_Pin_5;   // A
  CHANAL[6] = GPIO_Pin_6;   // A
  CHANAL[7] = GPIO_Pin_7;   // A
  CHANAL[8] = GPIO_Pin_8;   // B
  CHANAL[9] = GPIO_Pin_9;   // A
  CHANAL[10] = GPIO_Pin_10; // A

  CHANAL[11] = GPIO_Pin_0;  // B
  CHANAL[12] = GPIO_Pin_1;  // B
  CHANAL[13] = GPIO_Pin_11; // B
  CHANAL[14] = GPIO_Pin_14; // B
  CHANAL[15] = GPIO_Pin_15; // B
  CHANAL[16] = GPIO_Pin_5;  // B
  CHANAL[17] = GPIO_Pin_10; // B

  ////////////////////////////////////////////////////////////

  PORT_CHANAL[0] = GPIOA; // 3
  PORT_CHANAL[1] = GPIOA; // 4
  PORT_CHANAL[2] = GPIOA; // 5
  PORT_CHANAL[3] = GPIOA; // 6
  PORT_CHANAL[4] = GPIOA; // 7
  PORT_CHANAL[5] = GPIOA; // 8
  PORT_CHANAL[6] = GPIOA;
  PORT_CHANAL[7] = GPIOA;  // 8
  PORT_CHANAL[8] = GPIOA;  // 9
  PORT_CHANAL[9] = GPIOA;  // 10
  PORT_CHANAL[10] = GPIOA; // 11

  PORT_CHANAL[11] = GPIOB; // B
  PORT_CHANAL[12] = GPIOB; // B
  PORT_CHANAL[13] = GPIOB; // B
  PORT_CHANAL[14] = GPIOB; // B
  PORT_CHANAL[15] = GPIOB; // B
  PORT_CHANAL[16] = GPIOB; // B
  PORT_CHANAL[17] = GPIOB; // B

  /////////////////////////////////////////////////////////////

  PORT_ADC[0] = GPIOA;

  ADC_CHANALL_PIN[0] = GPIO_Pin_0;
  ADC_CHANALL_PIN[1] = GPIO_Pin_1;
  ADC_CHANALL_PIN[2] = GPIO_Pin_2;
  ADC_CHANALL_PIN[3] = GPIO_Pin_3;
  ADC_CHANALL_PIN[4] = GPIO_Pin_4;
  ADC_CHANALL_PIN[5] = GPIO_Pin_5;
  ADC_CHANALL_PIN[6] = GPIO_Pin_6;
  ADC_CHANALL_PIN[7] = GPIO_Pin_7;
  ADC_CHANALL_PIN[8] = GPIO_Pin_8;
  ADC_CHANALL_PIN[9] = GPIO_Pin_9;
  ADC_CHANALL_PIN[10] = GPIO_Pin_10;

  ADC_CHANALL[0] = ADC_Channel_0;
  ADC_CHANALL[1] = ADC_Channel_1;
  ADC_CHANALL[2] = ADC_Channel_2;
  ADC_CHANALL[3] = ADC_Channel_3;
  ADC_CHANALL[4] = ADC_Channel_4;
  ADC_CHANALL[5] = ADC_Channel_5;
  ADC_CHANALL[6] = ADC_Channel_6;
  ADC_CHANALL[7] = ADC_Channel_7;
  ADC_CHANALL[8] = ADC_Channel_8;
  ADC_CHANALL[9] = ADC_Channel_9;
  ADC_CHANALL[10] = ADC_Channel_10;

#endif

}


void mode_open(uint8_t number_repetitions_regime_open) {
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("JAMMERS");
  lcd_set_xy(0, 1);
  lcd_out_char("WORK");
  while(!GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE));
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
      lcd_out_char("SLC_number_CH");
      lcd_set_xy(0, 1);
      if (push_enter == 1)
        number_of_channels = ++number_of_channels;
      if (number_of_channels == MAX_CHANAL)
        number_of_channels = 0;
      lcd_out_number(number_of_channels);

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
      lcd_out_char("PIN_NULL_SWITCH");
      lcd_set_xy(0, 1);
      if (push_enter == 1)
        pin_null = ++pin_null;
      if (pin_null == MAX_CHANAL)
        pin_null = 0;
      lcd_out_number(pin_null);

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
