#include "delay_.h"
#include "hd44780_driver.h"
#include "menu.h"
#include "mode.h"
#include "stm32f10x_conf.h"

ErrorStatus HSE_ON;
FlagStatus PLL_ON;
RCC_ClocksTypeDef RCC_value;
uint8_t source_clk;

void RCC_Config(void);
void GPIO_Config(void);
void NVIC_Configuration(void);
void ADC_Config(void);
void UART_Config(void);

#define TESTER        // TESTER/ProgBox
#define QUARZ         //  QUARZ/RC
#define STM32F103C8T6 // STM32F103ZET6/ STM32F103C8T6

int main(void) {
  uint8_t mode = 0;
  number_repetitions_regime_open = 0;
  matrix_for_validation = 0;
  number_of_channels = MAX_CHANAL;
  pin_null = 0;
  numb_bits = 8;
  adc_level_add = 300;
  set_option_push = 0;
  mode_combo_number = 0;
  type_test_signal = 0; // 0 - digit, 1 - analog

#ifdef TESTER
  RCC_Config();
  delay_us(200); // We look forward to when the Walk t transient
  GPIO_Config();
  lcd_init();
  // UART_Config();
  NVIC_Configuration();
  ADC_Config();
#endif

#ifdef ProgBox
  RCC_Config();
  GPIO_Config();
  lcd_init();
  ADC_Config();
  NVIC_Configuration();
  UART_Config();
#endif

  lcd_clear();
  lcd_set_xy(0, 0);

#ifdef ProgBox
  lcd_out_char("ProgBox v.1.4");
#endif

#ifdef TESTER
  lcd_out_char("ProgBox v.5.0");
  delay_us(2000);
#endif

  lcd_set_xy(0, 1);
  lcd_out_char("18.06.2017");
  delay_us(2000);
  lcd_clear();

  source_clk = RCC_GetSYSCLKSource();
  switch (source_clk) {
  case 0x00:
    lcd_set_xy(0, 0);
    lcd_out_char("HSI_Clock_use");
    break;
  case 0x04:
    lcd_set_xy(0, 0);
    lcd_out_char("HSE_Clock_use");
    break;
  case 0x08:
    lcd_set_xy(0, 0);
    lcd_out_char("PLL clock source");
    break;
  }

  lcd_set_xy(0, 1);
  lcd_out_char("CLK_VAL = ");
  lcd_out_number(RCC_value.HCLK_Frequency / 1000000);
  lcd_out_char("MHz");
  delay_us(1500);

  while (1) {

    if (mode == 0)
      mode = menu_1();

    switch (mode) {
    case 1:
      mode_open(number_repetitions_regime_open);
      mode = 0;
      break;

    case 2:
      mode_short();
      mode = 0;
      break;

    case 3:
      mode_matrix();
      mode = 0;
      break;

    case 4:
      mode_combo(mode_combo_number);
      mode = 0;
      break;

    case 5:
      mode_UART();
      mode = 0;
      break;

    case 6:
      test_sys();
      mode = 0;
      break;

    case 7:
      adjust();
      mode = 0;
      break;
    }
  }

  while (1)
    ;

  return 0;
}

void RCC_Config(void) {

#ifdef QUARZ
  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_ON);

  if ((HSE_ON = RCC_WaitForHSEStartUp()) == SUCCESS) {
    RCC_HCLKConfig(RCC_SYSCLK_Div2);
    RCC_PCLK1Config(RCC_HCLK_Div2);
    RCC_PCLK2Config(RCC_HCLK_Div16);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
      ;
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08)
      ;
    RCC_ClockSecuritySystemCmd(ENABLE);
  }
#endif

  RCC_GetClocksFreq(&RCC_value);
  SysTick_Config(RCC_value.HCLK_Frequency / 1000);

#ifdef STM32F103ZET6
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
#endif

#ifdef STM32F103C8T6
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
#endif

  // RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
  // RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
}

void GPIO_Config(void) {

  GPIO_InitTypeDef GPIOC_Config;
  GPIOC_Config.GPIO_Pin = CAP_ENTER | CAP_UP_DOWN | CAP_MODE;
  GPIOC_Config.GPIO_Mode = GPIO_Mode_IPD;
  GPIOC_Config.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(PORT_CAP, &GPIOC_Config);
}

void ADC_Config(void) {

  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("Config ADC");
  delay_us(500);

#ifdef STM32F103C8T6

  GPIO_InitTypeDef GPIO_Config_ADC;
  GPIO_Config_ADC.GPIO_Pin = GPIO_Pin_0;
  GPIO_Config_ADC.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Config_ADC.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_Config_ADC);

  ADC_InitTypeDef ADC_InitStructure;
  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = NUMB_ADC;
  ADC_Init(ADC1, &ADC_InitStructure);
  ADC_Cmd(ADC1, ENABLE);

  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_1Cycles5);
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1))
    ;
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1))
    ;
#endif

#ifdef STM32F103ZET6
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1,
                           ADC_SampleTime_1Cycles5); // ADC_Channel_6
#endif
}

void UART_Config(void) {

  GPIO_InitTypeDef UART1_GPIO;
  UART1_GPIO.GPIO_Mode = GPIO_Mode_AF_PP;
  UART1_GPIO.GPIO_Pin = GPIO_Pin_10;
  UART1_GPIO.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &UART1_GPIO);

  UART1_GPIO.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  UART1_GPIO.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOB, &UART1_GPIO);

  USART_InitTypeDef USART3_Config;
  USART3_Config.USART_BaudRate = 115200;
  USART3_Config.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART3_Config.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART3_Config.USART_Parity = USART_Parity_No;
  USART3_Config.USART_StopBits = USART_StopBits_1;
  USART3_Config.USART_WordLength = USART_WordLength_8b;
  USART_Init(USART3, &USART3_Config);
  TypeData_Init();
  USART_Cmd(USART3, ENABLE);
}

void NVIC_Configuration(void) {
  lcd_clear();
  lcd_set_xy(0, 0);
  lcd_out_char("Config NVIC");
  delay_us(500);
  NVIC_EnableIRQ(USART3_IRQn);
}
