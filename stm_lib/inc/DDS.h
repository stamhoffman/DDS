#define DDS_PORT   GPIOA
#define W_CLK      GPIO_Pin_7
#define FQ_UD      GPIO_Pin_6
#define DATA       GPIO_Pin_5
#define RESET      GPIO_Pin_4

#define TYPE_CONTROL  SERIAL // SERIAL or PARALLEL


void init_serial_control(void);
void reset_();
void send_data_serial();
void send_data_parallel();


struct
{
	uint32_t delta_Phase;
	uint8_t  phase;
	uint8_t  ;
	uint8_t  set_power_state;
} Codogram_control;


struct
{
	uint8_t mux6_set;
	uint8_t serial_mode_set;
	uint8_t power_down;
	uint8_t ph0;
	uint8_t ph1;
	uint8_t ph2;
	uint8_t ph3;
	uint8_t ph4;
} W0_control;

struct
{
	uint8_t mux6_set:0;
	uint8_t serial_mode_set;
	uint8_t power_down;
	uint8_t ph0;
	uint8_t ph1;
	uint8_t ph2;
	uint8_t ph3;
	uint8_t ph4;
} control;

enum mode_set {Enable = 1,Disable = 0};

