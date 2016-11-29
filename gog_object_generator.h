

#ifndef OBJECT_GENERATOR_H
#define OBJECT_GENERATOR_H

#include <glib-2.0/glib/gtypes.h>


G_BEGIN_DECLS

typedef struct _GogObjectFiles GogObjectFiles;

GogObjectFiles* gog_generate_object(const gchar* __namespace,const char* __object_name );
        
        
        
G_END_DECLS

#endif /* OBJECT_GENERATOR_H */

