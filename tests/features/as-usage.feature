@assembler
@as
@usage
@as-usage
Feature: Run assembler with different arguments

  Scenario: print usage
     Given we have assembler
      When we run assembler with "--help" as arguments
      Then assembler will print "Usdage:"

  Scenario: invalid arguments
     Given we have assembler
      When we run assembler without arguments
      Then assembler will print "Error: invalid arguments"
      And assembler will print "Usage:"
