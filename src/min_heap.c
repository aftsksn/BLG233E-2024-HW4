#include <stddef.h>
#include "../include/min_heap.h"

// !!!!!!!!!   memcpy(dest,src,size)    !!!!!!!!!


// HELPER FUNCTIONS
size_t parent(size_t i){return (i-1) / 2;}
size_t left_child(size_t i){return 2*i + 1;}
size_t right_child(size_t i){return 2*i + 2;}

void swap(void *x, void *y, size_t size)
{
    void *temp = (void*) malloc(size);
    memcpy (temp, x, size);
    memcpy (x, y, size);
    memcpy (y, temp, size);
    free(temp); // very importante
}

//BU INSERTTE İŞİMİZE YARAYACAK
void heapify_up(MinHeap *heap, size_t index)
{
    if (index < 0 || index >= heap->size) return; //invalid index
    size_t parent_index = parent(index); 
    while (index > 0 && heap->compare((char*)heap->data + heap->element_size * index, 
                                      (char*)heap->data + heap->element_size * parent_index) < 0) 
    { // İLKİ KÜÇÜKSE NEGATİF DÖNDÜRÜYORMUŞ, BURDA PARENT DAHA BÜYÜKSE (DÜZ İNDEXTEKİ DAHA KÜÇÜKSE) SWAP ATCAZ
        swap ((char*)heap->data + index * heap->element_size,
              (char*)heap->data + parent_index * heap->element_size, heap->element_size);
              // INDEXLERI GUNCELLE DEVAM
              index = parent_index;
              parent_index = parent(index);
    }
}

// BU ROOTU SİLMEDE İŞE YARAYACAK
void heapify_down(MinHeap *heap, size_t index)
{
    if (index < 0 || index >= heap->size) return; //invalid index
    size_t left_child_index, right_child_index, index_smallest;

    while (1) 
    {
        left_child_index = left_child(index);
        right_child_index = right_child(index);
        index_smallest = index;

        if (left_child_index < heap->size && 
            heap->compare((char*)heap->data + left_child_index * heap->element_size, 
                          (char*)heap->data + index_smallest * heap->element_size) < 0) 
        {
            index_smallest = left_child_index;
        }

        if (right_child_index < heap->size && 
            heap->compare((char*)heap->data + right_child_index * heap->element_size, 
                          (char*)heap->data + index_smallest * heap->element_size) < 0) 
        {
            index_smallest = right_child_index;
        }

        if (index_smallest == index) break;
        swap((char*)heap->data + index * heap->element_size, 
             (char*)heap->data + index_smallest * heap->element_size, 
             heap->element_size);
        // UPDATELE DEVAM
        index = index_smallest;
    }
}

// Creates a new heap with initial capacity
// Element_size specifies the size of stored elements in bytes
// Compare function must return negative if first argument is smaller
MinHeap* heap_create(size_t capacity, size_t element_size, 
                    int (*compare)(const void*, const void*))
{
    MinHeap *heap = (MinHeap*) malloc(sizeof(MinHeap));
    if (NULL == heap) return NULL;
    
    heap->data = (void*) malloc(element_size * capacity);
    if (NULL == heap->data) {free (heap); return NULL;} // if you dont free the heap, memory leak can occur
    
    heap->capacity = capacity;
    heap->element_size = element_size;
    heap->size = 0;
    heap->compare = compare;
    return heap;
}

// Deallocates all memory used by the heap
void heap_destroy(MinHeap* heap)
{
    if (heap != NULL)
    {
    free(heap->data);
    free(heap);
    }
}

// Adds new element to heap
// Element is added at the end and bubbled up to maintain heap property
// If heap is full, capacity is doubled automatically
// Returns 1 if successful, 0 if memory allocation fails
int heap_insert(MinHeap* heap, const void* element)
{
    if (heap->size >= heap->capacity) // büyük olmaz da riske atmayalım baba
    {
        // sanıyorum datayı realloca eşitlesek sknt oluyor o yüzden böyle implement ettim, kati delilim yok
        void* new_data = realloc(heap->data, heap->capacity * 2 * heap->element_size);
        if (!new_data) return 0;
        heap->data = new_data;
        heap->capacity *= 2;
    }
    memcpy((char*)heap->data + heap->size * heap->element_size, element, heap->element_size);
    heapify_up(heap, heap->size++); // havalı coding şekli
    return 1;
}

// Removes and returns the minimum element (root)
// Last element is moved to root and bubbled down
// Returns 1 if successful, 0 if heap is empty
int heap_extract_min(MinHeap* heap, void* result)
{
    if (heap->size == 0) return 0;

    memcpy(result, heap->data, heap->element_size); //rootu resulta gönder
    heap->size--; 
    memcpy(heap->data, (char*)heap->data + heap->element_size * heap->size, heap->element_size); // son elementi root yap
    heapify_down(heap, 0); // roottan başlayıp düzelt
    return 1;
}

// Returns the minimum element without removing it
// Returns 1 if successful, 0 if heap is empty
int heap_peek(const MinHeap* heap, void* result)
{
    if (heap->size == 0) return 0;
    memcpy (result, heap->data, heap->element_size); // rootu resulta gönder
    return 1;
}

// Returns current number of elements in heap
size_t heap_size(const MinHeap* heap) {return heap->size;}

// Merges heap2 into heap1
// Grows capacity of heap1 if needed
// Returns 1 if successful, 0 if memory allocation fails or heaps are incompatible
int heap_merge(MinHeap* heap1, const MinHeap* heap2)
{
    for (size_t i = 0; i < heap2->size; i++) {
        // heap2 elemanlarını birer birer koycaz, malloc hatası alırsak 0 çevircek ife gircek 0 returnleyecek olmazsa 1 returnleyecek
        if (!heap_insert(heap1, (char*)heap2->data + heap2->element_size * i)) 
        {
            return 0;
        }
    }
    return 1;
}