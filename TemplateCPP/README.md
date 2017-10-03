# <insert_challenge_name_here>

https://www.hackerrank.com/challenges/<insert_challenge_name_here>

# Build

* Make sure to include your own version of `libstdc++-6.dll`, I've included mine from GCC 6.3.0.
* Configure the scons makefile (`SConstruct`) if necessary.
* Run the following commands:

`scons`  
`main.exe`  

# Template

Replace template string with challenge name: 
    `sed -i -- 's/<insert_challenge_name_here>/replacement_name/g' main.cpp`  
    `sed -i -- 's/<insert_challenge_name_here>/replacement_name/g' README.md`  
For above `sed` to work on Windows 10, make sure your user has 'Full control' permissions.