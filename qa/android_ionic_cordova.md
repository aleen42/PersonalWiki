## How to build up Android development environment when using Ionic and Cordova to build APP [Back](./qa.md)

This note is referenced to an answer on Stack Overflow: http://stackoverflow.com/a/36201240

Before you can build Android applications, you must install the Android SDK. Installing the Android SDK also installs the AVD Manager, a graphical user interface for creating and managing Android Virtual Devices (AVDs).

1. From the [Android web site](http://developer.android.com/sdk/index.html), download the correct version of the Android SDK for your operating system.
2. Unzip the archive to a location of your choosing. For example, on Linux or Mac, you can place it in the root of your user directory. See the [Android Developers](http://developer.android.com/sdk/installing/index.html) web site for additional installation details.
3. Configure the `ANDROID_HOME` environment variable based on the location of the Android SDK. Additionally, consider adding `ANDROID_HOME/tools`, and `ANDROID_HOME/platform-tools` to your PATH.

### Mac OS X

```bash
export ANDROID_HOME=/<installation location>/android-sdk-macosx
export PATH=${PATH}:$ANDROID_HOME/tools:$ANDROID_HOME/platform-tools
```

### Linux

```bash
export ANDROID_HOME=/<installation location>/android-sdk-linux
export PATH=${PATH}:$ANDROID_HOME/tools:$ANDROID_HOME/platform-tools
```

### Windows

```bash
set ANDROID_HOME=C:\<installation location>\android-sdk-windows
set PATH=%PATH%;%ANDROID_HOME%\tools;%ANDROID_HOME%\platform-tools
```

The Android SDK download does not include specific Android platforms. To run the code in this guide, you need to download and install the latest SDK platform. You do this by using the Android SDK and AVD Manager that you installed in the previous section.

1. Open the Android SDK Manager window:
    ```
    android
    ```

    > **Note**: If this command does not open the **Android SDK Manager**, then your path is not configured correctly.
2. Select the **Tools** checkbox.
3. Select the checkbox for the **latest Android SDK**.
4. From the **Extras** folder, select the checkbox for the **Android Support Library**.
5. Click the **Install packages**... button to complete the download and installation.
    > **Note**: You may want to install all the available updates, but be aware it will take longer, as each API level is a large download.
