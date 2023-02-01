#include <stdio.h>
#include <math.h>
#include <string.h>

int main (int argc, char* argv[])
{
  char resname[50];  
  int read_char;
  int i;
  int c;
  int comparison_result;
  float x1, y1, z1, affinity;
  
  FILE * pFile;
  FILE * pFile1;
  FILE * pFile2;  
  
  pFile = fopen ("AllSets.pdb","r");
  pFile1 = fopen ("AllScores.txt","r");
  pFile2 = fopen ("data.pdb","w");

  read_char=1;
  while(read_char>0)
  {
   read_char = fscanf (pFile, "%s", resname);
   comparison_result = strcmp(resname,"HOH");
   if(comparison_result==0)
   {
    for(i=0; i<11; i++)
     c = fgetc (pFile);
    fscanf (pFile, "%f %f %f", &x1, &y1, &z1);
    fscanf (pFile1, "%f", &affinity);
    if (affinity < 0) fprintf(pFile2, "%8.3f%8.3f%8.3f%8.1f\n", x1, y1, z1, affinity);
   }   
  }

  fclose (pFile);
  fclose (pFile1);
  fclose (pFile2); 

  return 0;
}
