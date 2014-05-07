JAVAC	= javac
JAVA	= java

default:: TreeCalculation.class

clean::
	-rm -f *.class speedup.dat speedup.png

# kleines Testbeispiel
run:: TreeCalculation.class
	$(JAVA) TreeCalculation 14 1 4

TreeCalculation.class: TreeCalculation.java
	$(JAVAC) $<

