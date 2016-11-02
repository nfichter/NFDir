#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

#include <sys/stat.h>
#include <time.h>

#include <string.h>
#include <errno.h>

int listFiles(char * path) {
  char * file_names[] = calloc(1000,sizeof(char));
  int num_in_files = 0;
  
  
  struct dirent *directory_names = calloc(10,sizeof(struct dirent));
  int num_in_directories = 0;
  
  DIR * dirStream = opendir(path);
  struct dirent * file = readdir(dirStream);
  while (file) {
    if (file->d_type == DT_DIR) {
      directory_names[num_in_directories] = file->d_name;
      num_in_directories++;
    }
    else {
      file_names[num_in_files] = file->d_name;
      num_in_files++;
    }
    file = readdir(dirStream);
  }

  struct dirent * fp = file_names;
  struct dirent * dp = directory_names;

  
  printf("\ndirectories:\n\n");
  while (dp != NULL) {
    printf("\t%s\n",&dp);
    dp++;
  }

  printf("\nfiles:s\n\n");
  while (fp != NULL) {
    printf("\t%s\n",&fp);
    fp++;
  }
}

int main() {
  listFiles(".");
  return 0;
}
