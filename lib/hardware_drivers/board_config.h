#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

// Board identifier
#define BOARD_WAVESHARE_AMOLED_18

// Display configuration (SH8601)
#define LCD_CS    19
#define LCD_SCLK  1
#define LCD_SDIO0 3
#define LCD_SDIO1 2
#define LCD_SDIO2 4
#define LCD_SDIO3 5
#define LCD_RST   -1 // Controlled by software
#define TFT_WIDTH  368
#define TFT_HEIGHT 448

// Touch configuration (FT3168)
#define I2C_SDA     6
#define I2C_SCL     7
#define TOUCH_INT   47

// Audio configuration (ES8311)
#define I2S_WS    20
#define I2S_SCK   21
#define I2S_SD    22

// IMU configuration (QMI8658)
#define IMU_ADDR  0x6B

// RTC configuration (PCF85063)
#define RTC_ADDR  0x51

// Power Management configuration (AXP2101)
#define AXP_ADDR  0x34

// TF Card configuration
#define SD_CMD    23
#define SD_CLK    24
#define SD_D0     25
#define SD_D1     26
#define SD_D2     27
#define SD_D3     28

// UART configuration
#define UART_TX   8
#define UART_RX   9

// USB configuration
#define USB_DM    10
#define USB_DP    11

// GPIO Expander (TCA9554)
#define EXIO0 12
#define EXIO1 13
#define EXIO2 14
#define EXIO3 15
#define EXIO4 16 // PWR button
#define EXIO5 17
#define EXIO6 18
#define EXIO7 19 // LCD_CS

#endif // BOARD_CONFIG_H
