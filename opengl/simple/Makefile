COMP	:= g++ -g -I.. -I/d/MSYS64/mingw64/include/mesa/GL

TUT01_OBJ := tut01.o simplegl.o glew.o
tut01: $(TUT01_OBJ)
	$(COMP) $(OBJ) -o simple -L . -L x86_64-w64-mingw32/lib -lglfw3 -lopengl

SIMPLE_OBJ := simple.o simplegl.o texture.o glew.o

simple: $(SIMPLE_OBJ)
	$(COMP) $(SIMPLE_OBJ) -o simple -L . -L x86_64-w64-mingw32/lib -lglfw3 -lopengl32 -lgdi32

simple.o: simple.cc simplegl.hh
	$(COMP) -c simple.cc

simplegl.o: simplegl.cc simplegl.hh
	$(COMP) -c simplegl.cc

texture.o: texture.cpp simplegl.hh
	$(COMP) -c $<

glew.o: glew.c
	$(COMP) -c glew.c

clean:
	rm *.o
