.SUFFIXES: .java .class

.java.class:
	javac $*.java

all: *.class

run: all
	java Main

clean:
	rm -f *.class
