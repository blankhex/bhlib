#!/bin/sh
find . \( -iname "*.h" -o -iname "*.c" -o -iname "*.md" \) -exec sed -i .bak "s/[ ]*$//" {} \;
find . -iname "*.bak" -exec rm {} \;
