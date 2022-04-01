PROG:=Main.class
SRCS:=Main.java

JAVAC:=javac

all: $(PROG)

$(PROG): $(SRCS)
	$(JAVAC) $<

.PHONY: edit go

go: $(PROG)
	java $(basename $(PROG))

edit:
	@geany -s -i *.java &

clean:
	@rm -f *.class core tags

Main.class: Main.java Expression.java Term.java SymbolTab.java
