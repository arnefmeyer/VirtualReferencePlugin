# VirtualRef plugin

A flexible virtual reference plugin for the open-ephys 
[plugin-GUI](https://github.com/open-ephys/plugin-GUI/).

Features:

- Control over full reference matrix
- Global gain for all references
- Loading/saving of reference matrices

# Installation

First build [plugin-gui](https://github.com/open-ephys/plugin-gui) (development branch with cmake) following
[Building plugin-GUI](https://open-ephys.atlassian.net/wiki/spaces/OEW/pages/1301643269/Creating+Build+files) and then
[Installing plugin-GUI](https://open-ephys.atlassian.net/wiki/spaces/OEW/pages/491544/Installation)

Then, following instructions for building third-party Plugins [Building Plugins](https://open-ephys.atlassian.net/wiki/spaces/OEW/pages/1259110401/Plugin+CMake+Builds)

In ```VirtualReferencePlugin\VirtualRef\Build``` folder

```
export GUI_BASE_DIR=path/to/GUI
```

```path/to/GUI``` should be changed to the absolute path where the plugin-gui folder is located

Then
```
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
make
make install
```

# Important

The open-ephys plugin GUI is currently updating it's internal structure. 
Therefore use the plugin's master branch for the master branch of the 
GUI and the plugin's development branch for the development branch of the GUI.

# TODO

- saving/loading parameters in json format

