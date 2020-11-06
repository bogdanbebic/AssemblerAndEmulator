from behave import *
import pexpect
import os


emulator_path = './Code/Emulator/output/emulator'


@given('we have emulator')
def step_impl(context):
    if not os.path.isfile(emulator_path):
        assert False, "emulator doesn't exist"


@when('we run emulator with "{text}" as arguments')
def step_impl(context, text):
    context.child = pexpect.spawn(emulator_path + ' ' + text)


@then('emulator will print "{text}"')
def step_impl(context, text):
    context.child.expect(text)
