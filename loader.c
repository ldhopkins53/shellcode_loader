#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
  // Check file specified on CLI is valid
  if (argc != 2) {
    fprintf(stderr, "[-] Usage: %s SHELLCODE_FILE\n", argv[0]);
    exit(EXIT_FAILURE);
  } else if (access(argv[1], F_OK) != 0) {
    fprintf(stderr, "[-] Unable to access %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  char *shellcode_file = argv[1];
  printf("[+] Loading %s\n", shellcode_file);

  // Get file size
  struct stat st;
  stat(shellcode_file, &st);
  printf("[+] File is %lu bytes\n", st.st_size);

  // Open file
  FILE *fd = NULL;
  if ((fd = fopen(shellcode_file, "r")) == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  // Load file into memory and execute it directly
  printf("[+] Mapping shellcode into memory\n");
  void (*shellcode)() =
      mmap(NULL, st.st_size, PROT_READ | PROT_EXEC, MAP_PRIVATE, fileno(fd), 0);
  if (shellcode == MAP_FAILED) {
    perror("mmap");
    exit(EXIT_FAILURE);
  }

  printf("[+] Executing shellcode\n");
  shellcode();

  fclose(fd);
  return EXIT_SUCCESS;
}
