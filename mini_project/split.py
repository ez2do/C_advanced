f1 = open("station_name.txt", "r")
fin = open("new_distance.txt", "r")
fout = open("mordern_distance.txt", "w")
id_dict = dict()

i = 1
for line in f1:
	words = line.split()
	id_dict[words[0]] = str(i)
	i = i + 1

for line in fin:
	words = line.split()
	fout.write(id_dict[words[0]] + ' ' + id_dict[words[1]] + ' ' + words[2] + '\n')

