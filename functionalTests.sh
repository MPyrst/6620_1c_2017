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

#1. No input
output="$($1 -i 2>&1)"
test_output="Option -i requires an argument."
expect "$output" "$test_output"


##2. No valid input
no_valid_inputs=("noValid" "elisa" "./build/elisa.txt ./build/alice.png")
for var in "${no_valid_inputs[@]}"
do
    output="$($1 -i ${var} 2>&1)"
    test_output='fatal: cannot open input file.'
    expect "$output" "$test_output"
done


##3. Help should be printed to stout (only first line verify)
help_options=("-h" "--help")
for var in "${help_options[@]}"
do
    output=$(printf "$($1 ${var})" | head -1)
    test_output='Usage:'
    expect "$output" "$test_output"
done

#4. Print version
version_options=("-V" "--version")
for var in "${version_options[@]}"
do
    output="$($1 ${var})"
    test_output='This is version 1.0 from tpo: Basic infrastructure.'
    expect "$output" "$test_output"
done

#5. Should verify file creation
test_file="testFile.txt"
echo "This is a test File">$test_file
output_file="./testOutput.txt"
output="$($1 -i $test_file -o $output_file 2>&1)"
if [ -f "$output_file" ];
then
   echo "Test OK"
else
   echo "Test FAILED: File $output_file does not exist"
fi

rm $test_file

#6. Should show usage if no valid option passed (only first line verify)
unknown_arguments=("-a" "-p" "-c")
for var in "${unknown_arguments[@]}"
do
    output="$($1 ${var} 2>&1)"
    test_output="Unknown argument '${var}'."
    expect "$output" "$test_output"
done

#7. No valid options
no_valid_characters=("--0" "--a1" "--59")
for var in "${no_valid_characters[@]}"
do
    output="$($1 ${var} 2>&1)"
    test_output="Unknown option character '\x0'."
    expect "$output" "$test_output"
done


#8. Empty file
touch $test_file
output="$($1 -i $test_file 2>&1)"
test_output="Empty input file."
expect "$output" "$test_output"
rm $test_file