#include<8051.h>

void Delay_ms_tim0(unsigned int t)
{
	do{
		TL0 = 0x18;	// 
		TH0 = 0xFC;
		TR0 = 1;	// CHO PHEP TIM0 HOATJ DONG
		while(!TF0);
		TR0 = 0; 	// tim 0 ngung dem
		TF0 = 0;	// xoa co tran
		t--;
	}while(t>0);
	
}

void main(){
	P2 = 0;
	TMOD &= 0xF0;	//xoa cac bit tren thanh ghi TMOD cua T0
	TMOD |= 0x01;	//chon mode 1 cho tim0
    while (1)
    {
        /* code */
        P2 = ~P2;
		Delay_ms_tim0(100);
    }
    
}