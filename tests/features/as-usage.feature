Feature: print usage

  Scenario: print usage
     Given we have assembler
      When we run assembler with "--help" as arguments
      Then assembler will print "Usage:"
