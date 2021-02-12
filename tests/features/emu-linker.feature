@emulator
@emu
@linker
Feature: Link files

  Scenario: link empty file
     Given we have emulator
      When we run emulator with "--link-only /dev/null /dev/null" as arguments
      Then emulator will print "Linking source files..."

  Scenario: link hello world
     Given we have emulator
      When we run emulator with "./tests/ss_elf/hello_linker_code.s.ss_elf ./tests/ss_elf/hello_linker_data.s.ss_elf ./tests/ss_elf/hello_linker_ivt.s.ss_elf --place=startup@0" as arguments
      Then emulator will print "Linking source files..."
      And emulator will print "Emulator started!"
      And emulator will print "Hello, World!"
      And emulator will print "Emulator finished!"

  Scenario: link hello world with relocated text
     Given we have emulator
      When we run emulator with "./tests/ss_elf/hello_linker_code.s.ss_elf ./tests/ss_elf/hello_linker_data.s.ss_elf ./tests/ss_elf/hello_linker_ivt.s.ss_elf --place=startup@0 --place=text@1024" as arguments
      Then emulator will print "Linking source files..."
      And emulator will print "Emulator started!"
      And emulator will print "Hello, World!"
      And emulator will print "Emulator finished!"
