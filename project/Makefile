THINGS  =

CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

CC		= msp430-elf-gcc
AS		= msp430-elf-as

all: main.elf

main.elf: ${THINGS} wakedemo.o p2interruptHandler.o led.o switches.o buzzer.o stateMachine.o ../lib/libTimer.a 
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: main.elf 
	msp430loader.sh main.elf

clean:
	rm -f *.o *.elf
