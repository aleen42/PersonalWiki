## @access [Back](../jsdoc.md)

This tag is mainly used for specifying the accessibility level of members: `package`, `private`, `protected`, and `public`.

- `@access package` is the same as `@package`.
- `@access private` is the same as `@private`.
- `@access protected` is the same as `@protected`.
- `@access public` is the same as `@public`.

*Note: Private members are not shown in the generated output unless JSDoc is run with the `-p/--private` command-line option.*

*a doclet's access level is different from its scope. It means that documenting with such a tag won't change its real running scope.*

```js
class Base {
    constructor() {
        /**
         * @type {number}
         * @private
         */
        this._private = 0;

        /**
         * @type {number}
         * @protected
         */
        this._protected = 1;

        /**
         * @type {number}
         * @public
         */
        this.public = 2;
    }
}

class Inherit extends Base {
    constructor() {
        super();
    }

    getPrivate() { console.log(this._private); /** Private member is not accessible */ }
}
```
