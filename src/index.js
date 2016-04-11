function getScript(src) {
    $(document.body).append('<script src="' + src + '" type="text/javascript"></script>');
}

$(document).ready(function () {
    $('.book').append('<div id="particles-js"></div>');
});