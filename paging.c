#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

char* get_page(char *loc);
char* get_next_target(char **);
char** get_all_links(char **);

int main(int argc, char *argv[]) {
	char *content = get_page("check1.html");
	char **links = get_all_links(&content);
	int i = 0;
	for(i = 0; links[i] != '\0'; i++) {
		printf("%s\n", links[i]);
	}
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

char* get_next_target(char **content) {
	char *link;
	char *ref;
	ref = (char *) malloc(1);
	strcpy(ref, "href");
	int i;
	char *ptr = strstr(*content, ref);
	if (ptr == NULL) {
		return NULL;
	}
	else {
		ptr = index(ptr, '\"');
		ptr++;
		int len = index(ptr, '\"') - ptr;
		link = (char *) malloc(len * sizeof(char) + 1);
		int i = 0;
		while(i < len) {
			link[i] = ptr[i];
			i++;
		}
		link[i] = '\0';
		ptr = index(ptr, '\"');
		ptr++;
		*content = ptr;
		printf("In get next target");
		printf("%s\n", *content);
		return link;
	}
}

char** get_all_links(char **content) {
	char **links = (char **) malloc(sizeof(char *));
	char *link;
	int i = 0;
	while((link = get_next_target(content)) != NULL) {
		links = realloc(links, (i + 2) * sizeof(char *));
		links[i] = link;
		i++;
		printf("In all links\n");
		printf("%s\n", *content);
	}
	links[i] = '\0';
	return links;
}