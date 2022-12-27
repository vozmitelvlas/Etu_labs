

minrun = 32


def insert(arr, start, end):  # вставки
    for i in range(start + 1, end + 1):
        cur = arr[i]
        sort_i = i - 1

        while sort_i >= start and cur < arr[sort_i]:
            arr[sort_i + 1] = arr[sort_i]
            # arr[sort_i] = cur
            sort_i -= 1

        arr[sort_i + 1] = cur

    return arr


def merge(arr, start, mid, end):  # слияние
    if mid == end:
        return arr

    first = arr[start:mid + 1]
    last = arr[mid + 1:end + 1]

    len1 = mid - start + 1
    len2 = end - mid

    index_left = index_right = 0
    index = start

    while index_left < len1 and index_right < len2:
        if first[index_left] < last[index_right]:
            arr[index] = first[index_left]
            index_left += 1
        else:
            arr[index] = last[index_right]
            index_right += 1
        index += 1

    while index_left < len1:
        arr[index] = first[index_left]
        index_left += 1
        index += 1

    while index_right < len2:
        arr[index] = last[index_right]
        index_right += 1
        index += 1

    return arr


def timsort(arr):
    n = len(arr)

    for start in range(0, n, minrun):
        end = min(start + minrun - 1, n - 1)
        arr = insert(arr, start, end)

    curr_size = minrun
    while curr_size < n:
        for start in range(0, n, curr_size * 2):
            mid = min(n - 1, start + curr_size - 1)
            end = min(n - 1, mid + curr_size)
            arr = merge(arr, start, mid, end)
        curr_size *= 2
    return arr


arr = [3, 2, 4, 1, 0]

print(timsort(arr))
