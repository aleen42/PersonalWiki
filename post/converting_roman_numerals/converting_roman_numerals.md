## [轉載] ALGORITHM SUNDAYS: CONVERTING ROMAN NUMERALS [Back](./../post.md)

> - Author: [Tobias Guse](https://github.com/tbgse)
> - Origin: http://www.selftaughtjs.com/algorithm-sundays-converting-roman-numerals/
> - Time: Mar, 13rd, 2016

After looking at [Caesars very own encryption cipher](http://www.selftaughtjs.com/algorithm-sundays-converting-roman-numerals/) last Sunday, Roman numerals were the obvious choice for today's post. Roman numerals were the standard way of writing numbers for over a thousand years in our history. Even after the decline of the Roman Empire, they remained in use for many centuries. Eventually they were replaced by the Arabic numbers that we are still using today. Converting Roman numerals to their more legible decimal counterparts is a beginner-friendly algorithm challenge you will find on many exercise websites. Do you remember how to count to 1000 using Roman numerals? Just in case that it's been a while since you've encountered Medieval Latin literature, have a look at the table of numbers below.

Decimal|1|5|10|50|100|500|1000
:-----:|-|-|--|--|---|---|----
Roman|I|V|X|L|C|D|M

Interesting. As you can see, we have a limited set of symbols here. We can create the numbers to fill the spaces by chaining multiple symbols. Let's have a look at the numbers 1-10.

Decimal|1|2|3|4|5|6|7|8|9|10
:-----:|-|-|-|-|-|-|-|-|-|--
Roman|I|II|III|IV|V|VI|VII|VIII|IX|X

Let's take a look at two special cases 4 and 9. What happens here is that instead of adding values, we are subtracting the first value from the second. So the Roman numeral at 4 is effectively `5-1`. At 9 we are looking at `10-1`. In every other case, we are simply adding up all the numbers to build the sum. So `VII` is `5+1+1 = 7`. As a rule of thumb, you should keep in mind that no letter should be repeated more than 3 times. If you are repeating it more than that, you should skip to the next letter and calculate the number using subtraction instead. Let's have a look at some examples

Roman|LXVI|DXXX|XCVII|XXXIX|XIX
:---:|----|----|-----|-----|---
Calculation|50+10+5+1|500+10+10+10|100-10+5+1+1|10+10+10+10-1|10+10-1
Result|66|530|97|39|19

The biggest challenge is to know when to add and when to subtract. I always try to look out for a pattern where a lower number is placed before a higher number. Take for example `XCVII`. `X` is smaller than `C`, so we need to calculate `C - X` instead of `X + C`.

Why do I give you such a lengthy introduction to this topic? I strongly believe that it's important to first really understand the pattern behind the problem you are trying to solve. If you try to write a Roman numeral converter without having recognized the patterns behind these numbers, you'll (most likely) end up writing code without logic. Long, buggy and unstructured code.

With that being said, let's write some code!

### CONVERTING ROMAN NUMERALS

For the first part of our algorithm, we will take a decimal number and convert it into a Roman number.

```js
function toRoman(num) { 

}

toRoman(24);
```

First, our algorithm needs to know about the different Roman numerals. Let's add two arrays. One for the Roman numbers, one for or decimal numbers.

```js
function toRoman(num) {  
    var decimal = [1000, 500, 100, 50, 10, 5, 1];
    var roman = ['M', 'D', 'C', 'L', 'X', 'V', 'I'];
}

toRoman(24);  
```

The idea behind our next step is simple. Let's take a number like 8 for example. We first check if it's dividable by 1000, 500 then 100 etc. - Once we find a value that is smaller or equal to our number, we will push the matching letter to our solution and subtract this value from our number. In the case of 8, it'd be `8-5 = 3`. Then we will again look for a match. The only number that matches our remainder of 3 now is I. We will once again add I to our result, subtract it from our number (3-1) and repeat the whole process until we reach 0. This will cause our algorithm to have pushed 1x `V` and 3x `I`. Combined the result will be `VIII`.

Our algorithm could look something like this:

```js
function toRoman(num) {  
    var result = '';
    var decimal = [1000, 500, 100, 50, 10, 5, 1];
    var roman = ['M', 'D', 'C', 'L', 'X', 'V', 'I'];
    
    for (var i = 0; i <= decimal.length; i++) {
        // looping over every element of our arrays
        while (num % decimal[i] < num) {   
            // keep trying the same number until we need to move to a smaller one     
            result += roman[i];
            // add the matching roman number to our result string
            num -= decimal[i];
            // subtract the decimal value of the roman number from our number
        }
    }
    
    return result;
}

toRoman(8); 
```

Now this works fine for numbers that only need an addition. However, this algorithm breaks on numbers that require subtraction.

```js
toRoman(8) // returns 'VIII'  
toRoman(5) // returns 'V'  
toRoman(3) // returns 'III'  
toRoman(4) // returns 'IIII'  
toRoman(9) // returns 'VIIII'
```

As our algorithm isn't as smart as we are, we need to fix this by adding in special cases for 4, 9, 40, 90 etc. to our arrays.

```js
function toRoman(num) {  
    var result = '';
    var decimal = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1];
    var roman = ['M', 'CM', 'D', 'CD', 'C', 'XC', 'L', 'XL', 'X', 'IX', 'V', 'IV', 'I'];
    
    for (var i = 0; i <= decimal.length; i++) {
        // looping over every element of our arrays
        while (num % decimal[i] < num) {   
            // keep trying the same number until it won't fit anymore      
            result += roman[i];
            // add the matching roman number to our result string
            num -= decimal[i];
            // remove the decimal value of the roman number from our number
        }
    }
    
    return result;
}
```

Let's give it a few final test runs.

```js
toRoman(123); //returns "CXXIII"  
toRoman(3290); // returns "MMMCCXC"  
toRoman(777); // returns "DCCLXXVII"  
toRoman(949); // returns "CMXLIX"  
toRoman(2000); // returns "MM"  
```

So far so good. Now let's take care of the second part - converting Roman numerals to decimal numbers. As we have our logic in place, reversing this process is not too hard.

```js
function fromRoman(str) {  
    var result = 0;
    // the result is now a number, not a string
    var decimal = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1];
    var roman = ['M', 'CM', 'D', 'CD', 'C', 'XC', 'L', 'XL', 'X', 'IX', 'V', 'IV', 'I'];
    
    for (var i = 0; i <= decimal.length; i++) {
        while (str.indexOf(roman[i]) === 0){
            //checking for the first characters in the string
            result += decimal[i];
            //adding the decimal value to our result counter
            str = str.replace(roman[i], '');
            //remove the matched Roman letter from the beginning
        }
    }
    
    return result;
}
```

Some test strings

```js
fromRoman("LXXXVII"); // returns 87  
fromRoman("XLIII"); //  returns 43  
fromRoman("XXII"); // returns 22  
fromRoman("DCCVII"); // returns 707  
fromRoman("LXIX"); // returns 69  
```

To wrap everything up, let's look at both functions together:

```js
function toRoman(num) {  
    var result = '';
    var decimal = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1];
    var roman = ['M', 'CM', 'D', 'CD', 'C', 'XC', 'L', 'XL', 'X', 'IX', 'V', 'IV', 'I'];
    
    for (var i = 0; i <= decimal.length; i++) {
        while (num % decimal[i] < num) {     
            result += roman[i];
            num -= decimal[i];
        }
    }
    
    return result;
}

function fromRoman(str) {  
    var result = 0;
    // the result is now a number, not a string
    var decimal = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1];
    var roman = ['M', 'CM', 'D', 'CD', 'C', 'XC', 'L', 'XL', 'X', 'IX', 'V', 'IV', 'I'];
    
    for (var i = 0; i <= decimal.length; i++) {
        while (str.indexOf(roman[i]) === 0){
            result += decimal[i];
            str = str.replace(roman[i], '');
        }
    }
    
    return result;
}
```

Please keep in mind that there are many ways to solve a problem and this solution is only one of many. There might be more efficient, beautiful or crafty solutions out there. If you have suggestions on how to improve this code, let me know in the comments. Until then, happy coding and enjoy the rest of your weekend.
