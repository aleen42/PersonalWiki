function getScript(src) {
    var scriptObj = document.createElement('script');
    scriptObj.src = src;
    scriptObj.type = 'text/javascript';
    document.body.appendChild(scriptObj);
}

window.onload = function () {
    var div = document.createElement('div');
    div.id = 'particles-js';
    document.getElementsByClassName('book')[0].appendChild(div);

    getScript('https://aleen42.gitbooks.io/personalwiki/content/src/jquery-2.1.4.min.js');
    getScript('https://aleen42.gitbooks.io/personalwiki/content/src/application.js');
};