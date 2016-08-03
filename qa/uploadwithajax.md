## How to upload files and data with jQuery ajax [Back](./qa.md)

```html
<form action="" method="post" id="form-data" enctype="multipart/form-data">
    <input type="file" name="file" id="postFile">
    <input type="text" name="text" value="abc">
    <input type="number" name="number" value="12">
</form>
```

```js
const formData = new FormData($('#form-data')[0]);

$.ajax({
	url: 'path to post',
	type: 'POST',
	dataType: 'json',
	data: formData,
	cache: false,
	contentType: false,
	processData: false
})
.done(function(data) {
	console.log(data);
})
.fail(function() {
	console.log("detect error");
});
```
