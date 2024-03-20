#!/bin/sh
find . \( -iname "*.h" -o -iname "*.c" \) -exec sed -i "s/[ \t]*$//" {} \;