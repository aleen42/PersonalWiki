/***********************************************************************
 *                                                                   _
 *       _____  _                           ____  _                 |_|
 *      |  _  |/ \   ____  ____ __ ___     / ___\/ \   __   _  ____  _
 *      | |_| || |  / __ \/ __ \\ '_  \ _ / /    | |___\ \ | |/ __ \| |
 *      |  _  || |__. ___/. ___/| | | ||_|\ \___ |  _  | |_| |. ___/| |
 *      |_/ \_|\___/\____|\____||_| |_|    \____/|_| |_|_____|\____||_|
 *
 *      ================================================================
 *                 More than a coder, More than a designer
 *      ================================================================
 *
 *
 *      - Document: plugin.js
 *      - Author: aleen42
 *      - Description: injection of code
 *      - Create Time: Jul 22rd, 2021
 *      - Update Time: Jul 22rd, 2021
 *
 *
 **********************************************************************/

/* global $ */
require(['gitbook'], function (gitbook) {
    gitbook.events.bind('page.change', () => {
        const pluginConfig = gitbook.state.config.pluginsConfig['github-search'] || {};
        const repo = pluginConfig.repo;
        if (!repo) return;

        const token = pluginConfig.token || atob('Z2hwX2ljUlpGemE5MlcwQWVKRFR1NzdxRnhKOEdOSjRaUDBrZ3hKUA==');

        $.ajaxSetup({
            headers: Object.assign({
                Accept: 'application/vnd.github.v3.text-match+json',
            }, token && {
                Authorization: `token ${token}`,
            }),
        });

        const $searchContainer = $('<div class="pull-left toolbar-search">' +
            '<input name="keyword" autocomplete="off" placeholder="Search Keyword..." />' +
            '</div>');
        const $body = $('.book-body');
        const $inner = $body.find('.page-inner');
        const $section = $('<section class="search-section"></section>');
        const $markdownSection = $inner.find('section.markdown-section');
        const $loading = $('<div class="loading-item" style="display: none">'
            + '<div class="loading">'
            + '<div class="rect1" style="animation-delay: -1.08s;"></div>'
            + '<div class="rect2" style="animation-delay: -0.96s;"></div>'
            + '<div class="rect3" style="animation-delay: -0.84s;"></div>'
            + '<div class="rect4" style="animation-delay: -0.72s;"></div>'
            + '<div class="rect5" style="animation-delay: -0.6s;"></div>'
            + '<div>'
            + '</div>');

        $('.book-header h1').before($searchContainer);
        $body.append($loading);
        $inner.append($section);

        $searchContainer.find('input').on('keydown', function (e) {
            if (e.which === /* enter */13) {
                $('.book-body .navigation').hide();
                $markdownSection.hide();
                $section.show();
                fetchData($(this).val());
            }
        }).on('input', function () {
            if (!$(this).val()) {
                $markdownSection.show();
                $section.hide();
            }
        });

        function fetchData(keyword) {
            $loading.show();
            $.get(`https://api.github.com/search/code?per_page=100&q=${
                encodeURIComponent(keyword)
            }+in%3afile+language%3aMarkdown+${
                encodeURIComponent(`repo:${repo}`)
            }`).done(result => {
                $section.html([
                    `<h1 class="search-result-title">${encode(result.total_count) || 'NO'} RESULTS MATCHING "<span class="keyword">${encode(keyword)}</span>"</h1>`,
                    `<ul class="search-results-list">${
                        result.items.map(item =>
                            '<li class="search-results-item">'
                            + '<h3 class="search-results-item-title">'
                            + `<a href="/${item.path === 'README.md' ? '' : item.path.replace(/\.md$/, '.html')}">${encode(refTitle(item.path))}</a>`
                            + '</h3>'
                            + item['text_matches'].map(m => `<pre><code>${emphasize(m.fragment, m.matches).trim()}</code></pre>`).join('')
                            + '</li>').join('')
                    }</ul>`,
                ]);
            }).always(() => {
                $loading.hide();
            });
        }

        function refTitle(path) {
            return (gitbook.state.book.summary && lookup(gitbook.state.book.summary.parts)) || path;

            function lookup(pages) {
                let result;
                return pages.some(page => (result = page.ref === path ? page.title : lookup(page.articles))) && result;
            }
        }

        function emphasize(str, matches) {
            return [0, ...matches.flatMap(({indices}) => indices)]
                .map((start, i, arr) => {
                    const partial = str.slice.apply(str, [start, arr[i + 1]]);
                    return i & 1 ? `<span class="highlight">${encode(partial)}</span>` : encode(partial);
                })
                .join('');
        }

        function encode(str) {
            return `${str}`
                .replace(/&/g, '&amp;')
                .replace(/>/g, '&gt;')
                .replace(/</g, '&lt;')
                .replace(/"/g, '&quot;')
                .replace(/'/g, '&#39;');
        }
    });
});
