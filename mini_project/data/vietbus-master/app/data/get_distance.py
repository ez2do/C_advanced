import json
from math import sin, cos, sqrt, atan2, radians

#############################################################################
# Data exploration
#
# - Manipulate data before build search tool
# - Clustering bus stops into routes
#############################################################################



#############################################################################
# Step 1: Fooling around with data
#############################################################################

def read_json():
    with open('data_stops.json', 'r') as f:
        bus_stop = json.load(f)
    return bus_stop

def dict_of(bus_stop):
    return {b['nid']:b['loc']['coordinates'] \
            for b in bus_stop}

def distance(x, y):
    "Geometry distance between 2 points: x = [lon, lat], y = [lon, lat]"
    # Earth radius
    R = 6373.0 
    # Convert to radian
    lon_x = radians(x[0])
    lat_x = radians(x[1])
    lon_y = radians(y[0])
    lat_y = radians(y[1])
    # Now calculate
    d_lon = lon_y - lon_x
    d_lat = lat_y - lat_x
    a = sin(d_lat / 2)**2 + cos(lat_x) * cos(lat_y) * sin(d_lon / 2)**2
    c = 2 * atan2(sqrt(a), sqrt(1 - a))
    return R * c

if __name__ == "__main__":
    "Uncomment this to exlore and save data, again"
    fout = open("distance.txt", "w")
    bus_stop = read_json()
    bus_dict = dict_of(bus_stop)
    bus_list = list()
    for b in bus_dict.items():
        print(b)
        b = list(b)
        bus_list.append(b)

    for i in range(0, len(bus_dict)):
        for j in range(0, len(bus_dict)):
            print(bus_list[i][0], bus_list[j][0], distance(bus_list[i][1], bus_list[j][1]))
            fout.write("%d %d %.3f\n" %(bus_list[i][0], bus_list[j][0], distance(bus_list[i][1], bus_list[j][1])))

    # show_all() # TOO MANY ERRORS, but what can we do?
    # save_routes()

