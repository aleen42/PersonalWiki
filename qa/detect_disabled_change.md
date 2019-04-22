## How to detect changes upon the disabled attribute of input elements? [Back](qa.md)

Based on the code snippet from https://gist.github.com/cmcnulty/7036509 and fix some bugs around detection of `Object.getOwnPropertyDescriptor`. As for modern browsers, I have added supports with `MutationObserver`.

```js
(function ($) {
    // https://gist.github.com/cmcnulty/7036509
    $.fn.onDisable = function (cb) {
        var $this = this;
        // Only perform this DOM change if we have to watch changes with propertychange
        // Also only perform if getOwnPropertyDescriptor exists - IE>=8
        // I suppose I could test for "propertychange fires, but not when form element is disabled" - but it would be overkill
        if (!('onpropertychange' in document.createElement('input')) && Object.getOwnPropertyDescriptor === void 0) {
            return $this;
        }

        // IE9-10 use HTMLElement proto, IE8 uses Element proto
        var someProto    = window.HTMLElement === void 0 ? window.Element.prototype : window.HTMLElement.prototype,
            someTrigger  = function (val) { cb && cb(val); },
            origDisabled = Object.getOwnPropertyDescriptor(someProto, 'disabled');

        if (document.createEvent) {
            someTrigger = function (val) {
                var event = document.createEvent('MutationEvent');
                /**
                 * Instantiate the event as close to native as possible:
                 * event.initMutationEvent(eventType, canBubble, cancelable, relatedNodeArg, prevValueArg, newValueArg, attrNameArg, attrChangeArg);
                 */
                event.initMutationEvent('DOMAttrModified', true, false, this.getAttributeNode('disabled'), '', '', 'disabled', 1);
                this.dispatchEvent(event);
                cb && cb(val);
            };
        } else if (document.fireEvent) {
            someTrigger = function (val) {
                this.fireEvent('onpropertychange');
                cb && cb(val);
            };
        }

        return $this.each(function () {
            if (origDisabled) {
                // call prototype's set, and then trigger the change.
                Object.defineProperty(this, 'disabled', {
                    set : function (isDisabled) {
                        // We store preDisabled here, so that when we inquire as to the result after throwing the event, it will be accurate
                        // We can't throw the event after the native send, because it won't be be sent.
                        // We must do a native fire/dispatch, because native listeners don't catch jquery trigger 'propertychange' events
                        $.data(this, 'preDisabled', isDisabled);
                        // Trigger with dispatchEvent
                        someTrigger.call(this, isDisabled);
                        return origDisabled.set.call(this, isDisabled);
                    },
                    get : function () {
                        var isDisabled = $.data(this, 'preDisabled');
                        if (isDisabled === void 0) {
                            isDisabled = origDisabled.get.call(this);
                        }
                        return isDisabled;
                    }
                });
            } else {
                // Use MutationObserver when using modern browsers
                var observer = new MutationObserver(function () {
                    cb && cb($this.prop('disabled'));
                });
                observer.observe(this, {attributes : true, attributeFilter: ['disabled']});
            }
        });
    };
}(jQuery));
```
