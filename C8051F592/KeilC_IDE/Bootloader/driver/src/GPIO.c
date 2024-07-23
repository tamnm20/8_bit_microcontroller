
void PORT_Init()
{
	U8 SFRPAGE_save = SFRPAGE;
	SFRPAGE = CONFIG_PAGE;

	P1MDIN |= 0xFF;                    // Enable LED as a push-pull output
	P1SKIP  |= 0xFF;                    // Skip the LED pin on the crossbar

	P2MDOUT |= 0x07;                    
	P2SKIP  |= 0x07;                   


	XBR2     = 0x40;                    // Enable crossbar and weak pull-ups

	SFRPAGE = SFRPAGE_save;
}

