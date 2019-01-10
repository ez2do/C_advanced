import json

fin = open("data_routes.json", "r")
fout = open("route_data.txt")
data = json.loads(fin.read())

for bus_id, routes in data.items():
	fout.write(str(list(bus_id)[1:]))
	for route in routes:
		fout.write(" " + route)
	fout.write("\n")