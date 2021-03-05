## Webpack + Font Awesome [Back](./../webpack.md)

### 1. Installation

Install dependency firstly:

```bash
npm install font-awesome --save
```

And install relative loaders:

```bash
npm install css-loader --save-dev
npm install file-loader --save-dev
npm install style-loader --save-dev
npm install url-loader --save-dev
```

### 2. Configuration

After installation, we are supposed to configure `webpack.config.js`:

```js
const path = require('path');

module.exports = {
    entry: './src/index.js',
    output: {
        path: path.join(__dirname, 'build'),
        filename: 'index.js'
    },
    resolve: {
        extensions: ['', '.js', '.jsx', '.css']
    },
    module: {
        loaders: [
            /** style */
            {
                test: /\.css/,
                loader: 'style!css?sourceMap',
            }, 

            /** font-awesome */
            {
                test: /\.woff(\?v=\d+\.\d+\.\d+)?$/,
                loader: "url?limit=10000&mimetype=application/font-woff"
            }, {
                test: /\.woff2(\?v=\d+\.\d+\.\d+)?$/,
                loader: "url?limit=10000&mimetype=application/font-woff"
            }, {
                test: /\.ttf(\?v=\d+\.\d+\.\d+)?$/,
                loader: "url?limit=10000&mimetype=application/octet-stream"
            }, {
                test: /\.eot(\?v=\d+\.\d+\.\d+)?$/,
                loader: "file"
            }, {
                test: /\.svg(\?v=\d+\.\d+\.\d+)?$/,
                loader: "url?limit=10000&mimetype=image/svg+xml"
            },

            /** babel */
            {
                test: /\.jsx?$/,
                loader: 'babel-loader',
                exclude: /node_modules/,
                query: {
                    presets: ['es2015', 'react']
                }
            }
        ]
    }
};
```

### 3. Usage

```html
<link rel="stylesheet" type="text/css" href="./node_modules/font-awesome/css/font-awesome.css">
```

@deprecated way, which cannot load with the latest version:

```js
import fa from 'font-awesome/css/font-awesome.css';

document.body.innerHTML = '<i class="fa fa-fw fa-question"></i>';
```