/**
  ******************************************************************************
  * @file    OTFDEC_OTFDEC_Encryption/Inc/macronix.h
  * @author  MCD Application Team
  * @brief   Specific part for Macronix memories
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MACRONIX_H
#define MACRONIX_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* MX25UM51245G Macronix memory */

/* Size of the flash */
#define OSPI_FLASH_SIZE             26U
#define OSPI_PAGE_SIZE              256U
#define OSPI_SECTOR_SIZE            4096U
#define OSPI_BLOCK_SIZE             65536U

/* Flash commands */
#define OCTAL_IO_DTR_READ_CMD       0xEE11U
#define OCTAL_IO_READ_CMD           0xEC13U
#define OCTAL_PAGE_PROG_CMD         0x12EDU
#define OCTAL_READ_STATUS_REG_CMD   0x05FAU
#define OCTAL_READ_CFG_REG_CMD      0x15EAU
#define OCTAL_READ_CFG_REG_2_CMD    0x718EU
#define OCTAL_SECTOR_ERASE_CMD      0x21DEU
#define OCTAL_BLOCK_ERASE_CMD       0xDC23U
#define OCTAL_WRITE_ENABLE_CMD      0x06F9U
#define READ_STATUS_REG_CMD         0x05U
#define READ_CFG_REG_CMD            0x15U
#define READ_CFG_REG_2_CMD          0x71U
#define WRITE_CFG_REG_2_CMD         0x72U
#define WRITE_ENABLE_CMD            0x06U
#define SECTOR_ERASE_CMD            0x20U
#define PAGE_PROG_CMD               0x02U
#define READ_CMD                    0x03U

/* Dummy clocks cycles */
#define DUMMY_CLOCK_CYCLES_READ_OCTAL   	NB_DUMMY_CYCLE

/* Auto-polling values */
#define WRITE_ENABLE_MATCH_VALUE    0x02U
#define WRITE_ENABLE_MASK_VALUE     0x02U

#define MEMORY_READY_MATCH_VALUE    0x00U
#define MEMORY_READY_MASK_VALUE     0x01U

#define AUTO_POLLING_INTERVAL       0x10U

/* Memory registers address */
#define CONFIG_REG2_ADDR1           0x0000000UL
#define CR2_DTR_OPI_ENABLE          0x02U
#define CR2_STR_OPI_ENABLE          0x01U

#define CONFIG_REG2_ADDR2           0x00000200UL
#define CR2_DQS_PRE_CYCLE			      0x01U

#define CONFIG_REG2_ADDR3           0x00000300UL
#define CR2_DUMMY_CYCLES_66MHZ      0x07U
#define CR2_DUMMY_CYCLES_84MHZ      0x06U
#define CR2_DUMMY_CYCLES_104MHZ     0x05U
#define CR2_DUMMY_CYCLES_133MHZ     0x03U
#define CR2_DUMMY_CYCLES_166MHZ     0x02U
#define CR2_DUMMY_CYCLES_200MHZ     0x00U

/* Memory delay */
#define MEMORY_REG_WRITE_DELAY      40U
#define MEMORY_PAGE_PROG_DELAY      2U

/* Read registers */
#define STATUS_REGISTER							0x00U
#define CFG_REGISTER								0x01U
#define CFG2_REGISTER1							0x02U
#define CFG2_REGISTER2							0x03U
#define CFG2_REGISTER3							0x04U

/* Exported functions ------------------------------------------------------- */

#endif /* __MACRONIX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
