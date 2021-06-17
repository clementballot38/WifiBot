# WifiBot GUI
*by Clément BALLOT & Jules GELUS*


## About
This program is a GUI developped in C++ with Qt to control the WifiBot (see [here](https://github.com/dginhac/wifibot) for documentation).


## Getting ready

### Project setup
To compile this program, you need :
* Visual Studio (developped on version 16.9.5)
* Qt VS Tools
* MSVC
* Qt 5.12.2

### Compile & run
1. Open the solution (QtApp/QtApp.sln) with Visual Studio
2. Check if Qt 5.12.2 is selected : open `Extensions -> Qt VS Tools -> Qt Versions Project Settings -> Qt -> Versions` and make sure the version `5.12.2_msvc2019_64` is selected as default
3. Run the code


## Description

### Classes
The project contains the following classes :
|      Class       |                                                   Function                                                   |
|:-----------------|:-------------------------------------------------------------------------------------------------------------|
|UiController      |Handles the interface update : gauges, buttons & camera                                                       |
|GaugeController   |Handles the update of a gauge widget : circular gauges (speed), "antenna" gauges (distance) and battery gauge |
|GamepadController |Handles controls with a controller (tested with Xbox One and Xbox 360 controllers)                            |
|MyRobot           |Handles the communications with the WifiBot                                                                   |

### Custom widgets
This project uses the following custom widgets :
|  Widget  |  Function                                                                              |
|:---------|:---------------------------------------------------------------------------------------|
| antenna  | The antenna-style gauge widget used to show the distance calculated by each IR sensor  |
| battery  | The battery-style gauge widget used to show the battery level                          |
| gauge    | The circular gauge widget used to show speed, acceleration & brakes                    |

### UI
The main UI file `QtApp.ui` was created with Qt Designer.