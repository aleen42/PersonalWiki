## React Hot Loader [Back](./../react.md)

### Installation

```bash
npm install react-hot-loader --save-dev
```

### Development Server

Create a file `server.js` to include the following script:

```js
/** server.js */

var webpack = require('webpack');
var WebpackDevServer = require('webpack-dev-server');
var config = require('./webpack.config');

new WebpackDevServer(webpack(config), {
    publicPath: config.output.publicPath,
    hot: true,
    historyApiFallback: true
}).listen(3000, 'localhost', function (err, result) {
    if (err) {
        return console.log(err);
    }
    
    console.log('Listening at http://localhost:3000/');
});
```

Then configure `package.json` to call the Webpack server on `npm start`:

```json
{
    "scripts": {
        "start": "node server.js",`
        "test": "echo \"Error: no test specified\" && exit 1"
    }
}

```