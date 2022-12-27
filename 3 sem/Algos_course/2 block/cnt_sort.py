def counting_sort(arr, largest):
    new_arr = [0] * (largest + 1)  # частота элементов

    for i in range(len(arr)):
        new_arr[arr[i]] = new_arr[arr[i]] + 1

    new_arr[0] = new_arr[0] - 1
    for i in range(1, largest + 1):
        new_arr[i] = new_arr[i] + new_arr[i - 1]
        print(new_arr)

    result = [0] * len(arr)

    arr = arr[::-1]
    for x in arr:
        result[new_arr[x]] = x
        new_arr[x] = new_arr[x] - 1

    return result


arr = [5, 1, 5, 2, 7, 7, 6, 4, 2, 1]
k = max(arr)
sorted_list = counting_sort(arr, k)
print(sorted_list)


# Алгоритм
# Подсчитываем, сколько раз в массиве встречается каждое значение, и заполняем массив подсчитанными элементами в соответствующих количествах. Счётчики для всего диапазона чисел создаются заранее (изначально равны нулю).
#
# Сложность сортировки по времени
# Худшая O(n + k)
# Средняя O(n + k)
# Лучшая O(n)