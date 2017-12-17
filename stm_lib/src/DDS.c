#include "stm32f10x_conf.h"

uint32_t calc_registr(double fraquent) {
  uint32_t control_registr_dds = 0;
  control_registr_dds = fraquent * 4294967296.0 / 180e6;
  return control_registr_dds;
}

void send_data_parallel(uint32_t control_registr_dds) {
  uint8_t count = 0;
  for (count = 0; count < 4; count++, control_registr_dds >>= 8) {
    control_registr_dds = control_registr_dds & 0xFF;
    GPIO_Write(PORT_DATA_DDS, (uint8_t)control_registr_dds);
    GPIO_SetBits(DDS_PORT_CONTROL, W_CLK);
    GPIO_ResetBits(DDS_PORT_CONTROL, W_CLK);
  }
  GPIO_SetBits(DDS_PORT_CONTROL, FQ_UD);
  GPIO_ResetBits(DDS_PORT_CONTROL, FQ_UD);
}

void config_port_dds() {

  if (DDS_PORT_CONTROL == GPIOB) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  }

  GPIO_InitTypeDef GPIO_DDS_CONTROL;
  GPIO_DDS_CONTROL.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_DDS_CONTROL.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_DDS_CONTROL.GPIO_Pin = W_CLK | FQ_UD | DATA_ | RESET;
  GPIO_Init(DDS_PORT_CONTROL, &GPIO_DDS_CONTROL);

#ifdef TYPE_CONTROL_PARALLEL
  if (PORT_DATA_DDS == GPIOA) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  }

  GPIO_InitTypeDef GPIO_DDS_DATA;
  GPIO_DDS_DATA.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_DDS_DATA.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_DDS_DATA.GPIO_Pin = BIT_DATA_ALL;
  GPIO_Init(PORT_DATA_DDS, &GPIO_DDS_DATA);

#endif
}

void set_option_dds(uint8_t phase, uint8_t mux6_mode, uint8_t serial_mode,uint8_t power_down)
{
	uint8_t w0 = 0;
	phase <<= 5;
	serial_mode <<= 1;
	power_down <<= 3;
	w0 = w0 | phase | serial_mode |power_down;
	GPIO_Write(PORT_DATA_DDS, w0);
    GPIO_SetBits(DDS_PORT_CONTROL, W_CLK);
    GPIO_ResetBits(DDS_PORT_CONTROL, W_CLK);
}

