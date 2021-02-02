# 02.02.2021
# wlr_986
# matilda_makefile
# -------------------------------------------------------------------------------------------------
#compiling:
COMP_OPT=-Wall
STD=-std=c++17
COMP=g++
OUT=-o index

FINISH_OBJ=./tmp/main.o ./tmp/Window.o
# -------------------------------------------------------------------------------------------------
# linking
SFML_LIBS=-lsfml-graphics -lsfml-window -lsfml-system
# -------------------------------------------------------------------------------------------------
FINISH_DEPTS=main window
# -------------------------------------------------------------------------------------------------
# -------------------------------------------------------------------------------------------------

finish: $(FINISH_DEPTS)
	$(COMP) $(FINISH_OBJ) $(COMP_OPT) $(STD) $(SFML_LIBS) $(OUT)
main:
	$(COMP) ./src/index.cpp -c -o ./tmp/main.o $(STD)
window:
	$(COMP) ./src/Window/Window.cpp -c -o ./tmp/Window.o $(STD)

