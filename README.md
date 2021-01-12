# Gst Custom Plugin Example

## Custom Plugin

The example of customplugin with custommetadata implementation is located in subfolder, gst-customplugin.

Go to the gst-customplugin folder for the following utilities

### Compile the metadata

```
./compile-meta
```

### Compile the filters

- Add the path of the metadata shared library to LIBRARY_PATH:

```
export LIBRARY_PATH=$LIBRARY_PATH:your/library/path
example:
export LIBRARY_PATH=$LIBRARY_PATH:$(pwd)
```

- Add the path of the metadata shared library to LD_LIBRARY_PATH (optional for plugin check):

```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:your/library/path
example:
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)
```

- Compile:

```
./compile-filters
```

## Run the APP

The APP is setup as a cmake project, and is completely seperated from the gst-customplugin.

After compiling the custom plugins, go back to the root path and do the following:

- Add the path of the metadata shared library to LD_LIBRARY_PATH:

``` 
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:your/library/path
example:
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/gst-customplugin
```

- Add the path of the shared library to GST_PLUGIN_PATH:

```
export GST_PLUGIN_PATH=$GST_PLUGIN_PATH:your/library/path
example:
export GST_PLUGIN_PATH=$GST_PLUGIN_PATH:$(pwd)/gst-customplugin
```

- Compile and run the APP:

```
mkdir build
cd build
cmake ..
make
./bin/my_app
```
