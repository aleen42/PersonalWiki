## How to solve the lib problem when using xampp to shell_exec c++ files [Back](./qa.md)

- When designing API with PHP to shell exec c++ binary files to use OpenCV, you will find that there is a problem about libstdc++
- **Reason**: there's something wrong about /opt/lampp/lib/libstdc++.so.6
- **Solution**: just backup the lib of libstdc++, and solve it.
