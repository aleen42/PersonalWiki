## Matrix transformations [Back](./../three.md)

**Three.js** uses matrices to encode 3D transformations---translations (position), rotations, and scaling. Every instance of [Object3D](http://threejs.org/docs/index.html#Reference/Core/Object3D) has a matrix which stores that object's **position**, **rotation**, and **scale**.

There are two ways to update an object's transformation:

1. Modify the object's **position**, **quaternion**, and **scale** properties, and let Three.js recompute the object's matrix from these properties:
    ```js
    object.position.copy(start_position);
	object.quaternion.copy(quaternion);
    ```
    
    By default, the **matrixAutoUpdate** property is set true, and the matrix will be automatically recalculated. If the object is static, or you wish to manually control when recalculation occurs, better performance can be obtained by setting the property false:
    
    ```js
    object.matrixAutoUpdate = false;
    ```
    
    And after changing any properties, manually update the matrix:
    
    ```js
    object.updateMatrix();
    ```
2. Modify the object's matrix directly. The [Matrix4](http://threejs.org/docs/index.html#Reference/Math/Matrix4) class has various methods for modifying the matrix:
    ```js
    object.matrix.setRotationFromQuaternion(quaternion);
	object.matrix.setPosition(start_position);
	object.matrixAutoUpdate = false;
    ```
    
    Note that **matrixAutoUpdate** must be set to **false** in this case, and you should make sure not to call **updateMatrix**. Calling **updateMatrix** will clobber the manual changes made to the matrix, recalculating the matrix from **position**, **scale**, and so on.