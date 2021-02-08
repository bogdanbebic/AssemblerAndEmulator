@emulator
@emu
@bare-memory
Feature: Run emulator with bare memory

  Scenario: emulate without code
     Given we have emulator
      When we run emulator with "--bare-memory /dev/null" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "Emulator finished!"

  Scenario: emulate hello
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/hello.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "Hello, World!"
      And emulator will print "Emulator finished!"

  Scenario: emulate hello timer
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/hello_timer.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
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

  Scenario: emulate hello terminal
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/hello_terminal.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
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

  Scenario: emulate test usage fault
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/hello_usage_fault.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "INT"
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

  Scenario: emulate test move instructions
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/test_move.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "001"
      And emulator will print "ABBA"
      And emulator will print "BABB"
      And emulator will print "Emulator finished!"

  Scenario: emulate test jump instructions
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/test_jump.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "12345"
      And emulator will print "Emulator finished!"

  Scenario: emulate test interrupt instruction
     Given we have emulator
      When we run emulator with "--bare-memory ./tests/ss_mem/hello_isr.s.ss_mem" as arguments
      Then emulator will print "Emulator started!"
      And emulator will print "INT"
      And emulator will print "Emulator finished!"
