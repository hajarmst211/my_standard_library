// memory_allocation_library.c

#include <unistd.h>

typedef struct MetaData{
    size_t size;
    int is_free;// 1 : free , 0 : allocated
    struct MetaData *next_chunk;
    struct MetaData *previous_chunk;
}MetaData;

static MetaData* free_chunks_list_head = NULL;

MetaData* search_available_chunk(size_t needed_size, MetaData* head){
    MetaData* current = head;
    while (current != NULL)
    {
        if (current->is_free && current->size >= needed_size)
            return current;
        current = current->next_chunk;
    }
    return NULL;
}

void remove_allocated_chunk(MetaData** chunk_to_remove){
    MetaData* metadata = *chunk_to_remove;
    MetaData* previous_chunk = metadata->previous_chunk;
    metadata->previous_chunk = NULL;
    MetaData* next_chunk = metadata->next_chunk;
    metadata->next_chunk = NULL;
    // changing the pointing ordre
    // topology checks for the next chunk
    if(metadata == NULL) return;

    if(next_chunk != NULL){
        next_chunk->previous_chunk = next_chunk;
    }

    // topology checks for the previous chunk
    if(previous_chunk != NULL)
        previous_chunk->next_chunk = next_chunk;
    else //that's gonna be the head 
        free_chunks_list_head = next_chunk;
}

void trim_chunk(MetaData* allocated_chunk, size_t needed_size){
    if(allocated_chunk == NULL) return;

    if(allocated_chunk->size <= needed_size + sizeof(MetaData)) return;
    
    MetaData* free_chunk= (MetaData*)((char*)allocated_chunk + needed_size); 
    size_t left_size = allocated_chunk->size - needed_size;
    //updating the size:
    allocated_chunk->size = needed_size; 
    //Setting the free_chunk parameters:
    free_chunk->is_free = 1;
    free_chunk->size = left_size;
    free_chunk->next_chunk = free_chunks_list_head;
    free_chunk->previous_chunk = NULL;
    //this wasnt intuitive to me. At first i tried to insert it at the end of the list
    // But, turned out that inserting at the begining is wiser because it allows to the just freed chunks to be used earlier and it has a O(1) time complexity
    if(free_chunks_list_head != NULL)
        free_chunks_list_head->previous_chunk = free_chunk;

    free_chunks_list_head = free_chunk;
}


void* request_memory_from_os(MetaData* metadata, size_t needed_size){
    void* new_system_break = sbrk(needed_size);
     if(new_system_break == (void*) -1)
        return NULL;
    
    // making the metadata:
    metadata= (MetaData*) new_system_break;
    metadata->is_free = 0;
    metadata->size = needed_size;
    metadata->next_chunk = NULL;
    metadata->previous_chunk = NULL;

    //returning a pointer to the user's data:
    void* users_data = (char*)(metadata +1);
    return users_data;
}

void* halloc(size_t data_size){
    if(data_size == 0) return NULL;

    size_t needed_size = data_size + sizeof(MetaData);
    // Find an available chunk:
    MetaData* available_chunk = search_available_chunk(needed_size, free_chunks_list_head);
    //Allocating memory:
    if(available_chunk != NULL){
        remove_allocated_chunk(&available_chunk);
        available_chunk->is_free = 0;
        trim_chunk(available_chunk, needed_size);
        return (char*)(available_chunk +1);//users data
    }

    return request_memory_from_os(available_chunk,  needed_size);
}

void free_pointer(void* chunk_ptr){
    if(chunk_ptr == NULL) return;

    MetaData* chunk = (MetaData*)((char*)chunk_ptr - sizeof(MetaData));
    chunk->is_free = 1;
    chunk->next_chunk = free_chunks_list_head;
    chunk->previous_chunk = NULL;
    if(free_chunks_list_head != NULL)
        free_chunks_list_head->previous_chunk = chunk;

    free_chunks_list_head = chunk;
}
