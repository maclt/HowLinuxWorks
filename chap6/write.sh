#!/bin/bash

rm -f testfile

echo "$(date): start write (file creation)"
dd if=/dev/zero of=testfile bs=1M count=200
echo "$(date): end write"

rm -f testfile
