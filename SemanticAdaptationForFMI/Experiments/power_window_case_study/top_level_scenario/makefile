CC=gcc
CFLAGS=-IC:fmi2 -O0 -g3 -Wall -c -fmessage-length=0
DEPS = $(wildcard *.h)
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
EXE = PowerWindowScenario.exe

exe: $(OBJECTS)
	$(CC) -o Debug\$(EXE) $(OBJECTS) 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f Debug\$(EXE) $(OBJECTS)
