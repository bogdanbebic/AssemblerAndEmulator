BUILD_DIR = build
INCLUDE_DIR = include
SRC_DIR = source
TEST_DIR = test

PROGRAM = assembler

TEST_PROGRAM = test_assembler

SRC_FILES = 
SRC_FILES += $(wildcard $(SRC_DIR)/*.cpp)

TEST_SRC_FILES = 
TEST_SRC_FILES += $(filter-out $(SRC_DIR)/main_as.cpp, $(SRC_FILES))
TEST_SRC_FILES += $(wildcard $(TEST_DIR)/*.cpp)

OBJ_FILES = 
OBJ_FILES += $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_FILES:.cpp=.o)))

TEST_OBJ_FILES = 
TEST_OBJ_FILES += $(addprefix $(BUILD_DIR)/, $(notdir $(TEST_SRC_FILES:.cpp=.o)))

CXX = g++
LD = g++

CXXFLAGS = 
CXXFLAGS += -I$(INCLUDE_DIR)
CXXFLAGS += -MMD -MP
CXXFLAGS += -Wall

.PHONY : all
all : $(BUILD_DIR)/$(PROGRAM) Makefile

.PHONY : test
test : $(BUILD_DIR)/$(TEST_PROGRAM) Makefile

$(BUILD_DIR)/$(TEST_PROGRAM) : $(TEST_OBJ_FILES) Makefile
	$(LD) $(LDFLAGS) -o $(@) $(TEST_OBJ_FILES)

$(BUILD_DIR)/$(PROGRAM) : $(OBJ_FILES) Makefile
	$(LD) $(LDFLAGS) -o $(@) $(OBJ_FILES)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp Makefile | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(@) $(<)

$(BUILD_DIR)/%.o : $(TEST_DIR)/%.cpp Makefile | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(@) $(<)

$(BUILD_DIR) :
	mkdir $(BUILD_DIR)

.PHONY : clean
clean :
	rm -rf $(BUILD_DIR)

-include $(wildcard $(BUILD_DIR)/*.d)
