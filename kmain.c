/******************************************************************************
 * kmain.c
 * The first entry function after boot.
 * ***************************************************************************/
void cls(void);
int main()
{
	char* video = (char *) 0xc00b8000;
	
	cls();
	char* string = "Booting Simple OS...";
	int i = 0;
	for (i = 0; i < 20; i++) {
		video[2*i] = string[i];
		video[2*i + 1] = 0x7;
	}

	return 0;
}

void
cls(void) {
	char *video = (char *) 0xc00b8000;
	int i;
	for (i = 0; i < 80*24; i++) {
		video[2*i] = ' ';
		video[2*i + 1] = 0x7;
	}
}
