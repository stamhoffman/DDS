#define DDS_PORT   GPIOA
#define W_CLK      GPIO_Pin_7
#define FQ_UD      GPIO_Pin_6
#define DATA_      GPIO_Pin_5
#define RESET      GPIO_Pin_4

#define TYPE_CONTROL_PARALLEL // SERIAL = 1 or PARALLEL = 0(default)

void config_port_dds(uint16_t port_control, uint16_t port_data);
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
