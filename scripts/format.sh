#!/bin/bash
set -eu

readonly scriptpath=$0;
readonly scriptdir=$(dirname $0)
readonly srcdir=$scriptdir/../list_processing
readonly testdir=$scriptdir/../list_processing_testing

function main(){
    format_files $srcdir
    format_files $testdir
}

function format_file(){
    local inpfile=$1; shift
    local tmpfile=$(mktemp)
    clang-format --style=file $inpfile > $tmpfile
    mv $tmpfile $inpfile
    rm $tmpfile
}

function format_files(){
    local inpdir=$1; shift
    local source_files=$(find $inpdir -type f -name "*.hpp")
    for source_file in $source_files
    do
        if [[ -f "$source_file" ]]
        then
            format_file $source_file
        fi
    done
}


main
