## Arrays in Shell [Back](./../Shell.md)

Arrays may be initialized with **variable[n]** notation, and to access elements with *curly bracket* notation like **$[variable[n]]**.

#### Initialization

```bash
# there is a convenient way of initializing an entire array
base64_charset=( {A..Z} {a..z} {0..9} + / = );

base64_charset=( [0]={A..Z} [1]={a..z} [2]={0..9} [3]=+ [4]=/ [5]== );
```

*Notice that: **declare -a** statement to an array declaration may speed up execution of subsequent operations on the array:*

```bash
declare -a bigOne=( /dev/* );           # All the files in /dev
declare -a bigTwo=( ${bigOne[@]} );
```

*Notice that: any variables can have array operations, even if they are not explicitly declared as arrays:*

```bash
#!/bin/bash

name=aleen
echo ${name[@]};        # => aleen
echo ${name[*]};        # => aleen
echo ${name[0]};        # => aleen
echo ${name[1]};        # => 

# array length
echo ${#name[@]};       # => 1
```

#### Operations

Add/Replace/Delete elements from an array:

```bash
#!/bin/bash

array=(zero one two three);

# add four to the array
array[4]=four;
echo ${array[@]};       # => zero one two three four

# replace three of the array
array[3]=replace_three;
echo ${array[@]};       # => zero one two replace_three four

# remove two from the array
unset array[2];
echo ${array[@]};       # => zero one replace_three four

# remove all elements
unset array;
echo ${array[@]};       # =>
```

If you want to read an element from an array, you can write like this:

```bash
#!/bin/bash

array=(zero one two three);

# get a specific element in an array
echo ${array[0]};       # => zero

# get a specific element and start at a specific position
echo ${array: 2};       # => ro
echo ${array[1]: 1};    # => ne
```

If you want to read some lengths like the length of the element or of the array:

```bash
#!/bin/bash

array=(zero one two three);

# get the length of the array
echo ${#array[*]};          # => 4
echo ${#array[@]};          # => 4

# get the length of the first item
echo ${#array};             # => 4
echo ${#array[0]};          # => 4
```

Trailing Substring Extraction:

```bash
#!/bin/bash

array=(zero one two three);

# read all elements
echo ${array[@]};           # => zero one two three
echo ${array[*]};           # => zero one two three
echo ${array[@]: 0};        # => zero one two three

# read elements started from the second
echo ${array[@]: 1};        # => one two three

# read first to third elemnt
echo ${array[@]: 0:2};      # => zer one two
```

Substring removals:

```bash
#!/bin/bash

array=(zero one two three four five five);

# removal of the shortest match from front of the string
echo ${array[@]#f*r};       # => zero one two three five five

# removal of the longest match from front of the string
echo ${array[@]##t*e};      # => zero one two four five five

# removal of the shortest match from front of the string
echo ${array[@]%h*e};       # => zero one two t four five five

# removal of the longest match from front of the string
echo ${array[@]%%t*e};      # => zero one two four five five
```

String replacement:

```bash
#!/bin/bash

array=(four fivefive);

# replace first occurence of substrings
echo ${array[@]/iv/XYZ};                    # => four fXYZefive

# replace all occurences of substrings
echo ${array[@]//iv/XYZ};                   # => four fXYZefXYZe

# delete first occurence of substrings
echo ${array[@]/iv/};                       # => four fefive

# delete all occurences of substrings
echo ${array[@]//iv/};                      # => four fefe

# replace front-end occurence of substrings
echo ${array[@]/#fi/XYZ};                   # => four XYZefive

# replace back-end occurence of substrings
echo ${array[@]/%ve/XYZ};                   # => four fivefiXYZ
```

#### Loading files to an array

```bash
#!/bin/bash

# read line from test.txt
# zero
# one
# two

# the first way
array=($(awk "{print $1}" "test.txt"));
echo $(array[*]);                           # => zero one two

# the second way
n=0;
while read a;
do
    array[$n]=$a;
    ((n++));
done<test.txt  
echo $(array[*]);                           # => zero one two

# the third way
n=1  
while ((n<=$(cat test.txt|wc -l)))  
do  
    array[$n]=$(cat test.txt|sed -n "${n}p"|awk '{print $1}');
    ((n+=1));
done
echo $(array[*]);                           # => zero one two
```

#### Empty arrays

```bash
#!/bin/bash

array0=( zero one two );
echo ${#array0[@]};                         # => 3

array1=("");
echo ${#array1[@]};                         # => 1

array2=();
echo ${#array2[@]};                         # => 0

array3=(  );
echo ${#array3[@]};                         # => 0
```

#### Array copying

```bash
#!/bin/bash

array_before=( zero one two three );

# Deep Copy
array_deep_copy=${array_before[@]};

echo Before: ${array_before[@]};            # => Before: zero one two three
echo Deep_Copy: ${array_deep_copy[@]};      # => Deep_Copy: zero one two three

array_before[4]=four;

echo Before: ${array_before[@]};            # => Before: zero one two three four
echo Deep_Copy: ${array_deep_copy[@]};      # => Deep_Copy: zero one two three
```

#### Array concatenation

```bash
#!/bin/bash

array_before=( zero one );
array_after=( two three );
concat=( ${array_before[@]} ${array_after[@]} );
echo ${concat[*]};                          # => zero one two three 
```