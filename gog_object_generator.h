#pragma once

#include <glib-2.0/glib.h>


G_BEGIN_DECLS

enum {
    GOG_OBJECT_FINAL_PRIVATE
};

void gog_generate_object(gint object_type,gchar* output_path,gchar* _namespace,gchar* _object_name,gchar* _parent_namespace,gchar* _parent_object_name );
        
        
        
G_END_DECLS


