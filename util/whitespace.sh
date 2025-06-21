#!/bin/sh
find . \( -iname "*.h" -o -iname "*.c" -o -iname "*.md" -o -iname "*.pod" \) -exec sed -i.bak "s/[ ]*$//" {} \;
find . -iname "*.bak" -exec rm {} \;
