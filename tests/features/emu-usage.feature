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
      Then emulator will print "invalid cmd options"
      And emulator will print "Usage:"

  Scenario: invalid arguments - no bare memory file
     Given we have emulator
      When we run emulator with "--bare-memory" as arguments
      Then emulator will print "invalid cmd options"
      And emulator will print "Usage:"

  Scenario: invalid arguments - duplicate section name
     Given we have emulator
      When we run emulator with "--place=duplicate_name@0x0000 --place=duplicate_name@0x4000" as arguments
      Then emulator will print "invalid cmd options"
      And emulator will print "Usage:"

  Scenario: invalid arguments - no linker memory file for output
     Given we have emulator
      When we run emulator with "--link-only" as arguments
      Then emulator will print "invalid cmd options"
      And emulator will print "Usage:"
