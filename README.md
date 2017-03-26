# 6620_1c_2017

Informe: https://www.overleaf.com/8670630sfcdvtgcrqqx

<b>Aclaraciones TP0 ( ya validadas con el docente):</b>
<ul>
  <li>Como espacios en blanco usamos de separador "\t\n\r\r\n":
    <ul>
      <li>\t</li>
      <li>\n</li>
      <li>\r</li>
      <li>\r\n</li>
    </ul>
  </li>
  <li>Las palabras se pueden repetir.</li>
  <li>Ordenamiento case sensitive, usando strcmp().</li>
  <li>Se cuenta como caracter al inicio del archivo, por eso la primer palabra en los textos de /archivos queda al final después de ordenar.</li>
</ul>


#cMake based project

Build steps from root folder:

1- mkdir build && cd build

2- cmake ..

3- make

4- ./tp0

#Functional tests

Run steps:

./functionalTests.sh "$EXECUTABLE_PATH"
