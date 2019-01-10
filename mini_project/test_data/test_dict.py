bus_dict = {1: [1, 1], 2:[2,2]}
bus_list = list()

for b in bus_dict.items():
	print(b)
	b = list(b)
	bus_list.append(b)

for i in range(0, len(bus_list)):
	for j in range(0, len(bus_list)):
		print(bus_list[i], bus_list[i][1], bus_list[j], bus_list[j][1])