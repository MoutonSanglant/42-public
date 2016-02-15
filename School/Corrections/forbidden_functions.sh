#!/bin/bash

grep -E "printf" $@
grep -E "malloc" $@
echo "done"
