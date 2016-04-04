#!/bin/bash

nm -u $@ | grep -E "printf"

#grep -E "printf" $@
#grep -E "malloc" $@
#echo "done"
