#Documentation variables
DOXYGEN=doxygen
DOXYGEN_CONFIG_FILE=Doxyfile
DOC_DIR=doc

#Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LDFLAGS=-lm
GTKFLAGS= `pkg-config --cflags --libs gtk+-2.0`
LD=gcc
TAR_NAME=mastermind_10.tar.gz

#Files
EXEC=mastermind
OBJECTS=source/main_mastermind.o source/controller_mastermind.o source/model_mastermind.o source/view_mastermind.o
FILES=Doxyfile Makefile Images

#Rules
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS) $(GTKFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(GTKFLAGS)

run: $(EXEC)
	./$(EXEC)

doc:
	doxygen $(DOXYGEN_CONFIG_FILE)

rapport: rapport/rapport.tex
	pdflatex rapport/rapport.tex

clean:
	rm -rf */*.o $(EXEC) $(DOC_DIR) $(TAR_NAME)

archive: doc rapport
	tar -czf $(TAR_NAME) source rapport $(FILES) $(DOC_DIR)
