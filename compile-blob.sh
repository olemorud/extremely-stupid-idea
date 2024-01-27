#!/bin/sh

set -eu

for cmd in ld as clang-format; do
    command -v $cmd &>/dev/null || (echo command $cmd not found; exit 1 )
done

if [ "$#" -ne "1" ]; then
    printf "Usage: %s <asm file>" $0 >/dev/stderr
    exit 1
fi

as_output=$(mktemp)
ld_output=$(mktemp)
cleanup() {
    rm $as_output
    rm $ld_output
}
trap cleanup EXIT

as $1 -o $as_output
ld --oformat binary $as_output -o $ld_output

(
    echo '#pragma once'
    echo 'static const unsigned char binary_data[] = {'
    tail $ld_output -c +4097 | hexdump -v --format='"" 1/1 "0x%02x,"'
    echo '};'
) | clang-format
