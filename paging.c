#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

char* get_page(char *loc);
char* get_next_target();
char** get_all_links();

char* content;

int main(int argc, char *argv[]) {
	content = get_page("check1.html");
	printf("%s\n", content);
	// printf("%s\n", get_next_target());
	char **links = get_all_links();
	int j = sizeof(links)/sizeof(char **);
	for(int i = 0; links[i] != '\0'; i++) {
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
		link[0] = '\0';
		int i = 0;
		while(ptr[0] != '\"') {
			int pre = strlen(link);
			link = realloc(link, strlen(link) + 2);
			link[pre] = ptr[0];
			link[pre + 1] = '\0';
			ptr++;
		}
		ptr++;
		content = ptr;
		return link;
	}
}

char** get_all_links() {
	char **links = (char **) malloc(sizeof(char *));
	char *link;
	int i = 0;
	while((link = get_next_target()) != NULL) {
		links = realloc(links, (i + 2) * sizeof(char *));
		links[i] = link;
		i++;
	}
	links[++i] = '\0';
	return links;
}