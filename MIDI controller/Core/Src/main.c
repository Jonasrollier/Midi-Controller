/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Definitieve MIDI Matrix Controller met Diagnose-LED
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "tusb.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADDR_WRITE  0x40
#define ADDR_READ   0x41
#define IODIRA      0x00
#define IODIRB      0x01
#define GPPUB       0x0D
#define GPIOA_REG   0x12
#define GPIOB_REG   0x13
/* Debounce: 3 opeenvolgende scans (3 × 20ms = 60ms) moeten
 * consistent zijn voor een toestandsovergang wordt bevestigd. */
#define DEBOUNCE_THRESHOLD  3
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi1;

PCD_HandleTypeDef hpcd_USB_DRD_FS;

/* USER CODE BEGIN PV */
bool    key_state[16]      = {false}; /* bevestigde toestand per toets */
uint8_t debounce_count[16] = {0};     /* integrator teller 0..DEBOUNCE_THRESHOLD */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void MCP_Write(uint8_t reg, uint8_t data);
uint8_t MCP_Read(uint8_t reg);
void Matrix_Scan(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void MCP_Write(uint8_t reg, uint8_t data) {
    uint8_t tx[3] = {ADDR_WRITE, reg, data};
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, tx, 3, 10);
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
}

uint8_t MCP_Read(uint8_t reg) {
    uint8_t tx[3] = {ADDR_READ, reg, 0x00};
    uint8_t rx[3] = {0, 0, 0};
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, tx, rx, 3, 10);
    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);
    return rx[2];
}

void Matrix_Scan(void) {
    for (int col = 0; col < 4; col++) {
        MCP_Write(GPIOA_REG, (uint8_t)(~(1u << col)));
        uint8_t rows = MCP_Read(GPIOB_REG) & 0x0F;

        for (int row = 0; row < 4; row++) {
            int     index = (row * 4) + col;
            uint8_t note  = 60 + index;

            /* Ruwe (niet-gedebounced) lezing: actief LAAG */
            bool raw = !(rows & (1u << row));

            /* Integrator debounce:
             *   Ingedrukt  → teller omhoog tot DEBOUNCE_THRESHOLD
             *   Losgelaten → teller omlaag tot 0
             * Toestand wordt pas bevestigd bij respectievelijk
             * de bovengrens of de ondergrens. */
            if (raw) {
                if (debounce_count[index] < DEBOUNCE_THRESHOLD)
                    debounce_count[index]++;
            } else {
                if (debounce_count[index] > 0)
                    debounce_count[index]--;
            }

            bool debounced_pressed  = (debounce_count[index] >= DEBOUNCE_THRESHOLD);
            bool debounced_released = (debounce_count[index] == 0);

            /* Stuur MIDI alleen bij bevestigde toestandsovergang */
            if (tud_midi_mounted()) {
                if (debounced_pressed && !key_state[index]) {
                    key_state[index] = true;
                    uint8_t msg[] = {0x09, 0x90, note, 127};
                    tud_midi_packet_write(msg);
                } else if (debounced_released && key_state[index]) {
                    key_state[index] = false;
                    uint8_t msg[] = {0x08, 0x80, note, 0};
                    tud_midi_packet_write(msg);
                }
            }
        }
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_PCD_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  /* CRS: synchroniseer HSI48 op USB SOF pulsen */
  __HAL_RCC_CRS_CLK_ENABLE();
  RCC_CRSInitTypeDef RCC_CRSInitStruct = {0};
  RCC_CRSInitStruct.Prescaler             = RCC_CRS_SYNC_DIV1;
  RCC_CRSInitStruct.Source                = RCC_CRS_SYNC_SOURCE_USB;
  RCC_CRSInitStruct.Polarity              = RCC_CRS_SYNC_POLARITY_RISING;
  RCC_CRSInitStruct.ReloadValue           = __HAL_RCC_CRS_RELOADVALUE_CALCULATE(48000000, 1000);
  RCC_CRSInitStruct.ErrorLimitValue       = 34;
  RCC_CRSInitStruct.HSI48CalibrationValue = 32;
  HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);

  /* TinyUSB */
  tusb_init();

  /* MCP23S17 init */
  HAL_Delay(500);
  MCP_Write(IODIRA, 0x00); /* GPA0-3 output (kolommen) */
  MCP_Write(IODIRB, 0xFF); /* GPB0-3 input  (rijen)    */
  MCP_Write(GPPUB,  0x0F); /* pull-ups op GPB0-3       */

  /* Readback self-test: bewijst dat SPI werkt */
  if (MCP_Read(IODIRA) != 0x00 || MCP_Read(GPPUB) != 0x0F) {
    Error_Handler(); /* SPI defect: hangt hier (zichtbaar in debugger) */
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    tud_task();
    static uint32_t last_scan = 0;
    if (HAL_GetTick() - last_scan >= 20) {
      last_scan = HAL_GetTick();
      Matrix_Scan();
    }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV2;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the programming delay
  */
  __HAL_FLASH_SET_PROGRAM_DELAY(FLASH_PROGRAMMING_DELAY_0);
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CKPER;
  PeriphClkInitStruct.CkperClockSelection = RCC_CLKPSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 0x7;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  hspi1.Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
  hspi1.Init.ReadyPolarity = SPI_RDY_POLARITY_HIGH;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_DRD_FS.Instance = USB_DRD_FS;
  hpcd_USB_DRD_FS.Init.dev_endpoints = 8;
  hpcd_USB_DRD_FS.Init.speed = USBD_FS_SPEED;
  hpcd_USB_DRD_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_DRD_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.battery_charging_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.vbus_sensing_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.bulk_doublebuffer_enable = DISABLE;
  hpcd_USB_DRD_FS.Init.iso_singlebuffer_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_DRD_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET); /* CS inactief hoog bij reset */

  /*Configure GPIO pin : SPI_CS_Pin */
  GPIO_InitStruct.Pin = SPI_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PC4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
