## Environment Setup [Back](./../angular1.md)

### 1. Installation

Firstly, clone the [angular-phonecat repository](https://github.com/angular/angular-phonecat) located at GitHub by running the following command:

```bash
git clone --depth=16 https://github.com/angular/angular-phonecat.git
```

> the `--depth=16` option tells Git to pull down only the last 16 commits, which make it faster to download

After then, install all dependencies through `npm`:

- Bower
- Http-Server
- Karma
- Protractor

```bash
npm install
```

Running `npm install` will also automatically use bower to download the AngularJS framework into the directory `app/bower_componets`.

### 2. Running the Development Web Server

Start the web server by running:

```bash
npm start
```

Then it will create a local web server that is listening to the port 8000 of the local machine.

> If you want to serve the app on a different IP address or port, edit the "start" script within `package.json`, and use `-a` to set up another address, and `-p` to set up the port. At the same time, you also need to upade the `baseUrl` configuration property in `e2e-test/protractor.conf.js`.

### 3. Running Unit Tests

Unit tests focus on testing small isolated parts of application. The angular-phonecat project use [Karma](https://karma-runner.github.io/) to run the unit tests for the application. Start it by running:

```
npm test
```

With running Karma, it will read the configuration file `karma.conf.js` located at the root of the project directory, which tells Karma to:

1. Open up instances of the Chrome and Firefox browsers and connect them to Karma
2. Execute all the unite tests in these browsers
3. Report the result of tests in the terminal
4. Watch all JavaScript files in the project, and re-run tests whenever any change happens