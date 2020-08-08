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
