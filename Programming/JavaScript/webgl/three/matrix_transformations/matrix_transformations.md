## Matrix transformations [Back](./../three.md)

**Three.js** uses matrices to encode 3D transformations---translations (position), rotations, and scaling. Every instance of [Object3D](http://threejs.org/docs/index.html#Reference/Core/Object3D) has a matrix which stores that object's **position**, **rotation**, and **scale**.

There are two ways to update an object's transformation:

1. Modify the object's position, quaternion, and scale properties, and let Three.js recompute the object's matrix from these properties: