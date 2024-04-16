#Documentation variables
DOXYGEN=doxygen
DOXYGEN_CONFIG_FILE=Doxyfile
DOC_DIR=doc

#Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
GTKFLAGS= `pkg-config --cflags --libs gtk+-2.0`
LD=gcc
TAR_NAME=mastermind_10.tar.gz

#Files
EXEC=mastermind
OBJECTS=source/main.mastermind.o source/controller.mastermind.o source/modal.mastermind.o source/view.mastermind.o
FILES=Doxyfile Makefile Images

#Rules
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS) $(GTKFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(GTKFLAGS)

doc:
	doxygen $(DOXYGEN_CONFIG_FILE)

clean:
	rm -rf */*.o $(EXEC) $(DOC_DIR) $(TAR_NAME)

archive:
	tar -czf $(TAR_NAME) *.c *.h $(FILES)
