JFLAGS = -g
JCC = javac

default: all

all: ProducerConsumer.class

ProducerConsumer.class: ProducerConsumer.java
	$(JCC) $(JFLAGS) ProducerConsumer.java
	jar cf ProducerConsumer ProducerConsumer.class
clean:
	$(RM) *.class ProducerConsumer
package:
	zip Harris-Elijah-HW4.zip ProducerConsumer.java Makefile README.txt


