#!/usr/bin/env python
# coding=utf-8
import requests
import json
import random
import string

def rand_str():
    return ''.join(random.sample(string.ascii_letters + string.digits, 10))

def send_req():
    data = {}
    data['message'] = 'name'
    data['ids'] = []
    url = 'http://127.0.0.1:8000/EchoService/Echo' 
    while True:
        data['ids'].append(rand_str())
        data_str = json.dumps(data)
        resp = requests.get(url, data=data_str)
        print(resp.text)

if __name__ == '__main__':
    send_req()
