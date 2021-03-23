cp /share/ex_data/ex3/{birthdays.txt,story.txt} ./
grep -E '^[A-Z][a-z]{,3}:' birthdays.txt > names1-4.txt
grep '19[45][0-9]$' birthdays.txt | sed -r s'/(.*): (.*)/\1/' | sort -k1,1 > years40-59.txt
grep -E '[A-Z][a-z]*: July [1-9][0-9]?, [1-9][0-9][0-9][0-9]' birthdays.txt | sort -k3,3n | sed -r 's/(.*): (.*) (.*), ([0-9]{2})([0-9]{2})/\1 was born on \3\/7\/\5/' > birthdays-july.txt
echo story.txt has\ `grep '[0-9]' story.txt | tr [[:punct:]][[:space:]] '\n' | grep '^[1-9][0-9]*$' | wc -l` numbers
cat story.txt | tr [A-Z] [a-z] | tr [[:space:]][[:punct:]] '\n' | grep '^[a-z][a-z]*$' | sort | uniq -c | grep -E '.*[1-9][0-9]+.*' | tail -n1 | sed -r 's/(.*) ([1-9][0-9]+) (.*)/Word \"\3\" appears \2 times in story.txt/'
