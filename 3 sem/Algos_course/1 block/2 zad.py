#python

def check_bracket(string):
    pseudo_stack = []
    stack = []
    bracket_list = [')', '(', ']', '[', '}', '{']
    bracket_dict = {
        ')': '(',
        ']': '[',
        '}': '{',
    }
    m = 0
    for i in range(len(string)):
        m = i+1
        if string[i] in bracket_list:
            if string[i] in bracket_dict.values():
                pseudo_stack.append(string[i])
                stack.append(i + 1)
            else:
                if not pseudo_stack:
                    return m
                else:
                    if pseudo_stack[-1] == bracket_dict.get(string[i]):
                        del pseudo_stack[-1]
                        del stack[-1]
                    else:
                        return m
    if pseudo_stack:
        return stack[0]
    else:
        return "Success"


a = input()
print(check_bracket(a))