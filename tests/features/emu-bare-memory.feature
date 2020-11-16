@emulator
@emu
@bare-memory
Feature: Run emulator with bare memory

  Scenario: emulate without code
     Given we have emulator
      When we run emulator with "/dev/null" as arguments
      Then emulator will print "Linking source files..."
      And emulator will print "Emulator started!"
      And emulator will print "Emulator finished!"
