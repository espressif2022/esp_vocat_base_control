/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

// Command codes - Send
#define ECHO_BASE_CMD_SET_ANGLE                       0x01

#define ECHO_BASE_CMD_SET_ACTION                      0x02
//sub commands for ECHO_BASE_CMD_SET_ACTION
#define ECHO_BASE_CMD_SET_ACTION_SHARK_HEAD           0x0000  /**< Shake head action */
#define ECHO_BASE_CMD_SET_ACTION_SHARK_HEAD_DECAY     0x0001  /**< Gradual decreasing shake head */
#define ECHO_BASE_CMD_SET_ACTION_LOOK_AROUND          0x0002  /**< Look around action */
#define ECHO_BASE_CMD_SET_ACTION_BEAT_SWING           0x0003  /**< Beat-synchronized swing */
#define ECHO_BASE_CMD_SET_ACTION_CAT_NUZZLE           0x0004  /**< Cat nuzzle action */

#define ECHO_BASE_CMD_SET_CALIBRATE                   0x03
//sub commands for ECHO_BASE_CMD_SET_CALIBRATE
#define ECHO_BASE_CMD_RECV_CALIBRATE_START             0x0011
#define ECHO_BASE_CMD_RECV_CALIBRATE_STEP1             0x0012
#define ECHO_BASE_CMD_RECV_CALIBRATE_STEP2             0x0013

// Command codes - Receive
#define ECHO_BASE_CMD_RECV_SLIDE_SWITCH               0x03
//sub commands for ECHO_BASE_CMD_RECV_SLIDE_SWITCH
#define ECHO_BASE_CMD_RECV_SWITCH_INIT                0x0000
#define ECHO_BASE_CMD_RECV_SWITCH_SLIDE_DOWN          0x0001
#define ECHO_BASE_CMD_RECV_SWITCH_SLIDE_UP            0x0002
#define ECHO_BASE_CMD_RECV_SWITCH_REMOVE_FROM_UP      0x0003
#define ECHO_BASE_CMD_RECV_SWITCH_REMOVE_FROM_DOWN    0x0004
#define ECHO_BASE_CMD_RECV_SWITCH_PLACE_FROM_UP       0x0005
#define ECHO_BASE_CMD_RECV_SWITCH_PLACE_FROM_DOWN     0x0006
#define ECHO_BASE_CMD_RECV_SWITCH_SINGLE_CLICK        0x0007
#define ECHO_BASE_CMD_RECV_SWITCH_FISH_ATTACHED       0x0008
#define ECHO_BASE_CMD_RECV_SWITCH_FISH_DETACH         0x0009
#define ECHO_BASE_CMD_RECV_SWITCH_PAIR_DETECT         0x000A
#define ECHO_BASE_CMD_RECV_SWITCH_PAIR_CANCEL         0x000B

#define ECHO_BASE_CMD_RECV_PERCEPTION                 0x06

#define ECHO_BASE_CMD_RECV_ACTION                     0x02
//sub commands for ECHO_BASE_CMD_RECV_ACTION
#define ECHO_BASE_CMD_RECV_ACTION_DONE                0x0010

#define ECHO_BASE_CMD_RECV_HEARTBEAT                  0x00
//sub commands for ECHO_BASE_CMD_RECV_HEARTBEAT
#define ECHO_BASE_CMD_RECV_HEARTBEAT_ALIVE            0x0001

/**
 * @brief Command response callback function type
 *
 * @param cmd      Command code
 * @param data     Pointer to data buffer
 * @param data_len Length of data
 * @param user_ctx User context pointer
 */
typedef void (*echo_base_control_cmd_callback_t)(uint8_t cmd, uint8_t *data, int data_len, void *user_ctx);

/**
 * @brief Echo base control configuration structure
 */
typedef struct {
    uart_port_t uart_num;                        /**< UART port number */
    gpio_num_t tx_pin;                           /**< UART TX pin */
    gpio_num_t rx_pin;                           /**< UART RX pin */
    uint32_t baud_rate;                          /**< UART baud rate (default: 115200) */
    uint32_t rx_buffer_size;                     /**< UART RX buffer size (default: 1024) */
    echo_base_control_cmd_callback_t cmd_cb;    /**< Command response callback (can be NULL) */
    void *user_ctx;                              /**< User context for callback */
} echo_base_control_config_t;

/**
 * @brief  Initialize echo base control module
 *
 *         Configure and install UART driver for communication with echo base device.
 *         UART configuration: 115200 baud rate, 8 data bits, no parity, 1 stop bit.
 *         The handle is maintained internally.
 *
 * @param  config  Configuration structure containing UART settings
 *
 * @return
 *       - ESP_OK  Initialization successful
 *       - Other   Error code if initialization failed
 */
esp_err_t echo_base_control_init(const echo_base_control_config_t *config);

/**
 * @brief  Set echo base angle value
 *
 *         Send control frame via UART to set the target angle of echo base device.
 *
 * @param  angle   Angle value (range: 0~65535)
 *
 * @return
 *       - ESP_OK  Setting successful
 *       - Other   Error code if setting failed
 */
esp_err_t echo_base_control_set_angle(int angle);

/**
 * @brief  Set echo base action value
 *
 *         Send control frame via UART to set the target action of echo base device.
 *
 * @param  action  Action value
 *
 * @return
 *       - ESP_OK  Setting successful
 *       - Other   Error code if setting failed
 */
esp_err_t echo_base_control_set_action(int action);

/**
 * @brief  Set echo base calibrate
 *
 *         Send control frame via UART to calibrate echo base device.
 *
 * @return
 *       - ESP_OK  Setting successful
 *       - Other   Error code if setting failed
 */
esp_err_t echo_base_control_set_calibrate(void);

/**
 * @brief  Deinitialize echo base control module
 *
 * @return
 *       - ESP_OK  Deinitialization successful
 *       - Other   Error code if deinitialization failed
 */
esp_err_t echo_base_control_deinit(void);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

