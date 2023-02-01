#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
  char * pEnd;
  int read_char1,read_char2;
  int i;
  int c;
  float x1,x2;
  float y1,y2;
  float z1,z2;
  double distance;
  char resname[50];  
  int comparison_result1,comparison_result2;
  int match_flag;
  int matches_found=0;
  int experimental_waters=0;
  double critical_distance;
  
  FILE * pFile;
  FILE * pFile1;
  FILE * pFile2;
  FILE * pFile3;  
  FILE * pFile4;  
  
  pFile = fopen ("internal_experiment.pdb","r");
  pFile1 = fopen ("PredictedInternal.pdb","r");
  pFile2 = fopen ("match_experiment.pdb","w");
  pFile4 = fopen ("match_predicted.pdb","w");
  pFile3 = fopen ("match_statistics.txt","w");

  if(argc>1)
   critical_distance = strtod(argv[1],&pEnd);
  else
   critical_distance = 2.8; 

  read_char1=1;
  while(read_char1>0)
  {
   read_char1 = fscanf (pFile, "%s", resname);
   comparison_result1 = strcmp(resname,"HOH");
   comparison_result2 = strcmp(resname,"WAT");
   if(comparison_result1==0 || comparison_result2==0)
   {
    experimental_waters++;
    for(i=0; i<11; i++)
     c = fgetc (pFile);
    fscanf (pFile, "%f %f %f", &x1, &y1, &z1);

    read_char2=1;
    match_flag=0;
    while(read_char2>0 && match_flag==0)
    {
     read_char2 = fscanf (pFile1, "%s", resname);
     comparison_result1 = strcmp(resname,"HOH");
     comparison_result2 = strcmp(resname,"WAT");
     if(comparison_result1==0 || comparison_result2==0)
     {
      for(i=0; i<11; i++)
       c = fgetc (pFile1);
      fscanf (pFile1, "%f %f %f", &x2, &y2, &z2);
      distance=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
      if(distance<=critical_distance)
      {
       fprintf(pFile2, "%f %f %f\n", x1, y1, z1);
       fprintf(pFile4, "%f %f %f\n", x2, y2, z2);
       match_flag=1;
       matches_found++;
      } 
     } 
    }
    rewind(pFile1); 
   }   
  }

  fprintf(pFile3, "Experimental molecules:\t%d\nMathes found:\t %d\n", experimental_waters, matches_found);
  fprintf(pFile3, "Critical distance:\t %.1lf", critical_distance);

  fclose (pFile);
  fclose (pFile1);
  fclose (pFile2); 
  fclose (pFile3); 

  return 0;
}
