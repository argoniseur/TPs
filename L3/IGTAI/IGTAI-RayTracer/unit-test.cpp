

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defines.h"
#include "ray.h"
#include "scene.h"
#include "raytracer.h"
#include "image.h"

#include "expected.h"

void validTest(const char *desc, bool value, bool expected){
  printf("%s \t: [%s]\n", desc, value == expected ? "OK":"fail"); 
}

int main(void){
  
  Material dummy;
  Object *plane1 = initPlane(vec3(0,0,1), 0, dummy);
  Object *plane2 = initPlane(vec3(1,1,1), 2, dummy);
  Object *sphere1 = initSphere(vec3(0,0,0), 1, dummy);
  Object *sphere2 = initSphere(vec3(1, 1, 1), 0.5, dummy);

  Ray r;
  Intersection dummyInter;
  rayInit(&r, point3(0,0,0), vec3(1,0,0));
  validTest("r0 to sphere1", intersectSphere(&r, &dummyInter, sphere1), true);
  validTest("r0 to sphere2", intersectSphere(&r, &dummyInter, sphere2), false);
  validTest("r0 to plane1", intersectPlane(&r, &dummyInter, plane1), false);
  validTest("r0 to plane2", intersectPlane(&r, &dummyInter, plane2), false);

  rayInit(&r, point3(0,0,0), vec3(1,0,0), 0.01, 0.02);
  validTest("r1 to sphere1", intersectSphere(&r, &dummyInter, sphere1), false);
  validTest("r1 to sphere2", intersectSphere(&r, &dummyInter, sphere2), false);
  validTest("r1 to plane1", intersectPlane(&r, &dummyInter, plane1), false);
  validTest("r1 to plane2", intersectPlane(&r, &dummyInter, plane2), false);


  rayInit(&r, point3(2,2,2), vec3(-1,-1,0-1));
  validTest("r2 to sphere1", intersectSphere(&r, &dummyInter, sphere1), true);
  validTest("r2 to sphere2", intersectSphere(&r, &dummyInter, sphere2), true);
  validTest("r2 to plane1", intersectPlane(&r, &dummyInter, plane1), false);
  validTest("r2 to plane2", intersectPlane(&r, &dummyInter, plane2), false);

  freeObject(plane1);
  freeObject(plane2);
  freeObject(sphere1);
  freeObject(sphere2);

  bool beckmann=true;
  for(int i=0; i<beckmannExpectedCount; i++){
    beckmann &= abs(beckmannExpected[i].res - RDM_Beckmann(beckmannExpected[i].NdotH, beckmannExpected[i].alpha))<0.0001f;
  }
  printf("RDM_Beckmann \t: [%s]\n",  beckmann ? "OK":"fail");

  bool fresnel=true;
  for(int i=0; i<fresnelExpectedCount; i++){
    fresnel &= abs(fresnelExpected[i].res - RDM_Fresnel(fresnelExpected[i].LdotH, fresnelExpected[i].extIOR,fresnelExpected[i].intIOR))<0.0001f;
  }
  printf("RDM_Fresnel \t: [%s]\n",  fresnel ? "OK":"fail"); 

  return 0;
}
