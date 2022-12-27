# python
def add(arr, key, number):
    i = hash(key) % 1000
    if arr[i] == -1:
        arr[i] = [[key, number]]
    else:
        for ind, el in enumerate(arr[i]):
            if key == el[0]:
                arr[i][ind] = [key, number]
                return
        arr[i].append([key, number])


def find(arr, key):
    i = hash(key) % 1000
    if arr[i] == -1:
        return "not found"
    for el in arr[i]:
        if el[0] == key:
            return str(el[1])
    return "not found"


def dell(arr, key):
    i = hash(key) % 1000
    if arr[i] == -1:
        return
    for ind, el in enumerate(arr[i]):
        if el[0] == key:
            arr[i].pop(ind)
            break


arr = [-1] * 1000
n = int(input())
for i in range(n):
    command = input().split()
    if command[0] == "add":
        add(arr, command[1], command[2])
    elif command[0] == "find":
        print(find(arr, command[1]))
    elif command[0] == "del":
        dell(arr, command[1])
