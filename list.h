typedef struct list {
	int a;
	struct list* next;
}list;
list* read(int);
void read_line(list**, list*);
void output(list* p);