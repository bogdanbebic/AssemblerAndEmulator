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

  Scenario: link test ALU
     Given we have emulator
      When we run emulator with "./tests/ss_elf/test_alu.s.ss_elf" as arguments
      Then emulator will print "Linking source files..."
      And emulator will print "Emulator started!"
      And emulator will print "6"
      And emulator will print "4"
      And emulator will print "9"
      And emulator will print "2"
      And emulator will print "A"
      And emulator will print "B"
      And emulator will print "C"
      And emulator will print "D"
      And emulator will print "4"
      And emulator will print "1"
      And emulator will print "Emulator finished!"

  Scenario: link test jump
     Given we have emulator
      When we run emulator with "./tests/ss_elf/test_jump.s.ss_elf" as arguments
      Then emulator will print "Linking source files..."
      And emulator will print "Emulator started!"
      And emulator will print "12345"
      And emulator will print "Emulator finished!"

  Scenario: link test move
     Given we have emulator
      When we run emulator with "./tests/ss_elf/test_move.s.ss_elf" as arguments
      Then emulator will print "Linking source files..."
      And emulator will print "Emulator started!"
      And emulator will print "001"
      And emulator will print "ABBA"
      And emulator will print "BABB"
      And emulator will print "Emulator finished!"

  Scenario: link hello terminal
     Given we have emulator
      When we run emulator with "./tests/ss_elf/hello_terminal.s.ss_elf" as arguments
      Then emulator will print "Linking source files..."
      And emulator will print "Emulator started!"
      When we send "x" to emulator
      Then emulator will print "x"
      When we send "y" to emulator
      Then emulator will print "y"
      When we send "1" to emulator
      Then emulator will print "1"
      When we send "/" to emulator
      Then emulator will print "/"
      When we send "\" to emulator
      Then emulator will print "\\"
      And emulator will print "Emulator finished!"

  Scenario: link hello timer
     Given we have emulator
      When we run emulator with "./tests/ss_elf/hello_timer.s.ss_elf" as arguments
      Then emulator will print "Linking source files..."
      And emulator will print "Emulator started!"
      And emulator will print "TIMER"
      And emulator will print "TIMER"
      And emulator will print "TIMER"
      And emulator will print "TIMER"
      And emulator will print "TIMER"
      And emulator will print "TIMER"
      And emulator will print "TIMER"
      And emulator will print "TIMER"
      And emulator will print "TIMER"
      And emulator will print "TIMER"
      And emulator will print "Emulator finished!"
