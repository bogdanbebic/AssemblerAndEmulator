@emulator
@emu
Feature: Run emulator with different arguments

  Scenario: print usage
     Given we have emulator
      When we run emulator with "--help" as arguments
      Then emulator will print "Usage:"

  Scenario: invalid arguments
     Given we have emulator
      When we run emulator without arguments
      Then emulator will print "Error: invalid arguments"
      And emulator will print "Usage:"
