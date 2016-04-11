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
    
    setTimeout(function () {
        div.style.opacity = 1;
    }, 500);
    
    console.log(document.querySelector('.book .book-summary ul.summary::before'));
    
    window.getComputedStyle(document.querySelector('.book .book-summary ul.summary'), ':before').addEventListener('click', function () {
        console.log('what');
    });
};