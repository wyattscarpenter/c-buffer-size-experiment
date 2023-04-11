This git repo is a small project to benchmark the use of various input-reading strategies (mainly, input buffer size) in C. It moves 10 gibibytes around. The test is small, narrow, and shallow; the world of C I/O functions is large, and my time is limited and my C profiling expertise is meager. The test tries to simulate useful work slightly, so that the problem is not as completely trivial as, say, renaming a file. It mainly just shows that a bigger buffer size is better, and compiler optimizations will not save you from this fact. It also shows, to my surprise, that mmap is not as good as a big buffer. It is possible that I was using mmap wrong. I would have liked to test a gibibyte buffer as well, but it seems this is not allowed on my system.

You can run this test using `test.sh`. Be advised: if you run this project, it may hog all your system resources and make your computer unresponsive for a while!

The project is almost entirely perfectly-portable standard C, except mmap.c relies on the unix standard header, and the mmap header. Also, `test.sh` itself is a Bourne shell script (unix shell script).

I used this test on Windows 10, WSL 1, Ubuntu 22.04.1 LTS, gcc version 11.3.0 (Ubuntu 11.3.0-1ubuntu1~22.04). Here is a typical output.

```
We will now test copying 10GiB from `/dev/zero` to `wc` using various sizes and types of intermediate buffer. (The calls to wc are to make sure the memory has to be used for something on output and cant just be effortlessly dropped by the OS. We drop the output of wc, though, since it doesnt change or matter.) This may take some time.
Using the built-in unix `head` command:
15.09
10737418240
mmap -O3: 16.60 seconds
mmap -O2: 15.00 seconds
mmap -O1: 14.94 seconds
mmap -O0: 15.39 seconds
1MiB -O3: 4.59 seconds
1MiB -O2: 4.69 seconds
1MiB -O1: 4.57 seconds
1MiB -O0: 4.65 seconds
1KiB -O3: 17.64 seconds
1KiB -O2: 17.71 seconds
1KiB -O1: 17.68 seconds
1KiB -O0: 18.17 seconds
1B -O3: 78.04 seconds
1B -O2: 78.14 seconds
1B -O1: 82.44 seconds
1B -O0: 247.50 seconds
I would have liked to have a version of this program that manually read a whole input file into memory using the size from `stat` or `fseek(file_pointer, 0L, SEEK_END); file_size = ftell(file_pointer); rewind(file_pointer);`, but I didnt for 2 reasons: 1. Im using /dev/zero which has no end. But thats surmountable. The real problem is that the max buffer size for fread on my system seems to be 1MiB, so I cant load a realistically huge file that way.
```
