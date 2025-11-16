#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../header/my_library.h"

int does_exist(char* path_to_file){
    return access(path_to_file, F_OK) == 0;
}

int open_file(char* path_to_file, int flags,  mode_t mode){
        if(flags & O_CREAT) {
        return open(path_to_file, flags, mode);  // mode needed
    } else {
        return open(path_to_file, flags);        // mode not needed
    }
}

int get_file_size(int file_descriptor){
    struct stat file_metadata ;
    if (fstat(file_descriptor, &file_metadata) < 0) {
        return -1;
    }

    return file_metadata.st_size;
}

int remove_file(char* path_to_file){
    if(!does_exist(path_to_file)){
        return -1;
    }
    int return_value = unlink(path_to_file);
    return return_value;
}

int set_permissions(char* path_to_file, int permissions){
    if(!does_exist(path_to_file)){
        if(!open(path_to_file, O_CREAT , permissions))
            return -1;
    }
    chmod(path_to_file, permissions);
    return 0;
}

char* read_from_file(char *path_to_file){
int file_descriptor = open(path_to_file, O_RDONLY);
    if(file_descriptor < 0){
        return "File not opened";
    }

    int file_size = get_file_size(file_descriptor);
    char* buffer = (char*)malloc(file_size*sizeof(char));
    if(!buffer){
        free(buffer);
        return "Memory allocation failed"; 
    }
    
    int read_bits = read(file_descriptor, buffer, file_size);
    if(read_bits < 0){
        free(buffer);
        return "no bits were read from the file";
    }

    buffer[file_size] = '\0';
    close(file_descriptor);
    return buffer;
}

char* read_using_fd(int file_descriptor){
    int file_size = get_file_size( file_descriptor);
    char* buffer = (char*)malloc(file_size*sizeof(char));
    if(!buffer){
        free(buffer);
        return "Memory allocation failed"; 
    }
    
    int read_bits = read(file_descriptor, buffer, file_size);
    if(read_bits < 0){
        free(buffer);
        return "no bits were read from the file";
    }

    buffer[file_size] = '\0';
    close(file_descriptor);
    return buffer;
}

char* read_at_offset(char* path_to_file, off_t offset){
    int file_descriptor = open(path_to_file, O_RDONLY);
    if(file_descriptor < 0){
        return "File not opened";
    }
    int whence = SEEK_SET; //to apply the function to the offset relative to the beginnig of the file
    off_t current_offset = lseek( file_descriptor, offset, whence);

    return read_using_fd(file_descriptor);
}

int overwrite_file(char* path_to_file, char* buffer){
    // S_IWOTH: write permission for others
    int buffer_size = length_string(buffer);
    //if the file does not exist we creat it and write on it
    int file_descriptor = open(path_to_file, O_CREAT |  O_TRUNC | O_WRONLY, 0644); 

    if (file_descriptor < 0) {
        perror("open failed");
        return 1;
    }

    ssize_t write_status = write(file_descriptor, buffer, buffer_size);
    if(write_status < 0){
        return 1;
    }
    close(file_descriptor);
    return 0;
}

int append_to_file(char* path_to_file, char* buffer){
    // S_IWOTH: write permission for others
    int buffer_size = length_string(buffer);
    int file_descriptor = open(path_to_file, O_CREAT | O_APPEND | S_IWOTH); 

    ssize_t write_status = write(file_descriptor, buffer, buffer_size);
    if(write_status < 0){
        return 1;
    }
    close(file_descriptor);
    return 0;
}

int copy_file(char* path_to_file){
    char* data = read_from_file(path_to_file);
    if(!data)
        return -1;

    int copy_fd = overwrite_file("copy.txt", data);

    return copy_fd;
}