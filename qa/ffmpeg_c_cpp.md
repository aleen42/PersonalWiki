## How to use ffmpeg in c/c++ [Back](./qa.md)

**Qt Creator** is a way for you to use ffmpeg in c/c++, and [here](http://infernusweb.altervista.org/wp/download/HMI/UsingFFMPEGinCwithQtCreator.pdf) you can read more for details

#### Ffmpeg as a system call

The built version of FFMPEG can be called by shell with an argument list (see the wiki on the
official web site), so to use this into a C++ code it is necessary to implement a **QProcess** that can start a program.

```bash
ffmpeg -i inputMovie.avi -acodec pcm_s16le outputAudioFile.wav
```

```cpp
QProcess _FFMPEG;
    QString _process = "ffmpeg";
    QStringList _paramList;
        _paramList << "-i"
            << "inputMovie.avi"
            << "-acodec"
            << "pcm_s16le"
            << "outputAudioFile.wav";

_FFMPEG.start(_process, _paramList);

if (!(_FFMPEG.waitForFinished()))
    qDebug() << "Conversion failed:" << _FFMPEG.errorString();
else
    qDebug() << "Conversion output:" << _FFMPEG.readAll();
```

The _FFMPEG is an object that can start an external program and communicate with
him. To the start function is necessary to give the name of the process (**ffmpeg**) and the
argument list (**_paramList**).
