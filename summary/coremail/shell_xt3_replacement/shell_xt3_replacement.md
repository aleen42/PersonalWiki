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

### Tutorial

If you want to use this shell, create it or download it from 192.168.209.6:

```bash
lftp -e 'mget /qc/cm/customer/民生银行/CMCU-15182/package/*; bye' -u "mailtechgz\\<账号>,<密码>" "ftp://192.168.209.6/"
```

Then change the mod:

```bash
chmod +x install.sh
```

Create a file `files.txt` to specify which files to replace:

```bash
# files.txt

webapp/WEB-INF/lang/XT3/resource.js
webapp/WEB-INF/lang/XT3/resource_zh_CN.js
webapp/WEB-INF/lang/XT3/resource_zh_TW.js
webapp/WEB-INF/lang/common/pref/preference.properties
webapp/WEB-INF/lang/common/pref/preference_zh_CN.properties
webapp/WEB-INF/lang/common/pref/preference_zh_TW.properties
webapp/WEB-INF/tags/XT3/mainLayout.tag
webapp/WEB-INF/tags/common/listSettings.tag
webapp/WEB-INF/tags/common/prefDoPreference.tag
webapp/XT3/assets/*/css/var1.css
webapp/XT3/assets/*/images/loading.gif
webapp/XT3/assets/*/images/to_top.png
webapp/XT3/assets/*/js/ajax/list.js
webapp/XT3/mbox/searchlist.jsp
webapp/XT3/pref/preference.jsp
webapp/XT3/mbox/list.jsp
```

And then run the script:

```bash
./install.sh
```
