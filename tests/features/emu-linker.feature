@emulator
@emu
@linker
Feature: Link files

  Scenario: link empty file
     Given we have emulator
      When we run emulator with "--link-only /dev/null /dev/null" as arguments
      Then emulator will print "Linking source files..."
