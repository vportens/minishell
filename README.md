
### minishell : petitcoquillage 

This program tries to recreate bash --posix behaviour in some ways.  

### Execution :
To execute this Program you have use linux.    
```
make && ./minishell
```
To check your leaks and ignore readline leaks, copy ```valgrind_readline_leaks_ignore.txt``` then execute the programme like it is written in this file :  ```cmd_valgrind_see_all_leaks.txt``` .  

### Informations Briefly
This programme follows some rules and try answer the projet's subject that you can see in : ```minishell.pdf```.
There is only one global variable for the exit_status and one singletone for the env.
Briefly, we have to recreate bash --posix comportement for ```|``` ```<``` ```<<``` ```>``` ```>>``` builtin ```cd ``` ```pwd``` ```exit with arg``` ```env``` ```unset``` ```export``` ```echo with option -n``` ```$?``` and of course ```$```

[(Click here for the source)](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html) 

### What you should know (Summary)
#### I- Parsing
- .1. Separation commande_line
- .1,1. Quote close and quoting rules
- .2. Separation of word in commande_line
- .2,1. Type of word
- .2,2. Expende word
- .2,3. Expende env
- .3. Prepare execution
- .4. Error parsing

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
- .3. Here_doc /// this part is not posix prouf, see end of point
 
#### IV- Execution
- .1. When fork
- .2. Command exist or right to execute?
- .3. Execution
- .4. Close fd
- .5. Exit_status
 
#### V- Test

# I- Parsing
## 1. Separation commande_line
**Here only '|' commande from each other, ';' is considere as a caracter :(**
## 1.1 Quote close, Quoting rules
At first, you should check if quotes are properly closed, following quoting rules: The first quote you see cancel the other type of quote until you see it again.    

For example:  
```" ' "``` quotes are closed because ```'``` is not considered as quote inside double quotes.  
  
**Quoting Rules**  
In bash there are a lot of characters with meanings such as ```$``` for env variables, single quotes and double quotes are used to play with or without those second meanings, these rules will be useful for you to catch each command line.  

**' Rules**  
```'``` make things easier and cancel all second meanings of characters, inside ```'``` ,```"```, ```$env```,``` ```, ```|```, ```< << > >>``` are just characters inside a single word  
Try ```echo '$USER | cat ls blablabla'```.    

**" Rules**  
```"``` like ```'``` cancel the second meanings of characters except for env variables that make you able to use ```'```, and like ```'``` all characters inside double quotes are a single word.    
Try ``` echo "$USER | 'ici c'est Paris;"``` . 
**No quote rules**  
Here all characters got there second meanings, and each  ``` ``` are separators of words.    
Try ```echo $USER hello there | ls | cat > file_out``` .   

**Found '|'**  
Your commande_line run from start to ```|```. You should know the quoting rules to not interpret a ```|``` as a character in double or single quotes.  
Then copy the string you get (without ```|```) into your structure commande_line (link list).   
Repeat the operation until the end of file.  

```
struct cmd_line{
    char             *cmd;
    stuct cmd_line   *next;
}
```
## 2. Separation of words in commande_line  
Now you got your list of commande_line, you need your list of words.    
For that, use the quoting rules and separate your commande_line in a link list of words.    
```
struct token{
    char            *word;
    enum            type;
    struct token    *next;
}

struct cmd_line{
    char                *cmd;
    struct  token       *word;
    struct  cmd_line    *next;
}
```

## 2.1 Type of words  
To differentiate if a word is an arg, a file or a heredoc. I set a type in my struct token following several rules.    
My type is set as an enum:  
```
enum type{
    NONE, //defaut set
    ARG, //word
    FILE_IN, //word == '<'
    HERE_DOC, // word == '<<'
    FILE_OUT, //word == '>'
    FILE_OUT_SUR, //word == '>>'
    OPEN_FILE, // word following '<'
    LIMITOR, // word following '<<'
    EXIT_FILE, // word followinf '>'
    EXIT_FILE_RET; // word following '>>'
}
```
Be careful, of ```syntax error near unexpected token 'x'```.    
Example :  
``` cat > > file_out```

## 2.2 Expand word
To expand each word, there are different rules depending on the Type.     
For each word, you have to cut space at start and at the end of it.  
Then expand each quotes following the quoting rules and skip the quotes.    
For env var, you have to check if it exist in env, if it's doesn't exit just skip it.  
Example :  
```word :                 "cou'cou"$lol'$USER   'a became word : cou'cou$USER   a (here $lol don't exist)```

**!!! Special Case 1**  
If a env is set like ``` export LS="ls -la"```.
First, in double quotes it is considered as a single word : ls -la  .    
Second, if it's not quotes, you have to split it on the space considering it as 2 words:  
 - word1 : ls   
 - word2 : -la  
  
Example in bash :  
``` 
Export LS="ls -la"
$LS // this should do a ls -la
"$LS" // this should print an error command "ls -la" not found
```
**!!! Special Case 2**  
For type limitors expand you have to not expand env var.  
For example try :  
```cat << $HOME```  
  
**!!! Special Case 3**  
For type IN_FILE and EXIT_FILE you do not have to split env on space,  
Exemple in bash :  
```
$> Export t="ha  ha"
$> echo baguette > $t
$> ls
'ha  ha'
$> cat < $t
baguette
```  

## 2.3 Expand env
Has you see higher,  
According to the type of the word, you have to expand the env with differents rules,  
In all cases, a env variable start by '$' and can only be compose by alphanum characters + ```_```   
```$?``` is not consider as a env variable but as the **exit_status** and ```?``` is not a alphanum character.   
And in case of ```$$``` I consider it as ```$``` 


## 3. Prepare execution  
Here you are, you should have all your commande_line struct with all your token word expand and the type of each word.  
Now to prepare execution we will set a list of type Arg to give to execve as a char **args in each our struct cmd_line;  
Not a big deal, look trought the struct token, count the number of type ARG and do a tab with all of them.  

```
struct token{
    char            *word;
    enum            type;
    struct token    *next;
}

struct cmd_line{
    char                *cmd;
    struct  token       *word;
    char                **args;
    struct  cmd_line    *next;
}
```

## Error parsing  
During all these steps you have to be carful of different types of error, as command line empty followed by a pipe.  
Thing like ><, << < <, >|, |<, | |,  
See the testing file  

# II- Builtin  




## 6. Exit  
There are four types of exit, each write exit in terminal:     
exit : exit and set exit status to 0;  
exit (num) : exit and set exit status to num  
exit (num alpha) : exit and set exit status to 2 + a error message  
exit (num) (num) (num) : doesn't exit and set exit status to 1 + a error message  

# III- Redirection  

## 1. Pipe  
Pipe will allow you to communicate through your list of command via file_directory (fd)   
In each cmd_line you will need a fd_in an a fd_out (int) **(man open)**   
Your first cmd_line fd_in will be set at STDIN, and the last cmd_line fd_out on STDOUT  
Connect your pipe[0] to the fd_out and pipe[1] to fd_in of the next cmd_line.  

## 2. Open Close file  

Now your command line are connected via fd, but maybe you have to redirect information via file set by the commande line right on bash,  
Go through your token lst, and if you got a Type file/heredoc/exitfile/exitfileout then, open it with open, and change your fd_in or fd_out  
And don't forget to close the fd that becomes ussless :)  

## 3. Here_doc  
For Here_doc, it is a special case,   
I personnaly chose the easy solution to creat a file with a random name and fill it with the imformation till i got my limitor word.  
**Becarefull**  
Here_doc is special, as for the expension, the content is expand with is own rules  
If the limitor is expand (had quote on it) the word in the file will not be expand, and if it's not, the word will be expand  
Exemple :  
```
bash : cat << hello""
>$PATH
>hello
bash : $PATH
bash : cat << hello
>$USER
>hello
bash : Vporten
```

For a more precise execution of minishell, before open file you should start by checking if you have here_doc through all your commande_line,  
Then write until you got a limitor directely in the fd give by pipe.  Then check if there are open file after  

# IV- Execution

## 1. When fork  
The real question is when not fork,  
And only when you have one commande line and it's a builtin, that allows you to move through your directory and move env  
When you have finish the parsing, there you start fork, one fork for each commande_line  
**man 2 fork**  
**man 2 waitpid**  

## 2. Commande exist or right to exectute?  
To execute a commande no builtin, you have two choice;  
if it's start by . or / it's an absolute path and then just pass it through execve,  
else you will have to found the real path of the commande by spliting $PATH on ':',  
join each split with the command, and try with access **(man 2 access)** if it exist    
if you reach the end of your split path without finding  a valide access, the command doesn't exist.  
The command can exist but without the right to open it, becarefull to the return of access.  

## 3. Execution

You have to start all your fork and exec all the command in the same time and after wait for it   
```time sleep 2 | sleep 2```

In fork,   
use dup2 with the your fd_in and fd_out **(man dup2)**  
close all your fd (all, not just the one in the commande line present here, you can close multiple time a same fd without have probleme)  
exec with execve,  
**(man 2 execve)**  
becarefull if execve fail, free all your memory in the fork and exit with the good exit status (commande not found or permission denied)  
  
Outside, use waitpid (man 2 waitpid) to wait for all the execution done   
Then close your local fd_in fd_out (cmd_line->fd_in and cmd_line->fd_out)   
  
## 4. Close fd   
Closng all your fd is important, you can check different ways, look for    
```cat | ls``` and ```cat | cat |ls ```   

 ## 5. Exit_status  
 Exit_status depands of multiple things,    
 If the commande work,  **0**  
 If a commande exist and fail cause of the arg, **1**  
 If a commande exist and you dont have the permission **126**  
 If a commande doesn't exist **127**  
 If a signal Kill or interrupte the commande **127 + signal**   
 If error parsing **2**  
 Exit status come with Error message in your terminal, **don't forget that the error fd is 2**  
 (putstr_fd)   


 Here is some wait to try it on bash  
 ```
 bash> touch new && chmod 000 new && ./new
 bash> echo $?
 ```
   
 ## END  
 Thanks for reading, if this tuto help you don't forgot to stars and follow, and maybe minishell destructor will be on the way :)   
   
**vportens**  
**readme for minishell**  

