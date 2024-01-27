#!/bin/bash

set -eu

make -B

./server &
sleep 0.01
server_pid=$!

if [ "$#" -gt 0 ]; then
    gdb client
else
    ./client
fi

kill $server_pid

