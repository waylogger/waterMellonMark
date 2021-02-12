
# -------------------------------------------------------------------------------------------------
GTK_OPT=`pkg-config gtkmm-3.0 --cflags --libs`
TMP=./tmp
SRC=./src
# -------------------------------------------------------------------------------------------------
COMP=g++
COMP_OPT=-std=c++17 -Wall
NO_LINK=-c
OUT=-o main
# -------------------------------------------------------------------------------------------------
OBJS=$(TMP)/main.o $(TMP)/Matilda_window.o
DEPS=main
DEV_DEPS=done
# -------------------------------------------------------------------------------------------------

done: $(DEPS)
	$(COMP) $(COMP_OPT) $(OBJS) $(OUT) $(GTK_OPT)

main:	matilda
	$(COMP) $(COMP_OPT) $(NO_LINK) $(GTK_OPT) $(SRC)/main.cpp -o $(TMP)/main.o

matilda:
	$(COMP) $(COMP_OPT) $(NO_LINK) $(GTK_OPT) $(SRC)/Matilda_window.cpp -o $(TMP)/Matilda_window.o
	
