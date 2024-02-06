## How to calculate the FPS value of a page [Back](./../qa.md)

Here is a way to calculate the FPS value of a website, but it should be a performance topic we should discuss:

- How to calculate
- How to improve

```js
function fps(callback) {
    var requestAnimationFrame =    
        /** Chromium */
        window.requestAnimationFrame ||
        /** Webkit */
        window.webkitRequestAnimationFrame ||
        /** Mozilla Geko   */
        window.mozRequestAnimationFrame ||
        /** Opera Presto */
        window.oRequestAnimationFrame ||
        /** IE Trident */
        window.msRequestAnimationFrame ||
        /** Fallback function  */
        function (callbackFunc) {
            window.setTimeout(callbackFunc, 1000 / 60);   
        };

    var fps = 0;
    var last = Date.now();
    var offset;

    function step() {
        offset = Date.now() - last;
        fps += 1;

        if (offset >= 1000) {
            last += offset;

            /** callback with calculated fps */
            callback(fps);
        }

        requestAnimationFrame(step);
    }

    step();
}
```
