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
npm install -g bower
````

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

### 4. Running E2E Tests

E2E (end-to-end) tests are used to ensure that the application behaves as expected. How? It will simulate real user interactions in the browser.

E2E tests are kept in the `e2e-tests` directory, run by [Protractor](https://github.com/angular/protractor).

Before running applications, we may need to install some drivers relied by Protractor:

```bash
npm run update-webdriver
```

Then, make sure we have started up a running application:

```bash
npm start
```

Then, run it:

```bash
npm run protractor
```

With running Protractor, it will read the configuration file at `e2e-tests/protractor.conf.js`, which tells Protractor to:

- Open up a Chrome browser to connect to the application
- Execute all the E2E tests in this browser
- Report the result of tests in the the terminal
- Close the browser and exit
