/* iKPYT

 Эта маленькая программка управляет 4-мя последовательно соединёнными SK6805 RGB LED
 Она мне понадобилась чтобы проверить купленные на AliExpress Светодиоды

 Если кому надо - дарю.

 */

#include "stm32f4xx.h"

RCC_ClocksTypeDef Clock;


void Delay(uint32_t Count) {
  while(Count--) {
  }
}
void High(void)
{
    GPIOD->BSRRL = GPIO_Pin_4;
    Delay(9L);
    GPIOD->BSRRH = GPIO_Pin_4;
    Delay(5L);
}
void Low(void)
{
    GPIOD->BSRRL = GPIO_Pin_4;
    Delay(4L);
    GPIOD->BSRRH = GPIO_Pin_4;
    Delay(14L);
}
int main(void) 
{	
  uint8_t i;

  RCC_GetClocksFreq(&Clock); 

  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);   


  u8 Green[4] = {0x1,0xFF,0x1,0x1};
  u8 Red[4]   = {0xFF,0x1,0x1,0x1};
  u8 Blue[4]  = {0x1,0x1,0xFF,0xF};
  uint32_t color[4];
  while(1) {

    GPIOD->BSRRH = GPIO_Pin_4;
    Delay(25*80L);
  
    color[0] = (Green[0]<<16)+(Red[0]<<8)+Blue[0];
    color[1] = (Green[1]<<16)+(Red[1]<<8)+Blue[1];
    color[2] = (Green[2]<<16)+(Red[2]<<8)+Blue[2];
    color[3] = (Green[3]<<16)+(Red[3]<<8)+Blue[3];
    
    for(int m=1<<23; m; m>>=1)
    {
      (color[0]&m)? High() : Low() ; 
    }
    for(int m=1<<23; m; m>>=1)
    {
      (color[1]&m)? High() : Low() ; 
    }
    for(int m=1<<23; m; m>>=1)
    {
      (color[2]&m)? High() : Low() ; 
    }
    for(int m=1<<23; m; m>>=1)
    {
      (color[3]&m)? High() : Low() ; 
    }

    GPIOD->BSRRL = GPIO_Pin_4;

    if( Green[0]) ++Green[0];  else
    if( Red[0] )   ++Red[0];    else
    if( Blue[0] ) ++Blue[0];    else
    {
      Green[0] = 0x1;
      Red[0]   = 0x1;
      Blue[0]  = 0x3f;
    }
    if( Red[1] )   ++Red[1];    else
    if( Blue[1] ) ++Blue[1];    else
    if( Green[1]) ++Green[1];  else
    {
    
      Green[1] = 0x31;
      Red[1]   = 0x1;
      Blue[1]  = 0x1;
    }
    
    if( Red[2] )   ++Red[2];    else
    if( Green[2]) ++Green[2];  else
    if( Blue[2] ) ++Blue[2];    else
    {
      Green[2] = 0x1;
      Red[2]   = 0x1;
      Blue[2]  = 0x31;
    }
    if( Blue[3] ) ++Blue[3];    else
    if( Green[3]) ++Green[3];  else
    if( Red[3] )   ++Red[3];    else
    {
      Green[3] = 0x1;
      Red[3]   = 0x31;
      Blue[3]  = 0x1;
    }    
    Delay(25*1000*3L);
  }

}


