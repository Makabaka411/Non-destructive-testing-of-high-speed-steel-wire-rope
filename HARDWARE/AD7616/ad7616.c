#include "ad7616.h"

int16_t adc_data_a[8];
int16_t adc_data_b[8];
int s_volt_a[8];
int s_volt_b[8];
u8 CH_NUM = 8;

void AD7616_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(RESET_GPIO_CLK | SEQEN_GPIO_CLK | RNGSEL0_GPIO_CLK | RNGSEL1_GPIO_CLK | SER_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(D0_GPIO_CLK | D1_GPIO_CLK | D2_GPIO_CLK | D3_GPIO_CLK | D4_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(D5_GPIO_CLK | D6_GPIO_CLK | D7_GPIO_CLK | D8_GPIO_CLK | D9_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(D10_GPIO_CLK | SDOB_GPIO_CLK | SDOA_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(OS0_GPIO_CLK | OS1_GPIO_CLK | OS2_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(WR_GPIO_CLK | SCK_GPIO_CLK | CS_GPIO_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(CH0_GPIO_CLK | CH1_GPIO_CLK | CH2_GPIO_CLK | BUSY_GPIO_CLK | CONVST_GPIO_CLK, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;      /* 输出 */
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;     /* 推挽 */
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;       /* 上拉 */
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz; /* 高速 */

    GPIO_InitStruct.GPIO_Pin = RESET_GPIO_PIN;
    GPIO_Init(RESET_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SEQEN_GPIO_PIN;
    GPIO_Init(SEQEN_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = RNGSEL0_GPIO_PIN;
    GPIO_Init(RNGSEL0_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = RNGSEL1_GPIO_PIN;
    GPIO_Init(RNGSEL1_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SER_GPIO_PIN;
    GPIO_Init(SER_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D0_GPIO_PIN;
    GPIO_Init(D0_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D1_GPIO_PIN;
    GPIO_Init(D1_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D2_GPIO_PIN;
    GPIO_Init(D2_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D3_GPIO_PIN;
    GPIO_Init(D3_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D4_GPIO_PIN;
    GPIO_Init(D4_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D5_GPIO_PIN;
    GPIO_Init(D5_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D6_GPIO_PIN;
    GPIO_Init(D6_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D7_GPIO_PIN;
    GPIO_Init(D7_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D8_GPIO_PIN;
    GPIO_Init(D8_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D9_GPIO_PIN;
    GPIO_Init(D9_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = D10_GPIO_PIN;
    GPIO_Init(D10_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = OS0_GPIO_PIN;
    GPIO_Init(OS0_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = OS1_GPIO_PIN;
    GPIO_Init(OS1_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = OS2_GPIO_PIN;
    GPIO_Init(OS2_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = WR_GPIO_PIN;
    GPIO_Init(WR_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SCK_GPIO_PIN;
    GPIO_Init(SCK_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = CS_GPIO_PIN;
    GPIO_Init(CS_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = CH0_GPIO_PIN;
    GPIO_Init(CH0_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = CH1_GPIO_PIN;
    GPIO_Init(CH1_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = CH2_GPIO_PIN;
    GPIO_Init(CH2_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = CONVST_GPIO_PIN;
    GPIO_Init(CONVST_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; /* 输入 */

    /* 数据输入引脚配置 */
    GPIO_InitStruct.GPIO_Pin = SDOB_GPIO_PIN;
    GPIO_Init(SDOB_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SDOA_GPIO_PIN;
    GPIO_Init(SDOA_GPIO_PORT, &GPIO_InitStruct);

    /* BUSY引脚配置 */
    GPIO_InitStruct.GPIO_Pin = BUSY_GPIO_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; /* 浮空 */
    GPIO_Init(BUSY_GPIO_PORT, &GPIO_InitStruct);

    AD7616_State_Init();

    delay_ms(1);
    AD7616_Reset();
    delay_ms(10);

    AD7616_Write_Data(0x8400);            /* 配置寄存器复位 */
    AD7616_Write_Data(0x8600);            /* 通道寄存器复位 */
    AD7616_Write_Data(0x8800 | Range_5V); /* ±5V输入 */
    AD7616_Write_Data(0x8A00 | Range_5V); /* ±5V输入 */
    AD7616_Write_Data(0x8C00 | Range_5V); /* ±5V输入 */
    AD7616_Write_Data(0x8E00 | Range_5V); /* ±5V输入 */
}

/**
 * @brief 引脚配置初始化
 */
void AD7616_State_Init(void)
{
    SEQEN = 0;

    RNGSEL0 = 0;
    RNGSEL1 = 0; /* 软件模式 */

    SER = 1; /* 串行 */

    D0 = 0;
    D1 = 0;
    D2 = 0;
    D3 = 0;
    D4 = 1; /* 输出在SDOA与SDOB上 */
    D5 = 0; /* 无CRC校验字 */
    D6 = 0;
    D7 = 0;
    D8 = 0;
    D9 = 0;

    OS0 = 0;
    OS1 = 0;
    OS2 = 0;
    WR = 0;

    SCK = 1;
    CS = 1;

    CH0 = 0;
    CH1 = 0;
    CH2 = 0;
    CONVST = 0;
}

/**
 * @brief AD7616完全复位
 */
void AD7616_Reset(void)
{
    RESET = 1;
    delay_us(1);
    RESET = 0;
    delay_us(2);
    RESET = 1;
}

/**
 * @brief 启动转换
 */
void AD7616_Start_Convst(void)
{
    CONVST = 1;
    CONVST = 1;
    delay_us(1);
    CONVST = 0;
    CONVST = 0;
    delay_us(1);
}

/**
 * @brief 读取一个通道的数据
 *
 * @param CHA_Data 通道A的数据
 * @param CHB_Data 通道B的数据
 */
void AD7616_SPI_Read(int16_t *CHA_Data, int16_t *CHB_Data)
{
    uint16_t rxdata_a = 0;
    uint16_t rxdata_b = 0;

    CS = 0;

    for (int i = 0; i < 16; i++)
    {
        rxdata_a <<= 1;
        rxdata_b <<= 1;

        SCK = 0;

        if (SDOA == SET)
        {
            rxdata_a++;
        }
        if (SDOB == SET)
        {
            rxdata_b++;
        }

        SCK = 1;
    }

    CS = 1;
    *CHA_Data = rxdata_a;
    *CHB_Data = rxdata_b;
}

/**
 * @brief 读取通道数据
 */
void AD7616_Read_Data(void)
{
    uint8_t i = 1;

    for ( i = 1; i < 9; i++)
    {
        AD7616_Write_Data(0x8600 | ((i & 0x07) << 4) | (i & 0x07));
        AD7616_Start_Convst();

        while (BUSY == 1)
        {
            delay_us(1);
        }

        AD7616_SPI_Read(&adc_data_a[i-1], &adc_data_b[i-1]);
    }

}

/**
 * @brief 输入范围为5V的转换
 */
void AD7616_Mask(void)
{
    for (int i = 0; i < CH_NUM; i++)
    {
        s_volt_a[i] = (float)((adc_data_a[i] * 5000.0) / 32767);
        s_volt_b[i] = (float)((adc_data_b[i] * 5000.0) / 32767);
    }
}

/**
 * @brief 向寄存器写入数据
 *
 * @param txdata 写入格式：最高位为1，而后6位地址，最后9位数据
 */
void AD7616_Write_Data(uint16_t txdata)
{
    CS = 0;

    for (int i = 0; i < 16; i++)
    {
        if (txdata & 0x8000)
        {
            D10 = 1;
        }
        else
        {
            D10 = 0;
        }
        SCK = 0;
        txdata <<= 1;
        SCK = 1;
    }

    CS = 1;

    D10 = 0;
}
