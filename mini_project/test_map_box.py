# Libraries used to grab the URL web stuff and import json 
import urllib.request, urllib.parse, urllib.error 
import json 
  
# Note that Google is increasingly requiring keys 
# for this API 
# service URL for Google Maps API 
key = '.json?access_token=pk.eyJ1IjoidHVhbmFuaGF2YWlsYWJsZSIsImEiOiJjanA0NG5rbDYwb3l3M3dvMXZ1MGVzNjVuIn0.Qy-B5HW1toEdJ056EYeAQQ'
serviceurl = 'https://api.mapbox.com/geocoding/v5/mapbox.places/'

fin = open("data_stops.json", "r");
fout1 = open("station_info.txt", "w");
fout2 = open("station_route.txt", "w");

station_info = json.loads(fin.read())
print(json.dumps(station_info, indent = 4))
for station in station_info:
    longtitude = station["loc"]["coordinates"][0]
    latitude = station["loc"]["coordinates"][1]
    nid = station["nid"]
    routes = station["route"]

    coordinates = str(longtitude) + ',' + str(latitude)
    url = serviceurl + coordinates + key

    print('Retrieving', url) 
  
    # urlopen() to get a handle 
    uh = urllib.request.urlopen(url) 
    # Read the whole document in UTF-8 
    data = uh.read().decode()
    print('Retrieved', len(data), 'characters') 
  
    # Load internal strings 
    try: 
        js = json.loads(data) 
    except: 
        js = None
    # If false then quit and print data 
    # if not js or 'status' not in js or js['status'] != 'OK': 
    #     print('==== Failure To Retrieve ====') 
    #     print(data) 
    #     continue
      
    # Call json dump and print it with an indent of four 
    #print(json.dumps(js, indent = 4)) 
      
    # Parsing and printing 
    place = js["features"][0]["text"]
    fout1.write(str(nid) + ' ' + place)
    fout1.write('\n')
    print(str(nid) + ' ' + place, end='')
    fout2.write(str(nid))
    for route in routes:
        print(' ' + str(route), end='')
        fout2.write(' ' + str(route))
    fout2.write('\n')
    print()