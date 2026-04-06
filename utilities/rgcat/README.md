Self-written version of the `cat` utility. Modified version of requirements followed from the original assignment (`w` replaced with `rg`, my initials<sup>[2](#namecheck)</sup>):

## rgcat

The program **rgcat** is a simple program. Generally, it reads a file as
specified by the user and prints its contents. A typical usage is as follows,
in which the user wants to see the contents of main.c, and thus types: 

```
prompt> ./rgcat main.c
#include <stdio.h>
...
```

As shown, **rgcat** reads the file **main.c** and prints out its contents. 
The "**./**" before the **rgcat** above is a UNIX thing; it just tells the
system which directory to find **rgcat** in (in this case, in the "." (dot)
directory, which means the current working directory). 

To create the **rgcat** binary, you'll be creating a single source file,
**rgcat.c**, and writing a little C code to implement this simplified version
of **cat**. To compile this program, you will do the following:

```
prompt> gcc -o rgcat rgcat.c -Wall -Werror
prompt> 
```

This will make a single *executable binary* called **rgcat** which you can
then run as above. 

You'll need to learn how to use a few library routines from the C standard
library (often called **libc**) to implement the source code for this program,
which we'll assume is in a file called **rgcat.c**. All C code is
automatically linked with the C library, which is full of useful functions you
can call to implement your program. Learn more about the C library
[here](https://en.wikipedia.org/wiki/C_standard_library) and perhaps
[here](https://www-s.acm.illinois.edu/webmonkeys/book/c_guide/)<sup>[1](#myfootnote1)</sup>.  

For this project, we recommend using the following routines to do file input
and output: **fopen()**, **fgets()**, and **fclose()**. Whenever you use a new
function like this, the first thing you should do is read about it -- how else
will you learn to use it properly?

On UNIX systems, the best way to read about such functions is to use what are
called the **man** pages (short for **manual**). In our HTML/web-driven world,
the man pages feel a bit antiquated, but they are useful and informative and
generally quite easy to use.

To access the man page for **fopen()**, for example, just type the following
at your UNIX shell prompt: 
```
prompt> man fopen
```

Then, read! Reading man pages effectively takes practice; why not start
learning now?

We will also give a simple overview here. The **fopen()** function "opens" a
file, which is a common way in UNIX systems to begin the process of file
access. In this case, opening a file just gives you back a pointer to a
structure of type **FILE**, which can then be passed to other routines to
read, write, etc. 

Here is a typical usage of **fopen()**:

```c
FILE *fp = fopen("main.c", "r");
if (fp == NULL) {
    printf("cannot open file\n");
    exit(1);
}
```

A couple of points here. First, note that **fopen()** takes two arguments: the
*name* of the file and the *mode*. The latter just indicates what we plan to
do with the file. In this case, because we wish to read the file, we pass "r"
as the second argument. Read the man pages to see what other options are
available. 

Second, note the *critical* checking of whether the **fopen()** actually
succeeded. This is not Java where an exception will be thrown when things goes
wrong; rather, it is C, and it is expected (in good programs, i.e., the
only kind you'd want to write) that you always will check if the call
succeeded. Reading the man page tells you the details of what is returned when
an error is encountered; in this case, the macOS man page says:

```
Upon successful completion fopen(), fdopen(), freopen() and fmemopen() return
a FILE pointer.  Otherwise, NULL is returned and the global variable errno is
set to indicate the error. 
```

Thus, as the code above does, please check that **fopen()** does not return
NULL before trying to use the FILE pointer it returns.

Third, note that when the error case occurs, the program prints a message and
then exits with error status of 1. In UNIX systems, it is traditional to
return 0 upon success, and non-zero upon failure. Here, we will use 1 to
indicate failure.

Side note: if **fopen()** does fail, there are many reasons possible as to
why.  You can use the functions **perror()** or **strerror()** to print out
more about *why* the error occurred; learn about those on your own (using
... you guessed it ... the man pages!).

Once a file is open, there are many different ways to read from it. The one
we're suggesting here to you is **fgets()**, which is used to get input from
files, one line at a time. 

To print out file contents, just use **printf()**. For example, after reading
in a line with **fgets()** into a variable **buffer**, you can just print out
the buffer as follows:

```c
printf("%s", buffer);
```

Note that you should *not* add a newline (\\n) character to the printf(),
because that would be changing the output of the file to have extra
newlines. Just print the exact contents of the read-in buffer (which, of
course, many include a newline).

Finally, when you are done reading and printing, use **fclose()** to close the
file (thus indicating you no longer need to read from it).

**Details**

* Your program **rgcat** can be invoked with one or more files on the command
  line; it should just print out each file in turn. 
* In all non-error cases, **rgcat** should exit with status code 0, usually by
  returning a 0 from **main()** (or by calling **exit(0)**).
* If *no files* are specified on the command line, **rgcat** should just exit
  and return 0. Note that this is slightly different than the behavior of 
  normal UNIX **cat** (if you'd like to, figure out the difference).
* If the program tries to **fopen()** a file and fails, it should print the
  exact message "rgcat: cannot open file" (followed by a newline) and exit
  with status code 1.  If multiple files are specified on the command line,
  the files should be printed out in order until the end of the file list is
  reached or an error opening a file is reached (at which point the error
  message is printed and **rgcat** exits). 

### Footnotes


<a name="myfootnote1">1</a>: Unfortunately, there is a lot to learn about the
C library, but at some point, you've just got to **read documentation** to
learn what is available. Why not now, when you are young? Or, if you are old,
why not now, before it's ... ahem ... too late?

<a name="namecheck">2</a>: I did check for already existing versions of this command, and it seems there's no conflict, theough there is one which was *very* close: see `grcat`. Also, it's its own file, so unless you're aliasing it (for whatever reason), you should be good.
