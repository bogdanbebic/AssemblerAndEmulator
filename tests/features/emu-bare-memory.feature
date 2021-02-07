@emulator
@emu
@bare-memory
Feature: Run emulator with bare memory

  Scenario: emulate without code
     Given we have emulator
      When we run emulator with "--bare-memory /dev/null" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "Emulator finished!"

  Scenario: emulate hello no loops
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/hello_no_loops.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "Hello, World!"
      And emulator will print "Emulator finished!"

  Scenario: emulate hello no loops offset
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/hello_no_loops_offset.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "Hello, World!"
      And emulator will print "Emulator finished!"

  Scenario: emulate hello no loops offset jmp
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/hello_no_loops_offset_jmp.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "World!"
      And emulator will print "Emulator finished!"

  Scenario: emulate test ALU
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/test_alu.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
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

  Scenario: emulate test function call
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/hello_function.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "Hello, World!"
      And emulator will print "Emulator finished!"
