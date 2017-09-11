# usma_kobuki
Header file to control Kobuki robot base through an Arduino's serial port

### Instructions to install the library:
1. From the XE475 course folder(\\usmasvddeecs\EECS\Cadet\Courses\XE475\Lab4), copy and paste `Kobuki` to the location where the Arduino IDE stores all libraries. The default location is usually `\Documents\Arduino\libraries`
2. The file structure is described below. Verify its contents after you have copied the `Kobuki` library folder.
```
   Kobuki
    │   keywords.txt
    │   Kobuki.h
    │   Kobuki.cpp
    └───examples
    |   └───lineFollower
    |   |       lineFollower.ino
    |   └───pseudoRandomWalker
    |           pseudoRandomWalker.ino 
    └───extras
        |   Kobuki_library_manual.pdf
        |   Kobuki_User_Guide.pdf
        |   API_Illustrations.pdf
        |   Kobuki_Protocol_Specification.pdf
```
4. Restart Arduino IDE to check if the newly added 'Kobuki' library has been detected. If it has been successfully imported, you must be able to see 'lineFollower' and 'pseudoRandomWalker' sketches under `Files -> Examples -> Kobuki`


### Quick links:
------------------------------------------------------------------------------
#### [Kobuki User Guide](https://github.com/westpoint-robotics/usma_kobuki/blob/master/Kobuki%20-%20User%20Guide.pdf)
#### [Kobuki.h Manual](https://github.com/westpoint-robotics/usma_kobuki/blob/master/Kobuki%20library%20manual.pdf)
