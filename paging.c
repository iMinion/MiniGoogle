#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

char* get_page(char *loc);
char* get_next_target();

char* content;

int main(int argc, char *argv[]) {
	content = get_page("check1.html");
	printf("%s\n", content);
	printf("%s\n", get_next_target());
	printf("%s\n", content);
	return 0;
}

char* get_page(char *loc) {
	char *page;
	page = (char *) malloc(1024 * sizeof(char));
	FILE *fp = fopen(loc, "r");
	char buffer[1024];
	while(fgets(buffer, 1024, fp) != NULL) {
		page = realloc(page, strlen(page) + 1 + 1024);
		strcat(page, buffer);
	}
	return page;
}

char* get_next_target() {
	char *link;
	char *ref;
	ref = (char *) malloc(1);
	strcpy(ref, "href");
	int i;
	char *ptr = strstr(content, ref);
	if (ptr == NULL) {
		return NULL;
	}
	else {
		ptr = index(ptr, '\"');
		ptr++;
		link = (char *) malloc(1);
		while(ptr[0] != '\"') {
			int pre = strlen(link);
			link = realloc(link, strlen(link) + 2);
			link[pre] = ptr[0];
			ptr++;
		}
		printf("Hello\n");
		ptr++;
		content = ptr;
		return link;
	}
}