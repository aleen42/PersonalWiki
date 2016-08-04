## How to detect whether an object is an array [Back](./../array.md)

To justice whether an object is an array, you may have so much methods, but the most proper one should be like this:

{%ace edit=false, lang='javascript', theme='tomorrow'%}
function isArray(obj) {
    return Array.isArray ? Array.isArray(obj) : Object.prototype.toString.call(obj) === '[object Array]';
}
{%endace%}

Problems of other methods, like only using Array.isArray will have some side effects under IE 8, have been discussed in [here](./../../../../post/array_inference_in_javascript/array_inference_in_javascript.md).
