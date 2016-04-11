function getScript(src) {
    var scriptObj = document.createElement('script');
    scriptObj.src = src;
    scriptObj.type = 'text/javascript';
    document.body.appendChild(scriptObj);
}

window.onload = function () {
    /**
     * animation background
     */
    var div = document.createElement('div');
    div.id = 'particles-js';
    document.getElementsByClassName('book')[0].appendChild(div);

    getScript('https://aleen42.gitbooks.io/personalwiki/content/src/jquery-2.1.4.min.js');
    getScript('https://aleen42.gitbooks.io/personalwiki/content/src/application.js');
    
    setTimeout(function () {
        div.style.opacity = 1;
    }, 500);
    
    /**
     * overlay icon
     */
    var overlayIcon = document.createElement('div');
    div.class = 'overlay-icon';
    document.getElementsByClassName('summary')[0].appendChild(overlayIcon);
};