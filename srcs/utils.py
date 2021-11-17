#! bin/python


def iter_command(command, func):
    def func_token(tokens):
        if type(tokens) == list:
            for i in tokens:
                i = func(i)
        elif type(tokens) == dict:
            for i in tokens.values():
                i = func(i)
        elif type(tokens) == str:
            tokens = func(tokens)
        return tokens
    for i in command['cmds']:
        if type(i['cmd']) == dict:
            iter_command(i['cmd'])
            func_token(i['cin'])
            func_token(i['cout'])
            func_token(i['args'])
            return
        i['cin'] = func_token(i['cin'])
        i['cout'] = func_token(i['cout'])
        i['cmd'] = func_token(i['cmd'])
        i['args'] = func_token(i['args'])
    return command