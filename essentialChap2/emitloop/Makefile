LLVM_CONFIG?=llvm-config

ifndef VERBOSE
QUIET:=@
endif

SRC_DIR?=$(PWD)
LDFLAGS+=$(shell $(LLVM_CONFIG) --ldflags)
COMMON_FLAGS=-Wall -Wextra
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags) -fno-rtti -D_GLIBCXX_USE_CXX11_ABI=0
CPPFLAGS+=$(shell $(LLVM_CONFIG) --cppflags) -I$(SRC_DIR)
LLVMLIBS=$(shell $(LLVM_CONFIG) --libs bitreader support)
SYSTEMLIBS=$(shell $(LLVM_CONFIG) --system-libs)

APP=emitloop
APP_OBJECTS=emitloop.o

default: $(APP)

%.o: $(SRC_DIR)/%.cppflags
	@echo Compiling $*.cpp
	$(QUIET)$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(APP) : $(APP_OBJECTS)
	@echo Linking $@
	$(QUIET)$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $^ $(LLVMLIBS) -pthread -ldl -ltinfo $(SYSTEMLIBS) 

clean::
	$(QUIET)rm -f $(APP) $(APP_OBJECTS)