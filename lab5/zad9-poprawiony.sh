#!/bin/bash

function print_permissions () {
    stat -c %A $1 | awk '{printf("%s: %s, %s, %s.\n%s: %s, %s, %s\n%s: %s, %s, %s\n", \
        "User", \
        substr($1, 2, 1) == "r" ? "can read" : "can'\''t read", \
        substr($1, 3, 1) == "w" ? "can write" : "can'\''t write", \
        substr($1, 4, 1) == "x" ? "can execute" : "can'\''t execute", \
        "Group", \
        substr($1, 5, 1) == "r" ? "can read" : "can'\''t read", \
        substr($1, 6, 1) == "w" ? "can write" : "can'\''t write", \
        substr($1, 7, 1) == "x" ? "can execute" : "can'\''t execute", \
        "Others", \
        substr($1, 8, 1) == "r"? "can read" : "can'\''t read", \
        substr($1, 9, 1) == "w"? "can write" : "can'\''t write", \
        substr($1, 10, 1) == "x" ? "can execute" : "can'\''t execute")}'
}

function print_content_size () {
    total=0
    if [ -d "$1" ]; then
        for file in "$1"/*; do
            if [ -e "$file" ]; then
                ((total+=$(print_content_size "$file")))
            fi
        done
    else
        ((total+=$(stat -c "%s" "$1")))
    fi
    echo $total
}

if [ $# -eq 1 ]; then
    path=$1
    echo "Path: $path"

    if [ -e $path ]; then

        if [ -d $path ]; then
            echo "This is a directory."
        else
            echo "This is a file."
        fi

        print_permissions "$path"

        echo "Owner: `stat -c "%G" $path`"

        echo "Last modification date: `date -r $path +"%d.%m.%Y"`"

        echo "Calculating total size, this make take a while..."
        print_content_size $path
    else
        echo "Error: path doesn't exist."
    fi

else
    echo "Error: must provide 1 arg (filepath)"
fi

exit 0