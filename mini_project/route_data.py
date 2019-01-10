import json

fin = open("data_routes.json", "r")
fout = open("route_data.txt", "w")
data = json.loads(fin.read())

for bus_id, routes in data.items():
	fout.write("".join(list(bus_id)[1:]))
	for route in routes:
		fout.write(" " + str(route))
	fout.write("\n")