#!/bin/sh
find . \( -iname "*.h" -o -iname "*.c" \) -exec sed -i .bak "s/[ ]*$//" {} \;
find . -iname "*.bak" -exec rm {} \;
