/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   myobject.h
 * Author: drolland
 *
 * Created on 28 novembre 2016, 12:50
 */

#ifndef NAMESPACE_OBJECTNAME_H
#define NAMESPACE_OBJECTNAME_H

#include <glib-2.0/glib-object.h>

G_BEGIN_DECLS
        
#define NAMESPACE_TYPE_OBJECTNAME (namespace_objectname_get_type())
#define NAMESPACE_OBJECTNAME(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),NAMESPACE_TYPE_OBJECTNAME,NamespaceObjectName))
#define NAMESPACE_OBJECTNAME_CLASS(klass) ( G_TYPE_CHECK_CLASS_CAST((obj),NAMESPACE_TYPE_OBJECTNAME,NamespaceObjectNameClass))
#define NAMESPACE_IS_OBJECTNAME(obj) ( G_TYPE_CHECK_INSTANCE_TYPE(obj))
#define NAMESPACE_IS_OBJECTNAME_CLASS(klass) ( G_TYPE_CHECK_CLASS_TYPE(klass))
#define NAMESPACE_OBJECTNAME_GET_CLASS(obj) ( G_TYPE_INSTANCE_GET_CLASS(obj))

typedef struct _my_object NamespaceObjectName;
typedef struct _my_object_class NamespaceObjectNameClass;
   
GType namespace_objectname_get_type();

/*  *******************************************  *
 *  NamespaceObjectName Public Methods           *
 *  *******************************************  */

NamespaceObjectName* my_object_new();              
   
        
G_END_DECLS
        
#endif /* NAMESPACE_OBJECTNAME_H */

