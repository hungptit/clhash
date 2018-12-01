#!/bin/bash
N=${1:-256}
mkdir -p data/string
mkdir -p data/numeric

printf "Maximum length: %d\n" $N

for idx in `seq 1 1 $N`;
do
	printf "len = %d\n" $idx
    LEN=$idx ./random_string --benchmark_format=json --benchmark_out="data/string/data_$idx.json" > /dev/null
    LEN=$idx ./random_data --benchmark_format=json --benchmark_out="data/numeric/data_$idx.json" > /dev/null 
done
./plot_benchmark_results.py data/data_ $N
