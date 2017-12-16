#include "stm32f10x_conf.h"

#define DDS_PORT   GPIOA
#define W_CLK      GPIO_Pin_7
#define FQ_UD      GPIO_Pin_6
#define DATA       GPIO_Pin_5
#define RESET      GPIO_Pin_4

#define TYPE_CONTROL  SERIAL // SERIAL or PARALLEL

void config_port_dds(uint16_t PORT_UPR, uint16_t PORT_DATA, uint16_t TYPE_CONTROL);
void init_serial_control(void);
void reset();
void send_data_serial();
void send_data_parallel();
uint32_t calc_registr();


struct
{
	uint32_t delta_phase;
	uint8_t  phase;
	uint8_t  sys_clock;
	uint8_t  fraquent_out;
} config_out;


typedef struct
{
	uint8_t mux6_mode;
	uint8_t serial_mode;
	uint8_t power_down;
	uint8_t ph0;
	uint8_t ph1;
	uint8_t ph2;
	uint8_t ph3;
	uint8_t ph4;
} w_control;

typedef struct
{
	uint8_t mux6_mode:1;
	uint8_t serial_mode:1;
	uint8_t power_down:1;
	uint8_t ph0:1;
	uint8_t ph1:1;
	uint8_t ph2:1;
	uint8_t ph3:1;
	uint8_t ph4:1;
} control;

typedef enum mode_set {Enable = 1,Disable = 0};


uint32_t calc_registr(double fraquent)
{
uint32_t control_registr_dds = 0;
control_registr_dds = fraquent * 4294967296.0/180e6;
return control_registr_dds;
}

void send_data_parallel(uint32_t control_registr_dds)
{
	uint8_t count = 0;
	for(count = 0; count < 4; control_registr_dds >>=8)
	{

	}


}

