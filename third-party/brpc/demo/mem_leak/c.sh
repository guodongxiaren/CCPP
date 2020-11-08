#!/bin/bash
curl -d '{"message":"xxxxx"}' 127.0.0.1:8000/EchoService/Echo
for i in {1..100000}
do
    echo $i
    curl -d '{"message":"ok", "ids":["11111111111", "22222222222", "333333333333", "4444444444444", "55555555555"]}' 127.0.0.1:8000/EchoService/Echo &
    usleep 10000
done
