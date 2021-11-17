#!/bin/python

import re
import os
from constants import blanks, meta, quote, opers, brs, redirect
from utils import iter_command


def unquoted_parts(token):
    try:
        token.index("\'")
    except ValueError:
        return [token]
    return token.split('\'')[0::2]


def get_dollars(i):
    assert type(i) == str
    end_var = " \t\'\""
    unq = unquoted_parts(i)
    dollars = [p for p in unq if '$' in p]
    for v in dollars:
        print(v[v.index('$'):])
        print(re.split(end_var, v[v.index('$'):])[0])
    return dollars


def dollar_expansions(command):
    def find_var_and_replace(i: str):
        assert type(i) == str
        dolls = get_dollars(i)
        for var in dolls:
            if var[1:] in os.environ.keys():
                i = i.replace(var, os.environ[var[1:]])
        return i
    return iter_command(command, find_var_and_replace)

