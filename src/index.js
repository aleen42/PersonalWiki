function getScript(src) {
    var scriptObj = document.createElement('script');
    scriptObj.src = src;
    scriptObj.type = 'text/javascript';
    document.body.appendChild(scriptObj);
}

window.onload = function () {
    var div = document.createElement('div');
    div.id = 'particles-js';
    document.getElementByClassName('book').appendChild(div);

    getScript('src/jquety-2.1.4.min.js');
    getScript('src/application.js');
};