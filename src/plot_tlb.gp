set title "Medición de TLB - Intel i5-8350U"
set xlabel "Número de Páginas"
set ylabel "Tiempo por Acceso (ns)"
set logscale x 2              # Escala logarítmica en eje X (base 2)
set grid                     # Mostrar cuadrícula
set term pngcairo size 800,600 enhanced font 'Arial,12'
set output "tlb_results.png"  # Nombre del archivo de salida

plot "results.csv" using 1:2 with linespoints title "TLB Access Time" \
     linecolor rgb "#0066cc" pointsize 1.5

