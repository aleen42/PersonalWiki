## [轉載] Code Review Best Practices [Back](./../post.md)

> - Author: [Kevin London](https://github.com/kevinlondon)
> - Origin: https://www.kevinlondon.com/2015/05/05/code-review-best-practices.html
> - Time: May, 5th, 2015

At my current company, we do a fair amount of code reviews. I had never done one before I started here so it was a new experience for me. I think it’s a good idea to crystalize some of the things I look for when I’m doing code reviews and talk about the best way I’ve found to approach them.

Briefly, a code review is a discussion between two or more developers about changes to the code to address an issue. Many articles talk about the benefits of code reviews, including knowledge sharing, code quality, and developer growth. I’ve found fewer that talk about what to look for in a review and how to discuss code under review.

### What I look for during a review

#### Architecture / Design

- [**Single Responsibility Principle**](http://en.wikipedia.org/wiki/Single_responsibility_principle): The idea that a class should have one-and-only-one responsibility. Harder than one might expect. I usually apply this to methods too. If we have to use “and” to finish describing what a method is capable of doing, it might be at the wrong level of abstraction.

- [**Open/Closed Principle**](http://en.wikipedia.org/wiki/Open/closed_principle): If the language is object-oriented, are the objects open for extension but closed for modification? What happens if we need to add another one of `x`?

- **Code duplication**: I go by the [“three strikes”](http://c2.com/cgi/wiki?ThreeStrikesAndYouRefactor) rule. If code is copied once, it’s usually okay although I don’t like it. If it’s copied again, it should be refactored so that the common functionality is split out.

- [**Squint-test offenses**](http://robertheaton.com/2014/06/20/code-review-without-your-eyes/): If I squint my eyes, does the shape of this code look identical to other shapes? Are there patterns that might indicate other problems in the code’s structure?

- **Code left in a better state than found**: If I’m changing an area of the code that’s messy, it’s tempting to add in a few lines and leave. I recommend going one step further and leaving the code nicer than it was found.

- **Potential bugs**: Are there off-by-one errors? Will the loops terminate in the way we expect? Will they terminate at all?

- **Error handling**: Are errors handled gracefully and explicitly where necessary? Have custom errors been added? If so, are they useful?

- **Efficiency**: If there’s an algorithm in the code, is it using an efficient implementation? For example, iterating over a list of keys in a dictionary is an inefficient way to locate a desired value.

#### Style

- **Method names**: Naming things is one of the hard problems in computer science. If a method is named `get_message_queue_name` and it is actually doing something completely different like sanitizing HTML from the input, then that’s an inaccurate method name. And probably a misleading function.

- **Variable names**: `foo` or `bar` are probably not useful names for data structures. `e` is similarly not useful when compared to `exception`. Be as verbose as you need (depending on the language). Expressive variable names make it easier to understand code when we have to revisit it later.

- **Function length**: My rule of thumb is that a function should be less than 20 or so lines. If I see a method above 50, I feel it’s best that it be cut into smaller pieces.

- **Class length**: I think classes should be under about 300 lines total and ideally less than 100. It’s likely that large classes can be split into separate objects, which makes it easier to understand what the class is supposed to do.

- **File length**: For Python files, I think around 1000 lines of code is about the most we should have in one file. Anything above that is a good sign that it should be split into smaller, more focused files. As the size of a file goes up, discoverability goes down.

- **Docstrings**: For complex methods or those with longer lists of arguments, is there a docstring explaining what each of the arguments does, if it’s not obvious?

- **Commented code**: Good idea to remove any commented out lines.

- **Number of method arguments**: For the methods and functions, do they have 3 or fewer arguments? Greater than 3 is probably a sign that it could be grouped in a different way.

- **Readability**: Is the code easy to understand? Do I have to pause frequently during the review to decipher it?

