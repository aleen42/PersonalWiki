## Something about parsing JSON [Back](./qa.md)

As we all know, if there is data returned with JSON formatting when doing Ajax requests, we can use `JSON.parse()` or `$.parseJSON()` to parse it into a JavaScript object, so that we can easily handle it. However, there are some cases we may need to pay attention to.

Originally, if the request header `Content-Type` is set with `text/plain` or `text/html`, there is no problem with using `JSON.parse()`. However, when we set it with `application/json` or `text/x-json`, do not use `JSON.parse()` to parse the returned data, as it throws an error.

Despite of this case, we should also focus on using a plugin, named `jQuery-File-Upload`. According to [its official wiki](https://github.com/blueimp/jQuery-File-Upload/wiki/Setup#content-type-negotiation), it has negotiated to `Content-Type` in IE8/IE9, causing another problem: `done` handler cannot be triggered when complete uploading, as the following snippet shown:

```js
/** jquery.fileupload.js */
jqXHR = jqXHR || (
    ((aborted || that._trigger(
        'send',
        $.Event('send', {delegatedEvent: e}),
        options
    ) === false) &&
    that._getXHRPromise(false, options.context, aborted)) ||
    that._chunkedUpload(options) || $.ajax(options)
).done(function (result, textStatus, jqXHR) {
    /** cannot be triggered under IE8/IE9 */
    that._onDone(result, textStatus, jqXHR, options);
});
```

It means that you cannot know when the uploading has been completed. Details has been described in [an item](http://stackoverflow.com/questions/10122165/blueimp-jquery-file-upload-done-complete-callbacks-not-working-for-ie-9) of StackOverflow.
