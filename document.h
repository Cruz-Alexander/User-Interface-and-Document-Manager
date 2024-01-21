#ifndef DOCUMENT_H 
#define DOCUMENT_H 

#define MAX_STR_SIZE 1024 
#define MAX_PARAGRAPHS 50 
#define MAX_PARAGRAPH_LINES 100 

#define SUCCESS 0 
#define FAILURE -1 

typedef struct { 
   int number_of_lines; 
   char *lines[MAX_PARAGRAPH_LINES]; 
} Paragraph; 

typedef struct { 
   char name[MAX_STR_SIZE]; 
   int number_of_paragraphs; 
   Paragraph paragraphs[MAX_PARAGRAPHS]; 
} Document; 

int init_document(Document *doc, const char *name); 
int reset_document(Document *doc); 
int print_document(Document *doc); 
int add_paragraph_after(Document *doc, int paragraphNumber); 
int add_line_after(Document *doc, int paragraphNumber, int lineNumber, const char *newLine); 
int load_document(Document *doc, const char *filename); 
int save_document(Document *doc, const char *filename); 

#endif
