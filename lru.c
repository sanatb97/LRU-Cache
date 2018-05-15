#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef struct node
{
	int info;
	struct node *prev;
	struct node *next;
	

	}node;


typedef struct cache
{
	node *head;
	node *tail;
	int size;
	int curr;
	int phit;
	int pmiss;
	
}cache;

typedef struct Hash
{
	int size;
	node* *a;

}Hash;

Hash* create_Hash( int size )
{
    
    Hash* hash = (Hash *) malloc( sizeof( Hash ) );
    hash->size = size;
 
    
    hash->a = (node **) malloc( hash->size * sizeof( node* ) );
 
    
    for( int i = 0; i < hash->size; i++ )
        hash->a[i] = NULL;
 
    return hash;
}
int isFULL(cache *c);


node* create_node(int data)
{
	node *temp=(node *)malloc(sizeof(node));
	temp->info=data;
	temp->prev=NULL;
	temp->next=NULL;
	return(temp);


}

cache* create_cache(cache *c,int n)
{		
	c=(cache*)malloc(sizeof(cache));
	c->head=NULL;
	c->tail=NULL;
	c->size=n;
	c->curr=0;
	c->phit=0;
	c->pmiss=0;
	
	return(c);

}

int isFull(cache *c)
{
	return(c->size==c->curr);
}

int isEmpty(cache *c)
{
	return(c->tail==NULL);
}



void insert( cache* c, Hash* hash, int info )
{
    
    if ( isFull( c) )
    {
       
        hash->a[ c->tail->info ] = NULL;
        delete(c);
    }
 
        node* temp = create_node( info );
    temp->next = c->head;
 
   
    if ( isEmpty( c ) )
        c->tail = c->head = temp;
    else  
    {
        c->head->prev = temp;
        c->head = temp;
    }
 
    
    hash->a[ info] = temp;
 
   
    c->curr++;
}


void delete(cache *c)
{
	
    if( isEmpty( c ) )
        return;
 
    
    if (c->head == c->tail)
        c->head = NULL;
 
    
    node* temp = c->tail;
   	c->tail = c->tail->prev;
 
    if (c->tail)
        c->tail->next = NULL;
 
    free( temp );
 
    
    c->curr--;
}

void find_in_cache(cache *c,Hash *hash,int info)
{
	node* r = hash->a[ info ];
 
    
    if ( r == NULL )
    {
        insert( c, hash, info );
        c->pmiss++;
    }
 
    
    else if (r != c->head)
    {
        
        r->prev->next = r->next;
        if (r->next)
           r->next->prev = r->prev;
 
       
        if (r == c->tail)
        {
           c->tail = r->prev;
           c->tail->next = NULL;
        }
 
        
        r->next = c->head;
        r->prev = NULL;
 
        
        r->next->prev = r;
 
        
        c->head = r;
        c->phit++;
    }
}
void printcache(cache *c)
{
	node *t=c->head;
	while(t!=NULL)
	{
		printf("%d ",t->info);
		t=t->next;
	}
	printf("\n");
}

void main()
{
 	clock_t t;
    
	int n,f;
	printf("Enter the number of pages\n");
	scanf("%d",&n);
	printf("Enter the number of frames\n");
	scanf("%d",&f);
	cache *c;
	c=create_cache(c,f);
	Hash *hash=create_Hash(n);
	

	int a[n];
	printf("Enter the pages\n");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);

		
	}
	t = clock();
	for( int i=0;i<n;i++)
	{
		find_in_cache(c,hash,a[i]);
		printf("Currently in cache (Step %d) : " , (i+1));
		printcache(c);
	}
	 t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
printf("Cache hits:%d\n",c->phit);
printf("Cache misses:%d\n",c->pmiss);
printf("Time taken:%f s",time_taken);

}