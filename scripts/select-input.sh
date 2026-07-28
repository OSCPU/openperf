size="test train ref huge"
for s in $size; do
  if [ "$s" == "$2" ]; then
    sed -i -e "s/^#\(.*$s.*\)/\1/" $1      # remove '#' if exists
  else
    sed -i -e "s/^\([^#].*$s.*\)/#\1/" $1  # add '#' if not exists
  fi
done
