include ../var.mk

LIB_DIR = ../lib

all: install

install: libparam.so
	if [ ! -d "$$LIB_DIR" ]; then mkdir -p $(LIB_DIR); fi; mv $^ $(LIB_DIR);

libparam.so: param.o
	$(CXX) -o $@ $^ -shared

param.o: param.cc
	$(CXX) -o $@ $< -c -fPIC $(OPT_FLAGS)

clean:
	$(RM) *.o *.so $(LIB_DIR)/*.so


