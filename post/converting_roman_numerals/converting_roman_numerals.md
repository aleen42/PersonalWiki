## [轉載] ALGORITHM SUNDAYS: CONVERTING ROMAN NUMERALS [Back](./../post.md)

> - Author: [Tobias Guse](https://github.com/tbgse)
- Origin: http://www.selftaughtjs.com/algorithm-sundays-converting-roman-numerals/
- Time: Mar, 13rd, 2016

After looking at [Caesars very own encryption cipher](http://www.selftaughtjs.com/algorithm-sundays-converting-roman-numerals/) last Sunday, Roman numerals were the obvious choice for today's post. Roman numerals were the standard way of writing numbers for over a thousand years in our history. Even after the decline of the Roman Empire, they remained in use for many centuries. Eventually they were replaced by the Arabic numbers that we are still using today. Converting Roman numerals to their more legible decimal counterparts is a beginner-friendly algorithm challenge you will find on many exercise websites. Do you remember how to count to 1000 using Roman numerals? Just in case that it's been a while since you've encountered Medieval Latin literature, have a look at the table of numbers below.

Decimal|1|5|10|50|100|500|1000
:-----:|-|-|--|--|---|---|----
Roman|I|V|X|L|C|D|M

Interesting. As you can see, we have a limited set of symbols here. We can create the numbers to fill the spaces by chaining multiple symbols. Let's have a look at the numbers 1-10.

Decimal|1|2|3|4|5|6|7|8|9|10
:-----:|-|-|-|-|-|-|-|-|-|--
Roman|I|II|III|IV|V|VI|VII|VIII|IX|X

Let's take a look at two special cases 4 and 9. What happens here is that instead of adding values, we are subtracting the first value from the second. So the Roman numeral at 4 is effectively `5-1`. At 9 we are looking at `10-1`. In every other case, we are simply adding up all the numbers to build the sum. So VII is 5+1+1 = 7. As a rule of thumb, you should keep in mind that no letter should be repeated more than 3 times. If you are repeating it more than that, you should skip to the next letter and calculate the number using subtraction instead. Let's have a look at some examples