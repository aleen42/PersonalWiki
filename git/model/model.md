## A successful Git branching model	[Back](./../git.md)

- <img src="./nvie-small@2x.jpg">
- By **Vincent Driessen**
- on Tuesday, January 05, 2010

- [**中文翻譯**](./../../translation/successful_git_branching/successful_git_branching.md)

In this post I present the development model that I've introduced for all of my projects (both at work and private) about a year ago, and which has turned out to be very successful. I've been meaning to write about it for a while now, but I've never really found the time to do so thoroughly, until now. I won't talk about any of the projects' details, merely about the branching strategy and release management.

<img src="./git-model@2x.png">

It focuses around Git as the tool for the versioning of all of our source code. (By the way, if you're interested in Git, our company GitPrime provides some awesome realtime data analytics on software engineering performance.)

### Why git?

For a thorough discussion on the pros and cons of Git compared to centralized source code control systems, [see](http://whygitisbetterthanx.com/) the [web](http://git.or.cz/gitwiki/GitSvnComparsion). There are plenty of flame wars going on there. As a developer, I prefer Git above all other tools around today. Git really changed the way developers think of merging and branching. From the classic CVS/Subversion world I came from, merging/branching has always been considered a bit scary ("beware of merge conflicts, they bite you!") and something you only do every once in a while.

But with Git, these actions are extremely cheap and simple, and they are considered one of the core parts of your daily workflow, really. For example, in CVS/Subversion books, branching and merging is first discussed in the later chapters (for advanced users), while in every Git book, it’s already covered in chapter 3 (basics).

As a consequence of its simplicity and repetitive nature, branching and merging are no longer something to be afraid of. Version control tools are supposed to assist in branching/merging more than anything else.

Enough about the tools, let’s head onto the development model. The model that I’m going to present here is essentially no more than a set of procedures that every team member has to follow in order to come to a managed software development process.

<a href="http://aleen42.github.io/" target="_blank" ><img src="./../../pic/tail.gif"></a>
