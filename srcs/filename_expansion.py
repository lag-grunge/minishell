#!/bin/python

import re
import os
from os import path, listdir
from pathlib import Path
from constants import blanks, meta, quote, opers, brs, redirect

pwd = os.path.realpath(__file__)
dirname = Path(pwd).parent.parent
child_names = [p for c in next(os.walk('../../..' / dirname), (None, [], []))[1:3] for p in c]
asterisk_list = [c for l in child_names for c in l]

def unquoted_parts(token, un_parts=[]):
    end = dict({})
    end['\''] = None
    end['\"'] = None
    try:
        end['\"'] = token.index("\"")
    except ValueError:
        pass
    try:
        end['\''] = token.index("\'")
    except ValueError:
        pass
    if end['\''] is None and end['\"'] is None:
        return [token]
    elif end['\"'] is None:
        return token.split('\'')[0::2]
    elif end['\''] is None:
        return token.split('\"')[0::2]
    else:
        if end['\"'] < end['\'']:
            spl = token.split["\""]
            un_parts.append([spl[0]])
            for c in unquoted_parts(spl[2:]):
                un_parts.append(c)
            return un_parts


def get_asterisks(unq):
    astr = []
    for p in unq:
        astr.extend([elem for elem in p if '*' in elem])
    return astr


def filter_child_names(asterisk):
    filtered = [c for c in child_names]
    for asp in asterisk.split('*'):
        filtered = [p for p in filtered if asp in p]
    return filtered


def find_asterisk_and_replace(token):
    assert type(token) == str
    unq = unquoted_parts(token)
    asterisks = get_asterisks(unq)
    for a in asterisks:
        fil_names = filter_child_names(a)
        if not fil_names:
            print("minishell: {} no matches found".format(a))
            exit(1)
        token = token.replace(a, fil_names)
    return token


def asterisk(tokens):
    if type(tokens) == list:
        for i in tokens:
            i = find_asterisk_and_replace(i)
    elif type(tokens) == dict:
        for i in tokens.values():
            i = find_asterisk_and_replace(i)
    elif type(tokens) == str:
        tokens = find_asterisk_and_replace(tokens)
    return tokens


def filename_expansions(command):
    for i in command['cmds']:
        if type(i['cmd']) == dict:
            filename_expansions(i['cmd'])
            asterisk(i['cin'])
            asterisk(i['cout'])
            asterisk(i['args'])
            return
        i['cin'] = asterisk(i['cin'])
        i['cout'] = asterisk(i['cout'])
        i['cmd'] = asterisk(i['cmd'])
        i['args'] = asterisk(i['args'])
    return command

