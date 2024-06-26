# Track Progress

# If currProg == lastProg then we are done
# else:
#   call updateProgApi

## API Part

import requests
import json
import argparse
import os
import subprocess
import configparser
import progress as prog

def get_timestamp() -> int:
    return int(subprocess.check_output(['git', 'show', '-s', '--format=%ct']).decode('ascii').rstrip())

def get_commit_hash() -> str:
    return subprocess.check_output(['git', 'rev-parse', 'HEAD']).decode('ascii').strip()

def get_api_post_url() -> str:
    url = domain + "/data/chameleontwist/jp/"
    return url

def push_data_to_api(data) -> None:
    url = get_api_post_url()
    r = requests.post(url, json=data)
    r.raise_for_status()

def check_git_hash() -> bool:
    currHash = get_commit_hash()
    
parser = argparse.ArgumentParser(description="Upload progress to API")
parser.add_argument("--api_key", help="API key for progress.deco.mp")
api_key = parser.parse_args().api_key

domain = "https://progress.deco.mp"

# Should be generated by progress chart
matching_funcs, all_funcs, funcs_matching_ratio, matching_size, total_size, matching_ratio = prog.getProgressData()

# data structure
entries = []
entries.append({
    "timestamp": get_timestamp(),
    "git_hash": get_commit_hash(),
    "categories": {
        "default": {
            "funcs": matching_funcs,
            "funcs/total": all_funcs,
            "bytes": matching_size,
            "bytes/total": total_size,
        },
    },
})

# Data to send to API
end_data = {
    "api_key": api_key,
    "entries": entries,
}

# get previous posts and check git hash
r = requests.get(domain+"/data/chameleontwist/jp/default/")
res = r.json()
prev_hash = res["chameleontwist"]["jp"]["default"][0]["git_hash"]
prev_matching_funcs = res["chameleontwist"]["jp"]["default"][0]["measures"]["funcs"]
prev_matching_size = res["chameleontwist"]["jp"]["default"][0]["measures"]["bytes"]

if prev_hash != get_commit_hash():
    if prev_matching_funcs < matching_funcs or prev_matching_size < matching_size:
        print("Change in progress... Pushing to API")
        push_data_to_api(end_data)
    else:
        print("No change in progress")
else:
    print("Current push already in API")
    