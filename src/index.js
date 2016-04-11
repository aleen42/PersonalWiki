function getScript(src) {
    $(document.body).append('<script src="' + src + '" type="text/javascript></script>');
}

window.onload = function () {
    
    getScript('src/jquety-2.1.4.min.js');
    getScript('src/application.js');
};