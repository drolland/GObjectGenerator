#include "namespace_objectname.h"

typedef struct _NamespaceObjectNamePrivate {
    
} NamespaceObjectNamePrivate;

G_DEFINE_TYPE_WITH_PRIVATE(NamespaceObjectName,namespace_objectname,PNAMESPACE_TYPE_POBJECTNAME)


void namespace_objectname_dispose(GObject* g_object){
    
    NamespaceObjectName* self = NAMESPACE_OBJECTNAME(g_object);
    
    
    G_OBJECT_CLASS(namespace_objectname_parent_class)->dispose(g_object);
}

void namespace_objectname_finalize(GObject* g_object){
    
    NamespaceObjectName* self = NAMESPACE_OBJECTNAME(g_object);
    
    
    G_OBJECT_CLASS(namespace_objectname_parent_class)->finalize(g_object);
}

void namespace_objectname_class_init(NamespaceObjectNameClass* klass){
    
    GObjectClass* g_object_class = G_OBJECT_CLASS(klass);

    if ( namespace_objectname_parent_class == NULL)
        namespace_objectname_parent_class = g_type_class_peek_parent(klass);
    
    g_object_class->dispose = namespace_objectname_dispose;
    g_object_class->finalize = namespace_objectname_finalize;
    
    /* Override functions here */
    

}

void namespace_objectname_init(NamespaceObjectName* self){
    
    self->priv = G_TYPE_INSTANCE_GET_PRIVATE(self,NAMESPACE_TYPE_OBJECTNAME,NamespaceObjectNamePrivate);
    
    // Init your instance Here
    

}


NamespaceObjectName* namespace_objectname_new(){
    return g_object_new(NAMESPACE_TYPE_OBJECTNAME,NULL);
}

