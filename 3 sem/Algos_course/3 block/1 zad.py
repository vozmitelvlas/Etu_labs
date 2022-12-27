def binary_search(arr, elem):
    low = 0
    high = len(arr) - 1

    while low <= high:

        middle = (low + high) // 2

        if arr[middle] == elem:
            return middle
        elif arr[middle] > elem:
            high = middle - 1
        else:
            low = middle + 1

    return -1


list1 = [12, 24, 32, 39, 45, 50, 54]
n = 45

result = binary_search(list1, n)

if result != -1:
    print("Element is present at index", str(result))
else:
    print("Element is not present in arr")
