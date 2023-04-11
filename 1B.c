#include <stdio.h>
int main(void){
  const size_t buffer_size = 1;
  const size_t data_size = 10ULL * 1024ULL*1024ULL*1024ULL; // 10 bibillion, 10 GiB.
  for(size_t i = 0; i < data_size; i+=buffer_size){
    int c = getchar();
    putchar(c);
  }
}