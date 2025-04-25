#!/bin/sh


# Check args
if [ $# -lt 1 ]; then
    echo "error: specify file"
    exit 1
fi

if [ ! -f $1 ]; then
    echo "error: file '$1' not found"
    exit 1
fi

echo "Checking file" $1


# Message about trailing space before EOL
eolerrors=$(grep -n "\s$" "$1" | cut -f1 -d: | while read -r line; do
    if [ "$line" ]; then
        echo "$1:$line: error: whitepace before EOL"
    fi
done)


# Message about non-empty last-line
linecount=$(($(wc -l "$1" | xargs | cut -f1 -d " ") + 1))
lastline=$(tail -n "+$linecount" $1)

llerrors=$(if [ "$lastline" ]; then
    echo "$1:$linecount: error: no EOL before EOF"
fi)


# Compute ranges of new lines
count=0; start=0; next=0
lines="$(grep -n "^$" "$1" | cut -f1 -d:)
0"
ranges=$(echo "$lines" | while read -r line; do
    if [ "$line" ]; then
        if [ $start -eq 0 ]; then
            start="$line"; count=1; next=$(($start + 1))
        elif [ "$line" -ne $next ]; then
            echo $start $count
            start="$line"; count=1; next=$(($start + 1))
        else
            count=$(($count + 1)); next=$(($next + 1))
        fi
    fi
done)


# Check that we have no more then 3 EOLs in the row
fewerrors=$(echo "$ranges" | while read -r line; do
    number=$(echo $line | cut -f1 -d " ")
    size=$(echo $line | cut -f2 -d " ")
    if [ $size -gt 2 ]; then
        echo "$1:$number: error: too many EOLs"
    fi
done)

# Print out errors
code=0
if [ "$eolerrors" ]; then
    echo "$eolerrors" 1>&2
    code=1
fi

if [ "$llerrors" ]; then
    echo "$llerrors" 1>&2
    code=1
fi

if [ "$fewerrors" ]; then
    echo "$fewerrors" 1>&2
    code=1
fi

exit $code
