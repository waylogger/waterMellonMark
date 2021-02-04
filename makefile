
# -------------------------------------------------------------------------------------------------
GTK_OPT=`pkg-config gtkmm-3.0 --cflags --libs`
TMP=./tmp
SRC=./src
# -------------------------------------------------------------------------------------------------
COMP=g++
COMP_OPT=-std=c++17 -Wall
NO_LINK=-c
OUT=-o index
# -------------------------------------------------------------------------------------------------
OBJS=$(TMP)/index.o $(TMP)/Matilda_window.o
DEPS=index matilda
DEV_DEPS=done
# -------------------------------------------------------------------------------------------------
dev: $(DEV_DEPS)

done: $(DEPS)
	$(COMP) $(COMP_OPT) $(OBJS) $(OUT) $(GTK_OPT)
index:
	$(COMP) $(COMP_OPT) $(NO_LINK) $(GTK_OPT) $(SRC)/index.cpp -o $(TMP)/index.o
matilda:
	$(COMP) $(COMP_OPT) $(NO_LINK) $(GTK_OPT) $(SRC)/Matilda_window.cpp -o $(TMP)/Matilda_window.o
	
