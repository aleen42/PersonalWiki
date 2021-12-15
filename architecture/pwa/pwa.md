## Progressive Web Apps (PWA) [Back](../architecture.md)

As an architecture to design web apps to make them more progressive, there is a series of mechanisms like [service workers](https://developer.mozilla.org/en-US/docs/Web/API/Service_Worker_API),  
[manifests](https://developer.mozilla.org/en-US/docs/Web/Manifest) you can use to do such an enhancement.

What has advantages brought by this architecture? It can conclude in different dimensions:

- **Discoverable** (can be found through search engines)
- **Installable** (can be launched via home screen or app)
- **Linkable** (can be shared via URL)
- **Network independent** (can work offline or with a poor network connection)
- **Progressively enhanced** (usable on a basic level on older browsers, but fully functional on the latest one)
- **Re-engageable** (can receive notifications in real-time)
- **Responsively designed** (usable in any devices with different resolution ratios)
- **Secure** (can protect sensitive data)

This document mainly focused on what we can do in these dimensions.

### 1. Discoverable

To enable web apps a better representation in search engines (a better SEO), we can:

- use some proprietary (所有權) technologies like [Open Graph](https://ogp.me/) to specify metadata according to a specific protocol.
- define a manifest file to describe the name, author, icon(s), version, or other resources.

### 2. Installable

Installation of web apps is a feature available in modern browsers. It allows users to install apps on their devices or add them to the home screen on mobile devices. For example, if we define such a manifest file, Chrome will show an installation icon within the address bar, where users can install it.

```json
{
  "background_color": "purple",
  "description": "Shows random fox pictures. Hey, at least it isn't cats.",
  "display": "fullscreen",
  "icons": [
    {
      "src": "icon/fox-icon.png",
      "sizes": "192x192",
      "type": "image/png"
    }
  ],
  "name": "Awesome fox pictures",
  "short_name": "Foxes",
  "start_url": "/pwa-examples/a2hs/index.html"
}
```

Besides, we can also prompt users to install inside the app:

```js
let deferredPrompt;
window.addEventListener('beforeinstallprompt', e => {
    // Prevent Chrome 67 and earlier from automatically showing the prompt
    e.preventDefault();
    
    // Stash the event so it can be triggered later.
    deferredPrompt = e;
    
    // Update UI to notify the user they can add to home screen
    const addBtn = document.createElement('<span>');
    addBtn.innerText = 'Add to home screen';
    document.body.appendChild(addBtn);
    
    addBtn.addEventListener('click', () => {
        // hide our user interface that shows our A2HS button
        addBtn.style.display = 'none';
        
        // Show the prompt
        deferredPrompt.prompt();
        
        // Wait for the user to respond to the prompt
        deferredPrompt.userChoice.then(choiceResult => {
            if (choiceResult.outcome === 'accepted') {
                console.log('User accepted the A2HS prompt');
            } else {
                console.log('User dismissed the A2HS prompt');
                addBtn.style.display = 'block';
            }
            deferredPrompt = null;
        });
    });
});
```

### 3. Linkable

All web apps should be linkable without an app store or a complex installation process.

### 4. Network independent

There are some factors to detect whether an app is network independent. They can be:

- revisited even if no network is available.
- browsed any content visited at least once, even under poor connectivity.
- controlled what to shown when there is no connectivity.

To implement those features, we can:

- use [Service Workers](https://developer.mozilla.org/en-US/docs/Web/API/Service_Worker_API) to control page offline requests, like querying data from a local cache.
- use [Cache API](https://developer.mozilla.org/en-US/docs/Web/API/Cache) for storing request / response objects.
- use [Web Storage](https://developer.mozilla.org/en-US/docs/Web/API/Web_Storage_API) and [IndexedDB](https://developer.mozilla.org/en-US/docs/Web/API/IndexedDB_API) to store application data offline.

### 5. Progressively enhanced

The word "*progressive*" means that the design achieves a usable experience for users of older browsers and devices with limited capabilities, while at the same time having a fully-feature experience when the environment is capable.

To do so, we can use feature detection to determine different behaviours, and choose some polyfills tools like [`core-js`](https://github.com/zloirock/core-js), [`autoprefixer`](https://github.com/postcss/autoprefixer) to add missing features.

The philosophy is similar with [Graceful Degradation (平稳退化)](https://developer.mozilla.org/en-US/docs/Glossary/Graceful_degradation), but they are not the same thing, and progressive enhancement is more positive.

### 6. Re-engageable

It means users can be re-engaged by updates and new content, even when not looking at the app or using their devices. For example, a new incoming mail can automatically update the mail list, rather than needing users to refresh manually.

There are some related techniques we may need to know:

- use [WebSocket](https://developer.mozilla.org/en-US/docs/Web/API/WebSocket) or [Push API](https://developer.mozilla.org/en-US/docs/Web/API/Push_API) to construct connections between servers and clients to subscribe changes.
- use [Notifications API](https://developer.mozilla.org/en-US/docs/Web/API/Notifications_API) to control the display of system notifications to the end-user in [Web Workers](https://developer.mozilla.org/en-US/docs/Web/API/Web_Workers_API).

### 7. Responsively designed

We can use [media queries](https://developer.mozilla.org/en-US/docs/Web/CSS/Media_Queries) and [viewport](https://developer.mozilla.org/en-US/docs/Glossary/Viewport) to fit any device with different resolution ratio. It should be a big topic, and here is a suggested list of documents around this:

- https://tympanus.net/codrops/tag/responsive/
- https://responsivedesign.is/
- ...

### 8. Secure

In addition to taking advantage of HTTPS, we can also use some methods to avoid XSS in web apps, like using [js-xss](https://github.com/leizongmin/js-xss), [iframe sandbox](https://developer.mozilla.org/en-US/docs/Web/HTML/Element/iframe#attr-sandbox), or [Content-Security-Policy (CSP) Header](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Security-Policy) to control resources.

Besides, it is a common case to escape HTML strings before rendering, when they are passed outside the app.
