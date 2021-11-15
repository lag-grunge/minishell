#!/bin/python

import re
import os
from os import path, listdir
from pathlib import Path
from constants import blanks, meta, quote, opers, brs, redirect


def unquoted_parts(token):
    end = None
    try:
        end = token.index("\'")
    except ValueError:
        pass
    if end is None:
        return [token]
    else:
        return token.split('\'')[0::2]


def get_vars(i):
    assert type(i) == str
    vars = []
    end = None
    end_var_list = [c for l in [blanks, quote] for c in l]
    unq = unquoted_parts(i)
    vars = [p for p in unq if '$' in p]
    for v in vars:
        v = re.split("".join(end_var_list), v[v.index('$'):])[0]
    return vars


def find_var_and_replace(i:str):
    assert type(i)==str
    dolls = get_vars(i)
    for var in dolls:
        if var[1:] in os.environ.keys():
            i = i.replace(var, os.environ[var[1:]])
    return i


def dollar(tokens):
    if type(tokens) == list:
        for (j, i) in enumerate(tokens):
            tokens[j] = find_var_and_replace(i)
    elif type(tokens) == dict:
        for i in tokens:
            tokens[i] = find_var_and_replace(tokens[i])
    elif type(tokens) == str:
        tokens = find_var_and_replace(tokens)
    return tokens


def dollar_expansions(command):
    for i in command['cmds']:
        if type(i['cmd']) == dict:
            dollar_expansions(i['cmd'])
            dollar(i['cin'])
            dollar(i['cout'])
            dollar(i['args'])
            return
        i['cin'] = dollar(i['cin'])
        i['cout'] = dollar(i['cout'])
        i['cmd'] = dollar(i['cmd'])
        i['args'] = dollar(i['args'])
    return command

