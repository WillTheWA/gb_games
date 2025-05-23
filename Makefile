CC = ../../../bin/lcc

BINS = pomodoro.gb

all: $(BINS)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> compile.bat

# Compile and link pomodoro.c, typeset.c, numset.c into pomodoro.gb
pomodoro.gb: pomodoro.c typeset.c numset.c
	$(CC) -o $@ $^

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi
