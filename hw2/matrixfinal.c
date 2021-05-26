#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Element {
    int value;
    int row;
    int column;
    struct Element *rowElement;
    struct Element *columnElement;
};

struct Header {
    int index;
    struct Header *header;
    struct Element *element;
};

struct Matrix {
    struct Header *headRowHeader;
    struct Header *headColumnHeader;
    int rows;
    int columns;
    int fillValue;
};

int findrowheader(struct Matrix *m,int row){
	struct Header *p;
	for(p=m->headRowHeader;p!=NULL;p=p->header){
		if(p->index==row)
			break;
	}
	return p!=NULL; /*return 0 if no pointer is found*/
}
struct Header *locaterowheader (struct Matrix *m, int row){
	struct Header *p;
	for(p=m->headRowHeader;p!=NULL;p=p->header){
		if(p->index==row){
			break;
		}		
	}
	return p;
}
struct Header *locatecolheader (struct Matrix *m, int col){
	struct Header *p;
	for(p=m->headColumnHeader;p!=NULL;p=p->header){
		if(p->index==col){
			break;
		}	
	}
	return p;
}
int findcolheader(struct Matrix *m,int col){
	struct Header *p;
	for(p=m->headColumnHeader;p!=NULL;p=p->header){
		if(p->index==col)
			break;
	}
	return p!=NULL; 
}
void Element_locator(struct Header *rowhead, struct Header *colhead, int value,int row, int column){
	struct Element *node=malloc(sizeof(struct Element));
	node->column=column;
	node->row=row;
	node->value=value;
	node->columnElement=NULL;
	node->rowElement=NULL;
	
	if(rowhead->element!=NULL){
		struct Element *p;
		p=rowhead->element;
		while(p->rowElement!=NULL)
			p=p->rowElement;
		p->rowElement=node;
	}
	if(colhead->element!=NULL){
		struct Element *p;
		p=colhead->element;
		while(p->columnElement!=NULL)
			p=p->columnElement;
		p->columnElement=node;
	}
	if(colhead->element==NULL)
		colhead->element=node;
	if(rowhead->element==NULL)
		rowhead->element=node;
}

void Header_pushc(struct Matrix *m, int index){
	struct Header *nextheader=malloc(sizeof(struct Header));
	nextheader->header=NULL;
	nextheader->index=index;
	nextheader->element=NULL;
	if(m->headColumnHeader==NULL){
		m->headColumnHeader=nextheader;	
	}else{
		nextheader->header=m->headColumnHeader;
		m->headColumnHeader=nextheader;	
	};
}
void Header_pushr(struct Matrix *m, int index){
	struct Header *nextheader=malloc(sizeof(struct Header));
	nextheader->header=NULL;
	nextheader->index=index;
	nextheader->element=NULL;
	if(m->headRowHeader==NULL){
		m->headRowHeader=nextheader;	
	}else{
		nextheader->header=m->headRowHeader;
		m->headRowHeader=nextheader;	
	};
}

void Header_add(struct Header *head, int index){
	struct Header *p, *target;
	target=malloc(sizeof(struct Header));
	target->index=index;
	target->element=NULL;
	target->header=NULL;
	
	if(head->header==NULL){
		head->header=target;
	}else{
	/*insert in middle*/
		p=head;
		for(;p->header!=NULL;p=p->header){
			if((p->header->index)>index){
				target->header=p->header;
				p->header=target;
				break;
			}	
		}
	/*append*/
		if(p->header==NULL)
			p->header=target;		
	}
	
}

int MTRX_getElement(struct Matrix *m, int row, int column){
	struct Header *p;
	p=m->headColumnHeader;
	if(p==NULL){
	/*if the headcolumnheader does not exist, do not get value*/
		return m->fillValue;
	}else{	
		for(;p!=NULL;p=p->header){
			if(p->index==column)
				break;
		}
		if(p==NULL){
			return m->fillValue;
		}else{
			struct Element *q=p->element;
			for(;q!=NULL;q=q->columnElement){
				if(q->row==row)
					return q->value;
			}
			if(q==NULL)
				return m->fillValue;
			}
		}
		return m->fillValue;	
}
void MTRX_write(struct Matrix *m, char *filename){
	/*find every value in the matrix and print into files*/
	int n,k;
	FILE *out;
	/*open file*/
	out=fopen(filename,"w");
	if(out==NULL){
		printf("Couldn't open file %s'", filename);
 	}
	
	for(n=1;n<m->rows+1;n++){
		for(k=1;k<m->columns;k++){
			fprintf(out,"%d ",MTRX_getElement(m,n,k));
		}
		fprintf(out,"%d",MTRX_getElement(m,n,k));
		fprintf(out,"\n");	
	}
	fclose(out);
	}
	
void MTRX_testwrite(struct Matrix *m){
	int n,k;
	for(n=1;n<m->rows+1;n++){
		for(k=1;k<m->columns;k++){
			printf("%d ",MTRX_getElement(m,n,k));	
		}
		printf("%d",MTRX_getElement(m,n,k));
		printf("\n");	
		}
	}

struct Matrix MTRX_alloc(char *filename, int fillValue){
	/*read from the file, ignore the space, one \n means end of one row.
	only store the values not 0
	trace and mark the row, column number*/
	struct Matrix mar;
	int *num=malloc(sizeof(int));
	FILE *f;
	char c;
	int i,j;
	
	mar.headColumnHeader=NULL;
	mar.headRowHeader=NULL;
	mar.columns=0;
	mar.rows=1;
	mar.fillValue=fillValue;
	f=fopen(filename,"r");
	if(f==NULL){
		printf("Couldn't open file %s'", filename);
	}
	/*get the total number of row and column
	get a frame of spots*/
	c=getc(f);
	while(c!=EOF){
		if(c==' ')
			mar.columns++;
		if(c=='\n'){
			c=getc(f);
			if(c!=EOF){
				mar.rows++;
				mar.columns=1;	
			}
			ungetc(c,f); 
		}
		c=getc(f);
	}
	
	/*set to the beginning and get numbers to element node one by one*/
	rewind(f);
	for(i=1;i<mar.rows+1;i++){
		for(j=1;j<mar.columns+1;j++){
			fscanf(f,"%d",num);
			if(*num!=fillValue){
				if(findrowheader(&mar,i)==0){
					if(i==1||mar.headRowHeader==NULL){
						Header_pushr(&mar,i);
					}else{
					Header_add(mar.headRowHeader,i);		
				}				
			}
				if(findcolheader(&mar,j)==0){
					if(j==1||mar.headColumnHeader==NULL){
						Header_pushc(&mar,j);
					}else{
						Header_add(mar.headColumnHeader,j);
					}		
			}
			Element_locator(locaterowheader(&mar,i),locatecolheader(&mar,j),*num,i,j); 		
			}
		}
	}
	fclose(f);
	free(num);
	return mar;
}


struct Matrix MTRX_add(struct Matrix *a, struct Matrix *b, int fillValue){
	int i,j;
	int value;
	
	struct Matrix mark;
	mark.columns=a->columns;
	mark.fillValue=fillValue;
	mark.rows=a->rows;
	mark.headColumnHeader=NULL;
	mark.headRowHeader=NULL;
	
	if(a->columns==b->columns && a->rows==b->rows){
		for(i=1;i<a->rows+1;i++){
			for(j=1;j<a->columns+1;j++){
				if(MTRX_getElement(a,i,j)==fillValue&&MTRX_getElement(b,i,j)==fillValue){
					/*ignore if both element is fillValue=non-exist*/
					continue;
				}else{
					value=MTRX_getElement(a,i,j)+MTRX_getElement(b,i,j);
					/*create new header if there is no header*/
					if(findrowheader(&mark,i)==0){
						if(i==1||mark.headRowHeader==NULL)
							Header_pushr(&mark,i);
						else
							Header_add(mark.headRowHeader,i);						
					}
					if(findcolheader(&mark,j)==0){
						if(j==1||mark.headColumnHeader==NULL)
							Header_pushc(&mark,j);
						else
							Header_add(mark.headColumnHeader,j);
					}	
					Element_locator(locaterowheader(&mark,i),locatecolheader(&mark,j), value,i,j);		
				}
			}
		}	
	}					
	return mark;
}
struct Matrix MTRX_multiply(struct Matrix *a, struct Matrix *b, int fillValue){
	struct Matrix mark;
	mark.columns=b->columns;
	mark.fillValue=fillValue;
	mark.rows=a->rows;
	mark.headColumnHeader=NULL;
	mark.headRowHeader=NULL;
	if(a->columns==b->rows){
		int sum, n, p, i, j;
		sum=0;
		for(j=1;j<b->columns+1;j++){
			for(i=1;i<a->rows+1;i++){
				for(n=1,p=1;(n<a->columns+1)&&(p<b->rows+1);n++,p++){
					sum+=MTRX_getElement(a,i,n)*MTRX_getElement(b,p,j);
				}

				if(sum==fillValue){
				/*ignore if element is fillValue=non-exist, but instead swap col with row*/
					sum=0;
					continue;
				}else{
					/*create new header if there is no header*/
					if(findrowheader(&mark,i)==0){
						if(i==1||mark.headRowHeader==NULL)
							Header_pushr(&mark,i);
						else
							Header_add(mark.headRowHeader,i);						
					}
					if(findcolheader(&mark,j)==0){
						if(j==1||mark.headColumnHeader==NULL)
							Header_pushc(&mark,j);
						else
							Header_add(mark.headColumnHeader,j);
					}	
					Element_locator(locaterowheader(&mark,i),locatecolheader(&mark,j), sum,i,j);		
				}
			sum=0;
			}
			
			}
		}

	return mark;
}

struct Matrix MTRX_transpose(struct Matrix *m){
	int i,j;
	int value;
	
	struct Matrix mark;
	mark.columns=m->rows;
	mark.fillValue=m->fillValue;
	mark.rows=m->columns;
	mark.headColumnHeader=NULL;
	mark.headRowHeader=NULL;
	
	for(i=1;i<mark.rows+1;i++){
		for(j=1;j<mark.columns+1;j++){
			if(MTRX_getElement(m,j,i)==m->fillValue){
				/*ignore if element is fillValue=non-exist, but instead swap col with row*/
				continue;
			}else{
				value=MTRX_getElement(m,j,i);
				/*create new header if there is no header*/
				if(findrowheader(&mark,i)==0){
					if(i==1||mark.headRowHeader==NULL)
						Header_pushr(&mark,i);
					else
						Header_add(mark.headRowHeader,i);						
				}
				if(findcolheader(&mark,j)==0){
					if(j==1||mark.headColumnHeader==NULL)
						Header_pushc(&mark,j);
					else
						Header_add(mark.headColumnHeader,j);
				}	
				Element_locator(locaterowheader(&mark,i),locatecolheader(&mark,j), value,i,j);		
			}
		}
	}			
	return mark;
}

void MTRX_free(struct Matrix* m){
	int i;
	struct Header *head=m->headColumnHeader;
	/*from back to front, free all the elements*/
	for(i=m->columns;i>0;i--){
		if(findcolheader(m,i)!=0){
			struct Header *col=locatecolheader(m,i);
			struct Element *p=col->element;
			while(p!=NULL){
				struct Element *q=p->columnElement;
				p->columnElement=NULL;
				p->rowElement=NULL;
				free(p);
				p=q;
			}
		}	
	}
	/*free all the headers*/
	while(head!=NULL){
		struct Header *q=head->header;
		head->element=NULL;
		head->header=NULL;
		free(head);
		head=q;		
	}
	
	head=m->headRowHeader;
	while(head!=NULL){
		struct Header *q=head->header;
		head->element=NULL;
		head->header=NULL;
		free(head);
		head=q;		
	}
}

int main() {
    struct Matrix a, b ,c, d, t;

    a = MTRX_alloc("matrixA.txt", 0);
    b=MTRX_alloc("matrixB.txt", 0);
	c=MTRX_add(&a,&b,0);
	d=MTRX_multiply(&a,&b,0);
	t = MTRX_transpose(&a);
	
   	MTRX_testwrite(&a);printf("\n");
	MTRX_testwrite(&t);printf("\n");
	MTRX_testwrite(&b);printf("\n");
	MTRX_testwrite(&c);printf("\n");
	MTRX_testwrite(&d);printf("\n");
	MTRX_write(&t, "matrixtest.txt");
	MTRX_free(&t);
	MTRX_free(&a);
	printf("\n");
    return 0;
}
