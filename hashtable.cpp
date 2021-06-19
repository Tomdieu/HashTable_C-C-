#include<iostream>
#include<string.h>

using namespace std;

typedef struct node
{
    string key;
    string value;
}val;

//declaration of my list
typedef struct ht_table
{
    val value;
    struct ht_table *next;
}ht_table;

//declaration of my class Hashtable
class HashTable
{
private:
    ht_table *array[26] = {NULL};
    //function to sort an index of list in array
    void sort(ht_table * list)
    {
        int swapped,i;
        ht_table *ptr,*lptr = NULL;
        if(list == NULL)
            return;

        do
        {
            swapped = 0;
            ptr = list;
            while(ptr->next != lptr)
            {
                if(ptr->value.key > ptr->next->value.key)
                {
                    swap(ptr,ptr->next);
                    swapped = 1; 
                }
                ptr = ptr->next;
            }
            lptr = ptr;
        }while(swapped);
    }

    //use to swap two node list
    void swap(ht_table *a,ht_table *b)
    {
        val tmp = a->value;
        a->value = b->value;
        b->value = tmp;
    }

public:
    //this function return the correct index where to insert the element
    int getKey(string key)
    {
        int i = 0;
        for(char c = 'a'; i <= 25 && c <= 'z';c++,i++ )
        {
            if((key[0] == c ) or ((key[0]+32) == c))
            {
                return i;
            }
        }
        return i;
    }

    //function to add in hashtable
    void add(string key,string value)
    {
        int k = getKey(key);
        ht_table *n = NULL,*e = NULL;
        e = (ht_table*)malloc(sizeof(ht_table));
        
        e->value.key = key;
        e->value.value = value;
        e->next = NULL;

        if(e == NULL)
            exit(0);
        n = array[k];
        if(n == NULL)
        {
            array[k] = e;
        }
        else
        {
            for(;n->next != NULL;n = n->next);
            n->next = e;
        }
        //at this poin i sort my list at position array[k]
        sort(array[k]);
    }
    
    //function use to print the list
    void print()
    {
        char a('A');
        for(int i = 0;i <= 25 && a<= 'Z';i++,a++)
        {
            cout<<a<<" -> ";
            for(ht_table *n = array[i];n != NULL;n = n->next)
            {
                cout<<"["<<n->value.key<<" : "<<n->value.value<<"] ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    //this function search in the hashtable the key pass in parameter
    string search(string key)
    {
        int k = getKey(key);

        ht_table *r = array[k];

        if(r == NULL)
            return NULL;
        for(;r != NULL;r= r->next)
        {
            if(r->value.key == key)
            {
                return r->value.value;
            }
        }
        return "";
    }

    //this function permits me to add at the end of a list
    void push(ht_table **list,string k,string v)
    {
        ht_table *e = NULL,*tmp;
        e = (ht_table*)malloc(sizeof(ht_table));
        
        e->value.key = k;
        e->value.value = v;
        e->next = NULL;

        if(*list == NULL)
        {
            *list = e;
        }
        else
        {
            tmp = *list;
            for(;tmp->next != NULL;tmp = tmp->next);
            tmp->next = e;
        }
    }

    //this function delete the key and value pass in parameter if it exist
    void remove(string key)
    {
        int k = getKey(key);

        if(array[k] == NULL)
            return;

        ht_table *list = NULL;
        ht_table *n = array[k];

        for(;n != NULL;n = n->next)
        {
            if(n->value.key != key)
            {
                push(&list,n->value.key,n->value.value);
            }
        }

        array[k] = list;
    }

    //this function set all the index of array to NULL
    void Free()
    {
        for(int i=0;i<26;i++)
        {
            if(array[i] != NULL)
                array[i] = NULL;
        }
    }

};

int main(int argc, char const *argv[])
{
    HashTable p ;

    p.add("Ivan","A programmer C/C++ and python programmer");
    p.add("python","Is The Best Programming Language In The World.");
    p.add("C","C is one of my best Programming language");
    p.add("Pascal","The First programming language i learn");
    p.print();
    cout<<p.search("I")<<endl;
    p.remove("Ivan");
    p.print();
    p.Free();
    p.print();
    return 0;
}