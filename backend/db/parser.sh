if [ $# -ne 2 ]; then
  echo "Usage: $0 input_directory output_file"
  exit 1
fi

# Merge all JSON files in the directory
echo "[" > $2
for file in $1/*.json
do
  sed 's/^\[//;s/\]$//' $file >> $2
  echo "," >> $2
done
sed -i '$d' $2
echo "]" >> $2