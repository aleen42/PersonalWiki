## Shell for replacing files of XT3	[Back](./../coremail.md)

This shell will automatically check the local version and replace new files of XT3, with modifying them with specific version.

### Shell

```bash
#!/bin/bash

GLOBIGNORE="*"

# backup
if [ ! -d webapp_bak ]; then
    echo "Baking Up"
    cp -r webapp webapp_bak
fi

# convert CRLF to LF
sed -i 's/\r$//' files.txt

# unzip files from the package
echo "Unzip Files"

file_list=""

n=0
while read file;
do
    files[$n]=$file
    file_list="$file_list $file"
    ((n++))
done<files.txt
files[$n]=$file
file_list="$file_list $file"

`which unzip` -o wmweb.zip ${file_list} -d wmweb

# find out the largest number of versions in the current environment
target=`ls ./webapp/XT3/assets/ -lt | sed -n '2, 1p' | awk '{print $NF}'`

# find out the largest number of versions in the installation package
source=`ls ./wmweb/webapp/XT3/assets/ -lt | sed -n '2, 1p' | awk '{print $NF}'`

# modify the version of sources
echo "Modify Version"

echo -e "\t[log] Current Version: $source"
echo -e "\t[log] Deployment Version: $target"

modified_list=($(grep $source -rl ./wmweb/))

for file in ${modified_list[@]};do
    echo -e "\t[log] $file"
done

sed -i "s/$source\b/$target/g" `grep $source -rl ./wmweb/`

# installation
echo "Install"

for file in ${files[@]};do
    source_path="wmweb/$file"
    GLOBIGNORE=""
    target_path=`dirname "$file"`
    echo -e "\t[log] mv $source_path $target_path/"
    mv $source_path $target_path/
done

# clear
echo "Clear Files"

rm -r wmweb
rm wmweb.zip
rm files.txt
rm install.sh

echo "Completed"

```
