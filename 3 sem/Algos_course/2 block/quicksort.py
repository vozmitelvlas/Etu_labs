def sort(array):
    less = []
    equal = []
    greater = []

    if len(array) > 1:
        pivot = array[0]
        for x in array:
            if x < pivot:
                less.append(x)
            elif x == pivot:
                equal.append(x)
            elif x > pivot:
                greater.append(x)
        return sort(less) + equal + sort(greater)
    else:
        return array


arr = [5, 1, 5, 2, 7, 7, 6, 4, 2, 1]
print(sort(arr))


# Быстрая сортировка
#
# ➢ Скорость работы зависит от выбора опорного элемента
# ➢ В худшем случае скорость работы O(n2
#
# ), в среднем и лучшем -
#
# O(nlogn)
# ➢ Работает без привлечения дополнительной памяти (in-place)
# ➢ Принцип работы:
# 1. Выбирается опорный элемент
# 2. Элементы сортируемого массива делятся на 3 части: меньше опорного
# элемента, равные ему и больше
# 3. Для меньшей и большей частей массива повторяются пункты 1, 2