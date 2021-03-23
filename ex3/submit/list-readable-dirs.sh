ls -l $dir | grep -E '^d' | sed -r 's/(.*) (.*)$/\2 /' | tr -d '\n' | sed -r 's/(.*)/\1\n/'
