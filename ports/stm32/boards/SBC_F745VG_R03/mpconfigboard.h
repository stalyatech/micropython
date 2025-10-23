#define MICROPY_HW_BOARD_NAME       "simpleRTK2B-SBC-R03"
#define MICROPY_HW_MCU_NAME         "STM32F745"
#define MICROPY_HW_FLASH_FS_LABEL   "SBC"

// Define the frozen script to be executed during boot
#define MICROPY_BOARD_FROZEN_BOOT_FILE "_boot.py"

#define MICROPY_PY_SYS_PLATFORM  	MICROPY_HW_BOARD_NAME

#ifndef MICROPY_FLOAT_IMPL
#define MICROPY_FLOAT_IMPL          (MICROPY_FLOAT_IMPL_DOUBLE)
#endif

#define MICROPY_HW_HAS_SWITCH       (0)
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (0)
#define MICROPY_HW_HAS_FLASH        (1)
#define MICROPY_HW_ENABLE_RNG       (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_DAC       (0)
#define MICROPY_HW_ENABLE_USB       (1)
#define MICROPY_HW_USB_FS 					(1)
#define MICROPY_HW_ENABLE_SDCARD    (1)
#define MICROPY_HW_SDMMC_BUS_WIDTH  (1)
#define MICROPY_HW_SDCARD_MOUNT_AT_BOOT	(1)
#define MICROPY_HW_SDMMC_BUS_WIDTH  (1)
#define MICROPY_PY_THREAD       		(1)
#define MICROPY_ENABLE_DOC_STRING   (1)

// HSE is 12MHz
// VCOClock = HSE * PLLN / PLLM = 12 MHz * 216 / 6 = 432 MHz
// SYSCLK = VCOClock / PLLP = 432 MHz / 2 = 216 MHz
// USB/SDMMC/RNG Clock = VCOClock / PLLQ = 432 MHz / 9 = 48 MHz
#define MICROPY_HW_CLK_PLLM (6)
#define MICROPY_HW_CLK_PLLN (216)
#define MICROPY_HW_CLK_PLLP (RCC_PLLP_DIV2)
#define MICROPY_HW_CLK_PLLQ (9)

// From the reference manual, for 2.7V to 3.6V
// 151-180 MHz => 5 wait states
// 181-210 MHz => 6 wait states
// 211-216 MHz => 7 wait states
#define MICROPY_HW_FLASH_LATENCY    FLASH_LATENCY_7 // 210-216 MHz needs 7 wait states

// UART config
#define MICROPY_HW_UART1_TX         (pin_B6) // F9H1_TXD GPS3
#define MICROPY_HW_UART1_RX         (pin_B7) // F9H1_RXD GPS3
#define MICROPY_HW_UART2_TX         (pin_D5) // F9H2_TXD GPS2
#define MICROPY_HW_UART2_RX         (pin_D6) // F9H2_RXD GPS2
#define MICROPY_HW_UART3_TX         (pin_D8) // SRV_TXD
#define MICROPY_HW_UART3_RX         (pin_D9) // SRV_RXD
#define MICROPY_HW_UART4_TX         (pin_C10)// XBEE_A_TXD
#define MICROPY_HW_UART4_RX         (pin_C11)// XBEE_A_RXD
#define MICROPY_HW_UART6_TX         (pin_C6) // XBEE_B_TXD
#define MICROPY_HW_UART6_RX         (pin_C7) // XBEE_B_RXD
#define MICROPY_HW_UART7_TX         (pin_E8) // GSM_TXD
#define MICROPY_HW_UART7_RX         (pin_E7) // GSM_RXD
#define MICROPY_HW_UART7_RTS        (pin_E9) // GSM_RTS
#define MICROPY_HW_UART7_CTS        (pin_E10)// GSM_CTS
#define MICROPY_HW_UART8_TX         (pin_E1) // F9P_TXD GPS1
#define MICROPY_HW_UART8_RX         (pin_E0) // F9P_RXD GPS1

#define MICROPY_HW_UART_REPL        PYB_UART_3
#define MICROPY_HW_UART_REPL_BAUD   115200

// I2C buses
#define MICROPY_HW_I2C3_SCL         (pin_A8) // I2C_SCL
#define MICROPY_HW_I2C3_SDA         (pin_C9) // I2C_SDA

// SPI
#define MICROPY_HW_SPI1_NSS         (pin_D7)
#define MICROPY_HW_SPI1_SCK         (pin_B3)
#define MICROPY_HW_SPI1_MISO        (pin_B4)
#define MICROPY_HW_SPI1_MOSI        (pin_B5)

#define MICROPY_HW_SPI4_NSS         (pin_E11)
#define MICROPY_HW_SPI4_SCK         (pin_E12)
#define MICROPY_HW_SPI4_MISO        (pin_E13)
#define MICROPY_HW_SPI4_MOSI        (pin_E14)

// Use external SPI flash for storage
#define MICROPY_HW_SPIFLASH_SIZE_BITS       (128 * 1024 * 1024)
#define MICROPY_HW_SPIFLASH_CS              (pin_D7)
#define MICROPY_HW_SPIFLASH_SCK             (pin_B3)
#define MICROPY_HW_SPIFLASH_MOSI            (pin_B5)
#define MICROPY_HW_SPIFLASH_MISO            (pin_B4)
#define MICROPY_HW_SPIFLASH_ENABLE_CACHE    (1)

extern const struct _mp_spiflash_config_t spiflash_config;
extern struct _spi_bdev_t spi_bdev;
#define MICROPY_HW_BDEV_IOCTL(op, arg) ( \
    (op) == BDEV_IOCTL_NUM_BLOCKS ? (MICROPY_HW_SPIFLASH_SIZE_BITS / 8 / FLASH_BLOCK_SIZE) : \
    (op) == BDEV_IOCTL_INIT ? spi_bdev_ioctl(&spi_bdev, (op), (uint32_t)&spiflash_config) : \
    spi_bdev_ioctl(&spi_bdev, (op), (arg)) \
)
#define MICROPY_HW_BDEV_READBLOCKS(dest, bl, n) spi_bdev_readblocks(&spi_bdev, (dest), (bl), (n))
#define MICROPY_HW_BDEV_WRITEBLOCKS(src, bl, n) spi_bdev_writeblocks(&spi_bdev, (src), (bl), (n))
#define MICROPY_HW_BDEV_SPIFLASH_EXTENDED (&spi_bdev) // for extended block protocol
#define MICROPY_HW_BDEV_SPIFLASH_OFFSET_BYTES	(0)

// CAN busses
#define MICROPY_HW_CAN1_TX          (pin_D0)
#define MICROPY_HW_CAN1_RX          (pin_D1)

// LEDs
#define MICROPY_HW_LED1             (pin_E13)    // LED1
#define MICROPY_HW_LED2             (pin_E12)    // LED2
#define MICROPY_HW_LED3             (pin_D4)    // LED3
#define MICROPY_HW_LED_ON(pin)      (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_OFF(pin)     (mp_hal_pin_low(pin))

// USB config (CN13 - USB OTG FS)
#define MICROPY_HW_USB_FS              (1)
#define MICROPY_HW_USB_OTG_ID_PIN      (pin_A10)

// SD card detect switch
#define MICROPY_HW_SDCARD_DETECT_PIN        (pin_D3)
#define MICROPY_HW_SDCARD_DETECT_PULL       (GPIO_PULLUP)
#define MICROPY_HW_SDCARD_DETECT_PRESENT    (GPIO_PIN_SET)

// SD card
#define MICROPY_HW_SDCARD_BUS_WIDTH (1)
#define MICROPY_HW_SDMMC_D0			(pin_C8)
#define MICROPY_HW_SDMMC_CK 		(pin_C12)
#define MICROPY_HW_SDMMC_CMD 		(pin_D2)

// Ethernet via RMII
#define MICROPY_HW_ETH_MDC          (pin_C1)
#define MICROPY_HW_ETH_MDIO         (pin_A2)
#define MICROPY_HW_ETH_RMII_REF_CLK (pin_A1)
#define MICROPY_HW_ETH_RMII_CRS_DV  (pin_A7)
#define MICROPY_HW_ETH_RMII_RXD0    (pin_C4)
#define MICROPY_HW_ETH_RMII_RXD1    (pin_C5)
#define MICROPY_HW_ETH_RMII_TX_EN   (pin_B11)
#define MICROPY_HW_ETH_RMII_TXD0    (pin_B12)
#define MICROPY_HW_ETH_RMII_TXD1    (pin_B13)
#define MICROPY_HW_ETH_RST          (pin_B14)
#define MICROPY_HW_ETH_INT    	    (pin_B15)

// Bootloader configuration
#define MBOOT_FSLOAD 			(1)
#define MBOOT_VFS_FAT 			(1)

// #define MBOOT_SPIFLASH_LAYOUT     "/0x00000000/64*32Kg"
#define MBOOT_SPIFLASH_LAYOUT "/0x80000000/64*32Kg"
#define MBOOT_SPIFLASH_ERASE_BLOCKS_PER_PAGE (32 / 4)
#define MBOOT_SPIFLASH_ADDR     	(0x00000000)
#define MBOOT_SPIFLASH_BYTE_SIZE	(MICROPY_HW_SPIFLASH_SIZE_BITS / 8)
#define MBOOT_SPIFLASH_SPIFLASH 	(&spi_bdev.spiflash)
#define MBOOT_SPIFLASH_CONFIG 		(&spiflash_config)
