## Server-side Environment [Back](./../tooling_integration.md)

One of the great things about React is that it doesn't require the DOM as a dependency, which means it is possible to render a React application on the server and send the HTML markup down to the client. 

### Node.js

[Node.js](http://nodejs.org/) is a popular JavaScript runtime that comes with an extensive core library and support for installing packages from npm to expand on the basic functionality.

If you use JSX, you may want to pre-compile your components. Alternatively you may want to consider using [Babel's require hook](https://babeljs.io/docs/usage/require/) or [`babel-node`](https://babeljs.io/docs/usage/cli/#babel-node).

> Note:

> Some versions of Node.js have an `Object.assign` implementation that does not preserve key order. This can cause errors when validating the markup, creating a warning that says "React attempted to reuse markup in a container but the checksum was invalid". If you run into this issue, you can override `Object.assign` to use a polyfill that preserves key order. For more details, see [Issue #6451](https://github.com/facebook/react/issues/6451).

### C\#

Support for server-side component rendering and JSX compilation (via Babel) in a .NET Framework / ASP.NET environment is provided through our [ReactJS.NET](http://reactjs.net/) project.

### Nashorn

Nashorn is a lightweight high-performance JavaScript runtime that runs within the **JVM**. React should run out of the box in Java 8+.

{$ace edit=false, lang='java' $}
import java.io.IOException;
import java.io.InputStream;
import java.io.FileReader;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

public class ReactRender
{
    public static void main(String[] args) throws ScriptException, IOException {
        ScriptEngine nashorn = new ScriptEngineManager().getEngineByName("nashorn");
        
        // These files can be downloaded as a part of the starter kit
        // from https://facebook.github.io/react
        nashorn.eval(new FileReader("path/to/react.js"));
        nashorn.eval(new FileReader("path/to/react-dom-server.js"));
        
        System.out.println(nashorn.eval(
            "ReactDOMServer.renderToString(" +
                "React.createElement('div', null, 'Hello World!')" +
            ");"
        ));
    }
}
{$endace$}
