#include <stdio.h>
#include <math.h>

int main (int argc, char* argv[])
{
  char buffer [50];    
  int p;
  int r=1;

  int box_size;
    
  float center_x;
  float center_y;
  float center_z;
  float size_x;
  float size_y;
  float size_z;
  int cpu, seed, exhaustiveness, num_modes;
  float energy_range;
  char receptor[80];
  char flex[80];
  char ligand[80];
  char out[80];
  char log[80];
    
  int num_boxes_x;  
  float margin_x;
  float left_edge_x;
  int num_boxes_y;  
  float margin_y;
  float left_edge_y;  
  int num_boxes_z;  
  float margin_z;
  float left_edge_z;

  float center_x_box[80];
  float center_y_box[80];
  float center_z_box[80];
  float size_x_box[80];
  float size_y_box[80];
  float size_z_box[80];

  int cx_chk=0;
  int cy_chk=0;
  int cz_chk=0;
  int sx_chk=0;
  int sy_chk=0;
  int sz_chk=0;
  int ex_chk=0;
  int enr_chk=0;
  int num_modes_chk=0;
  int cpu_chk=0;
  int seed_chk=0;
  int receptor_chk=0;
  int ligand_chk=0;
  int flex_chk=0;
  int out_chk=0;
  int log_chk=0;
  
  int i, ix, iy, iz, i1, i2, i3;
  int comparison_result1,comparison_result2;
  char str[80];
  FILE * pFile;
  FILE * pFile2;

  if(argc>1)
   box_size = atoi(argv[1]);
  else
   box_size = 15; 

// Serching for lines

  pFile = fopen("config.txt","r");

  while(r>0)    
  {
   r=fscanf (pFile, "%s", &str);


   comparison_result1 = strcmp(str,"center_x");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%f", &center_x);
     cx_chk=1;
    } 
   }
   
   comparison_result1 = strcmp(str,"center_y");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%f", &center_y);
     cy_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"center_z");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%f", &center_z);
     cz_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"size_x");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%f", &size_x);
     sx_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"size_y");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%f", &size_y);
     sy_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"size_z");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%f", &size_z);
     sz_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"exhaustiveness");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%d", &exhaustiveness);
     ex_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"energy_range");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%f", &energy_range);
     enr_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"num_modes");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%d", &num_modes);
     num_modes_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"seed");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%d", &seed);
     seed_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"receptor");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%s", &receptor);
     receptor_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"ligand");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%s", &ligand);
     ligand_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"flex");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%s", &flex);
     flex_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"cpu");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%d", &cpu);
     cpu_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"out");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%s", &out);
     out_chk=1;
    }
   }
   
   comparison_result1 = strcmp(str,"log");
   if (comparison_result1==0)
   {
    fscanf (pFile, "%s", &str);
    comparison_result2 = strcmp(str,"=");
    if (comparison_result2==0)
    {
     fscanf (pFile, "%s", &log);
     log_chk=1;
    }
   }
   
  } 

  fclose(pFile);

// End of search

//  Making space larger for surfacial molecules

	size_x=size_x+4*box_size;
	size_y=size_y+4*box_size;
	size_z=size_z+4*box_size;

//

 ix=num_boxes_x=(int)(size_x/box_size);
 iy=num_boxes_y=(int)(size_y/box_size);
 iz=num_boxes_z=(int)(size_z/box_size);

  pFile = fopen("box_number.txt","w");
   fprintf(pFile, "%d", num_boxes_x*num_boxes_y*num_boxes_z);
  fclose(pFile);

 margin_x=0.5*(size_x-box_size*num_boxes_x);
 margin_y=0.5*(size_y-box_size*num_boxes_y);
 margin_z=0.5*(size_z-box_size*num_boxes_z);

 left_edge_x=center_x-0.5*size_x;
 left_edge_y=center_y-0.5*size_y;
 left_edge_z=center_z-0.5*size_z;
 
 center_x_box[0]=left_edge_x+0.5*(margin_x+box_size);
 center_y_box[0]=left_edge_y+0.5*(margin_y+box_size);
 center_z_box[0]=left_edge_z+0.5*(margin_z+box_size);

 for(i=1; i<ix-1; i++)
  center_x_box[i]=left_edge_x+margin_x+(i+0.5)*box_size;

 for(i=1; i<iy-1; i++)
  center_y_box[i]=left_edge_y+margin_y+(i+0.5)*box_size;

 for(i=1; i<iz-1; i++)
  center_z_box[i]=left_edge_z+margin_z+(i+0.5)*box_size;

  center_x_box[ix-1]=left_edge_x+1.5*margin_x+(ix-0.5)*box_size;
  center_y_box[iy-1]=left_edge_y+1.5*margin_y+(iy-0.5)*box_size;
  center_z_box[iz-1]=left_edge_z+1.5*margin_z+(iz-0.5)*box_size;


 size_x_box[0]=size_x_box[ix-1]=margin_x+box_size;
 size_y_box[0]=size_y_box[iy-1]=margin_y+box_size;
 size_z_box[0]=size_z_box[iz-1]=margin_z+box_size;
 
 for(i=1; i<ix-1; i++)
  size_x_box[i]=box_size;

 for(i=1; i<iy-1; i++)
  size_y_box[i]=box_size;

 for(i=1; i<iz-1; i++)
  size_z_box[i]=box_size;



 i=1;
 for(i1=0; i1<ix; i1++)
 {
  for(i2=0; i2<iy; i2++)
  {
   for(i3=0; i3<iz; i3++)
   {
              
    p=sprintf (buffer, "box%d.txt", i);
    pFile2=fopen(buffer,"w"); 
/*
   comparison_result1 = strcmp(str,"size_x");
   comparison_result1 = strcmp(str,"size_y");
   comparison_result1 = strcmp(str,"size_z");
   comparison_result1 = strcmp(str,"exhaustiveness");
   comparison_result1 = strcmp(str,"energy_range");
   comparison_result1 = strcmp(str,"num_modes");
   comparison_result1 = strcmp(str,"seed");
   comparison_result1 = strcmp(str,"receptor");
   comparison_result1 = strcmp(str,"ligand");
   comparison_result1 = strcmp(str,"flex");
   comparison_result1 = strcmp(str,"cpu");
   comparison_result1 = strcmp(str,"out");
   comparison_result1 = strcmp(str,"log");
*/

  if (cx_chk==1) fprintf(pFile2, "center_x = %f\n", center_x_box[i1]);
  if (cy_chk==1) fprintf(pFile2, "center_y = %f\n", center_y_box[i2]);
  if (cz_chk==1) fprintf(pFile2, "center_z = %f\n", center_z_box[i3]);
  if (sx_chk==1) fprintf(pFile2, "size_x = %f\n", size_x_box[i1]);
  if (sy_chk==1) fprintf(pFile2, "size_y = %f\n", size_y_box[i2]);
  if (sz_chk==1) fprintf(pFile2, "size_z = %f\n", size_z_box[i3]);
  if (ex_chk==1) fprintf(pFile2, "exhaustiveness = %d\n", exhaustiveness);
  if (enr_chk==1) fprintf(pFile2, "energy_range = %f\n", energy_range);
  if (num_modes_chk==1) fprintf(pFile2, "num_modes = %d\n", num_modes);
  if (cpu_chk==1) fprintf(pFile2, "cpu = %d\n", cpu);
  if (seed_chk==1) fprintf(pFile2, "seed = %d\n", seed);
  if (receptor_chk==1) fprintf(pFile2, "receptor = %s\n", receptor);
  if (ligand_chk==1) fprintf(pFile2, "ligand = %s\n", ligand);
  if (flex_chk==1) fprintf(pFile2, "flex = %s\n", flex);
  if (out_chk==1) fprintf(pFile2, "out = %s\n", out);
  if (log_chk==1) fprintf(pFile2, "log = %s\n", log);

//  fprintf(pFile2, "%f\t%f\n%f\t%f\n", ave_coulomb,sigma_coulomb,ave_lj,sigma_lj);
 

  fclose(pFile2);
  i++;
   }
  }
 }
      
  return 0;
}

