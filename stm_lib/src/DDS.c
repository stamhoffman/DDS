#include "stm32f10x_conf.h"

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

void config_port_dds(uint16_t port_control, uint16_t port_data){

#ifdef TYPE_CONTROL_SERIAL


#endif

#ifdef 	 TYPE_CONTROL_PARALLEL
GPIO_TypeDef GPIO_UPR;
GPIO_UPR.GPIO_Pin = W_CLK;

#endif


}




