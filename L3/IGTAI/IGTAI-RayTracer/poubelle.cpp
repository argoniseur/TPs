bool intersectPlane(Ray *ray, Intersection *intersection, Object *obj) {
	
    bool existIntersection = false;
    float t = ray->tmin;
    
    //Vérification que l'objet est un plan
    if(obj->geom.type == SPHERE){
        return false;
    }
      
    vec3 normal = obj->geom.plane.normal;
    float dist = obj->geom.plane.dist;
    point3 r;
    
    //Calcul de l'intersection rayon/objet 
    while( (t <= ray->tmax) && !existIntersection ){
        r.x = ray->orig.x + t*ray->dir.x;
        r.y = ray->orig.y + t*ray->dir.y;
        r.z = ray->orig.z + t*ray->dir.z;
        
        if( dot(normal, r) + dist == 0 )
            existIntersection = true;
        else
            t++;
    }
        
    //Si il n'y a pas d'intersection --> false
    if (!existIntersection)
        return false;
    
    //Sinon calculer la valeur de t pour le point d'intersection
    float d = dot(normal, ray->dir);
    if(d != 0)
        t = -1*((dot(ray->orig, normal) + dist)/d);
    else
        return false;
    
    // tmin<=t<=tmax? -> false / true + mise à jour de intersection
    if(t < ray->tmin || t > ray->tmax)
        return false;

    intersection->normal = normal;
    intersection->position = rayAt(*ray, t);
    ray->tmax = t;
  
    return true;
}
