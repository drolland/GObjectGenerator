
#pragma once

#include <glib-object.h>

G_BEGIN_DECLS
        
//#define NAMESPACE_TYPE_OBJECTNAME (namespace_objectname_get_type())
//#define NAMESPACE_OBJECTNAME(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj),NAMESPACE_TYPE_OBJECTNAME,NamespaceObjectName))
//#define NAMESPACE_IS_OBJECTNAME(obj) ( G_TYPE_CHECK_INSTANCE_TYPE(obj))
//#define NAMESPACE_OBJECTNAME_CLASS(klass) ( G_TYPE_CHECK_CLASS_CAST((klass),NAMESPACE_TYPE_OBJECTNAME,NamespaceObjectNameClass))
//#define NAMESPACE_IS_OBJECTNAME_CLASS(klass) ( G_TYPE_CHECK_CLASS_TYPE(klass))
//
//
//typedef struct _NamespaceObjectName NamespaceObjectName;
//typedef struct _NamespaceObjectNameClass NamespaceObjectNameClass;
//typedef struct _NamespaceObjectNamePrivate NamespaceObjectNamePrivate;

G_DECLARE_FINAL_TYPE(NamespaceObjectName,namespace_objectname,NAMESPACE,OBJECTNAME,PNAMESPACEPOBJECTNAME)

typedef struct _NamespaceObjectNamePrivate NamespaceObjectNamePrivate;

typedef struct _NamespaceObjectName {
    PNamespacePObjectName parent_instance;
    NamespaceObjectNamePrivate* priv;
} NamespaceObjectName;

typedef struct _NamespaceObjectNameClass {
    PNamespacePObjectNameClass parent_class;
} NamespaceObjectNameClass;

GType namespace_objectname_get_type();

/*  *******************************************  *
 *  NamespaceObjectName Public Methods           *
 *  *******************************************  */

NamespaceObjectName* namespace_objectname_new();              
   
        
G_END_DECLS
