#ifndef config_h
#define config_h

#include "uart.h"
#include "util.h"
#include "i2c_sensor.h"
#include "io_config.h"

#include <stdint.h>

enum
{
	config_magic = 0x4afc0001,
	config_major_version = 2,
	config_minor_version = 7,
};

typedef enum
{
	config_flag_strip_telnet,
	config_flag_print_debug,
	config_flag_tsl_high_sens,
	config_flag_bh_high_sens,
	config_flag_cpu_high_speed,
	config_flag_wlan_power_save,
	config_flag_wlan_sdk_connect,
	config_flag_size
} config_flag_enum_t;

assert_size(config_flag_enum_t, 4);

typedef struct
{
	config_flag_enum_t id;
	const char *const short_name;
	const char *const long_name;
} config_flag_t;

typedef struct
{
	uint16_t port;
	uint16_t timeout;
} config_tcp_t;

typedef struct
{
	int8_t io;
	int8_t pin;
} config_io_t;

typedef struct
{
	char ssid[32];
	char passwd[32];
} config_ssid_t;

typedef struct
{
	uint32_t			magic;
	uint16_t			major_version;
	uint16_t			minor_version;

	config_ssid_t		client_wlan;

	uint32_t			flags;
	uart_parameters_t	uart;

	config_tcp_t		bridge;
	config_tcp_t		command;

	config_io_t			status_trigger;
	config_io_t			assoc_trigger;

	struct
	{
		ip_addr_t	server;
		int8_t		timezone;
	} ntp;

	struct
	{
		uint16_t	flip_timeout;
		char		default_msg[32];
	} display;

	i2c_sensor_config_t	i2c_sensors;
	io_config_t			io_config;
} config_t;

extern config_t config;

bool_t	config_get_flag(config_flag_enum_t);
bool_t	config_set_flag(config_flag_enum_t, bool_t onoff);
bool_t	config_get_flag_by_name(const string_t *);
bool_t	config_set_flag_by_name(const string_t *, bool_t);
void	config_flags_to_string(string_t *, const char *, const char *, int);

void	config_read(config_t *);
void	config_write(config_t *);
void	config_dump(string_t *, const config_t *cfg);

#endif
