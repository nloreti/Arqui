/*********************************************
c_ihandlers.c

*********************************************/

extern unsigned long int timertick;
int tickpos=640;

/* Handlers de interrupcion */
void
int_20(void)
{
	//puts("s");
	timertick+=1;
}


void
int_21(int scancode)
{
//		char *video = (char *) 0xb8000;
//    video[tickpos+=2]='B';
	
	
/* Se encola el scancode recibido en un buffer interno de scancodes. */
	enqueueKbBuffer((char)scancode);
}

void
int_32(void){
	puts("b");
}

void
int_0(void)
{
	printf("Zero divide error\n");
}

void
int_01(void)
{
	printf("Debug exception\n");
}

void
int_02(void)
{
	printf("Nonmascarable Interrupt\n");
}

void
int_03(void)
{
	printf("Breakpoint\n");
}

void
int_04(void)
{
	printf("Overflow\n");
}

void
int_05(void)
{
	printf("Bounds check\n");
}

void
int_06(void)
{
	printf("Invalid opcode\n");
}

void
int_07(void)
{
	printf("Coprocessor not available\n");
}

void
int_08(void)
{
	printf("Double fault\n");
}

void
int_09(void)
{
	printf("Overflow coprocessor segment\n");
}

void
int_10(void)
{
	printf("Invalid TSS\n");
}

void
int_11(void)
{
	printf("Segment not present\n");
}

void
int_12(void)
{
	printf("Stack exception\n");
}

void
int_13(void)
{
	printf("Segmentation fault - General protection\n");
}

void
int_14(void)
{
	printf("Page fault\n");
}

void
int_16(void)
{
	printf("Coprocessor error\n");
}

