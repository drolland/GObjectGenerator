



#include <string.h>
#include <gio/gio.h>
#include <glib/gstdio.h>
#include "gog_macros.h"
#include "gog_object_generator.h"

#undef G_LOG_DOMAIN
#define G_LOG_DOMAIN "Gog-ObjectGenerator" 

typedef struct _SubsTreeNode {
    GSList* childs;
    gchar c;
    gchar* substitute;
} SubsTreeNode;

static inline SubsTreeNode* subs_tree_node_new(gchar c,gchar* substitute){
    SubsTreeNode* node = g_malloc(sizeof(SubsTreeNode));
    node->childs = NULL;
    node->c = c;
    node->substitute = substitute;      // Assume we don't need to duplicate string
}

static inline void subs_tree_node_add_child(SubsTreeNode* self, SubsTreeNode* child){
    self->childs = g_slist_append(self->childs,child);
}

static inline SubsTreeNode* subs_tree_node_get_child(SubsTreeNode* self,gchar c){
    
    if ( self->childs == NULL)
        return NULL;
    
    GSList* list = self->childs;
    GSList* current = list;
    
    do {
        SubsTreeNode* node = (SubsTreeNode*)current->data;
        if ( node->c == c )
            return node;      
    } while( ( current = g_slist_next(current) ) != NULL );
 
    return NULL;    
}


static inline void subs_tree_node_free(gpointer self){
    
    SubsTreeNode* s = self;
    
    if ( s->childs ){
        g_slist_free_full(s->childs,subs_tree_node_free);
    }
    
    // Assume that subsiture string isn't a duplicate and hance we don't need to free it
    
    g_free(self);
}


SubsTreeNode* subs_tree_build(gchar** strings,gchar** substitution_strings,gint nb_strings){
    
    SubsTreeNode* tree_root = subs_tree_node_new('\0',NULL);
    
    for(int i = 0; i < nb_strings; i++){
        
        SubsTreeNode* iter = tree_root;
        
        size_t length = strlen(strings[i]);
        
        for(int j = 0; j < length ; j++){
            
            SubsTreeNode* get_node = subs_tree_node_get_child(iter,strings[i][j]);
            
            if ( get_node != NULL ){
                
                iter = get_node;

            }
            else{
                
                SubsTreeNode* new_node = subs_tree_node_new(strings[i][j],NULL);
                subs_tree_node_add_child(iter,new_node);
                iter = new_node;
                    
            }
                       
        }
        
        iter->substitute = substitution_strings[i];
        
    }
    
    return tree_root;
    
}


gchar* g_str_substitute(gchar* src,gint src_length,gchar** strings,gchar** substitution_strings,gint nb_strings){
    
    SubsTreeNode* tree_root = subs_tree_build(strings,substitution_strings,nb_strings);
    SubsTreeNode* iter = tree_root;
    
    gchar* src_begin = src;                 //  Pointers keeping track of the begining and the end of the source buffer interval to be copied to destination buffer
    gchar* src_end = src;                   
    gchar* dst_ptr = 0;                     //  pointer keeping track of the destination buffer position during the process of copy/substituion

    gchar* dst = 0;                         //  Destination string
    gint dst_size = 0;                      //  Computed size of the destination buffer
    
    // Compute needed destination buffer size 
    
    do {
        
        iter = subs_tree_node_get_child(iter,*src_end);
        if ( iter == NULL)
            iter = tree_root;
        src_end++;
        
        
        if ( iter != tree_root){
            SubsTreeNode* next = iter;
            
            gchar* src_end_backup = src_end - 1;
            
            
            while( (next = subs_tree_node_get_child(next,*src_end)) != NULL  ){
                src_end++;
                iter = next;
            }
            
            if ( iter->substitute != NULL){
                
                dst_size += strlen(iter->substitute);
            }
            else{
                dst_size += src_end - src_end_backup;
            }    
        } 
        else {
            dst_size++;
        }
        
        
    } while(*src_end != '\0');
    
    
    
    // Allocate destination buffer then do actual copy/substitution
    
    dst = g_malloc((dst_size+1)*sizeof(gchar));
    dst[dst_size] = '\0';
    dst_ptr = dst;
    
    src_end = src;

    iter = tree_root;
    
    do {
        
        iter = subs_tree_node_get_child(iter,*src_end);
        if ( iter == NULL)
            iter = tree_root;
        src_end++;
        
        
        if ( iter != tree_root){
           
            gchar* src_end_backup = src_end - 1;
                        
            SubsTreeNode* next = iter;
            
            while( (next = subs_tree_node_get_child(next,*src_end)) != NULL  ){
                src_end++;
                iter = next;
            }
            
            if ( iter->substitute != NULL){
                dst_size += strlen(iter->substitute);
                memcpy(dst_ptr,src_begin,src_end_backup-src_begin);
                dst_ptr += src_end_backup - src_begin;
                memcpy(dst_ptr,iter->substitute,strlen(iter->substitute));
                dst_ptr += strlen(iter->substitute);
                
            }
            else{ 
                memcpy(dst_ptr,src_begin,src_end -src_begin);
                dst_ptr += src_end  - src_begin;
            }    
            src_begin = src_end;
            iter = tree_root;
        } 
       
        
        
    } while(*src_end != '\0');
    
    memcpy(dst_ptr,src_begin,src_end-src_begin);
    dst_ptr += src_end - src_begin;
    *dst_ptr = '\0';
        
    if ( tree_root ) subs_tree_node_free(tree_root);
        
    return dst;
}

gchar* gog_build_name_upper(gchar* str){
    
    gsize length = strlen(str);
    gsize nb_underscore = 0;
    
    for(int i = 0; i < length; i++)
        if ( str[i] == '_') nb_underscore++;
    
    gchar* dst = g_malloc((length - nb_underscore +1) * sizeof(gchar));
    gchar* dst_ptr = dst;
    
    for(int i = 0; i < length; i++)
        if ( str[i] != '_') {
            *dst_ptr = g_ascii_tolower(str[i]);
             dst_ptr++;
        }
    
    return dst;
}

static gchar* gog_str_make_macro(gchar* str){  
    return g_ascii_strup(str,strlen(str));
}

static gchar* gog_str_make_name(gchar* str){  
    
    if ( str == NULL || str[0] == '\0')
        return NULL;
    
    gsize length = strlen(str);
    gsize nb_underscore = 0;
    
    for(int i = 0; i < length; i++)
        if ( str[i] == '_') nb_underscore++;
    
    gchar* dst = g_malloc((length - nb_underscore +1) * sizeof(gchar));
    dst[length-nb_underscore] = '\0';
   
    
    dst[0] = g_ascii_toupper(str[0]);
    gchar* dst_ptr = dst + 1;
     
    for(int i = 1; i < length; i++)
        if ( str[i] != '_') {
            if(str[i-1] == '_')
                *dst_ptr = g_ascii_toupper(str[i]);
            else
                *dst_ptr = g_ascii_tolower(str[i]);
            dst_ptr++;
        }
    
    return dst;
}

static gchar* gog_str_make_func(gchar* str){  
    return g_ascii_strdown(str,strlen(str));
}

void gog_generate_file(gchar* input_path,gchar* _namespace,gchar* _object_name,gchar* _parent_namespace,gchar* _parent_object_name,gchar* output_path){
    
    GError* error = 0;  
    gchar* read_buffer = 0;
    gsize read_buffer_size = 0 ;
    
    GFile* input_file = g_file_new_for_path(input_path);
    
    error = 0;
    GIOChannel* input_channel = g_io_channel_new_file(input_path,"r",&error);
    
    GOG_ERROR(error,"Error while opening input file : %s",error->message);
  
    
    error = 0;
    g_io_channel_read_to_end(input_channel,&read_buffer,&read_buffer_size,&error);
    GOG_ERROR(error,"Error occured while reading file template :  %s",error->message);
 
    
    
    enum {
        NAMESPACE_MACRO,
        NAMESPACE_NAME,
        NAMESPACE_FUNC,
        OBJECTNAME_MACRO,
        OBJECTNAME_NAME,
        OBJECTNAME_FUNC,
        PARENT_NAMESPACE_MACRO,
        PARENT_NAMESPACE_NAME,
        PARENT_NAMESPACE_FUNC,
        PARENT_OBJECTNAME_MACRO,
        PARENT_OBJECTNAME_NAME,
        PARENT_OBJECTNAME_FUNC,
        ENUM_TOTAL
    };
    
    gchar* strings[ENUM_TOTAL] =
    {
        "NAMESPACE"     ,   "Namespace"     ,   "namespace", 
        "OBJECTNAME"    ,   "ObjectName"    ,   "objectname",
        "PNAMESPACE"    ,   "PNamespace"    ,   "pnamespace",
        "POBJECTNAME"   ,   "PObjectName"   ,   "pobjectname"
    };
    
    gchar* substitute_string[ENUM_TOTAL];
    
    substitute_string[NAMESPACE_MACRO] = gog_str_make_macro(_namespace);
    substitute_string[NAMESPACE_NAME] = gog_str_make_name(_namespace);
    substitute_string[NAMESPACE_FUNC] = gog_str_make_func(_namespace);
    substitute_string[OBJECTNAME_MACRO] = gog_str_make_macro(_object_name);
    substitute_string[OBJECTNAME_NAME] = gog_str_make_name(_object_name);
    substitute_string[OBJECTNAME_FUNC] = gog_str_make_func(_object_name);
    substitute_string[PARENT_NAMESPACE_MACRO] = gog_str_make_macro(_parent_namespace);
    substitute_string[PARENT_NAMESPACE_NAME] = gog_str_make_name(_parent_namespace);
    substitute_string[PARENT_NAMESPACE_FUNC] = gog_str_make_func(_parent_namespace);
    substitute_string[PARENT_OBJECTNAME_MACRO] = gog_str_make_macro(_parent_object_name);
    substitute_string[PARENT_OBJECTNAME_NAME] = gog_str_make_name(_parent_object_name);
    substitute_string[PARENT_OBJECTNAME_FUNC] = gog_str_make_func(_parent_object_name);
    
    
    gchar* write_buffer = g_str_substitute(read_buffer,read_buffer_size,strings,substitute_string,ENUM_TOTAL);
    
    error = 0;
    GIOChannel* output_channel = g_io_channel_new_file(output_path,"w",&error);
    GOG_ERROR(error,"Error while opening output file : %s",error->message);
    
    error = 0;
    g_io_channel_write_chars(output_channel,write_buffer,strlen(write_buffer),NULL,&error);
    GOG_ERROR(error,"Error while writing to ouput file : %s",error->message);
    
    
 cleanup:
 
    if ( input_channel ) {
        g_io_channel_shutdown(input_channel,TRUE,NULL);
        g_io_channel_unref(input_channel);
    }
 
    if ( output_channel ) {
        g_io_channel_shutdown(output_channel,TRUE,NULL);
        g_io_channel_unref(output_channel);
    }
 
    if ( read_buffer ) g_free(read_buffer);
    
    if ( write_buffer) g_free(write_buffer);
 
    for(int i = 0; i < ENUM_TOTAL; i++) 
        if ( substitute_string[i] ){
            g_free(substitute_string[i]);
        }
            
    
}


void gog_generate_object(gchar* _namespace,gchar* _objectname,gchar* _parent_namespace,gchar* _parent_object_name,gchar* output_path ){
    
    GString* header_output_path = g_string_new(output_path);
    g_string_append_printf(header_output_path,"%s_%s.h",_namespace,_objectname);
    
    GString* source_output_path = g_string_new(output_path);
    g_string_append_printf(source_output_path,"%s_%s.c",_namespace,_objectname);
    
    gog_generate_file("object_final_private.c",_namespace,_objectname,_parent_namespace,_parent_object_name,source_output_path->str);
    gog_generate_file("object_final_private.h",_namespace,_objectname,_parent_namespace,_parent_object_name,header_output_path->str);
    
    
    g_string_free(header_output_path,TRUE);
    g_string_free(source_output_path,TRUE);
}








