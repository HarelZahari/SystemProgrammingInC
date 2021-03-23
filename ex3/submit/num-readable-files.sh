ls -l $dir | cut -f1 -d" " | grep -E '^[^d].*r.*r.*r' | wc -l
