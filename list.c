#include "list.h"
#include <stdio.h>
#include <stdlib.h>
list* read(int t) {
	list* new = malloc(sizeof(list));
	new->a = t;
	new->next = NULL;
	return new;
}
void read_line(list** p, list* new_list) {
	list* pre = NULL, * cur = NULL;
	//pre = NULL;
	if (*p == NULL) {
		*p = new_list;
		return;
	}
	cur = *p;
	int i = 1;
	//for (;cur->a < new_list->a;pre = cur, cur = cur->next,i++) {
	//	if (i = 10) {
	//		free(new_list);
	//		return;
	//	}
	//	if (cur->next == NULL) {
	//		cur->next = new_list;
	//		return;
	//	}
	//}
	if (pre == NULL) {
		new_list->next = cur;
		*p = new_list;
	}
	else {
		if (i == 10) {
			pre->next = new_list;
			free(cur);
		}
		pre->next = new_list;
		new_list = cur;
	}
	return;
}
void output(list* p, int score[]) {
	int i = 1;
	if (p == NULL) {
		printf("ÔÝÎÞ¼ÇÂ¼£¡\n");
		return;
	}
	for (;;p = p->next) {
		if (p->next == NULL) {
			score[i] = p->a;
			//printf("%d\n",score[i]);
			return;
		}
		score[i] = p->a;
		//printf("%d\n",score[i]);
		i++;
	}
}