/**
  @page WWDG_ResetAfterSwFailure Window Watchdog example

  @verbatim
  ******************************************************************************
  * @file    WWDG/WWDG_ResetAfterSwFailure/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the Window Watchdog example.
  ******************************************************************************
  *
  * Copyright (c) 2019 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

@par Example Description

How to perform periodic update of WWDG counter and simulate a software fault that
generates an MCU WWDG reset when a predefined time period has elapsed.


This projects is configured for STM32H735xx devices using STM32CubeH7 HAL and running on
STM32H735G-DK board from STMicroelectronics.

At the beginning of the main program the HAL_Init() function is called to reset
all the peripherals, initialize the Flash interface and the systick.
The SystemClock_Config() function is used to configure the system clock for STM32H735xx Devices :
The CPU at 520 MHz
The HCLK for D1 Domain AXI peripherals, D2 Domain AHB peripherals and D3 Domain AHB  peripherals at 260 MHz.
The APB clock dividers for D1 Domain APB3 peripherals, D2 Domain APB1 and APB2 peripherals and D3 Domain APB4 peripherals to run at 130 MHz.

The WWDG peripheral configuration is ensured by the HAL_WWDG_Init() function.
This later is calling the HAL_WWDG_MspInit()function which core is implementing
the configuration of the needed WWDG resources according to the used hardware (CLOCK,
GPIO, DMA and NVIC). You may update this function to change WWDG configuration.

The reset scope control bit should be set before enabling the WWDG to ensure
a wide system reset.

The WWDG timeout is set to 536 ms and the refresh window is set to 334 ms.
This means that, each cycle, the WWDG refresh must happen:
 - After 536 ms - 334 ms = 202 ms
 - Before 536 ms
The WWDG counter is refreshed each 202ms in the main program infinite loop to
prevent a WWDG reset.
LED1 is toggling at same frequency, indicating that the program is running.

An EXTI Line is connected to a GPIO pin, and configured to generate an interrupt
on the rising edge of the signal.

The EXTI Line is used to simulate a software failure: once the EXTI Line event
occurs by pressing the User push-button (PC.13), the corresponding interrupt is served.

In the ISR, a write to an invalid address generates a Hardfault exception containing
an infinite loop and preventing from returning to main program (the WWDG counter is
not refreshed).

As a result, when the WWDG counter falls to 63, the WWDG reset occurs.

If the WWDG reset is generated, after the system resumes from reset, LED1 is turned ON for 4s.

If the EXTI Line event does not occur, the WWDG counter is indefinitely refreshed
in the main program infinite loop, and there is no WWDG reset.

LED3 is turned ON and remains ON if any error occurs.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@Note If the  application is using the DTCM/ITCM memories (@0x20000000/ 0x0000000: not cacheable and only accessible
      by the Cortex M7 and the  MDMA), no need for cache maintenance when the Cortex M7 and the MDMA access these RAMs.
      If the application needs to use DMA(or other masters) based access or requires more RAM, then  the user has to:
              - Use a non TCM SRAM. (example : D1 AXI-SRAM @ 0x24000000)
              - Add a cache maintenance mechanism to ensure the cache coherence between CPU and other masters(DMAs,DMA2D,LTDC,MDMA).
              - The addresses and the size of cacheable buffers (shared between CPU and other masters)
                must be	properly defined to be aligned to L1-CACHE line size (32 bytes).

@Note It is recommended to enable the cache and maintain its coherence.
      Depending on the use case it is also possible to configure the cache attributes using the MPU.
      Please refer to the AN4838 "Managing memory protection unit (MPU) in STM32 MCUs"
      Please refer to the AN4839 "Level 1 cache on STM32F7 Series"

@par Keywords

System, WWDG, Downcounter, MCU Reset, Timeout, Software fault

@par Directory contents

  - WWDG/WWDG_ResetAfterSwFailure/Inc/stm32h7xx_hal_conf.h    HAL configuration file
  - WWDG/WWDG_ResetAfterSwFailure/Inc/stm32h7xx_it.h          Interrupt handlers header file
  - WWDG/WWDG_ResetAfterSwFailure/Inc/stm32h735g_discovery_conf.h  STM32H735G-DK board configuration file
  - WWDG/WWDG_ResetAfterSwFailure/Inc/main.h                  Header for main.c module

  - WWDG/WWDG_ResetAfterSwFailure/Src/stm32h7xx_it.c          Interrupt handlers
  - WWDG/WWDG_ResetAfterSwFailure/Src/main.c                  Main program
  - WWDG/WWDG_ResetAfterSwFailure/Src/stm32h7xx_hal_msp.c     HAL MSP file
  - WWDG/WWDG_ResetAfterSwFailure/Src/system_stm32h7xx.c      STM32H7xx system source file

@par Hardware and Software environment

  - This example runs on STM32H735xx devices.

  - This example has been tested with STMicroelectronics STM32H735G-DK
    board and can be easily tailored to any other supported device
    and development board.


@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example



 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
