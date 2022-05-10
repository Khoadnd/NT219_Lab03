#!/bin/bash

avg_time() { 
    local -i n=$1
    local foo real sys user
    shift
    (($# > 0)) || return;
    { read foo real; read foo user; read foo sys ;} < <(
        { time -p for((;n--;)){ "$@" &>/dev/null ;} ;} 2>&1
    )
    printf "%.5f\n" $(
        bc -l <<<"$real/$n;" )
}

cd ..

echo "Running test... sign 100 time"
avg_time 100 $(./main message.txt priv.pem sign)

echo "Running test... verify 100 time"
avg_time 100 $(./main message.txt signature.bin pub.pem verify)