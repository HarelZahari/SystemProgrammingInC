cp /share/ex_data/ex2/birthdays.txt ./
cat birthdays.txt | sort -k4,4r -k1,1 > birthdays_sorted.txt
cat birthdays.txt | cut -f1 -d"," | tr -d ":" | tr " " "\t" > birthdays_reformatted.txt
cat birthdays.txt | sort -k2,2 | cut -f2 -d" " | cut -c-3 | tr [a-z] [A-Z] | uniq -c >> birthdays_reformatted.txt
cut -f4 -d" " birthdays.txt | cut -c3-4 |paste -d" " birthdays.txt - | cut -f1,2,3,5 -d" " > birthdays_2digit-yr.txt
