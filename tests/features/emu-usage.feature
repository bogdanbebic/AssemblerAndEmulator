@emulator
@emu
@usage
@emu-usage
Feature: Run emulator with different arguments

  Scenario: print usage
     Given we have emulator
      When we run emulator with "--help" as arguments
      Then emulator will print "Usage:"

  Scenario: invalid arguments - no source files
     Given we have emulator
      When we run emulator without arguments
      Then emulator will print "Error: invalid arguments"
      And emulator will print "Usage:"

  Scenario: invalid arguments - no bare memory file
     Given we have emulator
      When we run emulator with "--bare-memory" as arguments
      Then emulator will print "Error: invalid arguments"
      And emulator will print "Usage:"

  Scenario: invalid arguments - duplicate section name
     Given we have emulator
      When we run emulator with "--place=duplicate_name@0x0000 --place=duplicate_name@0x4000" as arguments
      Then emulator will print "Error: invalid arguments"
      And emulator will print "Usage:"
