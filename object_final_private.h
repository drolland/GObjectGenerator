
#pragma once

#include <glib-object.h>

G_BEGIN_DECLS
        
#define NAMESPACE_TYPE_OBJECTNAME (namespace_objectname_get_type())
G_DECLARE_FINAL_TYPE(NamespaceObjectName,namespace_objectname,NAMESPACE,OBJECTNAME,PNamespacePObjectName)

typedef struct _NamespaceObjectNamePrivate NamespaceObjectNamePrivate;

typedef struct _NamespaceObjectName {
    PNamespacePObjectName parent_instance;
    NamespaceObjectNamePrivate* priv;
} NamespaceObjectName;

/* For use with derivable type
 * 
typedef struct _NamespaceObjectNameClass {
    PNamespacePObjectNameClass parent_class;
} NamespaceObjectNameClass;
*/


/*  *******************************************  *
 *  NamespaceObjectName Public Methods           *
 *  *******************************************  */

NamespaceObjectName* namespace_objectname_new();              
   
        
G_END_DECLS