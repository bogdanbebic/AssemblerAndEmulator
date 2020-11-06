BUILD_DIR = build
INCLUDE_DIR = include
SRC_DIR = source
PROGRAM = assembler

SRC_FILES = 
SRC_FILES += $(wildcard $(SRC_DIR)/*.cpp)

OBJ_FILES = 
OBJ_FILES += $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_FILES:.cpp=.o)))

CXX = g++
LD = g++

CXXFLAGS = 
CXXFLAGS += -I$(INCLUDE_DIR)
CXXFLAGS += -MMD -MP
CXXFLAGS += -Wall

.PHONY : all
all : $(BUILD_DIR)/$(PROGRAM) Makefile
	@echo $(PROGRAM) build successful

$(BUILD_DIR)/$(PROGRAM) : $(OBJ_FILES) Makefile
	$(LD) $(LDFLAGS) -o $(@) $(OBJ_FILES)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp Makefile | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(@) $(<) 

$(BUILD_DIR) :
	mkdir $(BUILD_DIR)

.PHONY : clean
clean :
	rm -rf $(BUILD_DIR)
