// data_structures.c

#include <stdint.h>
#include <unistd.h>
#include <assert.h>

typedef struct Metadata{
    size_t size;
    int is_free;// 1 : free , 0 : allocated
    struct Metadata *next;
}Metadata;

Metadata* create_metadata(size_t block_size, void* old_break){
    Metadata* meta = (Metadata*) old_break;
    meta->size = block_size;
    meta->is_free = 0;
    meta->next = NULL;
    return meta ;
}

void* my_malloc(size_t data_size){
    void* old_break = sbrk(0);
    size_t block_size = data_size + sizeof(Metadata);
   // the programme break will increase with the given size but retrurn sbrk(0)
    void* new_break = sbrk(block_size);

    if(new_break == (void*) -1){
        return NULL;
    }
    else{
        assert(new_break == old_break);
        Metadata* metadata = create_metadata(block_size, old_break);
        void* users_data = metadata + 1;
        return users_data;
    }
}
//returns a pointer to a free block adapted to the data_size + metadata_size
Metadata* request_malloc(Metadata** head, size_t data_size){
    Metadata* user_data;
    //first allocation: creation of the head
    if(head == NULL){
        user_data = my_malloc(data_size);
        *head = (Metadata*)user_data - 1;
    }
    if(head != NULL){
        Metadata* current = *head;
        Metadata* previous;
        size_t requested_size = data_size + sizeof(Metadata) ;

        while(!current && (current->size < requested_size || current->is_free == 0)){
            previous = current;
            current = current->next;
        }

        if(!current){
            user_data = my_malloc(data_size);
            previous->next = (Metadata*)user_data - 1;
        }

        else if(current->size >= requested_size || current->is_free == 0){
            //find last element
            current = NULL;
            while((*head)->next != NULL){
                *head = (*head)->next;
                current = (*head);
            }
            user_data = my_malloc(data_size);
            previous->next = (Metadata*)user_data -1;
            }
        return (Metadata*)user_data - 1;
    }
}

Metadata* free_meta(Metadata** meta){
    (*meta)->is_free = 1;
    (*meta)->next = NULL;
    return *meta;
}

void* my_free(Metadata* metadata){
    if(metadata == NULL){
        return NULL;
    }
    else{   
        void* current_break = sbrk(0);
        assert(metadata == current_break);
        free_meta(&metadata);
    }
    void* decremented_break = sbrk(- (uintptr_t)metadata);
    return decremented_break;
}

void* my_realloc(void* data_ptr){


}
