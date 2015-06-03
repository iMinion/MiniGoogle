#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

char* get_page(char *loc);
char* get_next_target(char **);
char** get_all_links(char **);
void crawl_web(char *);
int contains(char ***, char *);
int size(char ***);




int main(int argc, char *argv[]) {
	char *content = get_page("bing.html");
	char **links = get_all_links(&content);
	int i = 0;
	for(i = 0; links[i][0] != '\0'; i++) {
		// printf("%s\n", links[i]);
	}
	crawl_web("bing.html");
	return 0;
}

char* get_page(char *loc) {
	char *page;
	page = (char *) malloc(1024 * sizeof(char));
	FILE *fp = fopen(loc, "r");
	char buffer[1024];
	if(fp == NULL) {
		printf("File Not Found %s\n", loc);
		return NULL;
	}
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
		ptr = index(ptr, '</a>');
		ptr += 4;
		*content = ptr;
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
	}
	links[i] = (char *) malloc(1);
	links[i][0] = '\0';
	return links;
}

void crawl_web(char *seedurl) {
	char **visited = (char **) malloc(sizeof(char *) * 2);
	char **queue = (char **) malloc(sizeof(char *) * 2);
	char **processqueue = (char **) malloc(sizeof(char *) * 2);
	int sizev, sizeq, sizepq = 10;
	queue[0] = seedurl;
	queue[1] = (char *)malloc(1);
	queue[1][0] = '\0';
	visited[0] = (char *) malloc(1);
	visited[0][0] = '\0';
	processqueue[0] = (char *)malloc(1);
	processqueue[0][0] = '\0';
	while(queue[0][0] != '\0') {
		int i = 0;
		int j = 1;
		while(queue[i][0] != '\0') {
			if(contains(&visited, queue[i]) == 0) {
				sizev = size(&visited);
				visited = realloc(visited, (sizev + 2) * sizeof(char *));
				visited[sizev] = (char *)malloc(1);
				strcpy(visited[sizev], queue[i]);
				visited[sizev + 1] = (char *)malloc(1);
				visited[sizev + 1][0] = '\0';
				char *content = get_page(queue[i]);
				if(content != NULL) {
					char **links = get_all_links(&content);
					if(links != NULL) {
						int k = 0;
						while(links[k][0] != '\0') {
							if(contains(&visited, links[k]) == 0 
								&& index(links[k], '#') == NULL) {
								sizepq = size(&processqueue);
								processqueue = realloc(processqueue, 
												(sizepq + 2) * sizeof(char *));
								processqueue[sizepq] = (char *) malloc(1);
								strcpy(processqueue[sizepq], links[k]);
								processqueue[sizepq + 1] = (char *)malloc(1);
								processqueue[sizepq + 1][0] = '\0';
							}
							k++;
						}
					}
				}
			}
			i++;
		}
		queue = (char **)malloc(size(&processqueue) * sizeof(char *));
		queue[0] = (char *) malloc(1);
		queue[0][0] = '\0';
		int l = 0;
		sizepq = size(&processqueue);
		while(l < sizepq) {
			queue[l] = 
				(char *) malloc((strlen(processqueue[l]) + 1) * sizeof(char));
			strcpy(queue[l], processqueue[l]);
			l++;
		}
		queue[l] = (char *) malloc(1);
		queue[l][0] = '\0';

		processqueue = (char **)malloc(sizeof(char *));
		processqueue[0] = (char *) malloc(1);
		processqueue[0][1] = '\0';
	}
	int i = 0;
	sizev = size(&visited);
	while(i < sizev) {
		printf("%s\n", visited[i]);
		i++;
	}
}

int contains(char ***visited, char *tbf) {
	int i = 0;
	char **vis = *visited;
	while(vis[i][0] != '\0') {
		if(strcmp(vis[i], tbf) == 0) {
			return 1;
		}
		i++;
	}
	return 0;
}

int size(char ***array) {
	int i = 0;
	char **vis = *array;
	while(vis[i][0] != '\0') {
		++i;
	}
	return i;
}