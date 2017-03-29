This example assumes that you have zlib.lib and zlib.h 
installed and they are available for cl.

If you have these files in some certain place that cl
cannot find automatically, you can add the following:

/IpathToHeader pathToLib/zlib.lib

example: if the files are in ../../, add the following:

/I../../ ../../zlib.lib
