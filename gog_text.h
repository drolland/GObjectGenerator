

#ifndef GOG_SOURCE_CODE_H
#define GOG_SOURCE_CODE_H

#include <glib-2.0/glib.h>


G_BEGIN_DECLS
        
typedef struct _gog_text GogText;

GogText* gog_text_new();

void gog_text_append_lines(GogText* self, gchar* str);

gint gog_text_get_nb_lines(GogText* self);

gchar* gog_text_get_lines(GogText* self,int start,int end);






G_END_DECLS

#endif /* GOG_SOURCE_CODE_H */

