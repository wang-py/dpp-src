#include <stdio.h>
#include <math.h>
#include <string.h>

#define critical_distance 1.4

int main (int argc, char* argv[])
{
  char resname[50];  
  int read_char1, read_char2;
  int i;
  int c;
  int comparison_result, comparison_result1, comparison_result2;
  int first_iteration=1;
  int internal_flag;
  float distance;
  float x1, y1, z1, x2, y2, z2;
  int cyl1, cyl2, cyl3, cyl4, cyl5, cyl6;
  int resid=0;
  
  FILE * pFile;
  FILE * pFile1;
  FILE * pFile2;  
  
  pFile = fopen (argv[1],"r");
  pFile1 = fopen ("experiment.pdb","r");
  pFile2 = fopen ("internal_experiment.pdb","w");

  read_char1=1;
  while(read_char1>0)
  {
   read_char1 = fscanf (pFile1, "%s", resname);
   comparison_result1 = strcmp(resname,"HOH");
   comparison_result2 = strcmp(resname,"WAT");
   if(comparison_result1==0 || comparison_result2==0)
   {
    for(i=0; i<11; i++)
     c = fgetc (pFile1);
    fscanf (pFile1, "%f %f %f", &x1, &y1, &z1);

    read_char2=1;
    internal_flag=0;
    cyl1=cyl2=cyl3=cyl4=cyl5=cyl6=0;
    while(read_char2>0 && internal_flag==0)
    {
     read_char2 = fscanf (pFile, "%s", resname);
     comparison_result = strcmp(resname,"ATOM");
     if(comparison_result==0)
     {
      for(i=0; i<27; i++)
       c = fgetc (pFile);
      fscanf (pFile, "%f %f %f", &x2, &y2, &z2);
      distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
      if(distance<critical_distance)
      {
       if(z1>z2) cyl1=1;
       if(z1<z2) cyl2=1;   
      }        
      distance=sqrt((x1-x2)*(x1-x2)+(z1-z2)*(z1-z2));
      if(distance<critical_distance)
      {
       if(y1>y2) cyl3=1;
       if(y1<y2) cyl4=1;   
      }        
      distance=sqrt((z1-z2)*(z1-z2)+(y1-y2)*(y1-y2));
      if(distance<critical_distance)
      {
       if(x1>x2) cyl5=1;
       if(x1<x2) cyl6=1;   
      }        
      if(cyl1==1 && cyl2==1 && cyl3==1 && cyl4==1 && cyl5==1 && cyl6==1) internal_flag=1;
      if (internal_flag==1)
      {
       resid++;
       fprintf(pFile2, "ATOM%7d  O   HOH A%4d%12.3f%8.3f%8.3f  1.00  0.00\n", resid,resid,x1, y1, z1);   
      } 
     } 
    }
    rewind(pFile); 
   }   
  }

  fprintf(pFile2, "TER\nEND\n"); 

  fclose (pFile);
  fclose (pFile1);
  fclose (pFile2); 

  return 0;
}
