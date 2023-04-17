#!/bin/bash
#Netanel Landesman 315873588

# Makes sure enough arguments are passed:
if [ "$#" -lt 2 ]; then
  echo "Not enough parameters"
  exit 1
fi

# Checks if we got the -r flag:
if [ "$#" -eq 3 ] && [ "$3" = "-r" ]; then
  flag=true
else
  flag=false
fi

folder_path="$1"
word="$2"

# We will delete all compiled files:
find "$folder_path" -maxdepth 1 -type f -name "*.out" -delete

# We will compile all files containing the given word:
c_files=$(grep -li $word $folder_path/*.c)
for file in $c_files; do
    gcc -w "$file" -o "${file%.*}.out"
done

# We will take care of the case where the -r flag was inserted:
if $flag; then
    # We will run through the entire contents of the folder:
    for file in $(ls $folder_path); do
        if [[ -d "${folder_path}/${file}/" ]]; then
            # If it is a folder we will run the program recursively:
            $($0 $folder_path/$file $word "-r")
        fi
    done
fi


#if $flag; then
#  find "$folder_path" -type f -name "*.out" -delete
#else
#  find "$folder_path" -maxdepth 1 -type f -name "*.out" -delete
#fi
