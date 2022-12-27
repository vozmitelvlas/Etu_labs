# python
class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

    def __str__(self):
        left = self.left.key if self.left else None
        right = self.right.key if self.right else None
        return 'key: {}, left: {}, right: {}'.format(self.key, left, right)


def read_data():
    n = int(input())
    nodes = [Node(0) for _ in range(n)]
    for i in range(n):
        key, left, right = map(int, input().split())
        nodes[i].key = key
        if left != -1:
            nodes[i].left = nodes[left]
        if right != -1:
            nodes[i].right = nodes[right]
    return nodes[0]


def in_order(current, arr):
    if not current:
        return
    in_order(current.left, arr)
    arr.append(current.key)
    in_order(current.right, arr)
    return arr


def pre_order(current, arr):
    if not current:
        return
    arr.append(current.key)
    pre_order(current.left, arr)
    pre_order(current.right, arr)
    return arr


def post_order(current, arr):
    if not current:
        return
    post_order(current.left, arr)
    post_order(current.right, arr)
    arr.append(current.key)
    return arr


tmp = read_data()
in_ = map(str, in_order(tmp, []))
pre_ = map(str, pre_order(tmp, []))
post_ = map(str, post_order(tmp, []))

print(" ".join(in_))
print(" ".join(pre_))
print(" ".join(post_))
