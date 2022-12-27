def merge(arr):  # 4 3 2 1
    if len(arr) == 1:
        return

    middle = len(arr) // 2
    left, right = arr[:middle], arr[middle:]
    merge(left)
    merge(right)
    index_left = index_right = index = 0
    result = [0] * (len(left) + len(right))
    while index_left < len(left) and index_right < len(right):

        if left[index_left] <= right[index_right]:
            result[index] = left[index_left]
            index_left += 1

        else:
            result[index] = right[index_right]
            index_right += 1

        index += 1

    while index_left < len(left):
        result[index] = left[index_left]
        index_left += 1
        index += 1

    while index_right < len(right):
        result[index] = right[index_left]
        index_right += 1
        index += 1

    for i in range(len(arr)):
        arr[i] = result[i]

    return result


arr = list(map(int, input().split()))
print(merge(arr))


# Разделяй и властвуй
#
# ➢ Задача разбивается на подзадачи - меньшие экземпляры той же
# задачи.
# ➢ Подзадачи рекурсивно решаются.
# ➢ Если подзадача достаточно мала (проста), она решается как
# базовый случай.
# ➢ Решения подзадач объединяются в решение исходной задачи.




# Сортировка слиянием
#
# ➢ Как работает:
# ○ Массив разбивается на две части и рекурсивно сортируется
# ○ Если в рассматриваемом массиве один элемент, значит он отсортирован
# ○ После сортировки двух частей массива к ним применяется процедура
# слияния, которая по двум отсортированным частям получает исходный
# отсортированный массив.
#
# ➢ Требует дополнительно O(n) памяти
# ➢ Время работы во всех случаях O(nlgn)