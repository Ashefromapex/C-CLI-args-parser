This simple program analyses the command line arguments passed to it and compares it to an exisiting list of arguments you can set up in the main function.
It will return an array of integers responding to the place of the found command in the existing array (0 meaning first argument etc.) 
Example:

<img width="370" alt="image" src="https://github.com/user-attachments/assets/cf700071-273b-4d3f-9fea-67451104da5f" />

0 is at the first index of the returned array, because the "help" command (short name is 'h') is at the index of 0 in the command list:

<img width="391" alt="image" src="https://github.com/user-attachments/assets/eb6d4a9a-3e4a-4407-9c39-a72624f410e4" />

There exist two 'modes' for cli arguments, the "short" mode, meaning a single character argument preceded by a '-' and "long" mode, meaning a string of characters preceeded by '--'

In case no command is found at the corresponding place the array displays 
-1 in case nothing is found 
-2 in case that the command provided is too long (more than 1 character after '-')
-10 if no mode was detected 

Note that the outputted array always has -1 at index 0 


## Usage:
In the "commands" array in the main function, you can place as many commands as you want using this format:
1. Without whitespace write the "long" version of your command
2. Follow it with a whitespace, a comma and another whitespace ' , '
3. Write the "short" version of your command (single character only!!); If there does not exist a short version simply put an exclamation mark '!' instead

IMPORTANT: After you filled the array make sure to set the "MAXCOMMANDS" constant at the top of the file to the corresponding number (= the ammount of commands in the list) 

Additionaly you can adjust the "MAXARGV" constant in the comandparser function to limit the size ofthe array that is returned, in turn limiting the ammount of commands parsed 
