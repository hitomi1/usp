.SUFFIXES: .java .class

.java.class:
	javac $*.java

all: Board.class Main.class

run: all
	java Main

clean:
	rm -f *.class
