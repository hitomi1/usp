import json

def count_keys(json_obj):
    count = 0
    
    if isinstance(json_obj, dict):
        count += len(json_obj)
        for key in json_obj:
            count += count_keys(json_obj[key])
    elif isinstance(json_obj, list):
        for item in json_obj:
            count += count_keys(item)
    
    return count

# Function to read JSON from a file and count keys
def count_keys_in_file(filename):
    with open(filename, 'r') as file:
        json_obj = json.load(file)
    return count_keys(json_obj)

# Specify the filename
filename = 'teste.json'

# Count the number of keys in the JSON file
num_keys = count_keys_in_file(filename)
print(f"The JSON object in {filename} has {num_keys} keys.")
