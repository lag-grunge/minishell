#!/bin/python

import os
import re

from constants import blanks, meta, quote, opers, brs, redirect


def get_var(i):
    try:
        start = i.index('$') + 1
    except ValueError:
        return None
    end = len(i)
    for j in [blanks, meta, quote]:
        try:
            cur = i.index(j)
        except ValueError:
            continue
        if end > cur + 1:
            end = cur + 1
    return i[start:end]

def dollar(tokens):
    if type(tokens)==list:
        for i in tokens:
            var = get_var(i)
            if var in os.environ.keys():


def dollar_expansions(command):
    for i in command['cmds']:
        if type(i['cmd']) == dict:
            dollar_expansions(i['cmd'])
            return
        dollar(i['stdin'])
        dollar(i['stdout'])
        dollar(i['cmd'])
        dollar(i['args'])

