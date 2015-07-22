CPP=g++
CFLAGS=-I
OBJ = grid.o RL.o

%.o: %.cpp %.h
	$(CPP) -c $< 
%.o: %.cpp
	$(CPP) -c $<
RL: $(OBJ)
	$(CPP) -o a.out $^
clean:	
	rm *.o a.out *~ 
