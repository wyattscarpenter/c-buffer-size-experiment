#!/bin/sh

echo 'We will now test copying 10GiB from `/dev/zero` to `wc` using various sizes and types of intermediate buffer. (The calls to wc are to make sure the memory has to be used for something on output and cant just be effortlessly dropped by the OS. We drop the output of wc, though, since it doesnt change or matter.) This may take some time.'

echo 'Using the built-in unix `head` command:'
time -f "%e" head -c 10737418240 </dev/zero | wc -c

for i in mmap 1MiB 1KiB 1B; do
  for j in -O3 -O2 -O1 -O0; do
    cc "$i".c "$j"
    echo "$i" "$j": `(time -f "%e" ./a.out </dev/zero | wc -c >/dev/null) 2>&1` seconds
  done
done

echo 'I would have liked to have a version of this program that manually read a whole input file into memory using the size from `stat` or `fseek(file_pointer, 0L, SEEK_END); file_size = ftell(file_pointer); rewind(file_pointer);`, but I didnt for 2 reasons: 1. Im using /dev/zero which has no end. But thats surmountable. The real problem is that the max buffer size for fread on my system seems to be 1MiB, so I cant load a realistically huge file that way.'