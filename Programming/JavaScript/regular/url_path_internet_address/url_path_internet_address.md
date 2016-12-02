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
