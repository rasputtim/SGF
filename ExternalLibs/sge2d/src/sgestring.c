#include <sge.h>

int sgeCharIsWhitespace(char c) {
	if (
		(c==' ') ||
		(c=='\t') ||
		(c=='\n') ||
		(c=='\v') ||
		(c=='\a') ||
		(c=='\f') ||
		(c=='\r')
	   ) {
		return YES;
	}
	return NO;
}

char *sgeTrim(char *str) {
	char *ret=NULL;
	int cont=1;
	int i=0;
	int start=0;
	int end=0;
	int len=strlen(str);

	while ( (cont) && (i<len-1) ) {
		if (!sgeCharIsWhitespace(str[i])) {
			start=i;
			cont=0;
		}
		i++;
	}

	cont=1;
	i=len-1;
	while ( (cont) && (i>=0) ) {
		if (!sgeCharIsWhitespace(str[i])) {
			end=i;
			cont=0;
		}
		i--;
	}

	if (end<=start) {
		sgeNew(ret, char);
		return ret;
	}

	len=end-start+1;
	sgeMalloc(ret, char, len+1);
	strncpy(ret, str+start, len);
	return ret;
}

char *sgeLower(char *str) {
    char *ret=strdup(str);
    char *c=ret;
    for ( ; *c; ++c) *c = tolower(*c);
    return ret;
}

char *sgeUpper(char *str) {
    char *ret=strdup(str);
    char *c=ret;
    for ( ; *c; ++c) *c = toupper(*c);
    return ret;
}

static char *sgeConfigPartFromString(char *str, int part) {
	char *wc=strdup(str);
	char *eq=strchr(wc, '=');
	char *p=NULL;

	if (eq==NULL) {
		sgeFree(wc);
		return NULL;
	}

	eq[0]=0;
	if (part==0) {
		p=sgeTrim(wc);
	} else {
		p=sgeTrim(eq+1);
	}
	sgeFree(wc);
	return p;
}

char *sgeConfigNameFromString(char *str) {
	return sgeConfigPartFromString(str, 0);
}
char *sgeConfigValueFromString(char *str) {
	return sgeConfigPartFromString(str, 1);
}
