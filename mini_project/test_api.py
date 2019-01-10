# Libraries used to grab the URL web stuff and import json 
import urllib.request, urllib.parse, urllib.error 
import json 
  
# Note that Google is increasingly requiring keys 
# for this API 
# service URL for Google Maps API 
key = '&language=en&key=AIzaSyD6Br203E374t3n4xXbKaCNGW8DOql3iMY'
serviceurl = 'https://maps.googleapis.com/maps/api/geocode/json?'
  
while True: 
    address = input('Enter location: ') 
    if len(address) < 1: break
      
    # Concatenate the serviceurl and urllib.parse.urlencode 
    # which give a dictonary of address equal and this bit  
    # right here 
    url = serviceurl + urllib.parse.urlencode( 
        {'address': address}) + key

  
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
    if not js or 'status' not in js or js['status'] != 'OK': 
        print('==== Failure To Retrieve ====') 
        print(data) 
        continue
      
    # Call json dump and print it with an indent of four 
    print(json.dumps(js, indent = 4)) 
      
    # Parsing and printing 
    lat = js["results"][0]["geometry"]["location"]["lat"] 
    lng = js["results"][0]["geometry"]["location"]["lng"] 
    print('lat', lat, 'lng', lng) 
    location = js['results'][0]['formatted_address'] 
    print(location) 