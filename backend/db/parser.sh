if [ $# -ne 2 ]; then
  echo "Usage: $0 input_directory output_file"
  exit 1
fi

# Merge all JSON files in the directory
echo "{" > $2
echo "\"courses\": [" >> $2
first=true
for file in $1/*.json
do
  if [ "$first" = true ]; then
    first=false
  else
    echo "," >> $2
  fi
  sed '1d;$d' $file >> $2
done
echo "]" >> $2
echo "}" >> $2