# HackerRank

My hacker rank submissions.

## Generating solution code from template

1. Copy template directory to new directory (use dash `-` in directory name):
    `cp -a TemplateCPP\. <challenge-name>\`  

2. Replace template string with challenge name (use dash `-` in README.md):  
    `sed -i -- "s/<CHALLENGE_NAME_TEMPLATE>/<challenge-name>/g" README.md`  

3. Replace template string with challenge name (use underscore `_` in main.cpp):  
    `sed -i -- "s/<CHALLENGE_NAME_TEMPLATE>/<challenge_name>/g" main.cpp`  

For above `sed` to work on Windows 10, make sure your user has 'Full control' permissions.  

Note that some of the challenge URLs don't match the given challenge name.  
