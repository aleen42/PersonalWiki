## [原創] An automatically deployed GitBook project [Back](./../post.md)

This article mainly discusses how to create a automatically deployed GitBook project on your own, rather than relying on the original building at [gitbook.io](http://gitbook.io/). Before reading this article, you may have to know what is GitBook, and what it can do for you.

### Why GitBook?

GitBook is the earliest chosen tool to build a project for writing books or project documents for me. Before meeting this toolchain, I have already written this project, [PersonalWiki](https://github.com/aleen42/PersonalWiki), under GitHub to use documentations to record knowledge. With the simple writing language, Markdown, I can easily organize all knowledge into a book with splitting into chapters, according to domains, hobbies, etc. Since GitBook has been created in 2014, it has inspired me to convert my project into a page, where people can read in a more convenient way, especially with summary (the main structure of a GitBook project) to manage all chapters in PersonalWiki.

At that moment, GitBook has also released a desktop editing application to support writing and previewing Markdown files in local. That was absolute an awesome feature during its process of growths.

### Pain Spots

With writing more and more articles in this project, and creating some complicated plugins like [gitbook-treeview](https://github.com/aleen42/gitbook-treeview), or [gitbook-footer](https://github.com/aleen42/gitbook-footer), I have found that the building process of generating GitBook pages has become more and more time-consuming, especially in the case when I have to build all duplicated markdown files each time, most of which has not been modified.
 
 Another painful problem is that gitbook.io has always failed to build books if your one is too large to allocate enough memory.

That's why I try to make my project as an automatically deployed one.

Since I need to automatically deploy my rendered pages in GitHub, I have choosen to use [**Travis CI**](https://github.com/marketplace/travis-ci) to build and deploy when I have committed something. Hard time limitation? Travis CI has introduced a 50 minutes maximum job run time, which is also a hard limitation. With building almost 500 pages in this project, I have used at least 3 hours to run with GitBook client, which means that I have to shorten this time .  

### How To DO?

At first, I have to know why the process of building pages costs so much overhead. In usual, marking time is the most efficient way to find out the cause of this problem. During debugging, you may found that the most time of rendering a page has been cost in template parsing. After adding time marker in `gitbook/lib/templating/render.js`:
  
```js
var start = new Date();
return timing.measure(
    'template.render',

    Promise.nfcall(
        env.renderString.bind(env),
        content,
        context,
        {
            path: filePath
        }
    )
    .then(function(content) {
        console.log('rendering time: ', new Date() - start + 'ms');
        return TemplateOutput.create(content, blocks);
    })
);
```

The log has apparently shown that this process costs around 10 seconds in average to render one page each time. **TOO LONG**, but **NEEDED**! Why? Because most GitBook projects have used many types of plugins to extend features of its page like searching, sharing, indexing title, and so on. In all these plugins, the hook function like `page`, `page:before`, `page:after` will be called in this process. It means that some complicated plugins will always become the "Culprits" for its long processing.
 
Since I have no choice to work around this problem, I may need to reduce overhead of building in another way: Only build specific pages each time.
 
A project will always be updated with several files during each commit, and other files should be same with previous one before. Therefore, in order to shorten each building time, I may need to change GitBook.
 
#### Stop Cleaning Up
 
GitBook cleans up all files in output folder before building, so the first step is to change it to only clean pages that is not included in the summary within current commit.
 
*Note that: `gitbook` folder should not be considered*
 
```js
/** gitbook/lib/output/generateBook.js */
function generateBook(generator, book, options) {
    /** ... */
    return Promise(
        new Output({
         book: book,
         options: options,
         state: state,
         generator: generator.name
        })
    )
    
    /** Cleanup output folder */
    .then(function(output) {
        function walk(directory) {
            if (['gitbook'].indexOf(directory) > -1) {
                return;
            }
            
            var dirList = fs.readdirSync(directory);
            var isFolderDeleted = false;
            dirList.forEach(function (item) {
                if (isFolderDeleted) {
                    return;
                }
            
                var nextPath = path.resolve(directory, item);
                if (fs.statSync(nextPath).isDirectory()) {
                    walk(nextPath);
                } else if (/\.md$/i.test(item)) {
                    if (!book.getSummary().getByPath(path.relative(output.getRoot(), nextPath))) {
                        if (output.getRoot() === directory) {
                            /** delete file */
                            fs.unlinkSync(nextPath);
                        } else {
                            (function (dir) {
                                /** Delete folder when it does not exist in the book summary */
                                output.getLogger().debug.ln('cleanup folder: ', dir);
            
                                if (fs.existsSync(dir)) {
                                    fs.readdirSync(dir).forEach(function (file, index) {
                                        var curPath = path.resolve(dir, file);
                                        if (fs.statSync(curPath).isDirectory()) {
                                            /** recursive */
                                            deleteFolderRecursive(curPath);
                                        } else {
                                            /** delete file */
                                            fs.unlinkSync(curPath);
                                        }
                                    });
            
                                    fs.rmdirSync(dir);
                                }
                            })(directory);
            
                            isFolderDeleted = true;
                        }
                    }
                }
            });
        }
    
        !fs.existsSync(output.getRoot()) && fs.mkdirSync(output.getRoot());
        walk(output.getRoot());
        return output;
    })
 
    /** ... */
}
```
 
#### Copy Needed Assets

GitBook generally copies all files in your project into output folder during generating assets before building. As I do not clean up all files in that folder, and I don't want to update markdown files during this process, I need to change GitBook to copy what I want.
 
```js
/** gitbook/lib/output/generateAssets.js */
function generateAssets(generator, output) {
    /** ... */

    return Promise.reduce(assets, function(out, assetFile) {
        if (!/^style/gi.test(assetFile)) {
            /** only copy style files */
            return Promise(output);
        }
        
        /** ... */
    }, output);
}
```
 
#### Generate Needed Page

Now that should not all pages be generated, I may need to add a condition to tell GitBook tool what it should do when generating pages.
  
```js
/** gitbook/lib/output/generatePages.js */
function generatePages(generator, output) {
    /** ... */
    return Promise.reduce(pages, function(out, page) {
        var file = page.getFile();

        var filePath = file.getPath();
        var absoluteFilePath = path.join(out.getBook().getContentRoot(), filePath);
        var outputFilePath = path.join(out.getRoot(), filePath);

        /** check equality of coresponding markdown file in the output folder */
        if (fs.existsSync(outputFilePath)
            && fs.readFileSync(absoluteFilePath, { encoding: 'utf-8' }).replace(/\r|\n|\t/gi, '') === fs.readFileSync(outputFilePath, { encoding: 'utf-8' }).replace(/\r|\n|\t/gi, '')
            && fs.existsSync(path.join(out.getRoot(), fileToOutput(out, filePath)))
        ) {
            return Promise(out, page);
        }

        /** copy new markdown file to the output directory */
        var folderPath = path.dirname(outputFilePath);
        var checkParentFolder = function (folder) {
            var parentFolder = path.resolve(folder, '..')
            if (!fs.existsSync(parentFolder)) {
                checkParentFolder(parentFolder);
                fs.mkdirSync(parentFolder);
            }
        };

        if (!fs.existsSync(folderPath)) {
            checkParentFolder(folderPath);
            fs.mkdirSync(folderPath);
        }

        fs.createReadStream(absoluteFilePath).pipe(fs.createWriteStream(outputFilePath));

        /** ... */
    }, output);
}
```

At this moment, GitBook only builds modified pages, and I just need to configure Travis CI to build it up. In order to use custom GitBook to build, I have changed GitBook client tools to accept `local` as a validated version in `book.json`:
 
```json
{
    "gitbook": "local"
}
```

Here is the implement;

```js
/** gitbook-cli/lib/local.js */
function resolveVersion(condition) {
    if (condition === 'local') {
        var versionFolder = path.resolve(__dirname, '../../gitbook/');
        return Q({
            link: null,
            name: 'local',
            path: versionFolder,
            tag: 'latest',
            version: require(path.resolve(versionFolder, 'package.json')).version
        });
    } else {
        var versions = listVersions();
        var version = _.chain(versions)
            .find(function(v) {
                return tags.satisfies(v.name, condition);
            })
            .value();

        if (!version) return Q.reject(new Error('No version match: '+condition));
        return Q(version);
    }
}
```
 
Then I can just run the command `node gitbook-cli/bin/gitbook.js build` to start to build the book with custom GitBook tools. Remember to clone output folder into local path before running to build, and custom GitBook tools will build only when a new markdown file is added into summary, or an old markdown file is modified.

### Lunr

GitBook has used [**Lunr**](https://github.com/olivernn/lunr.js) as its searching engine to support searching words in a book. Here is the plugin, [plugin-lunr](https://github.com/GitbookIO/plugin-lunr) you can installed within your books. However, with same problems that I only want to build what I want, I have modified this plugin to support. More details can be checked on the Pull Request: https://github.com/GitbookIO/plugin-lunr/pull/5.
