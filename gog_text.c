#include "gog_text.h"

/**
 * SECTION: gog_text
 * @title: Text
 *
 * @short_description: type holding text data and providing
 * convenient access to it line-wise
 *
 * Arrays are similar to standard C arrays, except that they grow
 * automatically as elements are added.
 *
 * Array elements can be of any size (though all elements of one array
 * are the same size), and the array can be automatically cleared to
 * '0's and zero-terminated.
 *
 */

/****************************************
 * Abstraction for text lines
 ****************************************/

typedef struct _line{
    GString* str;
} _Line;

typedef struct _line_pair {
    _Line* l1;
    _Line* l2;
} _LinePair;

typedef struct _line_collection {
    GSList* list;
} _LineCollection;


_Line* _line_new(gchar* init){
    _Line* l = g_slice_new(_Line);
    l->str = g_string_new(init);
    return l;
}

#define _line_collection_concat(l1,l2)                      (_LineCollection*)g_slist_concat((GSList*)l1,(GSList*)l2)
#define _line_collection_append(lines,l)                    (_LineCollection*)g_slist_append((GSList*)lines,(GSList*)l)
#define _line_collection_length(lines)                      g_slist_length((GSList*)lines)
#define _line_collection_nth_data(lines,i)                  (_Line*)g_slist_nth_data((GSList*)lines,i)
#define _line_collection_last(lines)                        (_Line*)g_slist_last((GSList*)lines)
#define _line_collection_next(lines)                        (_LineCollection*)g_slist_next(lines)

static inline _LinePair _line_collection_get_range(_LineCollection* lines ,int start,int end){
    
    g_assert( start >= 0);
    g_assert( ( end < 0 ) || ( end > 0 && end > start));
    
    _LinePair pair;
    pair.l1 = NULL;
    pair.l2 = NULL;
    
    _LineCollection* current = lines;
    
    if ( current == NULL)
        return pair;
    
    /* find start line */
    int i = 0;
    while ( i != start || current->list->next != NULL ){
        i++;
        current = _line_collection_next(current);
    }

    /* start line too high*/
    if ( current->list->next == NULL && i != start){
        return pair;
    }
    
    pair.l1 = current->list->data;
    
    while ( i != end || current->list->next != NULL ){
        i++;
        current = _line_collection_next(current);
    }
    
    pair.l2 = current->list->data;   
    
    return pair;
}

/***************************************
 * Gog Text
 ***************************************/

typedef struct _gog_text{
    _LineCollection* lines;
} GogText;


GogText* gog_text_new(){
    GogText* t = g_slice_new(GogText);
    t->lines = NULL;
    return t;
}

void gog_text_append_lines(GogText* self,gchar* str){
    
    gchar** splitted_string = g_strsplit(str,"\n",0);
    
    _LineCollection* new_lines = NULL;

    for(gchar** current_str = splitted_string;*current_str != NULL;current_str++){
        _Line* nl = _line_new(*current_str);
        g_string_append_c(nl->str,'\n');
        new_lines = _line_collection_append(new_lines,nl);
    }
    
    self->lines = _line_collection_concat(self->lines,new_lines);
    
    g_strfreev(splitted_string);
}

gint gog_text_get_nb_lines(GogText* self){
    return _line_collection_length(self->lines);
}

/**
 * gog_text_get_lines:
 * @start:   Index of the first line ( starts à 0 )
 * @end:     Index of the last line  ( if end < 0, the last line will be the last available )
 * 
 * Returns the text contained beetwen line start and end ( Inclusive )
 *
 * Returns: the text
 */
gchar* gog_text_get_lines(GogText* self,int start,int end){
    
    _Line* start_line = NULL;
    _Line* end_line = NULL;
    
    if ( start >= 0)
        start_line = _line_collection_nth_data(self->lines,start);
    else
        start_line = _line_collection_nth_data(self->lines,0);
    
    if ( end >= 0)
        end_line = _line_collection_nth_data(self->lines,end);
    else
        end_line = _line_collection_last(self->lines);
 
    return NULL;
}

