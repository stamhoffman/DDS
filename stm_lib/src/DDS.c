#include "stm32f10x_conf.h"
#include "mode.h"

uint32_t calc_registr(double fraquent)
{
  uint32_t control_registr_dds = 0;
  control_registr_dds = fraquent * 4294967296.0 / 180e6;
  return control_registr_dds;
}

void config_port_dds()
{
  if (DDS_PORT_CONTROL == GPIOB) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  }

  GPIO_InitTypeDef GPIO_DDS_CONTROL;
  GPIO_DDS_CONTROL.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_DDS_CONTROL.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_DDS_CONTROL.GPIO_Pin = W_CLK | FQ_UD | DATA_ | RESET;
  GPIO_Init(DDS_PORT_CONTROL, &GPIO_DDS_CONTROL);
}
/**
  * @brief  setting the operation mode.
  * @param  phase signala, signal multiplier status, choose the mode of communication,
  * @retval None
  */

void pack_send_mode_dds(uint8_t phase, uint8_t mux6_mode, uint8_t serial_mode, uint8_t power_down)
{
/* ---  the first word from the 40-bit control register ---*/
  uint8_t w0 = 0;
  phase <<= 5;
  serial_mode <<= 1;
  power_down <<= 3;
  w0 = w0 | phase | serial_mode | power_down | mux6_mode;

  if (serial_mode == 0) {                      // Parallel load Mode
    GPIO_Write(PORT_DATA_DDS, w0);
    GPIO_SetBits(DDS_PORT_CONTROL, W_CLK);
    GPIO_ResetBits(DDS_PORT_CONTROL, W_CLK);
  }

  if (serial_mode == 1) {
    uint8_t count;
    for(count = 0; count < 8; count++, w0 = w0 >> 1)
    {
      w0 = w0 & 1;
      GPIO_SetBits(DDS_PORT_CONTROL, DATA_);
      GPIO_ResetBits(DDS_PORT_CONTROL, DATA_);
      GPIO_SetBits(DDS_PORT_CONTROL, W_CLK);
      GPIO_ResetBits(DDS_PORT_CONTROL, W_CLK);
    }
  }
}

void set_parallel_mode(void)
{
  GPIO_SetBits(DDS_PORT_CONTROL, RESET);        //Reset DDS
  GPIO_ResetBits(DDS_PORT_CONTROL, RESET);
  pack_send_mode_dds(0, 0, 0, mux_clobal);
  send_data_parallel(0);
}


void set_serial_mode(void)
{
  GPIO_SetBits(DDS_PORT_CONTROL, RESET);        //Reset DDS
  GPIO_ResetBits(DDS_PORT_CONTROL, RESET);
  pack_send_mode_dds(0, 0, 1, mux_clobal);
  GPIO_SetBits(DDS_PORT_CONTROL, FQ_UD);     // Serial load Mode
  GPIO_ResetBits(DDS_PORT_CONTROL, FQ_UD);
  send_data_serial_mode(0);
  GPIO_SetBits(DDS_PORT_CONTROL, FQ_UD);     // Serial load Mode
  GPIO_ResetBits(DDS_PORT_CONTROL, FQ_UD);
}


void send_data_serial_mode(uint32_t control_registr_dds)
{
  int count;
  for(count = 0; count < 32; count++, control_registr_dds = control_registr_dds >> 1)
  {
    GPIO_SetBits(DDS_PORT_CONTROL, DATA_);
    GPIO_SetBits(DDS_PORT_CONTROL, W_CLK);
    GPIO_ResetBits(DDS_PORT_CONTROL, W_CLK);
  }
}

void send_data_parallel(uint32_t control_registr_dds)
{
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
