SOURCES=$(shell cat makefile_sources)
CIBLE=displayAVL.exe indexation.exe anagrammes.exe

all: prog1 prog2 prog3

prog1 : $(SOURCES) ex1.c
	@echo -n "Production de l'exécutable \"displayAVL.exe\"\n"
	@gcc -Wall $(SOURCES) ex1.c -o displayAVL.exe
prog2 : $(SOURCES) ex2.c
	@echo -n "Production de l'exécutable \"indexation.exe\"\n"
	@gcc -Wall $(SOURCES) ex2.c -o indexation.exe -lm
prog3 : $(SOURCES) ex3.c
	@echo -n "Production de l'exécutable \"anagrammes.exe\"\n"
	@gcc -Wall $(SOURCES) ex3.c -o anagrammes.exe

clean: 
	@echo "Nettoyage de $(CIBLE)"
	@rm -rf $(CIBLE)
