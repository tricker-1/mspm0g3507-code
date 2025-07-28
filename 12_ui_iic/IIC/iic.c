#include "iic.h"
#include "ti_msp_dl_config.h"


#define SDA_OUT()   {                                                \
                        DL_GPIO_initDigitalOutput(I2C_SDA_IOMUX);    \
                        DL_GPIO_setPins(I2C_PORT, I2C_SDA_PIN);      \
                        DL_GPIO_enableOutput(I2C_PORT, I2C_SDA_PIN); \
                    }

#define SDA_IN()    { DL_GPIO_initDigitalInput(I2C_SDA_IOMUX); }

#define SDA_GET()   ( ( ( DL_GPIO_readPins(I2C_PORT,I2C_SDA_PIN) & I2C_SDA_PIN ) > 0 ) ? 1 : 0 )

#define SDA(x)      ( (x) ? (DL_GPIO_setPins(I2C_PORT,I2C_SDA_PIN)) : (DL_GPIO_clearPins(I2C_PORT,I2C_SDA_PIN)) )
#define SCL(x)      ( (x) ? (DL_GPIO_setPins(I2C_PORT,I2C_SCL_PIN)) : (DL_GPIO_clearPins(I2C_PORT,I2C_SCL_PIN)) )


void delay_us(unsigned char time)
{
    delay_cycles(80*time);
}

/******************************************************************
 * �� �� �� �ƣ�IIC_Start
 * �� �� ˵ ����IIC��ʼ�ź�
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void IIC_Start(void)
{
        SDA_OUT();
        
        SCL(0);
        SDA(1);
        SCL(1);
        
        delay_us(5);
        
        SDA(0);
        delay_us(5);
        SCL(0);
        delay_us(5);
        
        
}

/******************************************************************
 * �� �� �� �ƣ�IIC_Stop
 * �� �� ˵ ����IICֹͣ�ź�
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void IIC_Stop(void)
{
        SDA_OUT();
        
        SCL(0);
        SDA(0);
        
        SCL(1);
        delay_us(5);
        SDA(1);
        delay_us(5);
        
}

/******************************************************************
 * �� �� �� �ƣ�IIC_Send_Ack
 * �� �� ˵ ������������Ӧ��
 * �� �� �� �Σ�0Ӧ��  1��Ӧ��
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void IIC_Send_Ack(uint8_t ack)
{
        SDA_OUT();
        SCL(0);
        SDA(0);
        delay_us(5);
        if(!ack) SDA(0);
        else         SDA(1);
        SCL(1);
        delay_us(5);
        SCL(0);
        SDA(1);
}

/******************************************************************
 * �� �� �� �ƣ�IIC_Wait_Ack
 * �� �� ˵ �����ȴ��ӻ�Ӧ��
 * �� �� �� �Σ���
 * �� �� �� �أ�1=��Ӧ��   0=��Ӧ��
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
uint8_t IIC_Wait_Ack(void)
{
        char ack = 0;
        unsigned char ack_flag = 10;
        SDA_IN();
    SDA(1);
        delay_us(5);
        SCL(1);
        delay_us(5);
        while( (SDA_GET()==1) && ( ack_flag ) )
        {
                ack_flag--;
                delay_us(5);
        }
        
        if( ack_flag <= 0 )
        {
                IIC_Stop();
                return 1;
        }
        else
        {
                SCL(0);
                SDA_OUT();
        }
        return ack;
}
/******************************************************************
 * �� �� �� �ƣ�IIC_Write
 * �� �� ˵ ����IICдһ���ֽ�
 * �� �� �� �Σ�datд�������
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void IIC_Write(uint8_t data)
{
        int i = 0;
        SDA_OUT();
        SCL(0);//����ʱ�ӿ�ʼ���ݴ���
        
        for( i = 0; i < 8; i++ )
        {
                SDA( (data & 0x80) >> 7 );
                delay_us(2);
        data<<=1;
        delay_us(6); 
                SCL(1);
                delay_us(4);
                SCL(0);
                delay_us(4);
                
        }
}

/******************************************************************
 * �� �� �� �ƣ�IIC_Read
 * �� �� ˵ ����IIC��1���ֽ�
 * �� �� �� �Σ���
 * �� �� �� �أ�������1���ֽ�����
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
uint8_t IIC_Read(void)
{
        unsigned char i,receive=0;
    SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
        {
        SCL(0);
        delay_us(5);
        SCL(1);
        delay_us(5);
        receive<<=1;
        if( SDA_GET() )
        {        
            receive|=1;   
        }
        delay_us(5); 
    }                
  return receive;
}

/******************************************************************
 * �� �� �� �ƣ�SHT20_Read
 * �� �� ˵ ����������ʪ��
 * �� �� �� �Σ�regaddr�Ĵ�����ַ regaddr=0xf3�����¶� =0xf5����ʪ�� 
 * �� �� �� �أ�regaddr=0xf3ʱ�����¶ȣ�regaddr=0xf5ʱ����ʪ��
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
float SHT20_Read(uint8_t regaddr)
{        
    unsigned char data_H = 0;
    unsigned char data_L = 0;
    float temp = 0;
    IIC_Start();
    IIC_Write(0x80|0);

    IIC_Write(regaddr);

       
    do{
    delay_us(10);
    IIC_Start();
    IIC_Write(0x80|1);
    
    }while( IIC_Wait_Ack() == 1 );

    delay_us(20);
    
    data_H = IIC_Read();
    IIC_Send_Ack(0);
    data_L = IIC_Read();
    IIC_Send_Ack(1);
    IIC_Stop();
    
    if( regaddr == 0xf3 )
    {
        temp = ((data_H<<8)|data_L) / 65536.0 * 175.72 - 46.85;
    }
    if( regaddr == 0xf5 )
    {
        temp = ((data_H<<8)|data_L) / 65536.0 * 125.0 - 6;
    }
   return temp;

}

void read_id(void)
{
    uint8_t temp;
    IIC_Start();
    IIC_Write(0x29<<1);
    temp=IIC_Wait_Ack();
    IIC_Write(0x80|0x12);
    temp=IIC_Wait_Ack();
    IIC_Stop();
    IIC_Start();
    IIC_Write((0x29<<1)|1);
    temp=IIC_Wait_Ack();
    temp=IIC_Read();
    IIC_Stop();
}
