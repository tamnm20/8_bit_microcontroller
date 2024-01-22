#include<8051.h>

void Delay_ms_tim0(unsigned int t)
{
	do{
		TL0 = 0x18;	// 
		TH0 = 0xFC;
		TR0 = 1;	// CHO PHEP TIM0 HOAT DONG
		while(!TF0);
		TR0 = 0; 	// tim 0 ngung dem
		TF0 = 0;	// xoa co tran
		t--;
	}while(t>0);
	
}

void uart_init(void){
	SM0 = 0; SM1 = 1; 	//Chon UART mode1
	TMOD &= 0x0F;		//xoa cac bit tren thanh ghi TMOD cua T1
	TMOD = 0x20;      	//Chon Timer1 8bit auto reload
	TH1 = 0xF3;			// 9600 baud
	TR1 = 1;         	//Timer 1 bat dau chay
	TI = 1; 			//san sang gui du lieu
	REN = 1;			//Cho phep nhan du lieu
}

void timer0_init(void){
	TMOD &= 0xF0;	//xoa cac bit tren thanh ghi TMOD cua T0
	TMOD |= 0x01;	//chon Timer0 16bit
}

void UART_SendByte(char data1) {
	if (data1 == '\n')
	{
		while (!TI);
		TI = 0;
		SBUF = 0x0D;
	}
    // Chờ cho đến khi TX1 Ready
    while (!TI);
    
    // Đặt TI1 về 0 để chuẩn bị cho lần gửi tiếp theo
    TI = 0;
    
    // Ghi dữ liệu vào thanh ghi truyền (SBUF1)
    SBUF = data1;
}

void UART_SendString (char *str)
{
	while (*str) 
	{
		UART_SendByte(*str++);
	}
}

char Uart_Data_Ready(void){
	return RI;
}

char Uart_Read(void){
	RI = 0;
	return SBUF;
}

char datatosend [] = "hello world!\n";

void main(){
	//P1 = 0xFF;
	uart_init();
	timer0_init();
	char a = 0;
	//int i=0;
	UART_SendString(datatosend);
    while (1)
    {
        /* code */
        //P1 = ~P1;
		//P1=1;
		for(a = 'a';a<='z';a++){
			UART_SendByte(a);
		}
		Delay_ms_tim0(1);
		// if(Uart_Data_Ready()==1){
		// 	P1 = Uart_Read();
		// 	// a = Uart_Read();
		// 	// UART_SendByte(a);
		// }
		// i++;
		// UART_SendByte(i);
		// Delay_ms_tim0(10);
		// UART_SendByte(0x4E);
		// Delay_ms_tim0(1000);
    }  
}