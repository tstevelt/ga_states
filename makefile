
PROG=ga_states

ifeq ($(LDFLAGS),"-m32")
LIB = ga_states.a
XLIB = /usr/local/lib/weblib.a /usr/local/lib/shslib.a -lm
else
LIB = ga_states_64.a
XLIB = /usr/local/lib64/weblib.a /usr/local/lib64/shslib.a -lm
endif

DEF = /usr/local/include

WEBDIR1 = /var/www/vhosts/stevelt/html
PRG1 = $(WEBDIR1)/ga_states.cgi

WEBDIR2 = /var/www/vhosts/silverhammersoftware/html
PRG2 = $(WEBDIR2)/ga_states.cgi

FILES= \
	$(LIB)(ga_states.o) \
	$(LIB)(getargs.o)	\
	$(LIB)(GetInput.o)	\
	$(LIB)(initgrid.o)	\
	$(LIB)(initial.o)	\
	$(LIB)(obj_func.o)	\
	$(LIB)(random.o)	\
	$(LIB)(generation.o) \
	$(LIB)(crossover.o) \
	$(LIB)(select_fit.o) \
	$(LIB)(sortfuncs.o) \
	$(LIB)(report.o)	\
	$(LIB)(MakeMap.o)

STAMP: $(PRG1) $(PRG2)

$(PRG1) : $(LIB)
	echo "Making $(PRG1)"
	gcc $(LDFLAGS) -o $(PRG1) $(LIB) $(XLIB)

$(PRG2) : $(LIB)
	echo "Making $(PRG2)"
	gcc $(LDFLAGS) -o $(PRG2) $(LIB) $(XLIB)

$(LIB) : $(FILES)

$(FILES): ga_states.h $(DEF)/shslib.h

html:
	cp -pv MapTest1.html $(WEBDIR1)/MapTest1.html

.SILENT:

all:
	rm -f $(LIB)
	make 
	make html

