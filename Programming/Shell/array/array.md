## Arrays in Shell [Back](./../Shell.md)

Arrays may be initialized with **variable[n]** notation, and to access elements with *curly bracket* notation like **$[variable[n]]**.

#### Initialization

```bash
# there is a convenient way of initializing an entire array
base64_charset=( {A..Z} {a..z} {0..9} + / = )
```

*Notice that: any variables can have array operations, even if they are not explicitly declared as arrays:*

```bash
name=aleen
echo ${name[@]} # => aleen
echo ${name[*]} # => aleen
echo ${name[0]} # => aleen
echo ${name[1]} # => 

echo ${#name[@]} # => 1
```

