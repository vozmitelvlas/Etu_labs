from algos4 import find


def test_first():
    print(find("abc", "abcabcabc") == [6, 3, 0])


def test_second():
    print(find("a", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == [39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27,
                                                                    26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14,
                                                                    13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0])


def test_third():
    print(find("a", "b") == [])


def test_fourth():
    print(find("o0oO", "dsfsdfdo0oOdsfdfgadfo0oOo0oOo0oOo0oOgfgdrgero0oO") == [44, 32, 28, 24, 20, 7])


if __name__ == "__main__":
    test_first()
    test_second()
    test_third()
    test_fourth()
