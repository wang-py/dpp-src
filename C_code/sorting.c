#include <stdio.h>
#include <math.h>
#include <string.h>

int main (int argc, char* argv[])
{
  int read_char;
  int i;
  int c;
  float x, y, z, r;
  float affinity, cur_affinity, prev_affinity, min_affinity, max_affinity;
  char str[50];  
  int comparison_result;
  int first_iteration=1;
  int num_waters=0;

 
  
  
  FILE * pFile;
  FILE * pFile2;  
  
  pFile = fopen ("PredictedWaters.pdb","r");
  pFile2 = fopen ("sorted.pdb","w");

  read_char=1;
  while(read_char>0)
  {
   read_char = fscanf (pFile, "%s", str);
   comparison_result = strcmp(str,"HOH");
   if(comparison_result==0)
   {
    num_waters++;
    for(i=0; i<11; i++)
     c = fgetc (pFile);
    fscanf (pFile, "%f %f %f %f %f", &x, &y, &z, &r, &affinity);
    if(first_iteration==1)
    {        
     first_iteration=0;
     min_affinity=max_affinity=affinity;
    }
    if(affinity<min_affinity)min_affinity=affinity;
    if(affinity>max_affinity)max_affinity=affinity;
   }   
  }

  cur_affinity=min_affinity;

  while(num_waters>0)
  {
   rewind(pFile);
   read_char=1;
   while(read_char>0)
   {
    read_char = fscanf (pFile, "%s", str);
    comparison_result = strcmp(str,"HOH");
    if(comparison_result==0)
    {
     for(i=0; i<11; i++)
      c = fgetc (pFile);
     fscanf (pFile, "%f %f %f %f %f", &x, &y, &z, &r, &affinity);
     if(affinity==cur_affinity)
     {        
      fprintf(pFile2, "%8.3f%8.3f%8.3f%8.2f%8.2f\n", x, y, z, r, affinity);
      num_waters--;	
     }
    }
   }

   prev_affinity=cur_affinity;
   cur_affinity=max_affinity;
   rewind(pFile);
   read_char=1;
   while(read_char>0)
   {
    read_char = fscanf (pFile, "%s", str);
    comparison_result = strcmp(str,"HOH");
    if(comparison_result==0)
    {
     for(i=0; i<11; i++)
      c = fgetc (pFile);
     fscanf (pFile, "%f %f %f %f %f", &x, &y, &z, &r, &affinity);
     if(affinity>prev_affinity && affinity<cur_affinity) cur_affinity=affinity;
    }
   }

  }

  fclose (pFile);
  fclose (pFile2); 

  return 0;
}
