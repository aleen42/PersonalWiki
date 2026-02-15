## Something about &lt;iframe&gt; [Back](./qa.md)

There are 3 troubles in using `<iframe>`:

- `<iframe>` will block the event `onload` of the page.
- It's impossible for search engines to search contents from `<iframe>`, which make it hard to do **Search Engine Optimization (SEO)**.

**Solution:** use JavaScript to set `src` for `<iframe>` dynamically.

- `<iframe>` will share **Connection Pool (連接池)** with pages, which will affect the loading of pages in parallel.

