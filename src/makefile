DIR=bin

all: linkedlist

linkedlist: $(DIR)
	gcc LinkedList.c Person.c Main.c -o ../$(DIR)/App.exe

$(DIR):
	if ! test -d ../$(DIR); then	\
		mkdir ../$(DIR);	\
	fi

clean: $(DIR)
	rm ../$(DIR)/App.exe
