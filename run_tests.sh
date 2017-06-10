#!/bin/sh

mytest ()
{
    "$@"
    local status=$?
    if [ $status -ne 0 ]; then
        echo "error with $@" >&2
    fi
    return $status
}

./sch DRR ./tests/inp1.txt out.txt 1 2
mytest cmp -s out.txt ./tests/out1_DRR_w1_q2.txt

./sch DRR ./tests/inp1.txt out.txt 3 2
mytest cmp -s out.txt ./tests/out1_DRR_w3_q2.txt

./sch DRR ./tests/inp2.txt out.txt 1 10
mytest cmp -s out.txt ./tests/out2_DRR_w1_q10.txt

./sch DRR ./tests/inp2.txt out.txt 8 10
mytest cmp -s out.txt ./tests/out2_DRR_w8_q10.txt

./sch DRR ./tests/inp3.txt out.txt 1 40
mytest cmp -s out.txt ./tests/out3_DRR_w1_q40.txt

./sch DRR ./tests/inp3.txt out.txt 30 40
mytest cmp -s out.txt ./tests/out3_DRR_w30_q40.txt
