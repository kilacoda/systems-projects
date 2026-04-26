#! /bin/bash

if ! [[ -x rgsh ]]; then
    echo "rgsh executable does not exist"
    exit 1
fi

../tester/run-tests.sh $*


