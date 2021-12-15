const path = require('path');
const fs = require('fs');

if (!fs.existsSync(path.resolve(__dirname, 'gh-pages/_config.yml'))) {
    fs.writeFileSync(path.resolve(__dirname, 'gh-pages/_config.yml'), `exclude: 
    - "*.md"`, 'utf8');
}

if (!fs.existsSync(path.resolve(__dirname, 'gh-pages/CNAME'))) {
    fs.writeFileSync(path.resolve(__dirname, 'gh-pages/CNAME'), 'wiki.aleen42.com', 'utf8');
}
