## Better Browser Using [Back](./qa.md)

- there are serveral steps to use browser well.

#### Web Browsers

- Choose major browsers: **Firefox**, **Chrome**, **Internet Explorer**, and **Safari**.
- Alaways update your browsers


#### Adjust settings

- 1. Disable third-party cookies.
	- Third-party cookies are tracking identifiers used by advertising networks to track your behavior as you browse from website to website. They are an abomination(憎惡) and serve no legitimate(合法使用的) purpose.
		- Firefox: **Preferences** > **Privacy** > **Accept third-party cookies** > **Never**.
		- Chrome: **Settings** > **Show advanced settings…** > **Content settings** > **Block third-party cookies and site data**.
- 2. Clear cookies on exit.
	- Most browsers keep cookies around much longer than necessary. It is best to configure your browser to delete cookies when you quit the browser.
		- Firefox: **Preferences** > **Privacy** > **Keep until** > **I close Firefox**.
		- Chrome: **Settings** > **Show advanced settings…** > **Content settings** > **Keep local data only until you quit your browser**.
- 3. Disable Flash.
	- Flash is a plug-in from Adobe that has been the cause an endless stream of security problems. We highly recommend that you remove or disable Flash.
		- Firefox: **Add-ons** > **Plugins** > **Flash** > **Never Activate**.
		- Chrome: **Settings** > **Show advanced settings…** > **Content settings** > **Do not run plugins by default**.
- 4. Disable Java.
	- Java also has many security problems and you probably have never used it. Remove or disable it with haste(緊促感).
		- Firefox: **Add-ons** > **Plugins** > **Java** > **Never Activate**.
		- Chrome: **Settings** > **Show advanced settings…** > **Content settings** > **Do not run plugins by default**.

#### Browser extensions

##### Essential extensions

- These are absolutely essential browser extensions that everyone should be using all the time. They are stable, open source, and rarely cause websites to break.

------
- <img src="./better_browser_icon1.png"> [**uBlock**](https://github.com/gorhill/uBlock) prevents most advertisements and tracking networks. It is similar to Adblock Plus or Disconnect but works better and is much faster.

------
- <img src="./better_browser_icon2.png"> [**HTTPS Everywhere**](https://www.eff.org/https-everywhere) will automatically switch to secure TLS connections whenever the website supports it. This helps to protect against surveillance of the content of your web browsing, although it does not hide which websites you are visiting (unless you also run [Tor](https://help.riseup.net/en/security/network-security/tor) or a [VPN](https://help.riseup.net/en/vpn)).

------
- <img src="./better_browser_icon3.png"> [**Privacy Badger**](https://www.eff.org/privacybadger) dynamically detects attempts to track your browsing behavior and blocks content from these trackers. Privacy Badger is not designed to stop ads, so it is not a replacement for uBlock, but it includes some security features that uBlock does not have.

------

##### Advanced extensions

- These extensions are for advanced users because they are complicated to use or cause many websites to malfunction.
- These extensions attempt to overcome basic privacy flaws(瑕疵) in how web browsers work. However, many websites rely on these privacy flaws for basic functionality, so attempts to fix these problems can often make a website stop working.
- Some of these privacy flaws include:
	- **HTTP Referrer**: When you click a link, your browser sends to the new website the location of the old website. Because sensitive or personally identifying information might be included in the URL of a particular page, the HTTP Referrer should be disabled. You can only do this with an extension.
	- **HTTP User-Agent**: Your web browser sends a special "User-Agent" string to every website that it visits. This string contains a lot of uncommon information that can be used, in combination with other data, to uniquely identify your traffic. There is little point in the User-Agent string these days, and it is better to use a generic value, such as the one used by the Tor Browser.
	- **HTML5 Canvas**: Many websites have started to use the HTML5 Canvas to uniquely fingerprint your browser and track your behavior. There is currently no way to disable this, although some new extensions make a crude attempt.
	- **JavaScript**: JavaScript is essential for most websites these days, but there are times when you may wish to disable it. When JavaScript is enabled, it is much easier for a website to fingerprint your browser and track your behavior. Also, most browser security vulnerabilities(漏洞) are caused by JavaScript.
- For Firefox:
	- [**Self Destructing Cookies (Firefox)**](https://addons.mozilla.org/en-US/firefox/addon/self-destructing-cookies/) will clean out the cookies for a website when all the tabs for that site have been closed (rather than requiring that you restart the browser).
	- [**µMatrix**](https://addons.mozilla.org/en-US/firefox/addon/umatrix/) allows you to selectively block Javascript, plugins or other resources and control third-party resources. It effectively replaces NoScript and RequestPolicy.
	- [**Canvas Blocker**](https://addons.mozilla.org/en-US/firefox/addon/canvasblocker/) will allow you to disable HTML5 canvas support for particular websites.
- For Chrome:
	- [**µMatrix**](https://chrome.google.com/webstore/detail/%C2%B5matrix/ogfcmafjalglgifnmanfmnieipoejdcf) allows you to selectively block Javascript, plugins or other resources and control third-party resources. It also features extensive privacy features like user-agent masquerading, referering blocking and so on. It effectively replaces NoScript and RequestPolicy.
	- [**User-Agent Switcher**](https://chrome.google.com/webstore/detail/user-agent-switcher/ffhkkpnppgnfaobgihpdblnhmmbodake) will allow you to modify the HTTP User-Agent.
