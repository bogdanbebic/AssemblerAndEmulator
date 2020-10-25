from behave import *
import pexpect
import os


assembler_path = './assembler'


@given('we have assembler')
def step_impl(context):
    if not os.path.isfile(assembler_path):
        fail("assembler doesn't exist")


@when('we run assembler with "{text}" as arguments')
def step_impl(context, text):
    context.child = pexpect.spawn(assembler_path + ' ' + text)


@then('assembler will print "{text}"')
def step_impl(context, text):
    context.child.expect(text)
