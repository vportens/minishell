
### minishell : petitcoquillage 

This program try to recreate bash --posix comportement in certain limite

### Execution :
To execute this Program you have to be on linux 
```
make && ./minishell
```
To check your leaks and ignore readline leaks, copy ```valgrind_readline_leaks_ignore.txt``` then execute the programme as it is right on ```cmd_valgrind_see_all_leaks.txt``` 

### Informations Briefly
This programme follow some rule and try answer the projet's suject that you can see in : ```minishell.pdf```
There only one global variable for the exit_status and one singletone for the env
Briefly, we have to recreate bash --posix comportement for ```|``` ```<``` ```<<``` ```>``` ```>>``` builtin ```cd ``` ```pwd``` ```exit with arg``` ```env``` ```unset``` ```export``` ```echo with option -n``` ```$?``` and of course ```$```
all source need here :
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html

### What you should know
#### I- Parsing
- .1. Separation commande_line
- .2. Separation of word in commande_line
- .2,1. Type of word
- .2,2. Expende word
- .3. Prepare execution
- .4. Error parsing
- 
#### II- Builtin
- .1. Env
- .2. Export
- .3. Unset
- .4. Pwd
- .5. Cd
- .6. Exit

#### III- Redirection
- .1. Pipe
- .2. Open Close file
- .3. Here_doc /// this part is not posix prouf see end of point
 
#### IV- Execution
- .1. When fork
- .2. Commande exist or right to execute?
- .3. Execution
- .4. Close fd
 
#### V- Test

