To Compile the metadata:
    ./compile-meta

To Compile the filters:
Add the path of the metadata shared library to LIBRARY_PATH:
    export LIBRARY_PATH=$LIBRARY_PATH:your/library/path
    example:
    export LIBRARY_PATH=$LIBRARY_PATH:$(pwd)

To Run the APP:
1. Add the path of the metadata shared library to LD_LIBRARY_PATH:
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:your/library/path
    example:
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)
2. Add the path of the shared library to GST_PLUGIN_PATH:
    export GST_PLUGIN_PATH=$GST_PLUGIN_PATH:your/library/path
    example:
    export GST_PLUGIN_PATH=$GST_PLUGIN_PATH:$(pwd)
3. Go to your APP folder and run the APP
