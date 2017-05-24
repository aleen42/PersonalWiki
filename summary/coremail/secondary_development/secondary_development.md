## Secondary Development	[Back](./../coremail.md)

If you want to checkout to another development environment for secondary development, you have to take the place of the module named **wmweb**.

1. Open IDEA: [**Project Structure**] -> [**Modules**] -> [**wmweb**]
2. Delete it and reimport the specific file named **wmweb.iml** in the folder for your secondary development

After development completed, we may also have to package the project as following steps:

1. Modify the file named **build.xml**:
```xml
<property name="javalib2.dir" location="../cmj/javalib2"/>
<property name="wmsvr.dir" location="../cmj/wmsvr"/>
<strip-developing src="../cmj/cmj/cmlib/web" dest="${webapp.uncompressed.dir}"/>
```
2. Modify the file named **build.sh**:
```bash
__JAVALIB_DIR=`dirname "$0"`/../cmj/javalib2
```
3. Run the script:
```bash
bash build.sh
```
