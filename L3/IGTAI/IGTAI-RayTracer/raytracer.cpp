
#include "raytracer.h"
#include "scene_types.h"
#include "ray.h"
#include "image.h"
#include "kdtree.h"
#include <stdio.h>
#include <time.h>

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


bool intersectMirror(Ray *ray, Intersection *intersection, Object* obj)
{
  float denom = dot(obj->geom.mirror.normal,ray->dir);
  if (abs(denom) < acne_eps)
    return false;

  vec3 p0_l0 = obj->geom.mirror.center - ray->orig;
  float res = dot(p0_l0, obj->geom.mirror.normal)/denom;
  vec3 pos = ray->orig + (res) * ray->dir;

  if (res < ray->tmin || res > ray->tmax || distance(pos, obj->geom.mirror.center) > obj->geom.mirror.radius * obj->geom.mirror.radius)
  {
    return false;
  }
  ray->tmax = res;
  intersection->position = rayAt(*ray,res);
  intersection->normal = obj->geom.mirror.normal;
  intersection->mat = &(obj->mat);
  return true;
}

bool intersectTriangle(Ray *ray, Intersection *intersection, Object *obj)
{
  vec3 edge1, edge2;
  vec3 p,vec_q,vec_t;
  float determinant, inv_determinant, u, v;
  float res;

  edge1 = obj->geom.triangle.v1 - obj->geom.triangle.v0;
  edge2 = obj->geom.triangle.v2 - obj->geom.triangle.v0;
  p = cross(ray->dir,edge2);
  determinant = dot(edge1,p);
  //parallèle
  if (determinant > -acne_eps && determinant < acne_eps) return false;
  inv_determinant = 1.f / determinant;

  vec_t = ray->orig - obj->geom.triangle.v0;
  u = dot(vec_t,p)*inv_determinant;
  //en dehors du triangle
  if (u < 0.f || u > 1.f) return false;

  vec_q = cross(vec_t,edge1);
  v=dot(ray->dir,vec_q)*inv_determinant;
  //en dehors du triangle
  if (v< 0.f || u+v > 1.f) return false;

  res = dot(edge2,vec_q) * inv_determinant;

  if (res>acne_eps && (res<=ray->tmax && res>= ray->tmin))
  {
    ray->tmax=res;
    intersection->position = rayAt(*ray, res);
    intersection->normal = normalize(obj->geom.triangle.normal);
    intersection->mat = &(obj->mat);
    return true;
  }

  return false;
}

bool intersectEllipsoid(Ray *ray, Intersection *intersection, Object *obj) {
  vec3 vec_ray_center = ray->orig - obj->geom.ellipsoid.center;
  float res;
  float a = ((ray->dir.x * ray->dir.x) / (obj->geom.ellipsoid.size.x * obj->geom.ellipsoid.size.x)) +
            ((ray->dir.y * ray->dir.y) / (obj->geom.ellipsoid.size.y * obj->geom.ellipsoid.size.y)) +
            ((ray->dir.z * ray->dir.z) / (obj->geom.ellipsoid.size.z * obj->geom.ellipsoid.size.z));


  float b = ((2.f * vec_ray_center.x * ray->dir.x) / (obj->geom.ellipsoid.size.x * obj->geom.ellipsoid.size.x)) +
            ((2.f * vec_ray_center.y * ray->dir.y) / (obj->geom.ellipsoid.size.y * obj->geom.ellipsoid.size.y)) +
            ((2.f * vec_ray_center.z * ray->dir.z) / (obj->geom.ellipsoid.size.z * obj->geom.ellipsoid.size.z));
  

  float c = ((vec_ray_center.x * vec_ray_center.x) / (obj->geom.ellipsoid.size.x * obj->geom.ellipsoid.size.x)) +
            ((vec_ray_center.y * vec_ray_center.y) / (obj->geom.ellipsoid.size.y * obj->geom.ellipsoid.size.y)) +
            ((vec_ray_center.z * vec_ray_center.z) / (obj->geom.ellipsoid.size.z * obj->geom.ellipsoid.size.z)) - 1.f;

  float delta = ((b * b) - (4.f * a * c));
  if (sqrt(delta) < 0) return false;

  float t0 = (-b - sqrt(delta)) / (2.f * a);
  float t1 = (-b + sqrt(delta)) / (2.f * a);

  if ((t1 >= ray->tmin && t1 <= ray->tmax) ||
      (t0 >= ray->tmin && t0 <= ray->tmax)) {
    if (t0 < t1 && (t0 >= ray->tmin && t0 <= ray->tmax))
      res = t0;
    else if (t1 <= t0 && (t1 >= ray->tmin && t1 <= ray->tmax))
      res = t1;
  } else
    res = -1.0;

  if (res <= ray->tmax && res >= ray->tmin) {
    ray->tmax = res;
    intersection->position = rayAt(*ray, res+acne_eps);
    intersection->normal =
        normalize(intersection->position - obj->geom.ellipsoid.center);

        intersection->normal.x = 2.f*intersection->normal.x/(obj->geom.ellipsoid.size.x*obj->geom.ellipsoid.size.x);
        intersection->normal.y = 2.f*intersection->normal.y/(obj->geom.ellipsoid.size.y*obj->geom.ellipsoid.size.y);
        intersection->normal.z = 2.f*intersection->normal.z/(obj->geom.ellipsoid.size.z*obj->geom.ellipsoid.size.z);
    intersection->normal = normalize(intersection->normal);
    intersection->mat = &(obj->mat);
    return true;
  } else
    return false;
}



bool intersectCylinder (Ray *ray, Intersection *intersection, Object *obj)
{
  point3 p0 = point3(ray->orig.x-obj->geom.cylinder.center.x, ray->orig.y-obj->geom.cylinder.center.y, ray->orig.z-obj->geom.cylinder.center.z);

  float a = ray->dir.x*ray->dir.x+ray->dir.z*ray->dir.z;
  float b = 2.f*ray->dir.x*p0.x + 2.f*ray->dir.z*p0.z;
  float c = p0.x*p0.x+p0.z*p0.z-(obj->geom.cylinder.radius*obj->geom.cylinder.radius);

  double delta = b*b - 4*a*c;

  if (delta < 0 || a==0)
    return false;

  float t0 = (-b - sqrt(delta))/(2*a);
  float t1 = (-b + sqrt(delta))/(2*a);

  if (t0 < ray->tmin && t1 < ray->tmin)
    return false;

  if (t1 < t0 && (t1 <= ray->tmax && t1 >= ray->tmin))
  {
    float tmp = t0;
    t0=t1;
    t1=tmp;
}

  float y0 = p0.y + t0*ray->dir.y;
  float y1 = p0.y + t1*ray->dir.y;
  
  // si height = 1
  if (y0<-obj->geom.cylinder.height)
  {
// if y0<-1 && y1<-1 pas d'intersection. 
    if (y1<-obj->geom.cylinder.height)
      return false;
    else
    {
// if y0<-1 && y1>-1 intersection disque du bas
      float th = t0 + (t1-t0) * (y0+obj->geom.cylinder.height) / (y0-y1);
      if (th<=0-acne_eps)
        return false;

      if (th>=ray->tmin && th <= ray->tmax)
      {
        ray->tmax = th;
        intersection->position = rayAt(*ray, th+acne_eps);
        intersection->normal = vec3(0,-1,0);
        intersection->mat=&(obj->mat);
        return true;
      }
    }
  }
  else if (y0>=-obj->geom.cylinder.height && y0<=obj->geom.cylinder.height)
  {
// if y0<1 && y0>-1 intersection avec les côtés
    if (t0<=0-acne_eps)
      return false;
    if (t0<=ray->tmax && t0>=ray->tmin)
    {
      ray->tmax = t0;
      intersection->position = rayAt(*ray, t0+acne_eps);
      vec3 tmp;
      vec3 normal;
      vec3 intersection_tmp;

      tmp = obj->geom.cylinder.center;
      intersection_tmp = intersection->position;
      tmp.y = intersection_tmp.y;
      normal = vec3(intersection->position.x - tmp.x, intersection->position.y - tmp.y, intersection->position.z - tmp.z);
      intersection->normal = normalize(normal);
      intersection->mat = &(obj->mat);
      return true;
    }
  }
  else if (y0>obj->geom.cylinder.height)
  {
    if (y1>obj->geom.cylinder.height)
// if y0>1 && y1>1 pas d'intersection
      return false;
    else
    {
// if y0>1 && y1<1 intersection avec le disque du haut
      float th = t0 + (t1-t0) * (y0-obj->geom.cylinder.height)/(y0-y1);
      if (th<=0-acne_eps)
        return false;

      if (th<=ray->tmax && th>=ray->tmin)
      {
        ray->tmax = th;
        intersection->position = rayAt(*ray, th+acne_eps);
        intersection->normal = vec3(0,1,0);
        intersection->mat = &(obj->mat);
        return true;
      }
    }
  }
  return false;
}


bool intersectScene(const Scene *scene, Ray *ray, Intersection *intersection) {
  bool hasIntersection = false;
  size_t objectCount = scene->objects.size();

  //!\todo loop on each object of the scene to compute intersection

  for (int i=0;i<(int)objectCount;i++){
    if(scene->objects[i]->geom.type == SPHERE){
        if(intersectSphere(ray, intersection, scene->objects[i]))
          hasIntersection = true;
    }else if(scene->objects[i]->geom.type == PLANE){
        if(intersectPlane(ray, intersection, scene->objects[i]))
          hasIntersection = true;
    }else if (scene->objects[i]->geom.type == TRIANGLE) {
      if (intersectTriangle(ray, intersection, scene->objects[i]))
        hasIntersection = true;
    }else if (scene->objects[i]->geom.type == ELLIPSOID){
      if (intersectEllipsoid(ray, intersection, scene->objects[i]))
        hasIntersection = true;
    }else if (scene->objects[i]->geom.type == CYLINDER){
      if (intersectCylinder(ray, intersection, scene->objects[i]))
        hasIntersection = true;
    }else if (scene->objects[i]->geom.type == MIRROR){
      if (intersectMirror(ray, intersection, scene->objects[i]))
        hasIntersection = true;
    }
  }
  return hasIntersection;
}

/* ---------------------------------------------------------------------------
 */
/*
 *  The following functions are coded from Cook-Torrance bsdf model
 *description and are suitable only
 *  for rough dielectrics material (RDM. Code has been validated with Mitsuba
 *renderer)
 */

/** Normal Distribution Function : Beckmann
 * NdotH : Norm . Half
 */

// Shadowing and masking function. Linked with the NDF. Here, Smith function,
// suitable for Beckmann NDF
float RDM_chiplus(float c) {
	return (c > 0.f) ? 1.f : 0.f;
}



float RDM_Beckmann(float NdotH, float alpha) {

  float cosSquare = NdotH * NdotH;
  float haut = -((1-cosSquare) / (cosSquare));
  float num = exp(haut / (alpha*alpha));
  float den = (3.1415f * (alpha*alpha) * (cosSquare*cosSquare));
  return RDM_chiplus(NdotH)*(num/den);
}

// Fresnel term computation. Implantation of the exact computation. we can use
// the Schlick approximation
// LdotH : Light . Half
float RDM_Fresnel(float LdotH, float extIOR, float intIOR) {

  float cosTetaI;
  cosTetaI = LdotH;

  float sinTetaTCarre = ((extIOR/intIOR)*(extIOR/intIOR))*(1-(cosTetaI*cosTetaI));
  if (sinTetaTCarre>1)
  {
    return 1;
  }
  else
  {
    float cosTetaT=sqrt(1-sinTetaTCarre);

    float Rs = ((extIOR*cosTetaI-intIOR*cosTetaT)*(extIOR*cosTetaI-intIOR*cosTetaT))/((extIOR*cosTetaI+intIOR*cosTetaT)*(extIOR*cosTetaI+intIOR*cosTetaT));
    float Rp = ((extIOR*cosTetaT-intIOR*cosTetaI)*(extIOR*cosTetaT-intIOR*cosTetaI))/((extIOR*cosTetaT+intIOR*cosTetaI)*(extIOR*cosTetaT+intIOR*cosTetaI));

    float F = 0.5*(Rs+Rp);
    return F;
  }
}

// DdotH : Dir . Half
// DdotN : Half . Norm
float RDM_G1(float DdotH, float DdotN, float alpha) {

  float tanTetaD = sqrt(1-(DdotN*DdotN))/DdotN;
  float b = 1/(alpha*tanTetaD);
  float k = DdotH/DdotN;


  if (k > 0 && b < 1.6)
  {
    float num = (3.535*b)+(2.181*(b*b));
    float denum = 1+2.276*b+2.577*(b*b);
    return RDM_chiplus(k)*(num/denum);
  }
  else
  {
    return RDM_chiplus(k);
  }
    
  
}

// LdotH : Light . Half
// LdotN : Light . Norm
// VdotH : View . Half
// VdotN : View . Norm
float RDM_Smith(float LdotH, float LdotN, float VdotH, float VdotN,
                float alpha) {

  return clamp(dot(RDM_G1(LdotH,LdotN,alpha),RDM_G1(VdotH,VdotN,alpha)),acne_eps,1.f);
}

// Specular term of the Cook-torrance bsdf
// LdotH : Light . Half
// NdotH : Norm . Half
// VdotH : View . Half
// LdotN : Light . Norm
// VdotN : View . Norm
color3 RDM_bsdf_s(float LdotH, float NdotH, float VdotH, float LdotN,
                  float VdotN, Material *m) {
  
  return m->specularColor*((RDM_Beckmann(NdotH,m->roughness)*RDM_Fresnel(LdotH,1.f,m->IOR)*RDM_Smith(LdotH,LdotN,VdotH,VdotN,m->roughness))/
    (4.f*LdotN*VdotN));
}
// diffuse term of the cook torrance bsdf
color3 RDM_bsdf_d(Material *m) {
  return  m->diffuseColor / 3.1415f;
}

// The full evaluation of bsdf(wi, wo) * cos (thetai)
// LdotH : Light . Half
// NdotH : Norm . Half
// VdotH : View . Half
// LdotN : Light . Norm
// VdtoN : View . Norm
// compute bsdf * cos(Oi)
color3 RDM_bsdf(float LdotH, float NdotH, float VdotH, float LdotN, float VdotN,
                Material *m) {
  return (RDM_bsdf_d(m)+RDM_bsdf_s(LdotH,NdotH,VdotH,LdotN,VdotN,m));
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
  
  vec3 h = normalize(v+l);
  float LdotH,NdotH,VdotH,LdotN,VdotN;
  LdotH = clamp(dot(l,h),acne_eps,1.f);
  NdotH = clamp(dot(n,h),acne_eps,1.f);
  VdotH = clamp(dot(v,h),acne_eps,1.f);
  LdotN = clamp(dot(l,n),acne_eps,1.f);
  VdotN = clamp(dot(v,n),acne_eps,1.f);

  ret = RDM_bsdf(LdotH,NdotH,VdotH,LdotN,VdotN,mat)*lc*LdotN;
  return ret;	    
}

//! if tree is not null, use intersectKdTree to compute the intersection instead of intersect scene
color3 trace_ray(Scene * scene, Ray *ray, KdTree *tree) {
  color3 ret = color3(0,0,0);
  Intersection intersection, intersectionOmbre;
  Ray rayOmbre;
  size_t lightsCount = scene->lights.size();

  if(intersectScene(scene, ray, &intersection)){
    vec3 normal = intersection.normal;
    //vec3 v = (-(1.f))*(ray->dir);
    vec3 v =normalize(ray->orig - intersection.position);
    color3 lc;
    vec3 l;
    Material *mat = intersection.mat;
    
    for (int i = 0; i < (int)lightsCount; i++){
      lc = scene->lights[i]->color;
      l = normalize(scene->lights[i]->position - intersection.position);
      rayInit(&rayOmbre, intersection.position, l, acne_eps,distance(intersection.position,scene->lights[i]->position)-acne_eps);
      rayOmbre.orig=rayAt(rayOmbre,acne_eps);
      
      if (!intersectScene(scene, &rayOmbre, &intersectionOmbre)){
        ret = ret + shade(normal, v, l, lc, mat);
      }
    }
    float LdotH;
    color3 cr=color3(0,0,0);
    if (ray->depth <= 10){
      Ray reflection;
      vec3 v2 = normalize(ray->orig - intersection.position);
      rayInit(&reflection,intersection.position,normalize(reflect(ray->dir,intersection.normal)),0,100000,ray->depth+1);
      reflection.orig = rayAt(reflection,acne_eps);
      vec3 l2 = reflection.dir;
      vec3 h2 = normalize(v2+l2);
      LdotH = clamp(dot(l2,h2),acne_eps,1.f);
      cr = trace_ray(scene,&reflection,tree)*RDM_Fresnel(LdotH,1.f,intersection.mat->IOR)*intersection.mat->specularColor;
    }
    return ret + cr;

  }else{
    ret = scene->skyColor;
  }
  
  return ret;
}

void renderImage(Image *img, Scene *scene) {

  //! This function is already operational, you might modify it for antialiasing and kdtree initializaion
  float aspect = 1.f/scene->cam.aspect;
  srand(time(NULL));
  float x, y;
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
    for (size_t i = 0; i < img->width; i++) {
    color3 somme=color3(0,0,0);
    color3 *ptr;
      for (int k = 0; k < 8; k++) {
        
        x = (((float)rand() / (float)RAND_MAX) - 0.5f );
        y = (((float)rand() / (float)RAND_MAX) - 0.5f );
        
        ptr = getPixelPtr(img, i, j);
        vec3 ray_dir = scene->cam.center + ray_delta_x + ray_delta_y +
                     float(i+x) * dx + float(j+y) * dy ;
        Ray rx;
        rayInit(&rx, scene->cam.position, normalize(ray_dir));
        somme += trace_ray(scene, &rx, tree);
        
      }
      somme=somme/8.f;
      (*ptr)=somme;
    }
  }
}
