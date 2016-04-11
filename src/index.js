function getScript(src) {
    var scriptObj = document.createElement('script');
    scriptObj.src = src;
    scriptObj.type = 'text/javascript';
    document.body.appendChild(scriptObj);
}

window.onload = function () {
    var particles = document.createElement('div');
    particles.setAttribute('id', 'particles-js');
    document.body.appendChild(particles);
    
    particles.addEventListener('mouseover', function () {
    });
    
    getScript('src/jquery-2.1.4.min.js');
    getScript('src/application.js');
};