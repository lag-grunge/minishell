#! /bin/python

import sys

def get_tokens(line):
    blanks = [' ', '\t']
    meta = ['|', '&', '(', ')', '<', '>']
    quote = ['\'', '\"']
    tokens = []
    j_start = -1
    tmp_quote = '\0'
    for (j, i) in enumerate(line):
        if i == tmp_quote: #если есть цитирование и текущий символ совпадает с начальным символом, то окончить цитирование
            tmp_quote = '\0'
        elif tmp_quote != '\0': #в противном случае, если есть цитирование, пропустить текущий символ
            continue
        elif i in quote: #если нет цитирования и текущий символ
            # цитирования - начать цитирование, запомнив начальный символ
            tmp_quote = i
            if j > 0 and not line[j - 1] in meta and not line[j - 1] in blanks: #если предыдущий символ не мета и не пробельный не создавать токен
                continue
            if j > 0 and line[j - 1] in meta: #если предудыщий символ мета, то записать предыдущий токен
                tokens.append(line[j_start:j])
            j_start = j
        elif i in blanks or i == '\n':
            if j > 0 and not line[j - 1] in blanks: # если предыдущий не пробельный, то записываем токен
                tokens.append(line[j_start:j])
            j_start = -1
        elif i in meta: #если нет цитирования и текущий символ из мета
            if j > 0 and j_start != -1 and line[j - 1] in meta and not line[j - 1] in "()": # если уже начат какой-то токен,
                # a предудыщий относится к мета и не равен скобкам так, то пропустить
                continue
            if j > 0 and j_start != -1:
                tokens.append(line[j_start:j])
            j_start = j
        # если нет цитирования, обычный символ
        else:
            if j > 0 and line[j - 1] in meta:
                tokens.append(line[j_start:j])
            elif j > 0 and not line[j - 1] in blanks:
                continue
            j_start = j
    if tmp_quote != '\0':
        print("Error: unquoted!")
    print(tokens)
    return tokens

def get_commands(tokens):
    opers = ['||', '&&', '|']
    brs = ['(', ')']
    redirect = ['>', '<', '>>', '<<']
    def reset(command):
        command['cmd'] = "\0"
        command['args'] = []
        command['cin'] = dict({'<': 'stdin'})
        command['cout'] = dict({'>': 'stdout'})
        return (command)
    commands = dict({})
    commands['cmds'] = []
    commands['opers'] = []
    depth = [0]
    cmd_num = 0
    commands['cmds'].append(reset(dict({})))
    redir = "\0"
    tmp_br = 0
    for i in tokens:
        if i in redirect:
            redir = i
        elif redir != "\0":
            if redir == '<' or redir == '<<':
                commands['cmds'][cmd_num]['cin'][redir] = i
            else:
                commands['cmds'][cmd_num]['cout'][redir] = i
            redir = "\0"
        elif i in opers:
            redir = "\0"
            cmd_num += 1
            commands['cmds'].append(reset(dict({})))
            commands['opers'].append(dict({'oper': i}))
        elif i in brs:
            if i == '(':
                tmp_br += 1
                depth.append(0)
            elif i == ')':
                tmp_br -= 1
                depth.pop()
            if tmp_br < 0:
                print("Paranthesis error!")
        elif commands['cmds'][cmd_num]['cmd'] == "\0":
            commands['cmds'][cmd_num]['cmd'] = i
        else:
            commands['cmds'][cmd_num]['args'].append(i)
    if tmp_br > 0:
        print("Paranthesis error!")
    for i in commands['cmds']:
        print(i['cmd'])
        print(i['args'])
        print(i['cin'])
        print(i['cout'])
    print(commands['opers'])
    return commands

if __name__=="__main__":
    # 1. Reads its input from a file (see Section 3.8 [Shell Scripts], page 42), from a string
    # supplied as an argument to the -c invocation option (see Section 6.1 [Invoking Bash],
    # page 87), or from the user’s terminal.
    # with open("tests", "r") as fp:
    #     while fp.readline():
    start_line = sys.stdin.readline() # reads input from stdin

    # 2. Breaks the input into words and operators, obeying the quoting rules described in
    # Section 3.1.2 [Quoting], page 6. These tokens are separated by metacharacters. Alias
    # expansion is performed by this step (see Section 6.6 [Aliases], page 95).
    print(start_line)
    tokens = get_tokens(start_line)

    # 3. Parses the tokens into simple and compound commands (see Section 3.2 [Shell Com-
    # mands], page 8).
    command = get_commands(tokens)


    # 4. Performs the various shell expansions (see Section 3.5 [Shell Expansions], page 22),
    # breaking the expanded tokens into lists of filenames (see Section 3.5.8 [Filename Ex-
    # pansion], page 33) and commands and arguments.


    # 5. Performs any necessary redirections (see Section 3.6 [Redirections], page 35) and re-
    # moves the redirection operators and their operands from the argument list.

    # 6. Executes the command (see Section 3.7 [Executing Commands], page 39).

    # 7. Optionally waits for the command to complete and collects its exit status (see
    # Section 3.7.5 [Exit Status], page 41).

