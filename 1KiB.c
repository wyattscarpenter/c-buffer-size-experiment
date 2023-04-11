#include <stdio.h>
#include <assert.h>
#include <stdint.h>
int main(void){
  const size_t buffer_size = 1024UL; //note: the maximum buffer size my system will accept in fread seems to be 1MiB.
  assert(buffer_size > 0 && buffer_size < SIZE_MAX);
  const size_t data_size = 10ULL * 1024ULL*1024ULL*1024ULL; // 10LL*1000000000LL; //10 billion, 10 GB.
  assert(buffer_size <= data_size);
  unsigned char buffer[buffer_size];
  for(size_t i = 0; i < data_size; i+=buffer_size){  
    int ignored_error_code = fread(buffer, buffer_size, 1, stdin);
    fwrite(buffer, buffer_size, 1, stdout);
  }
}