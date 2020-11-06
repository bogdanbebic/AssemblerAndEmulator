@emulator
@emu
Feature: print usage

  Scenario: print usage
     Given we have emulator
      When we run emulator with "--help" as arguments
      Then emulator will print "Usage:"
