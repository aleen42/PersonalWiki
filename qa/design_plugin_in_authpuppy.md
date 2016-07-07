## Design a new authorized plugin in AuthPuppy [Back](./qa.md)

Firstly, create a `class.php` to contain your plugin, and here I have used myself as the plugin name.

```php
<?php

class apSoundtoothAuthenticator extends apAuthentication {
    protected $_name = "Splash-only plugin.  Just push the button";
    
    public function initialize(sfWebRequest $request, apBaseIdentity $identity) {
        // Nothing to do here
    }
    
    public function process(sfAction $action, sfWebRequest $request, apBaseIdentity $identity) {
        $identity->identify("splash_only", new apDefaultUser(), $this);
    }
    
    public function render() {
        return include_partial('node/defaultAuthTemplate'); //return simple_format_text('<p>No authenticator plugin has been installed and enabled so this is the default plugin.  Clicking the button below will authenticate you to the router</p><input type="submit"/>');
    }
}
```
