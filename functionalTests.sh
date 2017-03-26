#!/usr/bin/env bash

failed_tests_count=0

function expect {
if [ "$1" == "$2" ]
then
    echo "Test OK"
else
    failed_tests_count=$[$failed_tests_count+1]
    echo "Test FAILED: Expected '$1' to be equal to '$2'"
fi
}

#1. No valid input
no_valid_users=("" "noValid" "elisa" "./build/elisa.txt ./build/alice.png")
for var in "${no_valid_users[@]}"
do
    output="$($1 -i ${var})"
    test_output='Error: No se indicó archivo.'
    expect "$output" "$test_output"
done

#2. Help should be printed to stout (only first line verify)
help_options=("-h" "--help")
for var in "${help_options[@]}"
do
    output=$(printf "$($1 ${var})" | head -1)
    test_output='Usage:'
    expect "$output" "$test_output"
done

#3. Print version
version_options=("-V" "--version")
for var in "${version_options[@]}"
do
    output="$($1 ${var})"
    test_output='v1.0'
    expect "$output" "$test_output"
done

#4. Should verify file creation
output_file="./testOutput.txt"
output="$($1 -i ./testFile.txt -o $output_file)"
if [ -f "$output_file" ];
then
   echo "Test OK"
else
   echo "Test FAILED: File $output_file does not exist"
fi

#5. Should show usage if no valid option passed (only first line verify)
help_options=("-a" "-p" "--in" "")
for var in "${help_options[@]}"
do
    output=$(printf "$($1 ${var})" | head -1)
    test_output='Usage:'
    expect "$output" "$test_output"
done


