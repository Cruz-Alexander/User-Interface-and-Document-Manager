#include <stdio.h> 
#include <string.h> 
#include "document.h" 

/* Alexander Cruz, alexcruz, 119092071 */ 

/* Initialize a document with a given name */ 
int init_document(Document *doc, const char *name) { 
   if (doc != NULL && name != NULL && strlen(name) <= MAX_STR_SIZE) { 
      strcpy(doc->name, name); 
      return SUCCESS; 
   } 
   return FAILURE; 
}

/* Reset the content of a document */ 
int reset_document(Document *doc) { 
   if (doc != NULL) { 
      doc->number_of_paragraphs = 0; 
      return SUCCESS; 
   } 
   return FAILURE; 
}

/* Print the content of a document */ 
int print_document(Document *doc) { 
   int i, j; 

   if (doc != NULL) { 
      printf("Document name: \"%s\"\n", doc->name); 
      printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs); 

      for (i = 0; i < doc->number_of_paragraphs; i++) { 
         if (doc->paragraphs[i].number_of_lines > 0) { 
            for (j = 0; j < doc->paragraphs[i].number_of_lines; j++) { 
               printf("%s\n", doc->paragraphs[i].lines[j]); 
            } 
            if (i < (doc->number_of_paragraphs - 1)) 
               printf("\n"); 
         } 
      } 
      return SUCCESS; 
   } 
   return FAILURE; 
}

/* Add a new paragraph after a specified paragraph number */ 
int add_paragraph_after(Document *doc, int paragraphNumber) { 
   int i, start = 0, end = 0, numParas = 0; 

   if (doc != NULL) { 
      numParas = doc->number_of_paragraphs; 
      if (numParas < MAX_PARAGRAPHS && paragraphNumber <= numParas) { 
         if (paragraphNumber == 0 && !numParas) { 
            doc->paragraphs[0].number_of_lines = 0; 
         } else if (paragraphNumber == doc->number_of_paragraphs) { 
            end = doc->number_of_paragraphs; 
            doc->paragraphs[end].number_of_lines = 0; 
         } else { 
            start = doc->number_of_paragraphs; 
            for (i = start; i >= paragraphNumber; i--) { 
               doc->paragraphs[i + 1] = doc->paragraphs[i]; 
            } 
            doc->paragraphs[paragraphNumber].number_of_lines = 0; 
         } 
         (doc->number_of_paragraphs)++; 
         return SUCCESS; 
      } 
   } 
   return FAILURE; 
}

/* Add a new line after a specified paragraph and line number */ 
int add_line_after(Document *doc, int paragraphNumber, int lineNumber, const char *newLine) { 
   int i, numLines = 0; 
   char *pos, *line1, *line2; 

   if (doc != NULL && newLine != NULL) { 
      if (paragraphNumber <= doc->number_of_paragraphs) { 
         numLines = doc->paragraphs[paragraphNumber - 1].number_of_lines; 
         if (numLines < MAX_PARAGRAPH_LINES && lineNumber <= numLines) { 
            if (lineNumber == 0 && !numLines) { 
               doc->paragraphs[paragraphNumber - 1].lines[0] = malloc((strlen(newLine) + 1) * sizeof(char)); 
               strcpy(doc->paragraphs[paragraphNumber - 1].lines[0], newLine); 
            } else if (lineNumber == doc->paragraphs[paragraphNumber - 1].number_of_lines) { 
               doc->paragraphs[paragraphNumber - 1].lines[numLines] = malloc((strlen(newLine) + 1) * sizeof(char)); 
               strcpy(doc->paragraphs[paragraphNumber - 1].lines[numLines], newLine); 
            } else { 
               pos = strstr(doc->paragraphs[paragraphNumber - 1].lines[lineNumber], newLine); 
               line1 = malloc((strlen(doc->paragraphs[paragraphNumber - 1].lines[lineNumber]) + 1) * sizeof(char)); 
               strcpy(line1, doc->paragraphs[paragraphNumber - 1].lines[lineNumber]); 
               line2 = malloc((strlen(pos) + 1) * sizeof(char)); 
               strcpy(line2, pos); 
               doc->paragraphs[paragraphNumber - 1].lines[lineNumber] = realloc(doc->paragraphs[paragraphNumber - 1].lines[lineNumber], strlen(line1) + strlen(newLine) + strlen(line2) + 1); 
               strcpy(doc->paragraphs[paragraphNumber - 1].lines[lineNumber], line1); 
               strcat(doc->paragraphs[paragraphNumber - 1].lines[lineNumber], newLine); 
               strcat(doc->paragraphs[paragraphNumber - 1].lines[lineNumber], line2); 
            } 
            (doc->paragraphs[paragraphNumber - 1].number_of_lines)++; 
            return SUCCESS; 
         } 
      } 
   } 
   return FAILURE; 
}

/* Load the content of a document from a file */ 
int load_document(Document *doc, const char *filename) { 
   int paraNum = 0, lineNum = 0, numLines = 0, result = 0; 
   FILE *fp; 
   char buffer[MAX_STR_SIZE]; 

   if (doc != NULL && filename != NULL) { 
      fp = fopen(filename, "r"); 
      if (fp != NULL) { 
         while (fgets(buffer, MAX_STR_SIZE, fp) != NULL) { 
            if (buffer[0] == '\n') { 
               paraNum++; 
               lineNum = 0; 
            } else { 
               numLines = doc->paragraphs[paraNum].number_of_lines; 
               if (numLines < MAX_PARAGRAPH_LINES) { 
                  doc->paragraphs[paraNum].lines[lineNum] = malloc((strlen(buffer) + 1) * sizeof(char)); 
                  strcpy(doc->paragraphs[paraNum].lines[lineNum], buffer); 
                  (doc->paragraphs[paraNum].number_of_lines)++; 
                  lineNum++; 
               } else { 
                  result = FAILURE; 
                  break; 
               } 
            } 
         } 
         fclose(fp); 
         if (result != FAILURE) { 
            return SUCCESS; 
         } 
      } 
   } 
   return FAILURE; 
}

/* Save the content of a document to a file */ 
int save_document(Document *doc, const char *filename) { 
   int i, j; 
   FILE *fp; 

   if (doc != NULL && filename != NULL) { 
      fp = fopen(filename, "w"); 
      if (fp != NULL) { 
         for (i = 0; i < doc->number_of_paragraphs; i++) { 
            for (j = 0; j < doc->paragraphs[i].number_of_lines; j++) { 
               fprintf(fp, "%s", doc->paragraphs[i].lines[j]); 
            } 
            fprintf(fp, "\n"); 
         } 
         fclose(fp); 
         return SUCCESS; 
      } 
   } 
   return FAILURE; 
}
