# <insert_challenge_name_here>

https://www.hackerrank.com/challenges/<insert_challenge_name_here>

# Build

* Make sure to include your own version of `libstdc++-6.dll`, I've included mine from GCC 6.3.0.
* Configure the scons makefile (`SConstruct`) if necessary.
* Run the following commands:

`scons`  
`main.exe`  

# Template

Copy template directory to new directory (use dash `-` in directory name):
    `cp -a TemplateCPP\. <challenge-name>\`  

Replace template string with challenge name (use dash `-` in README.md):  
    `sed -i -- "s/<CHALLENGE_NAME_TEMPLATE>/<challenge-name>/g" README.md`  

Replace template string with challenge name (use underscore `_` in main.cpp):  
    `sed -i -- "s/<CHALLENGE_NAME_TEMPLATE>/<challenge_name>/g" main.cpp`  

For above `sed` to work on Windows 10, make sure your user has 'Full control' permissions.  
