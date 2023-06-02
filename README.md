# pacmod3_common

This repo contains code for both parsing and encoding pacmod3 CAN messages. 
The code related to parsing and encoding CAN frames is auto-generated thanks to the helpful [c-coderdbc](https://github.com/astand/c-coderdbc) tool.
The rest of the code is manually written and is used for packing and unpacking ROS [pacmod3_msgs](https://github.com/astuff/pacmod3_msgs).
The pacmod3_common library can be compiled under both ROS1 and ROS2 in order to reduce duplication and code maintenance efforts.

Each major version of the [pacmod DBC](https://github.com/astuff/pacmod_dbc) is supported by this pacmod3_common library.

## Version Support

Below is a table of supported DBC versions.

|Major Version|Full DBC Version|
|-|-|
|3|3.4.1|
|4|4.1.0|
|5|5.0.0|
|6|6.0.0|
|7|7.2.0|
|8|8.0.1|
|9|9.1.0|
|10|10.3.0|
|11|11.6.0|
|12|12.3.0|
