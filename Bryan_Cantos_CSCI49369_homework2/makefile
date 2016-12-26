

#FLAGS
C++FLAG = -g -std=c++0x

MATH_LIBS = -lm

EXEC_DIR=.


.cpp.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


#First Program (ListTest)

Cpp_OBJ_0=Image.o Line.o DisjSets.o p1.o
PROGRAM_NAME_0=p1
$(PROGRAM_NAME_0): $(Cpp_OBJ_0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_0) $(INCLUDES) $(LIBS_ALL)

Cpp_OBJ_1=Image.o Line.o DisjSets.o p2.o
PROGRAM_NAME_1=p2
$(PROGRAM_NAME_1): $(Cpp_OBJ_1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_1) $(INCLUDES) $(LIBS_ALL)

Cpp_OBJ_2=Image.o Line.o DisjSets.o p3.o
PROGRAM_NAME_2=p3
$(PROGRAM_NAME_2): $(Cpp_OBJ_2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ_2) $(INCLUDES) $(LIBS_ALL)


all: 
	make $(PROGRAM_NAME_0) 
	make $(PROGRAM_NAME_1) 
	make $(PROGRAM_NAME_2) 


clean:
	(rm -f *.o;)

(:
