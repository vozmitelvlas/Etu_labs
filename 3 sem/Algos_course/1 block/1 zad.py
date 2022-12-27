class Node:
    def __init__(self, data, prev=None, next=None):
        self.__data = data
        self.__prev__ = prev
        self.__next__ = next

    def get_data(self):
        return self.__data

    def __str__(self):
        if self is not None:
            next_el = None
            prev_el = None
            if self.__next__:
                next_el = self.__next__.__data
            if self.__prev__:
                prev_el = self.__prev__.__data

            return f"data: {self.__data}, prev: {prev_el}, next: {next_el}"


class LinkedList:
    def __init__(self, first=None, last=None):
        if not last and first:
            self.__first__ = Node(first)
            self.__last__ = None
            self.__length = 1
        if not first and last:
            raise ValueError('invalid value for last')
        if first and last:
            ob1 = Node(first)
            ob2 = Node(last)
            self.__first__ = ob1
            self.__last__ = ob2
            self.__first__.__next__ = ob2
            self.__last__.__prev__ = ob1
            self.__length = 2
        if not first and not last:
            self.__first__ = None
            self.__last__ = None
            self.__length = 0

    def __len__(self):
        return self.__length

    def __str__(self):

        if self is not None:
            if self.__length == 0:
                return 'LinkedList[]'

            if self.__first__ and self.__length == 1:
                return 'LinkedList[length = {}, [data: {}, prev: {}, next: {}]]'.format(self.__length,
                                                                                        self.__first__.get_data(),
                                                                                        self.__first__.__prev__,
                                                                                        self.__first__.__next__)

            if self.__first__ and self.__last__ and self.__length == 2:  # !!!
                return "LinkedList[length = {}, [data: {}, prev: {}, next: {}; data: {}, prev: {}, next: {}]]".format(
                    self.__length, self.__first__.get_data(), self.__first__.__prev__,
                    self.__first__.__next__.get_data(), self.__last__.get_data(), self.__last__.__prev__.get_data(),
                    self.__last__.__next__)

            if self.__length >= 2:
                tmp = self.__first__
                string = 'LinkedList[length = {}, ['.format(self.__length)
                prev_el = None
                while tmp.__next__:
                    next_el = tmp.__next__.get_data()
                    if not next_el:
                        next_el = None
                    string = string + f'data: {tmp.get_data()}, ' + f'prev: {prev_el}, ' + f'next: {next_el}; '
                    tmp = tmp.__next__
                    if not prev_el:
                        prev_el = tmp.__prev__.get_data()
                    else:
                        prev_el = tmp.__prev__.get_data()
                string = string + f'data: {tmp.get_data()}, ' + f'prev: {tmp.__prev__.get_data()}, ' + f'next: {tmp.__next__};'
                string = string[:-1:]
                string = string + ']]'
                return string

    def clear(self):
        tmp = self.__first__
        cur = self.__first__
        while cur.__next__:
            cur = tmp.__next__
            tmp = tmp.__next__
            if tmp:
                tmp.__next__ = None

        tmp.__prev__.__next__ = None
        tmp.__prev__ = None
        self.__length = 0

    def append(self, element):
        tmp = self.__first__
        el = Node(element)
        if self.__last__:
            return
        if not tmp:
            self.__first__ = el
        while tmp:
            if not tmp.__next__:
                el.__prev__ = tmp
                tmp.__next__ = el
                break
            tmp = tmp.__next__
        self.__length += 1

    def pop(self):
        tmp = self.__first__
        if self.__length == 0:
            raise IndexError('LinkedList is empty!')
        while tmp.__next__:
            tmp = tmp.__next__

        if not tmp.__prev__:
            self.__first__ = None
            self.__length -= 1
            return
        tmp.__prev__.__next__ = None
        self.__length -= 1

    def popitem(self, element):
        tmp = self.__first__
        ok = False
        while tmp:
            if tmp.get_data() == element:
                ok = True
                break
            else:
                tmp = tmp.__next__

        if ok and not tmp.__next__ and tmp.__prev__:
            tmp.__prev__.__next__ = None
            self.__length -= 1

            return
        elif ok and tmp.__next__ and tmp.__prev__:
            tmp.__prev__.__next__ = tmp.__next__
            tmp.__next__.__prev__ = tmp.__prev__
            self.__length -= 1

            return
        elif ok and tmp.__next__ and not tmp.__prev__:
            self.__first__ = self.__first__.__next__
            self.__first__.__prev__ = None
            self.__length -= 1
            return
        elif ok and not tmp.__next__ and not tmp.__prev__:
            self.__first__ = None
            self.__length -= 1
            return
        raise KeyError(f"{element} doesn't exist!")