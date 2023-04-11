#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
int main(void){
  const size_t buffer_size = 1024UL * 1024UL; //note: the maximum buffer size my system will accept in fread seems to be 1MiB.
  assert(buffer_size > 0 && buffer_size < SIZE_MAX);
  const size_t data_size = 10ULL * 1024ULL*1024ULL*1024ULL; // 10 bibillion, 10 GiB.
  assert(buffer_size <= data_size);
  void *stdin_memory_map = mmap(NULL, data_size, PROT_READ, MAP_PRIVATE, STDIN_FILENO, 0);
  void *stdout_memory_map = mmap(NULL, data_size, PROT_WRITE, MAP_SHARED_VALIDATE, STDOUT_FILENO, 0);
  //It's impossible/annoying to mmap stdout, so we just output regularly.
  for(long long int i = 0; i < data_size; i+=buffer_size){  
    fwrite(stdin_memory_map+i, buffer_size, 1, stdout);
  }
  munmap(stdin_memory_map, data_size);
  munmap(stdout_memory_map, data_size);
}