#include <reg52.h>
#include "usart.h"
#include "iic.h"  
/*
Ӳ���ӷ���
GY-56---c51
1��GY-56_RX---c51_TX,c51��λ������A5 65 01 0B ��ģ��
2��c51_TX---FT232,STM32�������ϴ�����λ��
3��GY-56_TX---c51_RX������ģ������
���˵��:
�ó�����ô��ڷ�ʽ��ȡģ�����ݣ�������9600

ע���жϺ���λ��stc_it.c
��ϵ��ʽ��
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
typedef  struct
{
	uint16_t distance;
	uint8_t   mode;
	uint8_t   temp;
}sensor;
void send_com(u8 function,u8 valve)
{
	u8 bytes[3]={0};
	bytes[0]=0xa5;
	bytes[1]=function;//�����ֽ�
    bytes[2]=valve;	 //ָ��ֵ
	USART_Send(bytes,4);//����֡ͷ�������ֽڡ�У���
}
void delay(uint16_t x)
{
    while(x--) ;

}
int main(void)
{

    u8 sum=0,i=0;

	sensor GY56;
	Usart_Int(9600);
	delay(1000);
	send_com(0x65,1);//���Ͷ���λ��ָ��
 	while(1)
	{
		if(Receive_ok)//���ڽ������
		{
			for(sum=0,i=0;i<(re_Buf_Data[3]+4);i++)//rgb_data[3]=3
			sum+=re_Buf_Data[i];
			if(sum==re_Buf_Data[i])//У����ж�
			{
				GY56.distance=re_Buf_Data[4]<<8|re_Buf_Data[5];
				GY56.mode=re_Buf_Data[6];
				GY56.temp=re_Buf_Data[7];

				send_3out(&re_Buf_Data[4],4,0x15);//�ϴ�����λ��
			}
			Receive_ok=0;//����������ϱ�־
		}	
	}
}
