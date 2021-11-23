
### minishell : petitcoquillage 

This program try to recreate bash --posix comportement in certain limite

### Execution :
To execute this Program you have to be on linux 
```
make && ./minishell
```
To check your leaks and ignore readline leaks, copy ```valgrind_readline_leaks_ignore.txt``` then execute the programme as it is right on ```cmd_valgrind_see_all_leaks.txt``` 

### Informations Briefly
This programme follow some rule and try answer the projet's suject that you can see in : ```minishell.pdf```.
There only one global variable for the exit_status and one singletone for the env.
Briefly, we have to recreate bash --posix comportement for ```|``` ```<``` ```<<``` ```>``` ```>>``` builtin ```cd ``` ```pwd``` ```exit with arg``` ```env``` ```unset``` ```export``` ```echo with option -n``` ```$?``` and of course ```$```

all source need here :
https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html

### What you should know
#### I- Parsing
- .1. Separation commande_line
- .1,1. Quote close and quoting rules
- .2. Separation of word in commande_line
- .2,1. Type of word
- .2,2. Expende word
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
- .3. Here_doc /// this part is not posix prouf see end of point
 
#### IV- Execution
- .1. When fork
- .2. Commande exist or right to execute?
- .3. Execution
- .4. Close fd
 
#### V- Test

# I- Parsing
## 1. Separation commande_line
**Here only '|' commande from each other, ';' is considere as a caracter :(**
## 1.1 Quote close, Quoting rules
At first, you should check if quote are properly close, following quoting rules :

The first quote you see cancel other type of quote untill you see it again  

Exemple :

```" ' "``` quote are close because ```'``` is not considere as quote inside double quote  
**Quoting rules**  
In bash there are a lot of caractere with meanings ass ```$``` for env variable, single quote and double quote are use to playe with or whitout those seconde   meaning, these rules will be useful to you to catch each commande line.  
**' rules**  
```'``` make thing easer and cancel all meaning of caractere, inside ```'``` ```"```, ```$env``` ``` ``` ```|``` ```< << > >>```are juste caracter inside a single word  
Try ```echo '$USER | cat ls blablabla'```  
**" rules**  
```"``` as ```'``` cancel second meaning of caractere exepte for env variable that make you able to use ```'```, and like ```'``` all caraceter inside double quote are a single word  
Try ``` echo "$USER | 'ici c'est Paris;"```  
**no quote rules**  
Here all caractere got there seconde meaning, and each ``` ``` are separator of word  
Try ```echo $USER hello there | ls | cat > file_out```  

**Found '|'**  
Your commande_line run from start to ```|```, You should know the quoting rules to not interpret a ```|``` as a caractere in double or single quote.  
Then copi the string you get (without '|') into your structure commande line (link list).   
Repeat the operation until the end of file.  

```
struct cmd_line{
    char             *cmd;
    stuct cmd_line   *next;
}
```
## 2. Separation of word in commande_line  
Now you go your list of commande_line with, you will have to got your list of word  
For that, use the quoting rule and separete your commande_line in a link list of word  
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

## 2.1 Type of word  
To to differentiate if a word is a arg a file a heredoc I set a type in my struct token following different rule  
My type is set as a enum as :  
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
Becarefull, of ```syntaxe error near unexpeted token 'x'```  
Exemple :  
``` cat > > file_out```

## 2.2 Expend word
To expend each word, there are differente rule following and some specifique to type limitor,  
For each word, you have to cut space at start and at the end of it,  
Then expend each quote following the quoting rule and skip the quote  
For env var, you have to check if it's exist in env, if it's doesn't exit, then skip it.  
Exemple :  
```word :                 "cou'cou"$lol'$USER   'a became word : cou'cou$USER   a (here $lol don't exist)```

**!!! special case 1**  
If a env is set like ``` export LS="ls -la"```  
There are to type of extend  
First, in double quote it is considere as a single word : ls -la  
Second, is it's not quote, you have to split it an the space considering it ass 2 word, word1 : ls word2 : -la  
Exemple in bash :  
``` 
Export LS="ls -la"
$LS // this should do a ls -la
"$LS" // this should print an error commande ls -la not found
```
**!!! special case 2**  
For type limitor expension you have to not expende env var  
Exemple try :  
```cat << $HOME```  
**!!! special case 3**
For type IN_FILE and EXIT_FILE you do not have to split env on space,  
Exemple in bash :  
```
$> Export t="ha  ha"
$> echo baguette > $t
$> ls
'ha ha'
$> cat < $t
baguette
```  

## 3. Prepare execution  
Here you are, you should have all your commande_line struct with all your token word expend and the type of each word.  
Now to prepare execution we will set an list of type Arg to path to execve as a char **args in each our struct cmd_line;  
Not a big deal, look trought the truct token, compte the number of type ARG and do a tab with all of them.  

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
During all these step you have to becarfull of deferent type of error, as commande line empty following by a pipe, or thing like ><, << < <, >|, |<, | |,  

# II- Builtin  

## 6. Exit  
There is four type of exit, each of use write exit in terminal :   
exit : exit and set exit status to 0;  
exit (num) : exit and set exit status to num  
exit (num alpha) : exit and set exit status to 2 + a error message  
exit (num) (num) (num) : doesn't exit and set exit status to 1 + a error message  

# III- Redirection  

## 1. Pipe  
Pipe will allow you to communicate throught your list of commande via file_directory (fd)  
In each cmd_line you will need a fd_in an a fd_out (int)  
Your first cmd_line fd_int will be set at STDIN, and the last cmd_line fd_out on STDOUT  
Connect your pipe[0] to the fd_out and pipe[1] to fd_in of the next cmd_line.  

## 2. Open Close file  

Now your commande line are connected via fd, but maybe you have to redirect information via file set by the commande line right on bash,  
Go throug your token lst, and if you got a Type file/heredoc/exitfile/exitfileout then, open it with open, and change your fd_in or fd_out  
And don't forget to close the fd that become ussless :)  

## 3. Here_doc  
For Here_doc, there a special case,   
I personnaly chose the easy solution to creat a file with a aleatorie name and file it with the imformation till i got my limitor word.  
**Becarefull**  
Here_doc is special, as for the expension, the contente is expend with is own rule  
If the limitor is expend (had quote on it) the word in the file will not be expend, and if it's not, the word will be expend  
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

# IV- Execution

## 1. When fork  
The real question is when not fork,  
And only when you have one commande line and it's a builtin, that allowe you to move through your directory and move env  

## 2. Commande exist or right to exectute?  
To execute a commande no builtin, you have two choice;  
if it's start by . or / it's a absolute path and then just pass it through execve,  
else you will have to foud the real path of the commande by split $PATH on ':' try with access if it's exist  
if you reatch the and of your split path without found a access, the commande doesn't exist.  
The commande can exist but withou the right to open it becarfull to the return of access.  

## 3. Execution

You have to start all your fork and exec all the commande in the same time and after wait for it   
```time sleep 2 | sleep 2```

In fork,   
use dup2 with the your fd_in and fd_out (read man dup2)  
close all your fd (all, not just the one in the commande line present here, you can close multiple time a same fd without have probleme)  
exec with execve,  
becarfull if execve fail to free all your memorie of the fork and exit with the good exit status (commande not found or permition denied)  
  
Outside, then use waitpid (man 2 waitpid) to wait for all the execution done  
Then close your local fd_in fd_out (cmd_line->fd_in and cmd_line->fd_out)  

## 4. Close fd  
Close all your fd is importante, you can check different way, look for   
```cat | ls``` and ```cat | cat |ls ```  


**vportens**
**readme for minishell**

