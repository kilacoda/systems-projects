#! /bin/bash

if ! [[ -x rgcat ]]; then
    echo "rgcat executable does not exist"
    exit 1
fi

../../tester/run-tests.sh $*


