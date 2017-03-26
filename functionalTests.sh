#!/usr/bin/env bash

failed_tests_count=0

function expect {
if [ "$1" == "$2" ]
then
    echo "Test OK"
else
    failed_tests_count=$[$failed_tests_count+1]
    echo "Test FAIL: Expected '$1' to be equal to '$2'"
fi
}

#1. No paso ningun archivo
output="$($1)"
test_output='Error: No se indicó archivo.'
expect "$output" "$test_output"

#2. Paso un archivo inexistente
no_valid_users=("" "noValid" "elisa" "./build/elisa.txt ./build/alice.png")
for var in "${no_valid_users[@]}"
do
    output="$($1 ${var})"
    test_output='Error: No se indicó archivo.'
    expect "$output" "$test_output"
done



