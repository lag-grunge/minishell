#!/bin/python

from constants import blanks, meta, quote, opers, brs, redirect


def check_brackets(tokens):
    tmp_br = 0
    for i in tokens:
        if i == '(':
            tmp_br += 1
        elif i == ')':
            tmp_br -= 1
        if tmp_br < 0:
            print("Paranthesis error!")
            return (1)
    if tmp_br > 0:
        print("Paranthesis error!")
        return (1)
    return (0)


def if_state_token(state, i):
    if state['redir']:
        state['redir'] = False
        return 1
    if state['br']:
        if i == ')':
            state['br'] -= 1
        elif i == '(':
            state['br'] += 1
        return 1
    return 0


def change_in_out(commands, cmd_num, i, next_token):
    if next_token in opers or next_token in brs or next_token in redirect:
        print("{} Unexpected token after {}".format(next_token, i))
        exit(2)
    if i == '<' or i == '<<':
        red_keys = commands['cmds'][cmd_num]['cin'].keys()
        if red_keys and list(red_keys)[0] != i:
            commands['cmds'][cmd_num]['cin'] = dict({})
        commands['cmds'][cmd_num]['cin'][i] = next_token
    elif i == '>' or i == '>>':
        red_keys = commands['cmds'][cmd_num]['cout'].keys()
        if red_keys and list(red_keys)[0] != i:
            commands['cmds'][cmd_num]['cout'] = dict({})
        commands['cmds'][cmd_num]['cout'][i] = next_token


def print_out(commands):
    for i in commands['cmds']:
        print(i['cmd'])
        print(i['args'])
        print(i['cin'])
        print(i['cout'])
    print(commands['opers'])


def reset(command):
    command['cmd'] = "\0"
    command['args'] = []
    command['cin'] = dict({'<': 'stdin'})
    command['cout'] = dict({'>': 'stdout'})
    return (command)


def opers_proc(commands, cmd_num, i, pipe):
    commands['cmds'].append(reset(dict({})))
    if i != '|' or not pipe:
        commands['opers'].append(dict({'oper': i, 'l': cmd_num - 1, 'r': cmd_num}))
    else:
        commands['opers'][-1]['r'] = cmd_num


def write_cmd_args(commands, cmd_num, i):
    if commands['cmds'][cmd_num]['cmd'] == "\0":
        commands['cmds'][cmd_num]['cmd'] = i
    else:
        commands['cmds'][cmd_num]['args'].append(i)


def get_commands(tokens):
    commands = dict({})
    commands['cmds'] = [reset(dict({}))]
    commands['opers'] = []
    cmd_num = 0
    state = dict({})
    state['redir'] = False
    state['pipe'] = False
    state['br'] = 0
    for (j, i) in enumerate(tokens):
        if if_state_token(state, i):
            continue
        if i == '(':
            state['br'] += 1
            commands['cmds'][cmd_num]['cmd'] = get_commands(tokens[(j + 1):])
        elif i == ')':
            return commands
        elif i in redirect:
            change_in_out(commands, cmd_num, i, tokens[j + 1])
            state['redir'] = True
        elif i in opers:
            cmd_num += 1
            opers_proc(commands, cmd_num, i, state['pipe'])
            state['pipe'] = i == '|'
        else:
            write_cmd_args(commands, cmd_num, i)
    return commands
