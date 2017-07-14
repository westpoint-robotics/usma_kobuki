# usma_kobuki
Header file to control Kobuki robot base through an Arduino's serial port

### Instructions to install the library:
1. Download/clone this repository to your desktop.
2. This repo contains two folders: examples and extras. The examples folder has two Arduino sketches. The extras folder
contains the Official Kobuki User Guide and a Manual for the custom-built Kobuki header file which explains the API.   
This repo also contains the Kobuki header file and the source file, which should not be modified. 
3. Move all files and folders in this repository to the location where the Arduino IDE stores all libraries. 
The default location is usually `\Documents\Arduino\libraries`
4. Restart Arduino IDE to check if the newly added 'Kobuki' library has been detected. If it has been successfully imported, you must be able to see 'lineFollower' and 'pseudoRandomWalker' sketches under `Files -> Examples -> Kobuki`

#### Quick links to the contents of the 'extras folder':
------------------------------------------------------------------------------
#### [Kobuki User Guide](https://github.com/westpoint-robotics/usma_kobuki/blob/master/Kobuki/extras/Kobuki%20User%20Guide.pdf)
#### [Kobuki.h Manual](https://github.com/westpoint-robotics/usma_kobuki/blob/master/Kobuki/extras/Kobuki%20library%20manual.pdf)
