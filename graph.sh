echo "グラフ作成中..."
gnuplot <<EOF
set datafile separator ","
set title '各手法のマージソート 処理速度'
set xlabel 'データ個数[個]'
set ylabel '処理速度[sec]'
set terminal png font "MigMix 2M,14"
set output './margesort.png'
set logscale x
plot "./data/margesort.txt" using 1:2 with linespoints pt 5 title '逐次処理',\
"./data/margesort_over_thread.txt" using 1:2 with linespoints pt 5 title '並列化(overThread)',\
"./data/margesort_fit_thread.txt" using 1:2 with linespoints pt 5 title '並列化'
EOF
echo "./margesort.pngにグラフ作成完了!!!"
open ./margesort.png
