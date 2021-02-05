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
