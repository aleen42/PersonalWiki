require(["gitbook"], function (gitbook) {
    // Load analytics.js
    gitbook.events.bind("start", function (e, config) {
        var script = document.createElement('script');
        var cfg = config.ga, token = cfg.token;
        script.src = 'https://www.googletagmanager.com/gtag/js?id=' + token;
        script.onload = function () {
            window.dataLayer = window.dataLayer || [];

            function gtag() {dataLayer.push(arguments);}

            gtag('js', new Date());
            gtag('config', token);
        };
        document.head.appendChild(script);
    });
});
