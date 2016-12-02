## URLs, Paths, and Internet Addresses [Back](./../regular.md)

What this chapter mainly concerns a wide range of programs is the various paths and locators for finding data:

- URLs, URNs, and related strings
- Domain names
- IP addresses
- Microsoft Windows file and folder names

### Validating URLs

- **Problem**

    How to check whether a give piece of text is a URL that is valid?

- **Solution**
    - Allow almost any URL:

        **/^(https?|ftp|file):\\/\\/.+$/i**

    - Require a domain name, and don't alow a username or password:

        **/^(https?|ftp):\\/\\/[a-z0-9-]+(\\.[a-z0-9-]+)+([\\/?].+)?$/i**

    - Require a domain name, and don't allow a username or password. Allow the scheme (http or ftp) to be omitted if it can be inferred from the subdomain (www or ftp):

        **/^((https?|ftp):\\/\\/|(www|ftp)\\.)[a-z0-9-]+(\\.[a-z0-9-]+)+([\\/?].&#42;)?/i**

    - Require a domain name and a path that points to an image file. Don’t allow a username, password, or parameters:

        **/^(https?|ftp):\\/\\/[a-z0-9-]+(\\.[a-z0-9-]+)+(\\/[\\w-]+)&#42;\\/[\w-]+\\.(gif|png|jpg)$/i**

### Finding URLs within full text

- **Problem**

    You may want to find URLs in a large body of text.

- **Solution**
    - URL without spaces:

        **/\\b(https?|ftp|file):\\/\\/\S+/i**

    - URL without spaces or final punctuation:

        **/\\b(https?|ftp|file):\\/\\/[-A-Z0-9+&@#/%?=~_|$!:,.;]&#42;[A-Z0-9+&@#/%=~_|$]/i**

    - URL without spaces or final punctuation. URLs that start with the **www** or **ftp** subdomain can omit the scheme:

        **/\\b((https?|ftp|file):\\/\\/|(www|ftp)\\.)[-A-Z0-9+&@#/%?=~_|$!:,.;]&#42;[A-Z0-9+&@#/%=~_|$]/**

### Validating URNs

- **Problem**

    You may want to check whether a string represents a valid Uniform Resource Name, or find URNs in a large body of text?

- **Solution**
    - Check whether a string consists entirely of a valid URN:

        **/^urn:[a-z0-9][a-z0-9-]{0,31}:[a-z0-9()+,\\-.:=@;$_!&#42;'%\\/?#]+$/**

    - Find a URN in a large body of text:

        **/\\burn:[a-z0-9][a-z0-9-]{0,31}:[a-z0-9()+,\\-.:=@;$_!&#42;'%\\/?#]+/**

### Validating generic URLs

- **Problem**

    You may want to check whether a given piece of text is a valid URL according to RFC 3986.

- **Solution**

    **/^([a-z][a-z0-9+\\-.]&#42;:(\\/\\/([a-z0-9\\-._~%!$&'()&#42;+,;=]+@)?([a-z0-9\\-._~%]+|\\[[a-f0-9:.]+\\]|\\[v[a-f0-9][a-z0-9\\-._~%!$&'()&#42;+,;=:]+\\])(:[0-9]+)?(\\/[a-z0-9\\-._~%!$&'()&#42;+,;=:@]+)&#42;\\/?|(\\/?[a-z0-9\\-._~%!$&'()&#42;+,;=:@]+(\\/[a-z0-9\\-._~%!$&'()&#42;+,;=:@]+)&#42;\\/?)?)|([a-z0-9\\-._~%!$&'()&#42;+,;=@]+(\\/[a-z0-9\\-._~%!$&'()&#42;+,;=:@]+)&#42;\\/?|(\\/[a-z0-9\\-._~%!$&'()&#42;+,;=:@]+)+\\/?)) (\\?[a-z0-9\\-._~%!$&'()&#42;+,;=:@\\/?]&#42;)?(#[a-z0-9\\-._~%!$&'()&#42;+,;=:@\\/?]&#42;)?$/**

### Extract the Scheme from a URL

- **Problem**

    How to extract the URL scheme from a string that holds a URL. For example, extract **http** from **http://www.regexcookbook.com**.

- **Solution**
    - **Extract the scheme from a URL known to be valid

        **/^([a-z][a-z0-9+\\-.]&#42;):/i**

    - **Extract the scheme while validating the URL**

        **/^([a-z][a-z0-9+\\-.]&#42;):(\\/\\/([a-z0-9\\-._~%!$&'()&#42;+,;=]+@)?([a-z0-9\\-._~%]+|\\[[a-f0-9:.]+\\]|\\[v[a-f0-9][a-z0-9\\-._~%!$&'()&#42;+,;=:]+\\])(:[0-9]+)?(\\/[a-z0-9\\-._~%!$&'()&#42;+,;=:@]+)&#42;\\/?|(\\/?[a-z0-9\\-._~%!$&'()&#42;+,;=:@]+(\\/[a-z0-9\\-._~%!$&'()&#42;+,;=:@]+)&#42;\\/?)?)(\\?[a-z0-9\\-._~%!$&'()&#42;+,;=:@\\/?]&#42;)?(#[a-z0-9\\-._~%!$&'()&#42;+,;=:@\\/?]&#42;)?$/i**

### Extract the host from a URL

- **Problem**

    How to extract the host from a string that holds a URL. For example, extract **www.regexcookbook.com** from **http://www.regexcookbook.com**.

- **Solution**
    - Extract the host from a URL known to be valid:

        **/^[a-z][a-z0-9+\\-.]&#42;:\\/\\/([a-z0-9\\-._~%!$&'()&#42;+,;=]+@)?([a-z0-9\\-._~%]+|\\[[a-z0-9\\-._~%!$&'()&#42;+,;=:]+\\])/i**

    - Extract the host while validating the URL:

        **/^[a-z][a-z0-9+\\-.]&#42;:\\/\\/([a-z0-9\\-._~%!$&'()&#42;+,;=]+@)?([a-z0-9\\-._~%]+|\\[[a-f0-9:.]+\\]|\\[v[a-f0-9][a-z0-9\\-._~%!$&'()&#42;+,;=:]+\\])(:[0-9]+)?(\\/[a-z0-9\\-._~%!$&'()&#42;+,;=:@]+)&#42;\\/?(\\?[a-z0-9\\-._~%!$&'()&#42;+,;=:@\\/?]&#42;)?(#[a-z0-9\\-._~%!$&'()&#42;+,;=:@\\/?]&#42;)?$/i**

### Extracting the port from a URL

- **Problem**

    You want to extract the port number from a string that holds a URL. For example, extract **80** from **http://www.regexcookbook.com:80/**.

- **Solution**
    - Extract the port from a URL known to be valid:

        **/^[a-z][a-z0-9+\\-.]&#42;:\\/\\/([a-z0-9\\-._~%!$&'()&#42;+,;=]+@)?([a-z0-9\\-._~%]+|\\[[a-z0-9\\-._~%!$&'()&#42;+,;=:]+\\]):([0-9]+)/i**

    - Extract the port while validating the URL:

        **/^[a-z][a-z0-9+\\-.]&#42;:\\/\\/([a-z0-9\\-._~%!$&'()&#42;+,;=]+@)?([a-z0-9\\-._~%]+|\\[[a-f0-9:.]+\\]|\\[v[a-f0-9][a-z0-9\\-._~%!$&'()&#42;+,;=:]+\\]):([0-9]+)(\\/[a-z0-9\\-._~%!$&'()&#42;+,;=:@]+)&#42;\\/?(\?[a-z0-9\\-._~%!$&'()&#42;+,;=:@\\/?]&#42;)?(#[a-z0-9\\-._~%!$&'()&#42;+,;=:@\\/?]&#42;)?$/i**

### Extracting the path from a URL

- **Problem**

    You want to extract the path from a string that holds a URL. For example, extract **/index.html** from **http://www.regexcookbook.com/index.html** or from **/index.html#fragment**.

- **Solution**
    - Extract the path from a string known to hold a valid URL, even if URLs that have no path:

        **/^([a-z][a-z0-9+\\-.]&#42;:(\\/\\/[^\\/?#]+)?)?([a-z0-9\\-._~%!$&'()&#42;+,;=:@\\/]&#42;)/i**

### Extracting the query from a URL

- **Problem**

    You may want to extract he query from a string that holds a URL. For example, extract **param=value** from **http://www.regexcookbook.com?param=value** or from **/index.html?param=value**.

- **Solution**

    **/^[^?#]+\\?([^#]+)/i**

### Extracting the fragment from a URL

- **Problem**

    You want to extract the fragment from a string that holds a URL. For example, extract **top** from **http://www.regexcookbook.com#top** or from **/index.html#top**.

- **Solution**

    **/#(.+)/i**

### Validating domain names

- **Problem**

    You want to check whether a string looks like it may be a valid, fully qualified domain name, or find such domain names in longest text.

- **Solution**
    - Check whether a string looks like a valid domain name:

        **/^([a-z0-9]+(-[a-z0-9]+)&#42;\\.)+[a-z]{2,}$/i**

    - Find valid domain names in longest text:

        **/\\b([a-z0-9]+(-[a-z0-9]+)&#42;\\.)+[a-z]{2,}\\b/i**

    - Check whether each part of the domain is not longer than 63 characters:

        **/\\b((?=[a-z0-9-]{1,63}\\.)[a-z0-9]+(-[a-z0-9]+)&#42;\\.)+[a-z]{2,63}\\b/i**

    - Allow internationalized domain names using the punycode (域名系統) notation:

        **/\\b((xn--)?[a-z0-9]+(-[a-z0-9]+)&#42;\\.)+[a-z]{2,}\\b/i**

    - Check whether each part of the domain is not longer than 63 characters, and allow internationalized domain names using the punycode notation:

        **/\\b((?=[a-z0-9-]{1,63}\\.)(xn--)?[a-z0-9]+(-[a-z0-9]+)&#42;\\.)+[a-z]{2,63}\\b/i**

### Matching IPv4 addresses

- **Problem**

    How to use regular expressions to match IPv4 addresses like **0.0.0.0**?

- **Solution**
    - Simple regex to check for an IP address:

        **/^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$/**

    - Accurate regex to check for an IP address, allowing leading zeros:

        **/^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/**

    - Accurate regex to check for an IP address, disallowing leading zeros:

        **/^(?:(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\.){3}(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$/**

    - Simple regex to extract IP addresses from longer text:

        **/\\b(?:[0-9]{1,3}\\.){3}[0-9]{1,3}\\b/**

    - Accurate regex to extract IP addresses from longer text, allowing leading zeros:

        **/\\b(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b/**

    - Accurate regex to extract IP addresses from longer text, disallowing leading zeros:

        **/\\b(?:(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\b/**

    - Simple regex that captures the four parts of the IP address:

        **/^([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})$/**

    - Accurate regex that captures the four parts of the IP address, allowing leading zeros:

        **/^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/**

    - Accurate regex that captures the four parts of the IP address, disallowing leading zeros:

        **/^(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$/**

### Matching IPv6 addresses

- **Problem**

    How to use regular expressions to match IPv6 addresses like **0:0:0:0:0:0:0:0**?

- **Solution**
    - Check whether the whole subject text is an IPv6 address using standard notation:

        **/^(?:[A-F0-9]{1,4}:){7}[A-F0-9]{1,4}$/i**

    - Check whether the whole subject text is an IPv6 address using mixed notation:

        **/^(?:[A-F0-9]{1,4}:){6}(?:(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$/i**

    - Check whether the whole subject text is an IPv6 address using standard or compressed notation:

        **/^(?:(?:[A-F0-9]{1,4}:){7}[A-F0-9]{1,4}|(?=(?:[A-F0-9]{0,4}:){0,7}[A-F0-9]{0,4}$)(([0-9A-F]{1,4}:){1,7}|:)((:[0-9A-F]{1,4}){1,7}|:)|(?:[A-F0-9]{1,4}:){7}:|:(:[A-F0-9]{1,4}){7})$/i**

    - Check whether the whole subject text is an IPv6 address using compressed or noncompressed mixed notation:

        **/^(?:(?:[A-F0-9]{1,4}:){6}|(?=(?:[A-F0-9]{0,4}:){0,6}(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$)(([0-9A-F]{1,4}:){0,5}|:)((:[0-9A-F]{1,4}){1,5}:|:)|::(?:[A-F0-9]{1,4}:){5})(?:(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$/i**

    - Check whether the whole subject text is an IPv6 address:

        **/^(?:(?:(?:[A-F0-9]{1,4}:){6}|(?=(?:[A-F0-9]{0,4}:){0,6}(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$)(([0-9A-F]{1,4}:){0,5}|:)((:[0-9A-F]{1,4}){1,5}:|:)|::(?:[A-F0-9]{1,4}:){5})(?:(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])|(?:[A-F0-9]{1,4}:){7}[A-F0-9]{1,4}|(?=(?:[A-F0-9]{0,4}:){0,7}[A-F0-9]{0,4}$)(([0-9A-F]{1,4}:){1,7}|:)((:[0-9A-F]{1,4}){1,7}|:)|(?:[A-F0-9]{1,4}:){7}:|:(:[A-F0-9]{1,4}){7})$/i**

### Validate windows paths

- **Problem**

    You may want to check whether a string looks like a valid path to a folder or file on the Microsoft Windows operating system.

- **Solution**
    - Drive letter paths:

        **/^[a-z]:\\\\(?:[&#94;\\\\/:&#42;?"<>|\\r\\n]+\\\\)&#42;[&#94;\\\\/:&#42;?"<>|\\r\\n]&#42;$/i**

    - Drive letter and UNC paths

        **/^(?:[a-z]:|\\\\\\\\[a-z0-9_.$ -]+\\\\[a-z0-9_.$ -]+)\\\\(?:[^\\\\/:&#42;?"<>|\\r\\n]+\\)&#42;[^\\\\/:&#42;?"<>|\\r\\n]&#42;$/i**

    - Drive letter, UNC, and relative paths

        **/^(?:(?:[a-z]:|\\\\\\\\[a-z0-9_.$ -]+\\\\[a-z0-9_.$ -]+)\\\\|\\\\?[&#94;\\\\/:&#42;?"<>|\\r\\n]+\\\\?)(?:[&#94;\\\\/:&#42;?"<>|\\r\\n]+\\\\)&#42;[&#94;\\\\/:&#42;?"<>|\\r\\n]&#42;$/i**

### Split windows paths into their parts

- **Problem**

    If a string turns out to hold a valid Windows path, then you may want to extract the drive, folder, and filename parts of the path separately.

- **Solution**
    - Drive letter paths:

        **/^([a-z]:)\\\\((?:[&#94;\\\\/:&#42;?"<>|\\r\\n]+\\\\)&#42;)([&#94;\\\\/:&#42;?"<>|\\r\\n]&#42;)$/i**

    - Drive letter and UNC paths

        **/^([a-z]:|\\\\\\\\[a-z0-9_.$ -]+\\\\[a-z0-9_.$ -]+)\\\\((?:[&#94;\\\\/:&#42;?"<>|\\r\\n]+\\\\)&#42;)([&#94;\\\\/:&#42;?"<>|\\r\\n]&#42;)$/i**

    - Drive letter, UNC, and relative paths

        **/^([a-z]:\\\\|\\\\\\\\[a-z0-9_.$ -]+\\\\[a-z0-9_.$ -]+\\\\|\\\\?)((?:[&#94;\\\\/:&#42;?"<>|\\r\\n]+\\\\)&#42;)([&#94;\\\\/:&#42;?"<>|\\r\\n]&#42;)$/i**

### Extract the driver letter from a windows path

- **Problem**

    How to extract the drive letter from a windows path? For example, extract **c** from **c:\\folder\\file.ext**.

- **Solution**

    **/^([a-z]):/i**

### Extract the server and share from a UNC path

- **Problem**

    How to extract the server and share from a UNC path? For example, extract **server** and **share** from **\\\\server\\share\\folder\\file.ext**.

- **Solution**

    **/^\\\\\\\\([a-z0-9_.$ -]+)\\\\([a-z0-9_.$ -]+)/i**

### Extract the folder from a windows path

- **Problem**

    How to extract the folder from a windows path? For example, extract **\\folder\\subfolder\\** from **c:\\folder\\subfolder\\file.ext** or **\\\\server\\share\\folder\\subfolder\\file.ext**.

- **Solution**

    **/^([a-z]:|\\\\\\\\[a-z0-9_.$ -]+\\\\[a-z0-9_.$ -]+)?((?:\\\\|^)(?:[&#94;\\\\/:&#42;?"<>|\\r\\n]+\\\\)+)/i**

### Extract the filename from a windows path

- **Problem**

    How to extract the filename from a windows path? For example, extract **file.ext** from **c:\\folder\\file.ext**.

- **Solution**

    **/[&#94;\\\\/:&#42;?"<>|\\r\\n]+$/i**

### Extract the file extension from a windows path

- **Problem**

    How to extract the file extension from a windows path? For example, extract **.ext** from **c:\\folder\\file.ext**.

- **Solution**

    **/\\.[&#94;.\\\\/:&#42;?"<>|\\r\\n]+$/i**

### Strip invalid characters from filenames

- **Problem**

    You may want to strip a string of characters that are not valid n windows filenames.

- **Solution**

    ```js
    function stripInvalidCh(subject) {
        subject = subject.replace(/[\\\/:"*?<>|]+/, '_');
    }
    ```
