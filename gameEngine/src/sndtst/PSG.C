#include <osbind.h>

int main()
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
	volatile char *PSG_reg_select_b = 0xFF8800;
	volatile char *PSG_reg_write_b = 0xFF8802;
	register char thing;
	unsigned long i = 0;

	long old_ssp = Super(0);
	
	thing = *PSG_reg_select;
	*PSG_reg_select_b = 2;
	thing = *PSG_reg_select;
	*PSG_reg_write_b = 200;
	
	*PSG_reg_select_b = 3;
	*PSG_reg_write_b = 0;
	
	*PSG_reg_select_b = 7;
	*PSG_reg_write_b = 0x7D;
	
	*PSG_reg_select_b = 9;
	*PSG_reg_write_b = 11;
	Cconws("here\r\n\0");
	while(i < 1000000)
		i++;
	Cconws("here\r\n\0");

	*PSG_reg_select = 0;		/* set channel A fine tune = 248 */
	*PSG_reg_write  = 250;

	*PSG_reg_select = 1;		/* set channel A coarse tune = 0 */
	*PSG_reg_write  = 0;

	*PSG_reg_select = 7;		/* enable channel A on mixer */
	*PSG_reg_write  = 0x3E;

	*PSG_reg_select = 8;		/* set channel A volume = 11 */
	*PSG_reg_write  = 11;

	while (!Cconis())/* tone now playing, await key */
		;

		
	*PSG_reg_select = 8;		/* set channel A volume = 0 */
	*PSG_reg_write  = 0;
	
	*PSG_reg_select_b = 9;
	*PSG_reg_write_b = 0;

	
	Cnecin();
	Super(old_ssp);
	return 0;
}
