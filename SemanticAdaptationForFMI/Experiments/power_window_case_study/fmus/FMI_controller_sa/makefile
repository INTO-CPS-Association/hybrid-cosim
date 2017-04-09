CC=gcc
CFLAGS=-IC:fmi2 -O0 -g3 -Wall -c -fmessage-length=0
DEPS = $(wildcard *.h)
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
LIB = libFMI_controller_sa.dll

lib: $(OBJECTS)
	$(CC) -shared -o Debug\$(LIB) $(OBJECTS) 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f Debug\$(LIB) $(OBJECTS)
