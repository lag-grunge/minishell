#! /bin/python

import sys
from tokens import get_tokens
from constants import blanks, meta, quote, opers, brs, redirect
from commands import get_commands, check_brackets, print_out
from expansions import dollar_expansions
from filename_expansion import filename_expansions



if __name__=="__main__":
    # 1. Reads its input from a file (see Section 3.8 [Shell Scripts], page 42), from a string
    # supplied as an argument to the -c invocation option (see Section 6.1 [Invoking Bash],
    # page 87), or from the user’s terminal.
    # with open("tests", "r") as fp:
    #      while True:
    # try:
    #     start_line = next(fp)
    # except StopIteration:
    #     fp.close()
    #     break;
            start_line = sys.stdin.readline() # reads input from stdin

    # 2. Breaks the input into words and operators, obeying the quoting rules described in
    # Section 3.1.2 [Quoting], page 6. These tokens are separated by metacharacters. Alias
    # expansion is performed by this step (see Section 6.6 [Aliases], page 95).
            print(start_line)
            tokens = get_tokens(start_line)
            print(tokens)

    #check_operators_redirect ???[< << > >> && || |]  && correct &&< incorrect

    # 3. Parses the tokens into simple and compound commands (see Section 3.2 [Shell Com-
    # mands], page 8).
            if not check_brackets(tokens):
                command = get_commands(tokens)
                print_out(command)
            else:
                exit(1)

    # 4. Performs the various shell expansions (see Section 3.5 [Shell Expansions], page 22),
    # breaking the expanded tokens into lists of filenames (see Section 3.5.8 [Filename Ex-
    # pansion], page 33) and commands and arguments.
            command = dollar_expansions(command)
            print(command)
            command = filename_expansions(command)
            print(command)

    #Write in C
    # 5. Performs any necessary redirections (see Section 3.6 [Redirections], page 35) and re-
    # moves the redirection operators and their operands from the argument list.


    # 6. Executes the command (see Section 3.7 [Executing Commands], page 39).

    # 7. Optionally waits for the command to complete and collects its exit status (see
    # Section 3.7.5 [Exit Status], page 41).

