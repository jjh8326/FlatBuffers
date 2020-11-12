How to compile
---------------
In command line run: gcc bankAccountInformation.c -o bankAccountInformationDemo -I./flatcc/include flatcc/lib/libflatccrt.a -g


How to recompile headers from FBS file
---------------
- If IBS file changes then new headers will need to be generated (this will break C code)
- To do this you will need a compiled version of the flatcc binary (https://github.com/dvidelabs/flatcc#building)
- Run this command in terminal: ./PATH_TO_FLATCC_BIN -c --reader bankAccountDefinition.fbs 
- This will generate new headers, make sure these headers are added and referenced in the XCode project
