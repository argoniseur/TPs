
#include "raytracer.h"
#include "scene_types.h"
#include "ray.h"
#include "image.h"
#include "kdtree.h"
#include <stdio.h>


/// acne_eps is a small constant used to prevent acne when computing intersection
//  or boucing (add this amount to the position before casting a new ray !
const float acne_eps = 1e-4;

bool intersectPlane(Ray *ray, Intersection *intersection, Object *obj) {
	
    if(obj->geom.type == SPHERE){
        return false;
    }
    
    vec3 normal = obj->geom.plane.normal;
    vec3 direction = ray->dir;
    
    if(dot(direction,normal) == 0.f)
		return false;
		
    float dist = obj->geom.plane.dist;
	float d = dot(normal, direction);


	float t = -1*((dot(ray->orig, normal) + dist)/d);


    if(t < ray->tmin || t > ray->tmax)
        return false;

    intersection->normal = normal;
    intersection->position = rayAt(*ray, t);
    intersection->mat = &(obj->mat);
    ray->tmax = t;
  
    return true;
}

bool intersectSphere(Ray *ray, Intersection *intersection, Object *obj) {

    if(obj->geom.type == PLANE){
        return false;
    }
      
    vec3 center = obj->geom.sphere.center;
    float radius = obj->geom.sphere.radius;

    vec3 OminC = ray->orig - center;
    float OCdotOC = dot(OminC, OminC);
    float dDotOC = dot(ray->dir,OminC);
    float b = 2*dDotOC;
    float c = OCdotOC - (radius*radius);
    float delta = (b*b) - 4*c;
    float t;
    if (delta > 0){
		float k = ((-b) - sqrt(delta))/2;
		float l = ((-b) + sqrt(delta))/2;
		if (k < l && k > ray->tmin)
			t = k;
		else
			t = l;
	}else if (delta == 0){
		t = (-b)/2;
	}
	else{
		return false;
	}

    // tmin<=t<=tmax
    if(t < ray->tmin || t > ray->tmax)
        return false;

	point3 p = rayAt(*ray, t);
    intersection->normal = normalize(p-center);
    intersection->position = p;
    intersection->mat = &(obj->mat);
    ray->tmax = t;
  
    return true;
}


bool intersectScene(const Scene *scene, Ray *ray, Intersection *intersection) {
  bool hasIntersection = false;
  size_t objectCount = scene->objects.size();

  //!\todo loop on each object of the scene to compute intersection

  for (int i=0;i<(int)objectCount;i++){
    if(scene->objects[i]->geom.type == SPHERE){
        if(intersectSphere(ray, intersection, scene->objects[i]))
          hasIntersection = true;
    }
    if(scene->objects[i]->geom.type == PLANE){
        if(intersectPlane(ray, intersection, scene->objects[i]))
          hasIntersection = true;
    }
  }
  return hasIntersection;
}

/* --------------------------------------------------------------------------- */
/*
 *	The following functions are coded from Cook-Torrance bsdf model description and are suitable only
 *  for rough dielectrics material (RDM. Code has been validated with Mitsuba renderer)
 */

/** Normal Distribution Function : Beckmann
 * NdotH : Norm . Half
 */
float RDM_Beckmann(float NdotH, float alpha) {


  //! \todo compute Beckmann normal distribution
  return 0.5f;

}

// Fresnel term computation. Implantation of the exact computation. we can use the Schlick approximation
// LdotH : Light . Half
float RDM_Fresnel(float LdotH, float extIOR, float intIOR) {

  //! \todo compute Fresnel term
  return 0.5f;

}


// Shadowing and masking function. Linked with the NDF. Here, Smith function, suitable for Beckmann NDF
float RDM_chiplus(float c) {
  return (c > 0.f) ? 1.f : 0.f;
}

// DdotH : Dir . Half
// HdotN : Half . Norm
float RDM_G1(float DdotH, float DdotN, float alpha) {

  //!\todo compute G1 term of the Smith fonction
  return 0.5f;

}

// LdotH : Light . Half
// LdotN : Light . Norm
// VdotH : View . Half
// VdotN : View . Norm
float RDM_Smith(float LdotH, float LdotN, float VdotH, float VdotN, float alpha) {

  //!\todo the Smith fonction
  return 0.5f;


}

// Specular term of the Cook-torrance bsdf
// LdotH : Light . Half
// NdotH : Norm . Half
// VdotH : View . Half
// LdotN : Light . Norm
// VdotN : View . Norm
color3 RDM_bsdf_s(float LdotH, float NdotH, float VdotH, float LdotN, float VdotN, Material *m) {

  //!\todo specular term of the bsdf, using D = RDB_Beckmann, F = RDM_Fresnel, G = RDM_Smith
  return color3(.5f);

  
}
// diffuse term of the cook torrance bsdf
color3 RDM_bsdf_d(Material *m) {

  //!\todo compute diffuse component of the bsdf
  return color3(.5f);

}

// The full evaluation of bsdf(wi, wo) * cos (thetai)
// LdotH : Light . Half
// NdotH : Norm . Half
// VdotH : View . Half
// LdotN : Light . Norm
// VdtoN : View . Norm
// compute bsdf * cos(Oi)
color3 RDM_bsdf(float LdotH, float NdotH, float VdotH, float LdotN, float VdotN, Material *m) {

  //! \todo compute bsdf diffuse and specular term
  return color3(0.f);

}




/* --------------------------------------------------------------------------- */

color3 shade(vec3 n, vec3 v, vec3 l, color3 lc, Material *mat ){
  color3 ret = color3(0.f);
  float dote = dot(l, n);
  color3 tmp;

  if (dote < 0)
    ret = color3(0,0,0);
  else{
    tmp = color3(mat->diffuseColor / 3.141f);
    tmp = tmp * dote;
    tmp = tmp * lc;
    ret = tmp;
  }
  return ret;	    
}

//! if tree is not null, use intersectKdTree to compute the intersection instead of intersect scene
color3 trace_ray(Scene * scene, Ray *ray, KdTree *tree) {  
  color3 ret = color3(0,0,0);
  Intersection intersection;
  size_t lightsCount = scene->lights.size();

  if(intersectScene(scene, ray, &intersection)){
    vec3 normal = intersection.normal;
    vec3 v = (-(1.f))*(ray->dir);
    color3 lc;
    vec3 l;
    Material *mat = intersection.mat;

    for (int i = 0; i < (int)lightsCount; i++){
      lc = scene->lights[i]->color;
      l = normalize(scene->lights[i]->position - intersection.position);
      ret = ret + shade(normal, v, l, lc, mat);
    }

  }else{
    ret = scene->skyColor;
  }



  

  return ret;
}

void renderImage(Image *img, Scene *scene) {

  //! This function is already operational, you might modify it for antialiasing and kdtree initializaion
  float aspect = 1.f/scene->cam.aspect;
    
  KdTree *tree =  NULL;


  //! \todo initialize KdTree

  float delta_y = 1.f / (img->height * 0.5f); //! one pixel size
  vec3 dy = delta_y * aspect * scene->cam.ydir; //! one pixel step 
  vec3 ray_delta_y = (0.5f - img->height * 0.5f) / (img->height * 0.5f) * aspect * scene->cam.ydir;

  float delta_x = 1.f / (img->width * 0.5f);
  vec3 dx = delta_x * scene->cam.xdir;
  vec3 ray_delta_x = (0.5f - img->width * 0.5f) / (img->width * 0.5f) *scene->cam.xdir;
  
    
  for(size_t j=0; j<img->height; j++) {
    if(j!=0) printf("\033[A\r");
    float progress = (float)j/img->height*100.f;
    printf("progress\t[");
    int cpt = 0;
    for(cpt = 0; cpt<progress; cpt+=5) printf(".");
    for(       ; cpt<100; cpt+=5) printf(" ");
    printf("]\n");
#pragma omp parallel for
    for(size_t i=0; i<img->width; i++) {
      color3 *ptr = getPixelPtr(img, i,j);
      vec3 ray_dir = scene->cam.center + ray_delta_x + ray_delta_y + float(i)*dx + float(j)*dy;

      Ray rx;
      rayInit(&rx, scene->cam.position, normalize(ray_dir));
      *ptr = trace_ray(scene, &rx, tree);

    }
  }
}
