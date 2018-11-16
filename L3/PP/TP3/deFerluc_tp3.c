#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <omp.h>
#include <sys/time.h>
 
typedef struct color_pixel_struct {
    unsigned char r,g,b; 
} color_pixel_type;

typedef struct color_image_struct
{
  int width, height;
  color_pixel_type * pixels;
} color_image_type;

typedef struct grey_image_struct
{
  int width, height;
  unsigned char * pixels;
} grey_image_type;

double t,start,stop;
/**********************************************************************/

color_image_type * loadColorImage(char *filename){
  int i, width,height,max_value;
  char format[8];
  color_image_type * image;
  FILE * f = fopen(filename,"r");
  if (!f){
    fprintf(stderr,"Cannot open file %s...\n",filename);
    exit(-1);
  }
  fscanf(f,"%s\n",format);
  assert( (format[0]=='P' && format[1]=='3'));  // check P3 format
  while(fgetc(f)=='#') // commentaire
    {
      while(fgetc(f) != '\n'); // aller jusqu'a la fin de la ligne
    }
  fseek( f, -1, SEEK_CUR);
  fscanf(f,"%d %d\n", &width, &height);
  fscanf(f,"%d\n", &max_value);
  image = malloc(sizeof(color_image_type));
  assert(image != NULL);
  image->width = width;
  image->height = height;
  image->pixels = malloc(width*height*sizeof(color_pixel_type));
  assert(image->pixels != NULL);
  
  for(i=0 ; i<width*height ; i++){
      int r,g,b;
      fscanf(f,"%d %d %d", &r, &g, &b);
      image->pixels[i].r = (unsigned char) r;
      image->pixels[i].g = (unsigned char) g;
      image->pixels[i].b = (unsigned char) b;
    }
  fclose(f);
  return image;
}

/**********************************************************************/

grey_image_type * createGreyImage(int width, int height){
  grey_image_type * image = malloc(sizeof(grey_image_type));
  assert(image != NULL);
  image->width = width;
  image->height = height;
  image->pixels = malloc(width*height*sizeof(unsigned char));
  assert(image->pixels != NULL);
  return(image);
}

/**********************************************************************/

void saveGreyImage(char * filename, grey_image_type *image){
  int i;
  FILE * f = fopen(filename,"w");
  if (!f){
    fprintf(stderr,"Cannot open file %s...\n",filename);
    exit(-1);
  }
  fprintf(f,"P2\n%d %d\n255\n",image->width,image->height);
  for(i=0 ; i<image->width*image->height ; i++){
    fprintf(f,"%d\n",image->pixels[i]);
  }
  fclose(f);
}

void egalisation_histo (grey_image_type * image){
	int w = image->width;
	int h = image->height;
	int H[256] = {0};
	start = omp_get_wtime();
	int C[256] = {0};
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for
		for(int i = 0;i<w*h;i++){
			H[image->pixels[i]] += 1;
		}
		
		C[0] = H[0];
		
		for (int i = 1;i<256;i++){
			C[i] = C[i-1] + H[i];
		}
		
		#pragma omp for
		for(int i = 0;i<w*h;i++){
			image->pixels[i] = 256*C[image->pixels[i]]/(w*h);
		}
	}
	stop=omp_get_wtime();
	t=stop-start;
	//0.079548 à 0.033194
	saveGreyImage("image_grise_contrastee.pgm", image);
	printf("\n%f\n",t);
}

grey_image_type * embossage(grey_image_type * image){
	int w = image->width;
	int h = image->height;
	grey_image_type * tmp = createGreyImage(w, h);
	start = omp_get_wtime();
	//ici, vu que l'on a l'image tmp pour stocker le résultat, on ne modifie pas l'image source et donc la dépendance de i et j disparait et l'on peut paralleliser
	#pragma omp parallel num_threads(4)
	{
		#pragma omp for
		for(int i = 0;i<w*h;i++)
			tmp->pixels[i] = image->pixels[i];
		int l;
		#pragma omp for
		for(int i = 1;i<h-1;i++){
			l = i*w;
			for(int j = 1;j<w-1;j++){
				tmp->pixels[l+j] = image->pixels[l-w+(j-1)]*-2 + image->pixels[l-w+j]*-1 +
					image->pixels[l+(j-1)]*-1 + image->pixels[l+(j+1)] + image->pixels[l+w+j] + image->pixels[l+w+(j+1)]*2 + 128;
			}
		}
	}
	stop=omp_get_wtime();
	t=stop-start;
	//0.046883 à 0.020974
	saveGreyImage("image_grise_embossee.pgm", tmp);
	printf("\n%f\n",t);
	return image;
}

grey_image_type * ppm_to_pgm(color_image_type *color){
	int w = color->width;
	int h = color->height;
	grey_image_type * image = createGreyImage(w, h);
	int r, g, b;
	start = omp_get_wtime();
	// Ici le parallelisme créée un ralentissement. 0.035037 à 0.054439 avec 4 threads
	//#pragma omp parallel num_threads(4)
	//{
		//#pragma omp for
		for(int i = 0;i<w*h;i++){
			r = color->pixels[i].r;
			g = color->pixels[i].g;
			b = color->pixels[i].b;
			image->pixels[i] = (299*r + 587*g + 114*b)/1000;
		}
	//}
	stop=omp_get_wtime();
	t=stop-start;
	saveGreyImage("image_grise.pgm", image);
	printf("\n%f\n",t);
	return image;
}

int main(int argc, char ** argv){
	
	color_image_type * x = loadColorImage(argv[1]);
	grey_image_type * y = createGreyImage(x->width, x->height);
	y = ppm_to_pgm(x);
	y = embossage(y);
	egalisation_histo(y);
	
	return 0;
}
