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
};