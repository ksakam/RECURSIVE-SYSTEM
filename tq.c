#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
#define BUFF_LEN 1024
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#include "../RECURSIVE-SYSTEM/Tree.h"
#include "../RECURSIVE-SYSTEM/import_export_Tree.c"

/*
struct options {
	int help;
	int stat;
	int check;
	int buff;
	int war;
	char *in;
	int f_counter;
	int f_print_T;
	int f_print_S;
	int f_print_status;
	int f_print_hierarchy;
	int f_print_hierarchy_status;
};
*/

void help(void){
	printf("USAGE:\n");
	printf(" tq [-h] [-s] [-c] buff=<size(int)> in=<input file> w=<print warnning> -F<x>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  buff : set integer.\n");
	printf("  in : set *chars (len < 1024).\n");
	printf("  war : set integer.\n");
	printf("  -F<x> : function symbol, e.g. \"-FS\" prints S-form.\n");
	printf("    -FT : prints T-form.\n");
	printf("    -FS : prints S-form.\n");
	printf("    -Fh : prints hierarchical-form.\n");
	printf("    -Fst : prints import status.\n");
	printf("    -Fhst : prints import status with hierarchical-form.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under construction.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).in = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).buff = BUFF_LEN;
	(*opt).in[0] = '\0';
	(*opt).war = 0;
	(*opt).f_counter = 0;
	(*opt).f_print_T = 0;
	(*opt).f_print_S = 0;
	(*opt).f_print_status = 0;
	(*opt).f_print_hierarchy = 0;
	(*opt).f_print_hierarchy_status = 0;
}

void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	(*opt).f_counter = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).stat = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff);
		}else if(strncmp(optv[i],"w=",2) == 0){
			sscanf(optv[i],"w=%d",&(*opt).war);
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).in);
		}else if(strncmp(optv[i],"-FT",3) == 0){
			(*opt).f_print_T = 1;
			(*opt).f_counter++;
		}else if(strncmp(optv[i],"-Fst",4) == 0){
			(*opt).f_print_status = 1;
			(*opt).f_counter++;
		}else if(strncmp(optv[i],"-FS",3) == 0){
			(*opt).f_print_S = 1;
			(*opt).f_counter++;
		}else if(strncmp(optv[i],"-Fhst",4) == 0){
			(*opt).f_print_hierarchy_status = 1;
			(*opt).f_counter++;
		}else if(strncmp(optv[i],"-Fh",3) == 0){
			(*opt).f_print_hierarchy = 1;
			(*opt).f_counter++;
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.buff:%d:\n",(*opt).buff);
	printf(" opt.in:%s:\n",(*opt).in);
	printf(" opt.war:%d:\n",(*opt).war);
	printf(" opt.fcount:%d:\n",(*opt).f_counter);
	printf(" opt.FT:%d:\n",(*opt).f_print_T);
	printf(" opt.FS:%d:\n",(*opt).f_print_S);
	printf(" opt.Fst:%d:\n",(*opt).f_print_status);
	printf(" opt.Fh:%d:\n",(*opt).f_print_hierarchy);
	printf(" opt.Fhst:%d:\n",(*opt).f_print_hierarchy_status);
}

int create_func_list(int *_flags,struct options *opt){
	int i=0;
	_flags = malloc(sizeof(int) * (*opt).f_counter);
}


int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	FILE *IN;
	int is_open = 0;
	int c;
	int fcount = 0;
	//struct Tree *(**flist)(struct Tree *tree);
	int *flist;
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	if(argc == 1){
		(*opt).help = 1;
	}
	if((*opt).help == 1){
		help();
		ie = 1;
	}
	if((*opt).stat == 1){
		status();
		ie = 1;
	}
	if((*opt).check == 1){
		check_options(opt);
		ie = 1;
	}
	if(ie == 1){
		exit(0);
	}
	//function list
	fcount = create_func_list(flist,opt);
	// open file
	if((IN = fopen((*opt).in,"r")) == NULL){
		perror((*opt).in);
		exit(1);
	}
	is_open = 1;

	// main function
	c = 1;
	struct Tree *top;
	top = Create_Node(BUFF_LEN);
		//c = importApp_Tree(IN,top,(*opt).war,fcount,(struct Tree *(*)())Function_Print_Status); // it cause mem leak, call many valiables every char
		c = importApp_Tree(IN,top,opt); // it cause mem leak, call many valiables every char
		/*
		if(c == '\n'){
			if((*opt).war > 0){ printf("\n\n---\n\n"); }
			if((*opt).f_print_status == 1){
			printf("  ");
			ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Status);
			}
			if((*opt).f_print_hierarchy == 1){
			ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_HeadHierarchy);
			}
			if((*opt).f_print_hierarchy_status == 1){
			ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_HeadHierarchyStatus);
			}
			if((*opt).f_print_T){
			ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head);
			printf("\n");
			}
			if((*opt).f_print_S){
			ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_S);
			printf("\n");
			}
			Function_RecursiveFreeForce(top);
			free(top);
			top = Create_Node(BUFF_LEN);
		}
		*/

	// close file
	if(is_open > 0){
		fclose(IN);
	}

	//function execution
	//Function_RecursivePrint_Head(top); printf("\n");

	// finish
	return(0);
}
