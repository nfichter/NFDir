#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include <sys/stat.h>
#include <time.h>

#include <string.h>
#include <errno.h>

int ls(char * path) {
  //PRINT FILES
  DIR * dirStream = opendir(path);
  struct dirent * file = readdir(dirStream);

  printf("\ndirectories:\n\n");
  while (file) {
    if (file->d_type == DT_DIR) {
      printf("%s\n",file->d_name);
    }
    file = readdir(dirStream);
  }

  closedir(dirStream);
  dirStream = opendir(path);
  file = readdir(dirStream);

  int size = 0;
  struct stat *buf = malloc(sizeof(struct stat));
  printf("\nfiles:\n\n");
  while (file) {
    if (file->d_type == DT_REG) {
      printf("%s\n",file->d_name);
      //SIZE STUFF
      stat(file->d_name,buf);
      size += buf->st_size;
      //==========
    }
    file = readdir(dirStream);
  }

  //FILE SIZE
  printf("\nsize: ");
  long B = size;
  long KB = B / 1024.0;
  long MB = KB / 1024.0;
  long GB = MB / 1024.0;

  if (KB > 1) {
    if (MB > 1) {
      if (GB > 1) {
	printf("%luGB\n",GB);
      }
      else {
	printf("%luMB\n",MB);
      }
    }
    else {
      printf("%luKB\n",KB);
    }
  }
  else {
    printf("%luB\n",B);
  }
  

  //
}

int main() {
  ls(".");
  return 0;
}
