#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>


#define nswords 853;

char* get_page(char *loc);
char* get_next_target(char **);
char** get_all_links(char **);
void crawl_web(char *);
int contains(char ***, char *);
int size(char ***);
char** get_keywords(char *);
int is_stop_word(char *);
char** get_words(char *);
void add_page_to_index(char *);
void add_to_index(char *, char *, int j);

typedef struct map {
	char *url;
	int count;
}Map;

typedef struct index {
	char *keyword;
	Map **maps;
}indextable;

indextable **ds = NULL;

char stopwords[853][20] = {"'ll","'ve","a","a's","able","about","above","abroad","abst","accordance","according","accordingly","across","act","actually","added","adj","adopted","affected","affecting","affects","after","afterwards","again","against","ago","ah","ahead","ain't","all","allow","allows","almost","alone","along","alongside","already","also","although","always","am","amid","amidst","among","amongst","amoungst","amount","an","and","announce","another","any","anybody","anyhow","anymore","anyone","anything","anyway","anyways","anywhere","apart","apparently","appear","appreciate","appropriate","approximately","are","aren","aren't","arent","arise","around","as","aside","ask","asking","associated","at","auth","available","away","awfully","b","back","backward","backwards","be","became","because","become","becomes","becoming","been","before","beforehand","begin","beginning","beginnings","begins","behind","being","believe","below","beside","besides","best","better","between","beyond","bill","biol","both","bottom","brief","briefly","but","by","c","c'mon","c's","ca","call","came","can","can't","cannot","cant","caption","cause","causes","certain","certainly","changes","clearly","co","co.","com","come","comes","computer","con","concerning","consequently","consider","considering","contain","containing","contains","corresponding","could","couldn't","couldnt","course","cry","currently","d","dare","daren't","date","de","definitely","describe","described","despite","detail","did","didn't","different","directly","do","does","doesn't","doing","don't","done","down","downwards","due","during","e","each","ed","edu","effect","eg","eight","eighty","either","eleven","else","elsewhere","empty","end","ending","enough","entirely","especially","et","et-al","etc","even","ever","evermore","every","everybody","everyone","everything","everywhere","ex","exactly","example","except","f","fairly","far","farther","few","fewer","ff","fifteen","fifth","fify","fill","find","fire","first","five","fix","followed","following","follows","for","forever","former","formerly","forth","forty","forward","found","four","from","front","full","further","furthermore","g","gave","get","gets","getting","give","given","gives","giving","go","goes","going","gone","got","gotten","greetings","h","had","hadn't","half","happens","hardly","has","hasn't","hasnt","have","haven't","having","he","he'd","he'll","he's","hed","hello","help","hence","her","here","here's","hereafter","hereby","herein","heres","hereupon","hers","herself","herseâ€?","hes","hi","hid","him","himself","himseâ€?","his","hither","home","hopefully","how","how's","howbeit","however","hundred","i","i'd","i'll","i'm","i've","id","ie","if","ignored","im","immediate","immediately","importance","important","in","inasmuch","inc","inc.","indeed","index","indicate","indicated","indicates","information","inner","inside","insofar","instead","interest","into","invention","inward","is","isn't","it","it'd","it'll","it's","itd","its","itself","itseâ€?","j","just","k","keep","keeps","kept","keys","kg","km","know","known","knows","l","largely","last","lately","later","latter","latterly","least","less","lest","let","let's","lets","like","liked","likely","likewise","line","little","look","looking","looks","low","lower","ltd","m","made","mainly","make","makes","many","may","maybe","mayn't","me","mean","means","meantime","meanwhile","merely","mg","might","mightn't","mill","million","mine","minus","miss","ml","more","moreover","most","mostly","move","mr","mrs","much","mug","must","mustn't","my","myself","myseâ€?","n","na","name","namely","nay","nd","near","nearly","necessarily","necessary","need","needn't","needs","neither","never","neverf","neverless","nevertheless","new","next","nine","ninety","no","no-one","nobody","non","none","nonetheless","noone","nor","normally","nos","not","noted","nothing","notwithstanding","novel","now","nowhere","o","obtain","obtained","obviously","of","off","often","oh","ok","okay","old","omitted","on","once","one","one's","ones","only","onto","opposite","or","ord","other","others","otherwise","ought","oughtn't","our","ours","ours ","ourselves","out","outside","over","overall","owing","own","p","page","pages","part","particular","particularly","past","per","perhaps","placed","please","plus","poorly","possible","possibly","potentially","pp","predominantly","present","presumably","previously","primarily","probably","promptly","proud","provided","provides","put","q","que","quickly","quite","qv","r","ran","rather","rd","re","readily","really","reasonably","recent","recently","ref","refs","regarding","regardless","regards","related","relatively","research","respectively","resulted","resulting","results","right","round","run","s","said","same","saw","say","saying","says","sec","second","secondly","section","see","seeing","seem","seemed","seeming","seems","seen","self","selves","sensible","sent","serious","seriously","seven","several","shall","shan't","she","she'd","she'll","she's","shed","shes","should","shouldn't","show","showed","shown","showns","shows","side","significant","significantly","similar","similarly","since","sincere","six","sixty","slightly","so","some","somebody","someday","somehow","someone","somethan","something","sometime","sometimes","somewhat","somewhere","soon","sorry","specifically","specified","specify","specifying","state","states","still","stop","strongly","sub","substantially","successfully","such","sufficiently","suggest","sup","sure","system","t","t's","take","taken","taking","tell","ten","tends","th","than","thank","thanks","thanx","that","that'll","that's","that've","thats","the","their","theirs","them","themselves","then","thence","there","there'd","there'll","there're","there's","there've","thereafter","thereby","thered","therefore","therein","thereof","therere","theres","thereto","thereupon","these","they","they'd","they'll","they're","they've","theyd","theyre","thick","thin","thing","things","think","third","thirty","this","thorough","thoroughly","those","thou","though","thoughh","thousand","three","throug","through","throughout","thru","thus","til","till","tip","to","together","too","took","top","toward","towards","tried","tries","truly","try","trying","ts","twelve","twenty","twice","two","u","un","under","underneath","undoing","unfortunately","unless","unlike","unlikely","until","unto","up","upon","ups","upwards","us","use","used","useful","usefully","usefulness","uses","using","usually","uucp","v","value","various","versus","very","via","viz","vol","vols","vs","w","want","wants","was","wasn't","way","we","we'd","we'll","we're","we've","wed","welcome","well","went","were","weren't","what","what'll","what's","what've","whatever","whats","when","when's","whence","whenever","where","where's","whereafter","whereas","whereby","wherein","wheres","whereupon","wherever","whether","which","whichever","while","whilst","whim","whither","who","who'd","who'll","who's","whod","whoever","whole","whom","whomever","whos","whose","why","why's","widely","will","willing","wish","with","within","without","won't","wonder","words","world","would","wouldn't","www","x","y","yes","yet","you","you'd","you'll","you're","you've","youd","your","youre","yours","yourself","yourselves","z","zero"};


int main(int argc, char *argv[]) {
	char *content = get_page("bing.html");
	// char **links = get_all_links(&content);
	int i = 0;
	// for(i = 0; links[i][0] != '\0'; i++) {
		// printf("%s\n", links[i]);
	// }
	crawl_web("bing.html");
	char **keywords = get_keywords(content);
	i = 0;
	printf("%d\n", size(&keywords));
	for(i = 0; i < size(&keywords); i++) {
		printf("%s\n", keywords[i]);
	}

	ds = (indextable **) malloc(sizeof(indextable *));
	ds[0] = NULL;
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


char** get_keywords(char *page) {
	char **keywords = (char **) malloc(sizeof(char *));
	keywords[0] = (char *) malloc(1);
	keywords[0][0] = '\0';
	while(page != NULL) {
		char * lptr = index(page, '>');
		char * rptr = index(lptr++, '<');
		char *word = (char *) malloc(1);
		word[0] = '\0';
		char * str;
		if(rptr != NULL) {
			str = (char *) malloc(sizeof(char) * (rptr -lptr + 1));
			strncpy(str, lptr, rptr - lptr);
			char ** words = get_words(str);
			int siz = size(&words);
			int i = 0;
			while(i < siz) {
				word = words[i];
				if(is_stop_word(word) == 0) {
					int si = size(&keywords);
					keywords = realloc(keywords, (si + 2) * sizeof(char *));
					keywords[si] = (char *)malloc(strlen(word) + 1);
					strcpy(keywords[si], word);
					keywords[si + 1] = (char *)malloc(1);
					keywords[si + 1][0] = '\0';
				}
				i++;
			}
		}
		page = rptr;
	}
	return keywords;
}

char ** get_words(char * str) {
	char ** words = (char **) malloc(sizeof(char *));
	words[0] = (char *) malloc(1);
	words[0][0] = '\0';
	int len = strlen(str);
	int i = 0;
	char * word = (char *) malloc(1);
	while(i < len) {
		if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
			word = realloc(word, strlen(word) + 2);
			word[strlen(word)] = str[i];
			word[strlen(word) + 1] = '\0';
		}
		else {
			int siz = size(&words);
			if(strlen(word) > 0) {
				words = realloc(words, (siz + 2) * sizeof(char *));
				words[siz] = (char *) malloc(1);
				strcpy(words[siz], word);
				words[siz + 1] = (char *) malloc(1);
				words[siz + 1][0] = '\0';
				word[0] = '\0';
			}
		}
		i++;
	}
	if(strlen(word) != 0) {
		int siz = size(&words);
		words = realloc(words, (siz + 2) * sizeof(char *));
		words[siz] = (char *) malloc(1);
		strcpy(words[siz], word);
		words[siz + 1] = (char *) malloc(1);
		words[siz + 1][0] = '\0';
	}
	return words;
}


int is_stop_word(char *word) {
	int l = 0;
	int h = 852;
	while(l <= h) {
		int m = (l + h)/2;
		int comp = strcmp(word, stopwords[m]);
		if(comp == 0) return 1;
		else if(comp < 0) {
			h = m - 1;
		}
		else l = m + 1;
	}
	return 0;
}

void add_page_to_index(char *location) {
	char **keywords = get_keywords(get_page(location));
	int s = sizeof(ds);
	int i = 0;
	int words = size(&keywords);
	while(i < words) {
		int j = 0;
		while(j < s) {
			if(strcmp(keywords[i], ds[j]->keyword) == 0) {
				add_to_index(keywords[i], location, j);
				break;
			}
			j++;
		}
		if(j == s) {
			ds = realloc(ds, (s + 2) * sizeof(indextable));
			ds[j] = (indextable *)malloc(sizeof(indextable *));
			ds[j]->keyword = keywords[i];
			ds[j]->maps = NULL;
			add_to_index(keywords[i], location, j);
		}
		i++;
	}
}

void add_to_index(char * word, char * loc, int j) {
	int i = 0;
	Map **map = ds[j]->maps;
	if(map != NULL) {
		int s = sizeof(map);
		while(i < s) {
			if(strcmp(map[i]->url, loc) == 0) {
				++map[i]->count;
				ds[j]->maps = map;
				return;
			}
			i++;
		}
		map = realloc(map, sizeof(Map *) * (s + 2));
		map[s] = (Map) malloc(sizeof(Map));
		map[s]->url = location;
		++map[s]->count;
		ds[j]->maps = map;
		return;
	}
	map = (Map *)malloc(sizeof(Map *));
	map->url = (char *)malloc(strlen(loc) + 1);
	strcpy(map->url, loc);
	map->url[strlen(loc)] = '\0';
	map->count = 1;
	ds[j]->maps = map;
	return;
}