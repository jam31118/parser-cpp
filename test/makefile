include ../var.mk

SRC_DIR = ../src
LIB_DIR = ../lib
PARAM_LIB_FLAGS = '-Wl,-rpath,$$ORIGIN/$(LIB_DIR)' -L$(LIB_DIR) -lparam 

all: parse

parse: parse.cc libparam.so
	$(CXX) -o $@ $< $(OPT_FLAGS) $(PARAM_LIB_FLAGS)

libparam.so:
	$(MAKE) -C $(SRC_DIR)

clean:
	$(RM) parse

