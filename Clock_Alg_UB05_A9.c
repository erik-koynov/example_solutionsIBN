#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//By Erik Koynov

struct RAM_page{
	unsigned int frame_index; 
	unsigned int read_bit;
	int page_number;
	struct RAM_page* next;
};
void initialize_memory(struct RAM_page* , int );

int main(int argc, const char * argv[]){
	int N = atoi(argv[1]);
	struct RAM_page *page = malloc(sizeof(struct RAM_page));
	page->frame_index = 0;
	page->read_bit = 0;
	page-> page_number = -1;
	page->next = page;
	initialize_memory(page,N);

	// pointers for the searches
	struct RAM_page *pointer = page;
	struct RAM_page *c_pointer = page;

	// pointer as described by the algorithm 
	struct RAM_page *last_start = page;

	// working process of memory
	while (1){
		
		printf("\nEnter the index of the page we want to store in RAM : ");
		int idx;
		scanf("%d",&idx);
		//getc(stdin);
		int present = 0;
		// check if page is already present
		printf("checking inside RAM\n");
		printf("POINTER currently pointing at : %i\n", last_start->frame_index );
		c_pointer = pointer;
		while(1){
			
			// if the page is already present -> update the read_bit to 1
			

			if (pointer->page_number == idx){
				printf("page is in RAM\n");
				pointer->read_bit = 1;
				printf("current frame index: %i, page number : %i\n", pointer->frame_index, pointer->page_number);
				// pointer to the next page 
				//pointer = pointer->next;
				
				
				present = 1;
				break;
			}


			// if the current slot neither the current slot is free nor contains the page we want -> increase the pointer
			// if we have traversed the whole RAM -> break and go to the next phase of the algorithm
			else{	
				
				pointer = pointer->next;
				
				if (pointer == c_pointer){
					printf("page is not in RAM\n");
					
					
					//pointer = pointer->next;
					break;
				}
				
			}
		}
		if (present==0){
			printf("beginning page replacement\n");}
		// insert new pages
		while (present==0){
			
			// if there are free slots -> store the page in that free slot
			if (last_start->page_number == -1){
				printf("there are free slots\n");
				
				last_start->read_bit = 1;
				printf("current frame index: %i\n", last_start->frame_index);
				last_start->page_number=idx;
				last_start = last_start->next; // incrementing LAST START
				
				printf("POINTER is being incremented %i\n",last_start->frame_index);
				pointer = pointer->next;
				printf("%p%p",last_start,pointer);
				//printf("going to next frame : %i\n", pointer->frame_index);
				
				present = 1;
				break;
			}
			if (last_start->read_bit == 0){
				printf("there are no free slots\n");
				printf("current frame index: %i, page number : %i\n", last_start->frame_index, last_start->page_number);
				last_start->page_number = idx;
				last_start->read_bit = 1;
				last_start= last_start->next;
				pointer = last_start;
				printf("POINTER is being incremented %i\n",last_start->frame_index);
				break;
			}
			last_start->read_bit = 0;
			last_start = last_start->next;
		}
		//print current state
		struct RAM_page *p = page;
		printf("FRM | PAG | RB |\n");
		while (1){
			if (last_start->frame_index == p->frame_index){
				printf("| %i | %i | %i |<---\n",p->frame_index, p->page_number, p->read_bit);
			}
			else{
			printf("| %i | %i | %i |\n",p->frame_index, p->page_number, p->read_bit);
			}
			if (p->next == page){break;}
			p = p->next;
		}	
	}
	printf("%i",page->next->next->read_bit);
} 

void initialize_memory(struct RAM_page* initial_page, int RAM_size){
	struct RAM_page *current_page = initial_page;
	printf("initializing RAM\n\n");
	for (int i=1; i<RAM_size; i++){
		struct RAM_page *next_page = malloc(sizeof(struct RAM_page));
		next_page->frame_index = i;	
		next_page->page_number = -1;
		next_page->next = initial_page;
		current_page->next =  next_page;
		current_page = next_page;
	}

}
