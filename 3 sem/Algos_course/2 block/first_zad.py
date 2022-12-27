stations = set(input().split(','))
length = int(input())
info = []
dic_info = {}
res = []

for i in range(length):
    info.append(input())
for i in range(length):
    dic_info[i] = set(info[i][2:])
    dic_info[i].discard(',')

while stations:

    main_cover = set()
    number_of_station = None

    for station, regions in dic_info.items():
        cover = stations & regions

        if len(cover) > len(main_cover):
            number_of_station = station
            main_cover = cover

    stations -= main_cover
    res.append(number_of_station)

res.sort()
res = list(map(str, res))
print(','.join(res))


