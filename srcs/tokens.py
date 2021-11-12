#! /bin/python3

from constants import blanks, meta, quote, opers, brs, redirect


def quotation(tokens, line, j, states):
    if j == 0:
        states['t_start'] = j
    else:
        prev = line[j - 1]
        if prev in meta:
            tokens.append(line[states['t_start']:j]) # записать токен если предыдущий мета
        if prev in blanks or prev in meta:
            states['t_start'] = j                    # если предыдущий мета или пробельный, начать новый токен
    tmp_quote = line[j]
    try:
        next = j + 1 + line[(j + 1):].index(tmp_quote) #если есть закрывающая кавычка
    except ValueError:
        next = j                                    # нет цитирования
    states['end_quote'] = next


def blanks_oper(tokens, line, j, states):
    if j > 0 and not line[j - 1] in blanks:  # если предыдущий не пробельный, то записываем токен
        tokens.append(line[states['t_start']:j])
    states['t_start'] = -1


def meta_oper(tokens, line, j, states):
    if states['t_start'] != -1:  # если уже начат какой-то токен,
        if line[j - 1] in meta and not line[j - 1] in "()":
            return  # a предудыщий относится к мета и не равен скобкам так, то пропустить
        tokens.append(line[states['t_start']:j])  # в противном случае записать токен
    states['t_start'] = j


def common_oper(tokens, line, j, states):
    if j > 0:
        prev = line[j - 1]
        if not prev in meta and not prev in blanks:  # если символ обычный - пропустить
            return
        if prev in meta:
            tokens.append(line[states['t_start']:j])  # если предыдущий мета, записать токен
    states['t_start'] = j


def get_tokens(line):
    tokens = []
    states = dict({})
    states['t_start'] = -1
    states['end_quote'] = -1
    for (j, i) in enumerate(line):
        if j <= states['end_quote']:  # есть цитирование?
            continue
        if i in quote:
            quotation(tokens, line, j, states)
        elif i in blanks or i == '\n':
            blanks_oper(tokens, line, j, states)
        elif i in meta:  # если нет цитирования и текущий символ из мета
            meta_oper(tokens, line, j, states)
        else:  # если нет цитирования, обычный символ
            common_oper(tokens, line, j, states)
    return tokens
