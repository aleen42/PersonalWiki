## Design a new authorized plugin in AuthPuppy [Back](./qa.md)

Firstly, create a `class.php` to contain your plugin, and here I have used myself as the plugin name.

```php
<?php
class apSoundtoothAuthenticator extends apAuthentication {
    /** title of the login page */
    protected $_name = "";
    
    public function initialize(sfWebRequest $request, apBaseIdentity $identity) {
        // Nothing to do here
    }
    
    public function process(sfAction $action, sfWebRequest $request, apBaseIdentity $identity) {
        $identity->identify("splash_only", new apDefaultUser(), $this);
    }
    
    public function render() {
        /** return the view you want */
        return include_partial('node/defaultAuthTemplate');
    }
}
```
