#define TYPE_CONTROL_PARALLEL // TYPE_CONTROL_SERIAL (default)

#define DDS_PORT_CONTROL   GPIOB
#define W_CLK      GPIO_Pin_0
#define FQ_UD      GPIO_Pin_1
#define DATA_      GPIO_Pin_2
#define RESET      GPIO_Pin_3

#ifdef TYPE_CONTROL_PARALLEL
#define PORT_DATA_DDS GPIOA
#define BIT_DATA_0 GPIO_Pin_4
#define BIT_DATA_1 GPIO_Pin_5
#define BIT_DATA_2 GPIO_Pin_6
#define BIT_DATA_3 GPIO_Pin_7
#define BIT_DATA_4 GPIO_Pin_8
#define BIT_DATA_5 GPIO_Pin_9
#define BIT_DATA_6 GPIO_Pin_10
#define BIT_DATA_7 GPIO_Pin_11
#define BIT_DATA_ALL (BIT_DATA_0 | BIT_DATA_1 | BIT_DATA_2 | BIT_DATA_3 | BIT_DATA_4 | BIT_DATA_5 | BIT_DATA_6 | BIT_DATA_7)

#endif

void config_port_dds(void);
void set_option_dds(uint8_t phase, uint8_t mux6_mode, uint8_t serial_mode,uint8_t power_down);
void reset(void);
void send_data_serial(uint32_t control_registr_dds);
void send_data_parallel(uint32_t control_registr_dds);
uint32_t calc_registr(double fraquent);


typedef enum mode_set {Enable = 1,Disable = 0};

