


#include "namespace_objectname.h"
#include "namespace_objectname_priv.h"

#include <glib-2.0/glib.h>

gpointer namespace_objectname_parent_class = NULL;

void namespace_objectname_dispose(GObject* _self){
    
    NamespaceObjectName* self = NAMESPACE_OBJECTNAME(_self);
    
    G_OBJECT_CLASS(namespace_objectname_parent_class)->dispose(_self);
    
}

void namespace_objectname_class_init(gpointer klass,gpointer* class_data){
    
    GObjectClass* g_object_class = G_OBJECT_CLASS(klass);

    namespace_objectname_parent_class = g_type_class_peek_parent(klass);
    
    g_object_class->dispose = namespace_objectname_dispose;
    
    /* Override functions here */
    
}

void namespace_objectname_instance_init(GObject* _self,GObjectClass* _klass){
    
    NamespaceObjectName* self = NAMESPACE_OBJECTNAME(_self);
    
    /* Init your instance Here*/
    
}



GType namespace_objectname_get_type() {
    static GType type = 0;
    if (G_UNLIKELY(type == 0)) {
        
        const GTypeInfo type_info ={
            
            (guint16)                   sizeof(NamespaceObjectNameClass),       /* Size of class */
            (GBaseInitFunc)             NULL,                                   /* Base class init */
            (GBaseFinalizeFunc)         NULL,                                   /* Base class finalize */
                        
            (GClassInitFunc)            namespace_objectname_class_init,        /* Class init */
            (GClassFinalizeFunc)        NULL,                                   /* Class_finalize */
            (gpointer)                  NULL,                                   /* Class data - Passed to class init*/
            
            (guint16)                   sizeof(NamespaceObjectName),            /* Size of instance */
            (guint16)                   0,                                      /* N_preallocs */
            (GInstanceInitFunc)         namespace_objectname_instance_init,     /* Instance_init */
            
            (const GTypeValueTable*)    NULL,                                   /* Value_table */
        };
        
        type = g_type_register_static(G_TYPE_OBJECT,"NamespaceObjectName",&type_info,0);
    }
    return type;
}

NamespaceObjectName* namespace_objectname_new(){
    return g_object_new(NAMESPACE_TYPE_OBJECTNAME,NULL);
}

