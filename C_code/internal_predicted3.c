#include <stdio.h>
#include <math.h>
#include <string.h>

#define critical_distance 1.4
#define min_distance 2.3

int main (int argc, char* argv[])
{
  char resname[50];  
  int read_char1, read_char2, read_char3;
  int i;
  int c;
  int comparison_result, comparison_result1, comparison_result2, comparison_result3;
  int first_iteration=1;
  int internal_flag;
  int min_distance_flag;
  float distance;
  float r, affinity;
  float x1, y1, z1, x2, y2, z2, x3, y3, z3;
  int cyl1, cyl2, cyl3, cyl4, cyl5, cyl6;
  int resid=0;
  
  FILE * pFile;
  FILE * pFile1;
  FILE * pFile2;  
  
  pFile = fopen (argv[1],"r");
  pFile1 = fopen ("sorted.pdb","r");
  pFile2 = fopen ("PredictedInternal.pdb","a+");

  read_char1=1;
  while(read_char1>0)
  {
    read_char1 = fscanf (pFile1, "%f %f %f %f %f", &x1, &y1, &z1, &r , &affinity);

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

        // Checking minimim distance

        min_distance_flag=1;
        rewind(pFile2);
        read_char3 = 1;
        while(read_char3 > 0)
        {
         read_char3 = fscanf (pFile2, "%s", resname);
         comparison_result3 = strcmp(resname,"HOH");
         if(comparison_result3==0)
         {
          for(i=0; i<11; i++)
           c = fgetc (pFile2);
          fscanf (pFile2, "%f %f %f", &x3, &y3, &z3);
          if ( (x1-x3)*(x1-x3) + (y1-y3)*(y1-y3) + (z1-z3)*(z1-z3) < min_distance*min_distance ) min_distance_flag=0;   
         }
        }

        // End of checking
        
        if(min_distance_flag==1)
        {
        resid++;
        fprintf(pFile2, "ATOM%7d  O   HOH A%4d%12.3f%8.3f%8.3f  1.00%6.2f\n", resid,resid,x1, y1, z1, affinity);   
        }

      } 
     } 
    }
    rewind(pFile);    
  }

  fprintf(pFile2, "TER\nEND\n"); 

  fclose (pFile);
  fclose (pFile1);
  fclose (pFile2); 

  return 0;
}
