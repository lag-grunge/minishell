#! /bin/python

from utils import iter_command

def find_quoting(token):
    ind = dict({})
    ind["\'"] = None
    ind["\""] = None
    try:
        ind["\'"] = token.index("\'")
    except ValueError:
        pass
    try:
        ind["\""] = token.index("\"")
    except ValueError:
        pass
    return ind


def quote_removal(command):
    def unquoting(token):
        ind = find_quoting(token)
        both_None = lambda a: a[0] is None and a[1] is None
        both_not_None = lambda a: not a[0] is None and not a[1] is None
        if both_None(ind.values()):
            return token
        elif ind["\""] is None or (both_not_None(ind.values()) and ind["\""] > ind["\'"]):
            sp = token.split("\'")
        elif ind["\'"] is None or (both_not_None(ind.values()) and ind["\""] < ind["\'"]):
            sp = token.split("\"")
        if len(sp) == 2:  # если одна кавычка, то не считается за цитирование
            if ind['\''] is None or ind["\""] is None:  # если присутствует один вид кавычек
                return token
            j = min(ind.values())
            return token[:(j + 1)] + unquoting(token[(j + 1):])
        else:
            return sp[0] + sp[1] + unquoting(sp[2])
    return iter_command(command, unquoting)
