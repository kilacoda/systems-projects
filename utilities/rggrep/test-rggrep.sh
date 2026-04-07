#! /bin/bash

if ! [[ -x rggrep ]]; then
    echo "rggrep executable does not exist"
    exit 1
fi

../../tester/run-tests.sh $*



