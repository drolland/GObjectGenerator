
#include "namespace_objectname.h"


// Internal API

void namespace_objectname_dispose(GObject* self);
void namespace_objectname_finalize(GObject* self);
void namespace_objectname_class_init(NamespaceObjectNameClass* klass,gpointer klass_data);
void namespace_objectname_instance_init(NamespaceObjectName* self,gpointer klass);

// Private Data structure
typedef struct _NamespaceObjectNamePrivate {
    
} NamespaceObjectNamePrivate;


PNamespacePObjectNameClass* namespace_objectname_parent_class = NULL;

void namespace_objectname_dispose(GObject* g_object){
    
    NamespaceObjectName* self = NAMESPACE_OBJECTNAME(g_object);
    
    
    G_OBJECT_CLASS(namespace_objectname_parent_class)->dispose(g_object);
}

void namespace_objectname_finalize(GObject* g_object){
    
    NamespaceObjectName* self = NAMESPACE_OBJECTNAME(g_object);
    
    
    G_OBJECT_CLASS(namespace_objectname_parent_class)->finalize(g_object);
}

void namespace_objectname_class_init(NamespaceObjectNameClass* klass,gpointer klass_data){
    
    GObjectClass* g_object_class = G_OBJECT_CLASS(klass);

    if ( namespace_objectname_parent_class == NULL)
        namespace_objectname_parent_class = g_type_class_peek_parent(klass);
    
    
    
    g_object_class->dispose = namespace_objectname_dispose;
    g_object_class->finalize = namespace_objectname_finalize;
    
    /* Override functions here */
    
    
    // Add private data to class instance
    g_type_class_add_private (klass, sizeof (NamespaceObjectNamePrivate));
}

void namespace_objectname_instance_init(NamespaceObjectName* self,gpointer klass){
    
    self->priv = G_TYPE_INSTANCE_GET_PRIVATE(self,NAMESPACE_TYPE_OBJECTNAME,NamespaceObjectNamePrivate);
    
    // Init your instance Here
    
    
    
    
}


NamespaceObjectName* namespace_objectname_new(){
    return g_object_new(NAMESPACE_TYPE_OBJECTNAME,NULL);
}

