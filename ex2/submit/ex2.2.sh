cp /share/ex_data/ex2/story.txt ./
head -n 11 story.txt | tr "aeiou" "AEIOU" > story2.txt
tail -n+900 story.txt | head -n100 | tr "0-9" "#" | tr -s "#" > story3.txt
cat story.txt | tr -s [:space:] " " | tr "\n" " " | tr -s "." "\n" | tr -s "\n" | tail -n101 > story4.txt
cat story.txt | tr -s [:space:] " " | tr -s [:punct:] " " | tr " " "\n" | sort | uniq | wc -l
