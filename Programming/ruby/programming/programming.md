## Programming [Back](./../ruby.md)

#### IO Operations

- To use `puts` to simply writes onto the screen whatever comes after it.
- To use `gets` to get words form the keyboard.
- To use `chomp` to take off the line break.

```rb
puts 1 + 2 

# same as the above one
puts 3

# output what input
puts gets

# comparition with chmop
let name = gets
puts 'Hello, ' + name + ', is that OK?'

let name = gets.chomp
puts 'Hello, ' + name + ', is that OK?'
```

#### Integers and Float

- Integers:

```rb
5
-205
99999999999999999999
0
```

- Float:

```rb
54.321
0.001
-205.3884
0.0
```

#### Letter

```rb
puts 'Hello, Aleen!'
```

- String Arithmetic

```rb
puts 'Hello, ' + 'Aleen!' # => Hello, Aleen!

puts 5 * 5 # => 20
puts '5' * 5 # => 55555
puts '5 * 5' # => 5 * 5
```

#### Variables and Assignments

```rb
let = 'variables'
puts let # => variables

# variables can point to any kind of object
let = 5 * (1 + 2)
puts let # => 15
```

#### Conversion

```rb
let1 = 2
let2 = '5'

puts let1 + let2 # It will go wrong
puts let1.to_s + let2 # => 25

puts '15'.to_f # => 15.0
puts '99.99'.to_i # => 99
```

#### Methods

```rb
# In Ruby, operators like +, * is just a shortcut way of .+, .*.
puts 'What\'s ' + 'up?'
puts 'What\'s '.+ 'up?'

# puts is really also a shortcut way
puts 'What?'
self.puts 'What?'

puts `pig` * 5
# Ruby cannot run puts 5 * `pigs`, because 5 cannot identify to copy 'pig' for 5 times.

# Some string methods
let1 = 'stop'
puts let1.reverse # => pots

let2 = 'Aleen'
puts 'There\'re ' + let2.length.to_s + ' characters in ' + let2

letters = 'aAbBcCdDeE'
puts letters.upcase # => AABBCCDDEE
puts letters.downcase # => aabbccddee
puts letters.swapcase # => AaBbCcDdEe
puts letters.capitalize # => Aabbccddee

let3 = 'Alien'
lineWidth = 50
puts let3.center(lineWidth)
puts let3.ljust(lineWidth)
puts let3.rjust(lineWidth)

# Random Methods
puts rand(101) # means to random from 0 to 100
puts srand(1776) # in the same rand serials => 24
puts srand(1776) # => 24

# Math Object
puts Math::PI
puts Math::E
puts Math.cos(Math::PI / 3) # => 0.5000000000000001
```

#### Flow Control

```rb
# Comparision Method
puts 1 > 2 # => false
puts 1 < 2 # => true

# Branching
if name == 'Aleen'
    puts 'Hello, ' + name + '!'
else
    puts 'Who are you, ' + name + '?'
end

# Looping
commands = gets.chomp
whild commands != 'exit'
    puts commands
    command = gets.chomp
end

# Logicial Operations
puts true and false # => false
puts true or false # => true
puts not(true) # => false
```
