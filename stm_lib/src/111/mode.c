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

#ifdef STM32F103ZET6

  CHANAL[0] = GPIO_Pin_1;   // E
  CHANAL[1] = GPIO_Pin_2;   // E
  CHANAL[2] = GPIO_Pin_15;  // F!!!
  CHANAL[3] = GPIO_Pin_6;   // E
  CHANAL[4] = GPIO_Pin_7;   // E
  CHANAL[5] = GPIO_Pin_8;   // E
  CHANAL[6] = GPIO_Pin_13;  // E
  CHANAL[7] = GPIO_Pin_14;  // E
  CHANAL[8] = GPIO_Pin_15;  // E
  CHANAL[9] = GPIO_Pin_4;   // E
  CHANAL[10] = GPIO_Pin_5;  // E
  CHANAL[11] = GPIO_Pin_9;  // E
  CHANAL[12] = GPIO_Pin_8;  // B !!!
  CHANAL[13] = GPIO_Pin_12; // E
  CHANAL[14] = GPIO_Pin_0;  // E

  CHANAL[15] = GPIO_Pin_0;  // B+
  CHANAL[16] = GPIO_Pin_1;  // B+
  CHANAL[17] = GPIO_Pin_2;  // B+
  CHANAL[18] = GPIO_Pin_9;  // B+
  CHANAL[19] = GPIO_Pin_10; // B+
  CHANAL[20] = GPIO_Pin_11; // B+
  CHANAL[21] = GPIO_Pin_12; // B+
  CHANAL[22] = GPIO_Pin_13; // B+
  CHANAL[23] = GPIO_Pin_14; // B+
  CHANAL[24] = GPIO_Pin_15; // B+

  CHANAL[25] = GPIO_Pin_0;  // F
  CHANAL[26] = GPIO_Pin_2;  // F
  CHANAL[27] = GPIO_Pin_3;  // F
  CHANAL[28] = GPIO_Pin_4;  // F
  CHANAL[29] = GPIO_Pin_5;  // F
  CHANAL[30] = GPIO_Pin_11; // F
  CHANAL[31] = GPIO_Pin_12; // F
  CHANAL[32] = GPIO_Pin_14; // F

  CHANAL[33] = GPIO_Pin_0;  // G
  CHANAL[34] = GPIO_Pin_1;  // G
  CHANAL[35] = GPIO_Pin_2;  // G
  CHANAL[36] = GPIO_Pin_3;  // G
  CHANAL[37] = GPIO_Pin_4;  // G
  CHANAL[38] = GPIO_Pin_5;  // G
  CHANAL[39] = GPIO_Pin_7;  // G
  CHANAL[40] = GPIO_Pin_8;  // G
  CHANAL[41] = GPIO_Pin_9;  // G
  CHANAL[42] = GPIO_Pin_10; // G
  CHANAL[43] = GPIO_Pin_11; // G
  CHANAL[44] = GPIO_Pin_12; // G
  CHANAL[45] = GPIO_Pin_13; // G
  CHANAL[46] = GPIO_Pin_14; // G
  CHANAL[47] = GPIO_Pin_15; // G

  PORT_CHANAL[0] = GPIOE;  // E
  PORT_CHANAL[1] = GPIOE;  // E
  PORT_CHANAL[2] = GPIOF;  // F!!!
  PORT_CHANAL[3] = GPIOE;  // E
  PORT_CHANAL[4] = GPIOE;  // E
  PORT_CHANAL[5] = GPIOE;  // E
  PORT_CHANAL[6] = GPIOE;  // E
  PORT_CHANAL[7] = GPIOE;  // E
  PORT_CHANAL[8] = GPIOE;  // E
  PORT_CHANAL[9] = GPIOE;  // E
  PORT_CHANAL[10] = GPIOE; // E
  PORT_CHANAL[11] = GPIOE; // E
  PORT_CHANAL[12] = GPIOB; // B!!!!
  PORT_CHANAL[13] = GPIOE; // E
  PORT_CHANAL[14] = GPIOE; // E

  PORT_CHANAL[15] = GPIOB; // B
  PORT_CHANAL[16] = GPIOB; // B
  PORT_CHANAL[17] = GPIOB; // B
  PORT_CHANAL[18] = GPIOB; // B
  PORT_CHANAL[19] = GPIOB; // B
  PORT_CHANAL[20] = GPIOB; // B
  PORT_CHANAL[21] = GPIOB; // B
  PORT_CHANAL[22] = GPIOB; // B
  PORT_CHANAL[23] = GPIOB; // B
  PORT_CHANAL[24] = GPIOB; // B

  PORT_CHANAL[25] = GPIOF; // F
  PORT_CHANAL[26] = GPIOF; // F
  PORT_CHANAL[27] = GPIOF; // F
  PORT_CHANAL[28] = GPIOF; // F
  PORT_CHANAL[29] = GPIOF; // F
  PORT_CHANAL[30] = GPIOF; // F
  PORT_CHANAL[31] = GPIOF; // F
  PORT_CHANAL[32] = GPIOF; // F

  PORT_CHANAL[33] = GPIOG; // G
  PORT_CHANAL[34] = GPIOG; // G
  PORT_CHANAL[35] = GPIOG; // G
  PORT_CHANAL[36] = GPIOG; // G
  PORT_CHANAL[37] = GPIOG; // G
  PORT_CHANAL[38] = GPIOG; // G
  PORT_CHANAL[39] = GPIOG; // G
  PORT_CHANAL[40] = GPIOG; // G
  PORT_CHANAL[41] = GPIOG; // G
  PORT_CHANAL[42] = GPIOG; // G
  PORT_CHANAL[43] = GPIOG; // G
  PORT_CHANAL[44] = GPIOG; // G
  PORT_CHANAL[45] = GPIOG; // G
  PORT_CHANAL[46] = GPIOG; // G
  PORT_CHANAL[47] = GPIOG; // G

#endif
}

void config_chanal_mux(void) {
  GPIO_Config_port_mux.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Config_port_mux.GPIO_Pin = PIN_MUX;
  GPIO_Config_port_mux.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PORT_MUX, &GPIO_Config_port_mux);
}

void reset_chanal_mux(void) {
  GPIO_SetBits(PORT_CONTROL_MUX, ALL_CONTROLL_MUX);
  GPIO_ResetBits(SET_MUX_CHANALL, ALL_CHANAL_MUX);
}

void set_channal_mux(uint16_t chanall) {

  if (chanall >= 0 && chanall <= 7) {
    GPIO_ResetBits(PORT_MUX, MUX_CONTROL_0);
    GPIO_SetBits(PORT_MUX, MUX_CONTROL_1);
    switch (chanall) {
    case 0:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX); // 0
      break;

    case 1:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX); // 1
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_0);
      break;

    case 2:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX); // 2
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_1);
      break;

    case 3:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_0);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_1);
      break;

    case 4:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_2);
      break;

    case 5:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_1 | MUX_CHANAL_2);
      break;

    case 6:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_1 | MUX_CHANAL_2);
      break;

    case 7:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, ALL_CHANAL_MUX);
      break;
    }
  }

  if (chanall >= 8 && chanall <= 15) {
    GPIO_ResetBits(PORT_MUX, MUX_CONTROL_0);
    GPIO_SetBits(PORT_MUX, MUX_CONTROL_1);

    switch (chanall - 8) {
    case 0:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      break;

    case 1:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_0);
      break;

    case 2:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_1);
      break;

    case 3:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_0);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_1);
      break;

    case 4:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_2);
      break;

    case 5:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_1 | MUX_CHANAL_2);
      break;

    case 6:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, MUX_CHANAL_1 | MUX_CHANAL_2);
      break;

    case 7:
      GPIO_ResetBits(PORT_MUX, ALL_CHANAL_MUX);
      GPIO_SetBits(PORT_MUX, ALL_CHANAL_MUX);
      break;
    }
  }
}

void reset_array() {
  uint8_t i, j;

  for (i = 0; i < MAX_CHANAL; i++) {
    for (j = 0; j < MAX_CHANAL; j++) {
      array_chek[i][j] = 0;
      array_error[i][j] = 0;
    }
  }
}

void data_collection() {
  reset_array();
  counter_array_chek = 0;
  uint16_t counter_c;

  if (type_test_signal == 0) {
    for (counter_c = 0; counter_c < MAX_CHANAL; counter_c++) {
      mode_open_init();
      set_chek_chanall_mode_open(counter_c);
      chek_chanall_mode_open(counter_c);
      reset_bit_out(counter_c);
    }
  }

  if (type_test_signal == 1) {
    for (counter_c = 0; counter_c < NUMB_ADC; counter_c++) {
      mode_open_init();
      set_chek_chanall_mode_open(counter_c);
      chek_chanall_mode_open(counter_c);
      reset_bit_out(counter_c);
    }
  }
}

void mode_open(uint8_t number_repetitions_regime_open) {
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("WORK MODE OPEN...");
  config_chanal_arm();

  if (number_repetitions_regime_open == 0) {
    while (GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE) == 0) {
      data_collection();
      show_result_work_mode_open();
    }
  } else {
    data_collection();
    show_result_work_mode_open();
  }
}

void mode_open_init(void) {
  int count;
  for (count = 0; count < MAX_CHANAL; count++) {
    GPIO_Config_port_in.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Config_port_in.GPIO_Pin = CHANAL[count];
    GPIO_Config_port_in.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_CHANAL[count], &GPIO_Config_port_in);
  }
}

void mode_matrix_init(void) {
  int count;
  for (count = 0; count < MAX_CHANAL; count++) {
    GPIO_Config_port_in.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Config_port_in.GPIO_Pin = CHANAL[count];
    GPIO_Config_port_in.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_CHANAL[count], &GPIO_Config_port_in);
  }
}

void set_chek_chanall_mode_open(uint16_t CHANALL) {
  GPIO_Config_port_out.GPIO_Pin = CHANAL[CHANALL];
  GPIO_Config_port_out.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Config_port_out.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Config_port_out);
  GPIO_SetBits(PORT_CHANAL[CHANALL], CHANAL[CHANALL]);
}

void chek_chanall_mode_open(uint16_t chanall) {
  counter_chanall = 0;
  uint8_t ci;
  int count_repead = 0;
  uint16_t adc_cal;
  uint16_t adc_cyr;

  adc_cal = 2500;

  if (type_test_signal == 0) {
    while (counter_chanall < MAX_CHANAL) {
      if (counter_chanall != chanall) {
        array_chek[counter_array_chek][counter_chanall] = GPIO_ReadInputDataBit(
            PORT_CHANAL[counter_chanall], CHANAL[counter_chanall]);
      }

      else {
        array_chek[counter_array_chek][counter_chanall] = 0;
      }
      counter_chanall++;
    }
  }

  if (type_test_signal == 1) {
    for (counter_chanall = 0; counter_chanall < NUMB_ADC; counter_chanall++) {
      if (counter_chanall != chanall) {
        ADC_CH_control(counter_chanall, ENABLE);
        adc_cyr = get_adc_value();

        if (adc_cyr < adc_cal)
          adc_cyr = adc_cal;

        if ((adc_cyr - adc_cal) > adc_level_add) {
          array_chek[counter_array_chek][counter_chanall] = 1;
          adc_chek[counter_array_chek][counter_chanall] = adc_cyr;

        }

        else {
          array_chek[counter_array_chek][counter_chanall] = 0;
        }

      } else {
        array_chek[counter_array_chek][counter_chanall] = 0;
      }
    }
  }

  GPIO_ResetBits(PORT_CHANAL[chanall], CHANAL[chanall]);
  counter_array_chek++;
}

void reset_bit_out(uint16_t CHANALL) {
  GPIO_ResetBits(PORT_CHANAL[CHANALL], CHANAL[CHANALL]);
}

void show_result_work_mode_open() {
  enum flag { Error, OK } Error_KZ = OK;
  uint8_t count_error = 0;
  uint8_t x = 0, y = 0;
  uint8_t i = 0, j = 0;
  uint8_t result;

  for (i = 0; i < MAX_CHANAL; i++) {
    for (j = 0; j < MAX_CHANAL; j++) {
      if (array_chek[i][j] == 1) {
        Error_KZ = ERROR;
        count_error++;
        lcd_clear();
        lcd_set_xy(0, 0);
        lcd_out_char("Error");
        lcd_set_xy(sizeof("Error"), 0);
        lcd_out_number(count_error);
        lcd_set_xy(0, 1);
        lcd_out_number(i);
        lcd_set_xy(sizeof(i) + 3, 1);
        lcd_out_char("&");
        lcd_set_xy(sizeof(i) + 5, 1);
        lcd_out_number(j);

        if (type_test_signal == 1) {
          lcd_set_xy(9, 1);
          lcd_out_number(adc_chek[i][j]);
        }

        push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
        if (push_mode == 1)
          break;

#ifdef OUT_UART
        send_Uart_str(USART3, "Error  ");
        send_Uart(USART3, i + 48);
        send_Uart(USART3, '&');
        send_Uart(USART3, (char)j + 48);
        send_Uart(USART3, ' ');
        USART_SendData(USART3, 13);
#endif

        delay_us(700);
      }
    }
  }

  if (Error_KZ == OK) {

    if (number_repetitions_regime_open == 1) {
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char("GOOD.Short NO!");
      while ((push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE)) == 0)
        ;
    }

#ifdef OUT_UART
    send_Uart_str(USART3, "GOOD.Short NO!");
    USART_SendData(USART3, 13);
#endif
  }
}

void mode_short() {
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("WORK MODE SHORT");
  config_chanal_arm();
  data_collection();
  chek_adress_mode_short(pin_null, numb_bits);
  show_result_work_mode_short();
}

void chek_adress_mode_short(uint8_t pin_null, uint8_t numb_bits) {
  uint8_t pin;
  uint8_t count_pin = 0;
  address = 0;

  for (pin = pin_null; pin <= (numb_bits + pin_null); pin++) {
    if (array_chek[17][pin] == 1) {
      address = address + exponentiation(2, count_pin);
    }
    count_pin++;
  }
}

void show_result_work_mode_short() {
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("Result Switch");
  lcd_set_xy(0, 1);
  lcd_out_number(address);

#ifdef OUT_UART
  send_Uart_str(USART3, "Result Switch ");
  Exponentiation send_Uart_str(USART3, "check = ");
  USART_SendData(USART3, check_switch);
  USART_SendData(USART3, 13);
#endif

  while ((push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE)) == 0)
    ;
}

void mode_matrix(void) {
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("MATRIX MODE");

  uint16_t prev_array_chek[MAX_CHANAL][MAX_CHANAL];

  counter_array_chek = 0;
  config_chanal_arm();
  mode_matrix_init();
  matrix_09_16_XW8();
  chek_chanall_mode_open(MAX_CHANAL - 1);

  int i = 0, j = 0;
  for (j = 0; j < MAX_CHANAL; j++) {
    prev_array_chek[i][j] = array_chek[i][j];
  }

  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("PUSH SWITCH");

  char *state_cap;

  while (GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE) == 0) {
    counter_array_chek = 0;
    mode_matrix_init();
    chek_chanall_mode_open(MAX_CHANAL - 1);

    j = 0;
    for (j = 0; j < MAX_CHANAL; j++) {
      if (prev_array_chek[i][j] ^ array_chek[i][j]) {
        lcd_clear();
        if (((j % 2) > 0) || (j == 0))
          lcd_set_xy(0, 0);
        if ((j % 2) == 0)
          lcd_set_xy(0, 1);
        lcd_out_char("SW");
        lcd_out_number(j);
        lcd_out_char(" ");
        lcd_out_char(&XW8_250_09_16[j]);
        if (array_chek[i][j] == 1) {
          if ((j % 2) > 0)
            lcd_set_xy(13, 0);
          if ((j % 2) == 0)
            lcd_set_xy(13, 1);
          lcd_out_char("ON");
        } else {
          if ((j % 2) > 0)
            lcd_set_xy(13, 0);
          if ((j % 2) == 0)
            lcd_set_xy(13, 1);
          lcd_out_char("OFF");
        }

        for (j = 0; j < MAX_CHANAL; j++) {
          prev_array_chek[i][j] = array_chek[i][j];
        }
      }
    }
  }
}

void show_result_work_mode_matrix(uint8_t switch_cap, char *state_switch) {
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("SWITCH STATE");
  lcd_set_xy(0, 1);
  lcd_out_char(XW8_250_09_16[switch_cap]);
  lcd_set_xy(11, 1);
  lcd_out_char(state_switch);

#ifdef OUT_UART
  send_Uart_str(USART3, "SWITCH STATE ");
  send_Uart_str(USART3, XW8_250_09_16[switch_cap]);
  send_Uart_str(USART3, state_switch);
  USART_SendData(USART3, 13);
#endif
}

void test_sys(void) {
  uint16_t level;
  uint16_t level_adc;
  push_mode = 0;

  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("TEST");
  delay_us(2000);

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

  ADC_CH_control(ADC_CHANALL[0], ENABLE);

  while (push_mode == 0) {
    level_adc = get_adc_value();
    lcd_set_xy(0, 0);
    lcd_out_char("ADC_LEVEL0");
    lcd_set_xy(0, 1);
    lcd_out_number(level_adc);
    delay_us(2000);
    push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_ENTER);
  }

  push_mode = 0;

  ADC_CH_control(ADC_CHANALL[1], ENABLE);

  while (push_mode == 0) {
    level_adc = get_adc_value();
    lcd_set_xy(0, 0);
    lcd_out_char("ADC_LEVEL1");
    lcd_set_xy(0, 1);
    lcd_out_number(level_adc);
    delay_us(2000);
    push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
  }

  push_mode = 0;

  ADC_CH_control(ADC_CHANALL[2], ENABLE);

  while (push_mode == 0) {
    level_adc = get_adc_value();
    lcd_set_xy(0, 0);
    lcd_out_char("ADC_LEVEL2");
    lcd_set_xy(0, 1);
    lcd_out_number(level_adc);
    delay_us(2000);
    push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
  }
}

uint16_t get_adc_value(void) {
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
    ;
  return ADC_GetConversionValue(ADC1);
}

uint16_t adc_calib(void) {
#define ADC_CAL_CIKL 50
  uint16_t cal = 0;
  uint8_t ADC_call_buffer_counter = 0;
  uint16_t cyr_ADC_value;

  for (ADC_call_buffer_counter = 0; ADC_call_buffer_counter < ADC_CAL_CIKL;
       ADC_call_buffer_counter++) {
    cyr_ADC_value = get_adc_value();
    if (cal < cyr_ADC_value)
      cal = cyr_ADC_value;
  }

  cal = cal + cal / ADC_CAL_CIKL;

  return cal;
}

void mode_UART(void) {
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

  counter_receive = 0;
  DATA_READ = NO;
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("Receiver data...");
  char *str = "Hello";

  while (push_mode == 0) {
    if (DATA_READ == YES) {
      lcd_clear();
      lcd_set_xy(0, 0);
      lcd_out_char(USART3_buffer);
      lcd_set_xy(0, 0);
      DATA_READ = NO;
    }

    send_Uart_str(USART3, str);

    push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
  }
}

void USART3_IRQHandler(void) {
  if (USART_GetFlagStatus(USART3, USART_SR_RXNE) == SET) {
    USART3_buffer[counter_receive++] = (char)USART_ReceiveData(USART3);
    DATA_READ = YES;
  }
}

void USART1_IRQHandler(void) {
  if (USART_GetFlagStatus(USART1, USART_SR_RXNE) == SET) {
    USART3_buffer[counter_receive++] = (char)USART_ReceiveData(USART1);
    DATA_READ = YES;
  }
}

void arm_scanf(char *const_char, char *out_string) {
  char *temp_pointer = out_string;
  int i = 0;
  while (const_char[i] != '\0') {
    temp_pointer[i] = const_char[i];
    i++;
  }

  const_char[i] != '\0';
}

void matrix_09_16_XW8(void) {
#ifdef STM32F103ZET6 // STM32F103C8T6/STM32F103ZET6

  arm_scanf("0", &XW8_250_09_16[0]);
  arm_scanf("1", &XW8_250_09_16[1]);
  arm_scanf("(Kv32)", &XW8_250_09_16[2]);
  arm_scanf("3", &XW8_250_09_16[3]);
  arm_scanf("4", &XW8_250_09_16[4]);
  arm_scanf("5", &XW8_250_09_16[5]);
  arm_scanf("6", &XW8_250_09_16[6]);
  arm_scanf("7", &XW8_250_09_16[7]);
  arm_scanf("8", &XW8_250_09_16[8]);
  arm_scanf("9", &XW8_250_09_16[9]);
  arm_scanf("10", &XW8_250_09_16[10]);
  arm_scanf("11", &XW8_250_09_16[11]);
  arm_scanf("12", &XW8_250_09_16[12]);
  arm_scanf("13", &XW8_250_09_16[13]);
  arm_scanf("14", &XW8_250_09_16[14]);
  arm_scanf("15", &XW8_250_09_16[15]);
  arm_scanf("16", &XW8_250_09_16[16]);
  arm_scanf("17", &XW8_250_09_16[17]);
  arm_scanf("18", &XW8_250_09_16[18]);
  arm_scanf("19", &XW8_250_09_16[19]);
  arm_scanf("20", &XW8_250_09_16[20]);
  arm_scanf("21", &XW8_250_09_16[21]);
  arm_scanf("22", &XW8_250_09_16[22]);
  arm_scanf("23", &XW8_250_09_16[23]);
  arm_scanf("24", &XW8_250_09_16[24]);
  arm_scanf("25", &XW8_250_09_16[25]);
  arm_scanf("26", &XW8_250_09_16[26]);
  arm_scanf("27", &XW8_250_09_16[27]);
  arm_scanf("28", &XW8_250_09_16[28]);
  arm_scanf("29", &XW8_250_09_16[29]);
  arm_scanf("30", &XW8_250_09_16[30]);
  arm_scanf("31", &XW8_250_09_16[31]);
  arm_scanf("32", &XW8_250_09_16[32]);
  arm_scanf("33", &XW8_250_09_16[33]);
  arm_scanf("34", &XW8_250_09_16[34]);
  arm_scanf("35", &XW8_250_09_16[35]);
  arm_scanf("36", &XW8_250_09_16[36]);
  arm_scanf("37", &XW8_250_09_16[37]);
  arm_scanf("38", &XW8_250_09_16[38]);
  arm_scanf("39", &XW8_250_09_16[39]);
  arm_scanf("40", &XW8_250_09_16[40]);
  arm_scanf("41", &XW8_250_09_16[41]);
  arm_scanf("42", &XW8_250_09_16[42]);
  arm_scanf("43", &XW8_250_09_16[43]);
  arm_scanf("44", &XW8_250_09_16[44]);
  arm_scanf("45", &XW8_250_09_16[45]);
  arm_scanf("46", &XW8_250_09_16[46]);
  arm_scanf("47", &XW8_250_09_16[47]);

#endif

#ifdef STM32F103C8T6
  arm_scanf("KV1", &XW8_250_09_16[0]);
  arm_scanf("KV2", &XW8_250_09_16[1]);
  arm_scanf("KV3", &XW8_250_09_16[2]);
  arm_scanf("KV4", &XW8_250_09_16[3]);
  arm_scanf("KV5", &XW8_250_09_16[4]);
  arm_scanf("KV6", &XW8_250_09_16[5]);
  arm_scanf("KV7", &XW8_250_09_16[6]);
  arm_scanf("KV8", &XW8_250_09_16[7]);
  arm_scanf("KV9", &XW8_250_09_16[8]);
  arm_scanf("KV10", &XW8_250_09_16[9]);
  arm_scanf("KV11", &XW8_250_09_16[10]);
  arm_scanf("KV12", &XW8_250_09_16[11]);
  arm_scanf("KV13", &XW8_250_09_16[12]);
  arm_scanf("KV14", &XW8_250_09_16[13]);
  arm_scanf("KV15", &XW8_250_09_16[14]);
  arm_scanf("KV16", &XW8_250_09_16[15]);
  arm_scanf("KV17", &XW8_250_09_16[16]);
  arm_scanf("KV18", &XW8_250_09_16[17]);

#endif
}

void mode_combo(uint8_t mode_combo_number) {
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("WORK MODE LOAD...");
  config_chanal_arm();

  uint8_t i, j;
  uint16_t prev_array_chek[MAX_CHANAL][MAX_CHANAL];

  mode_open_init();

  while (GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE) == 0) {

    reset_array();

    for (i = 0; i < MAX_CHANAL; i++) {
      for (j = 0; j < MAX_CHANAL; j++) {
        prev_array_chek[i][j] = 0;
      }
    }

    chek_chanall_mode_open(0);
    for (j = 0; j < MAX_CHANAL; j++) {
      prev_array_chek[i][j] = array_chek[i][j];
    }

    chek_chanall_mode_open(MAX_CHANAL - 1);
    array_chek[0][MAX_CHANAL - 1] = prev_array_chek[0][MAX_CHANAL - 1];

    enum flag { Error, OK } Error_KZ = OK;
    uint8_t count_error = 0;

    for (i = 0; i < 1; i++) {
      for (j = 0; j < MAX_CHANAL; j++) {
        if (array_chek[i][j] == 0) {
          Error_KZ = ERROR;
          count_error++;
          lcd_clear();
          lcd_set_xy(0, 0);
          lcd_out_char("Error");
          lcd_set_xy(sizeof("Error"), 0);
          lcd_out_number(count_error);
          lcd_set_xy(0, 1);
          lcd_out_number(i);
          lcd_set_xy(sizeof(i) + 3, 1);
          lcd_out_char("&");
          lcd_set_xy(sizeof(i) + 5, 1);
          lcd_out_number(j);

          if (type_test_signal == 1) {
            lcd_set_xy(9, 1);
            lcd_out_number(adc_chek[i][j]);
          }

          push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE);
          if (push_mode == 1)
            break;

#ifdef OUT_UART
          send_Uart_str(USART3, "Error  ");
          send_Uart(USART3, i + 48);
          send_Uart(USART3, '&');
          send_Uart(USART3, (char)j + 48);
          send_Uart(USART3, ' ');
          USART_SendData(USART3, 13);
#endif

          delay_us(700);
        }
      }
    }

    if (Error_KZ == OK) {

      if (number_repetitions_regime_open == 1) {
        lcd_clear();
        lcd_set_xy(0, 0);
        lcd_out_char("GOOD.Yes Short!");
        while ((push_mode = GPIO_ReadInputDataBit(PORT_CAP, CAP_MODE)) == 0)
          ;
      }

#ifdef OUT_UART
      send_Uart_str(USART3, "GOOD.Short NO!");
      USART_SendData(USART3, 13);
#endif
    }
  }
}

void mode_analog(void) {}

void config_chanal_mode_analog(void) {}

uint16_t ADC_CH_control(uint16_t ADC_chanall, FunctionalState ADC_CH_STATE) {
  GPIO_InitTypeDef GPIO_Config_ADC;
  GPIO_Config_ADC.GPIO_Pin = ADC_CHANALL_PIN[ADC_chanall];
  GPIO_Config_ADC.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Config_ADC.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Config_ADC);

  ADC_RegularChannelConfig(ADC1, ADC_CHANALL[ADC_chanall], 1,
                           ADC_SampleTime_1Cycles5);

  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1))
    ;
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1))
    ;
  uint16_t cal;
  cal = adc_calib();

  return 0;
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
