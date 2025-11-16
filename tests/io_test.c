#include "../header/my_library.h"
#include <stdio.h>
#include <fcntl.h>

int main(){
char *filename = "test.txt";

    printf("=== Testing File Utilities ===\n\n");

    // 1. Check existence
    printf("[1] does_exist before creation: %d\n", does_exist(filename));

    // 2. Create and write content
    printf("[2] overwrite_file -> creating file and writing text...\n");
    overwrite_file(filename, "Hello World!");

    printf("[3] does_exist after creation: %d\n", does_exist(filename));

    // 3. Read content
    printf("[4] read_from_file:\n");
    char *content = read_from_file(filename);
    printf("    Content: %s\n", content);

    // 4. Append
    printf("[5] append_to_file -> adding new text...\n");
    append_to_file(filename, "\nAppended text line.");

    // 5. Read again to verify append
    char *new_content = read_from_file(filename);
    printf("[6] Content after append:\n%s\n", new_content);

    // 6. Read from offset
    printf("[7] read_at_offset (offset 6):\n");
    char *partial = read_at_offset(filename, 6);
    printf("    Data starting at offset 6: %s\n", partial);

    // 7. Copy file
    printf("[8] copy_file -> making copy.txt...\n");
    int copy_status = copy_file(filename);
    printf("    Copy status: %d\n", copy_status);
    printf("    Copy content:\n%s\n", read_from_file("copy.txt"));

    // 8. Change permissions
    printf("[9] set_permissions(0666)...\n");
    set_permissions(filename, 0666);
    printf("    Done.\n");

    // 9. File size
    printf("[10] File size of test.txt: ");
    int fd = open_file(filename, O_RDONLY, 0);
    printf("%d bytes\n", get_file_size(fd));
    close(fd);

    // 10. Remove
    printf("[11] remove_file -> deleting test.txt and copy.txt...\n");
    remove_file(filename);
    remove_file("copy.txt");

    printf("[12] does_exist after remove: %d\n", does_exist(filename));

    printf("\n=== All tests executed ===\n");
    return 0;
}