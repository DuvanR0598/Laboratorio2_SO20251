#!/bin/bash
echo "Pages,Time(ns)" > results.csv  #Crea el encabezado del archivo CSV con dos columnas: "Pages" y "Time(ns)"
for pages in 1 2 4 8 16 32 64 128 256 512 1024; do #iterar sobre diferentes tamaños de páginas (potencias de 2, para detectar saltos en el TLB).
    ./tlb $pages 1000000 >> results.csv #Ejecutar el programa tlb con el número de páginas y 1000000 accesos, y agregar la salida al archivo CSV
done