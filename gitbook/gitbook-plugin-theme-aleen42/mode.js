require([ 'gitbook' ], function (gitbook) {
    gitbook.events.bind('start', function () {
        gitbook.toolbar.createButton({
            icon: 'fa fa-' + ((localStorage.getItem('color-mode') || 'light') === 'light' ? 'moon' : 'sun') + '-o',
            label: 'Toggle mode',
            position: 'right',
            className: 'j-toggle-mode',
            onClick: function () {
                var target = document.querySelector('.j-toggle-mode i');
                var mode = target.className.indexOf('fa-moon-o') > -1 ? 'dark' : 'light';
                target.className = 'fa fa-' + (mode === 'light' ? 'moon' : 'sun') + '-o';

                localStorage.setItem('color-mode', mode);
                document.documentElement.setAttribute('data-color-mode', mode);
            }
        });
    });

    gitbook.events.bind('page.change', function () {
        var mode = localStorage.getItem('color-mode') || 'light';
        var target = document.querySelector('.j-toggle-mode i');
        target.className = 'fa fa-' + (mode === 'light' ? 'moon' : 'sun') + '-o';
    });
});
