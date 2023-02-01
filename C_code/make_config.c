#include <stdio.h>
#include <math.h>
#include <string.h>

int main (int argc, char* argv[])
{
  int read_char;
  int i;
  int c;
  float x,min_x,max_x,center_x;
  float y,min_y,max_y,center_y;
  float z,min_z,max_z,center_z;
  int size_x,size_y,size_z; 
  char str[50];  
  int comparison_result;
  int first_iteration=1;

 
  
  
  FILE * pFile;
  FILE * pFile2;  
  
  pFile = fopen (argv[1],"r");
  pFile2 = fopen ("config.txt","w");


  read_char=1;
  while(read_char>0)
  {
   read_char = fscanf (pFile, "%s", str);
   comparison_result = strcmp(str,"ATOM");
   if(comparison_result==0)
   {
    for(i=0; i<27; i++)
     c = fgetc (pFile);
    fscanf (pFile, "%f %f %f", &x, &y, &z);
    if(first_iteration==1)
    {        
     first_iteration=0;
     min_x=max_x=x;
     min_y=max_y=y;
     min_z=max_z=z;
    }
    if(x<min_x)min_x=x;
    if(y<min_y)min_y=y;
    if(z<min_z)min_z=z;
    if(x>max_x)max_x=x;
    if(y>max_y)max_y=y;
    if(z>max_z)max_z=z;
   }   
  }

  size_x=(int)(max_x-min_x);
  size_y=(int)(max_y-min_y);
  size_z=(int)(max_z-min_z);

  center_x=0.5*(max_x+min_x);
  center_y=0.5*(max_y+min_y);
  center_z=0.5*(max_z+min_z);

  fprintf(pFile2, "center_x = %f\ncenter_y = %f\ncenter_z = %f\n\nsize_x = %d\nsize_y = %d\nsize_z = %d\n\nexhaustiveness = 20\nenergy_range = 100\nnum_modes = 20\n\n", center_x, center_y, center_z, size_x, size_y, size_z);

  fclose (pFile);
  fclose (pFile2); 

  return 0;
}
