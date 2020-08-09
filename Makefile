ASSEMBLER=./Code/Assembler/output/assembler
TESTS_OUTPUT_DIR=./Code/Assembler/output
TESTS_DIR=./tests

all: copy_to_code_dir
	g++ -Wall -v -I./Code/Assembler/include/ -o ./Code/Assembler/output/assembler ./Code/Assembler/src/*

copy_to_code_dir:
	cp ./VisualStudio/Assembler/Assembler/*.h ./Code/Assembler/include/
	cp ./VisualStudio/Assembler/Assembler/*.cpp ./Code/Assembler/src/

clean_code_dir: clean_code_include_dir clean_code_src_dir clean_code_output_dir

clean_code_include_dir:
	rm ./Code/Assembler/include/*.h || true

clean_code_src_dir:
	rm ./Code/Assembler/src/*.cpp || true

clean_code_output_dir:
	rm ./Code/Assembler/output/* || true

assembly-tests: run_test run_test_byte run_test_end run_test_extern run_test_global run_test_global run_test_global_before run_test_labels run_test_section run_test_skip run_test_word
	

run_test:
	$(ASSEMBLER) -o $(TESTS_OUTPUT_DIR)/test.ss_elf $(TESTS_DIR)/test.s

run_test_byte:
	$(ASSEMBLER) -o $(TESTS_OUTPUT_DIR)/test_byte.ss_elf $(TESTS_DIR)/test_byte.s 

run_test_end:
	$(ASSEMBLER) -o $(TESTS_OUTPUT_DIR)/test_end.ss_elf $(TESTS_DIR)/test_end.s
	
run_test_extern:
	$(ASSEMBLER) -o $(TESTS_OUTPUT_DIR)/test_extern.ss_elf $(TESTS_DIR)/test_extern.s
	
run_test_global:
	$(ASSEMBLER) -o $(TESTS_OUTPUT_DIR)/test_global.ss_elf $(TESTS_DIR)/test_global.s
	
run_test_global_before:
	$(ASSEMBLER) -o $(TESTS_OUTPUT_DIR)/test_global_before.ss_elf $(TESTS_DIR)/test_global_before.s
	
run_test_labels:
	$(ASSEMBLER) -o $(TESTS_OUTPUT_DIR)/test_labels.ss_elf $(TESTS_DIR)/test_labels.s
	
run_test_section:
	$(ASSEMBLER) -o $(TESTS_OUTPUT_DIR)/test_section.ss_elf $(TESTS_DIR)/test_section.s
	
run_test_skip:
	$(ASSEMBLER) -o $(TESTS_OUTPUT_DIR)/test_skip.ss_elf $(TESTS_DIR)/test_skip.s

run_test_word:
	$(ASSEMBLER) -o $(TESTS_OUTPUT_DIR)/test_word.ss_elf $(TESTS_DIR)/test_word.s
