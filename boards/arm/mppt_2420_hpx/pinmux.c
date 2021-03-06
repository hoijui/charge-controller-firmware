/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Copyright (c) 2020 Martin Jäger / Libre Solar
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

#define STM32G4X_PINMUX_FUNC_PC6_PWM8_CH1                                      \
	(STM32_PINMUX_ALT_FUNC_4 | STM32_PUSHPULL_NOPULL)

static const struct pin_config pinconf[] = {
#ifdef CONFIG_UART_1
	{STM32_PIN_PA9, STM32G4X_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PA10, STM32G4X_PINMUX_FUNC_PA10_USART1_RX},
#endif	/* CONFIG_UART_1 */
#ifdef CONFIG_UART_3
	{STM32_PIN_PC10, STM32G4X_PINMUX_FUNC_PC10_USART3_TX},
	{STM32_PIN_PC11, STM32G4X_PINMUX_FUNC_PC11_USART3_RX},
#endif	/* CONFIG_UART_2 */
#ifdef CONFIG_I2C_1
	{STM32_PIN_PA15, STM32G4X_PINMUX_FUNC_PA15_I2C1_SCL},
	{STM32_PIN_PB7, STM32G4X_PINMUX_FUNC_PB7_I2C1_SDA},
#endif /* CONFIG_I2C_1 */
#ifdef CONFIG_PWM_STM32_2
	{STM32_PIN_PA5, STM32G4X_PINMUX_FUNC_PA5_PWM2_CH1},
#endif /* CONFIG_PWM_STM32_2 */
#ifdef CONFIG_PWM_STM32_3
	{STM32_PIN_PC6, STM32G4X_PINMUX_FUNC_PC6_PWM3_CH1},
#endif /* CONFIG_PWM_STM32_3 */
#ifdef CONFIG_PWM_STM32_8
	{STM32_PIN_PC6, STM32G4X_PINMUX_FUNC_PC6_PWM8_CH1},
#endif /* CONFIG_PWM_STM32_8 */
#ifdef CONFIG_SPI_1
	/* SPI1 on the Arduino connectors pins A2, D3, D11, D12 */
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PA4, STM32G4X_PINMUX_FUNC_PA4_SPI1_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	/* SPI1_SCK should output on PA5, but is used for LD2 */
	{STM32_PIN_PB3, STM32G4X_PINMUX_FUNC_PB3_SPI1_SCK},
	{STM32_PIN_PA6, STM32G4X_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32G4X_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif /* CONFIG_SPI_1 */
#ifdef CONFIG_SPI_2
	/* SPI2 on the ST Morpho Connector CN10 pins 16, 30, 28, 26*/
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PB12, STM32G4X_PINMUX_FUNC_PB12_SPI2_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PB13, STM32G4X_PINMUX_FUNC_PB13_SPI2_SCK},
	{STM32_PIN_PB14, STM32G4X_PINMUX_FUNC_PB14_SPI2_MISO},
	{STM32_PIN_PB15, STM32G4X_PINMUX_FUNC_PB15_SPI2_MOSI},
#endif /* CONFIG_SPI_1 */
#ifdef CONFIG_SPI_3
	/* SPI3 on the ST Morpho Connector CN7 pins 17, 1, 2, 3*/
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PA15, STM32G4X_PINMUX_FUNC_PA15_SPI3_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PC10, STM32G4X_PINMUX_FUNC_PC10_SPI3_SCK},
	{STM32_PIN_PC11, STM32G4X_PINMUX_FUNC_PC11_SPI3_MISO},
	{STM32_PIN_PC12, STM32G4X_PINMUX_FUNC_PC12_SPI3_MOSI},
#endif /* CONFIG_SPI_3 */
#ifdef CONFIG_USB_DC_STM32
	{STM32_PIN_PA11, STM32G4X_PINMUX_FUNC_PA11_USB_DM},
	{STM32_PIN_PA12, STM32G4X_PINMUX_FUNC_PA12_USB_DP},
#endif	/* CONFIG_USB_DC_STM32 */
#ifdef CONFIG_ADC_2
    {STM32_PIN_PA4, STM32G4X_PINMUX_FUNC_PA4_ADC2_IN17},
#endif  /* CONFIG_ADC_2 */
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);


const char *led_ports[CONFIG_NUM_LED_PINS] = {
    DT_GPIO_LEDS_PWR_GPIOS_CONTROLLER,
};
const int led_pins[CONFIG_NUM_LED_PINS] = {
    DT_GPIO_LEDS_PWR_GPIOS_PIN,
};
