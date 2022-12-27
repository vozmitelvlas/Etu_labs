def insert(arr):
    for i in range(1, len(arr)):
        cur = arr[i]
        sort_i = i - 1

        while sort_i >= 0 and cur < arr[sort_i]:
            arr[sort_i + 1] = arr[sort_i]
            # arr[sort_i] = cur
            sort_i -= 1

        arr[sort_i + 1] = cur
    return arr


arr = [3, 2, 4, 1, 0]
print(insert(arr))

# худший случай О(n^2)
# средний случай О(n^2)
# лучший случай О(n), массив уже отсортирован
# метод двуз путевых встовок(улучшает алгоритм) //вставка в доп файл или массив в середину