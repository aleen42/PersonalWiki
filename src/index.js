function getScript(src) {
    $(document.body).append('<script src="' + src + '" type="text/javascript></script>');
}

$(document).ready(function () {
    $('.book').append('<div id="particles-js"></div>');
    getScript('src/jquety-2.1.4.min.js');
    getScript('src/application.js');
});