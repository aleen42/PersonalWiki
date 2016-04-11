function getScript(src) {
    $(document.body).append('<script src="' + src + '" type="text/javascript"></script>');
}

window.onload = function () {
    var particles = document.createElement('div');
    particles.setAttribute('id', 'particles-js');
    document.body.appendChild(particles);
    
    getScript('src/jquery-2.1.4.min.js');
    getScript('src/application.js');
};

$(document).ready(function () {
    $('.book').append('<div id="particles-js"></div>');
});