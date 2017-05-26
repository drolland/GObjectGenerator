



#include <string.h>
#include <gio/gio.h>
#include <glib/gstdio.h>
#include "gog_macros.h"
#include "gog_object_generator.h"
#include "gog_object_templates.h"


#undef G_LOG_DOMAIN
#define G_LOG_DOMAIN "Gog-ObjectGenerator" 

/*
 *  SubsTreeNodes are nodes composing the "Substition" Tree used to allow fast multpile string replacement in a char* buffer
 * 
 *  Convenient functions are provided to manipulate the tree.
 * 
 *  Each node contains a character and pointer to childs node. T
 * 
 *  End user only need to use g_str_substitute ( Defined in this file ).
 */

typedef struct _SubsTreeNode {
    GSList* childs;
    gchar c;
    gchar* substitute;
} SubsTreeNode;

#define SUBS_TREE_NODE(o) ((SubsTreeNode*)o)

static inline SubsTreeNode* subs_tree_node_new(gchar c,gchar* substitute){
    SubsTreeNode* node = g_malloc(sizeof(SubsTreeNode));
    node->childs = NULL;
    node->c = c;
    node->substitute = substitute;      // Assume we don't need to duplicate string
    return node;
}

static inline void subs_tree_node_add_child(SubsTreeNode* self, SubsTreeNode* child){
    self->childs = g_slist_append(self->childs,child);
}


static inline SubsTreeNode* subs_tree_node_get_child_unsorted(SubsTreeNode* self,gchar c){
    
    if ( self->childs == NULL)
        return NULL;
    
    GSList* list = self->childs;
    GSList* current = list;
    
    do {
        SubsTreeNode* node = (SubsTreeNode*)current->data;
        
        if ( c == node->c )
            return node;    
    } while( ( current = g_slist_next(current) ) != NULL );
 
    return NULL;    
}

/* subs_tree_node_get_child provides faster lookup but doesn't work on an unsorted tree */
static inline SubsTreeNode* subs_tree_node_get_child(SubsTreeNode* self,gchar c){
    
    if ( self->childs == NULL)
        return NULL;
    
    GSList* list = self->childs;
    GSList* current = list;
    
    
    do {
        SubsTreeNode* node = (SubsTreeNode*)current->data;
        if ( c < node->c )
            return NULL;
        if ( c == node->c )
            return node;    
    } while( ( current = g_slist_next(current) ) != NULL );
 
    return NULL;    
}

gint subs_tree_node_sort_childs_func(gconstpointer a,gconstpointer b){   
        return (int)SUBS_TREE_NODE(a)->c - (int)SUBS_TREE_NODE(b)->c ;
    }

static void subs_tree_node_sort_childs(SubsTreeNode* self){
          
    self->childs = g_slist_sort(self->childs,&subs_tree_node_sort_childs_func);
     
    for(GSList* iter = self->childs; iter != NULL ; iter = g_slist_next(iter) ){
        subs_tree_node_sort_childs(SUBS_TREE_NODE(iter->data));
    }
}


static inline void subs_tree_node_free(gpointer p){
    
    SubsTreeNode* self = p;
    
    g_slist_free_full(self->childs,subs_tree_node_free);
    
    // Assume that subsiture string isn't a duplicate and hance we don't need to free it
    
    g_free(self);
}


SubsTreeNode* subs_tree_build(gchar** strings,gchar** substitution_strings){
    
    g_assert(strings != NULL && substitution_strings != NULL);
    
    int nb_strings = g_strv_length(strings);
    
    if ( nb_strings != g_strv_length(substitution_strings)){
        g_warning("subs_tree_build : number of strings and replacement strings does not match");
        return NULL;
    }
    
    SubsTreeNode* tree_root = subs_tree_node_new('\0',NULL);
    
    for(int i = 0; i < nb_strings; i++){
        
        SubsTreeNode* iter = tree_root;
        
        size_t length = strlen(strings[i]);
        
        for(int j = 0; j < length ; j++){
            
            SubsTreeNode* get_node = subs_tree_node_get_child_unsorted(iter,strings[i][j]);
            
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
    
    
    /* Sort childs list according to character( Allow faster access during parsing */
    
    subs_tree_node_sort_childs(tree_root);
    
    return tree_root;
}


gchar* g_str_substitute(const gchar* src,gchar** strings,gchar** substitution_strings){
    
    g_return_val_if_fail(src,NULL);
    
    SubsTreeNode* tree_root = subs_tree_build(strings,substitution_strings);
    SubsTreeNode* iter = tree_root;
    
    g_return_val_if_fail(tree_root,NULL);
    
    const gchar* src_begin = src;                 //  Pointers keeping track of the begining and the end of the source buffer interval to be copied to destination buffer
    const gchar* src_end = src;                   
    gchar* dst_ptr = 0;                     //  pointer keeping track of the destination buffer position during the process of copy/substituion

    gchar* dst = 0;                         //  Destination string
    gsize dst_size = 0;                      //  Computed size of the destination buffer
    
    // Compute needed destination buffer size 
    
    do {
        
        iter = subs_tree_node_get_child(iter,*src_end);
        if ( iter == NULL)
            iter = tree_root;
        src_end++;
        
        
        if ( iter != tree_root){
            SubsTreeNode* next = iter;
            
            const gchar* src_end_backup = src_end;
            
            while( (next = subs_tree_node_get_child(next,*src_end)) != NULL  ){
                src_end++;
                iter = next;
            }
            
            if ( iter->substitute != NULL){
                
                dst_size += strlen(iter->substitute);
            }
            else{
                dst_size++;
                src_end = src_end_backup;
            }    
            
            iter = tree_root;
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
           
            const gchar* src_end_backup = src_end - 1;
            
                                    
            SubsTreeNode* next = iter;
            
            while( (next = subs_tree_node_get_child(next,*src_end)) != NULL  ){
                src_end++;
                iter = next;
            }
            
            if ( iter->substitute != NULL){
                memcpy(dst_ptr,src_begin,src_end_backup-src_begin);
                dst_ptr += src_end_backup - src_begin;
                memcpy(dst_ptr,iter->substitute,strlen(iter->substitute));
                dst_ptr += strlen(iter->substitute);
                src_begin = src_end;                
            }
            else{ 
                src_end = src_end_backup + 1;
            }    
            
            iter = tree_root;
        } 
       
        
        
    } while(*src_end != '\0');
    
    memcpy(dst_ptr,src_begin,src_end - 1 -src_begin);
    dst_ptr += src_end - 1 - src_begin;
    *dst_ptr = '\0';
        
    if ( tree_root ) subs_tree_node_free(tree_root);
        
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


static gchar* gog_generate_object_file_from_memory(const gchar* src,gchar* _namespace,gchar* _object_name,gchar* _parent_namespace,gchar* _parent_object_name){
    

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
        ENUM_END,
        ENUM_TOTAL
    };
    
    gchar* strings[ENUM_TOTAL] =
    {
        "NAMESPACE"     ,   "Namespace"     ,   "namespace", 
        "OBJECTNAME"    ,   "ObjectName"    ,   "objectname",
        "PNAMESPACE"    ,   "PNamespace"    ,   "pnamespace",
        "POBJECTNAME"   ,   "PObjectName"   ,   "pobjectname",
        NULL,
    };
    
    gchar* substitute_strings[ENUM_TOTAL];
    
    substitute_strings[NAMESPACE_MACRO] = gog_str_make_macro(_namespace);
    substitute_strings[NAMESPACE_NAME] = gog_str_make_name(_namespace);
    substitute_strings[NAMESPACE_FUNC] = gog_str_make_func(_namespace);
    substitute_strings[OBJECTNAME_MACRO] = gog_str_make_macro(_object_name);
    substitute_strings[OBJECTNAME_NAME] = gog_str_make_name(_object_name);
    substitute_strings[OBJECTNAME_FUNC] = gog_str_make_func(_object_name);
    substitute_strings[PARENT_NAMESPACE_MACRO] = gog_str_make_macro(_parent_namespace);
    substitute_strings[PARENT_NAMESPACE_NAME] = gog_str_make_name(_parent_namespace);
    substitute_strings[PARENT_NAMESPACE_FUNC] = gog_str_make_func(_parent_namespace);
    substitute_strings[PARENT_OBJECTNAME_MACRO] = gog_str_make_macro(_parent_object_name);
    substitute_strings[PARENT_OBJECTNAME_NAME] = gog_str_make_name(_parent_object_name);
    substitute_strings[PARENT_OBJECTNAME_FUNC] = gog_str_make_func(_parent_object_name);
    substitute_strings[ENUM_END] = NULL;
    
    
    gchar* dst = g_str_substitute(src,strings,substitute_strings);
     
               
    for(int i = 0; i < ENUM_TOTAL; i++) 
        if ( substitute_strings[i] ){
            g_free(substitute_strings[i]);
        }
    
    
    return dst;
    
}


void gog_generate_object_file(const gchar* src,gchar* output_path,gchar* _namespace,gchar* _object_name,gchar* _parent_namespace,gchar* _parent_object_name){
    
    GError* error = 0;  
        
    gchar* write_buffer = gog_generate_object_file_from_memory(src,_namespace,_object_name,_parent_namespace,_parent_object_name);
    

    GIOChannel* output_channel = g_io_channel_new_file(output_path,"w",&error);
    GOG_ERROR(error,"Error while opening output file : %s",error->message);
    
    g_io_channel_write_chars(output_channel,write_buffer,strlen(write_buffer),NULL,&error);
    GOG_ERROR(error,"Error while writing to ouput file : %s",error->message);

    cleanup:
    
    if ( output_channel ) {
        g_io_channel_shutdown(output_channel,TRUE,NULL);
        g_io_channel_unref(output_channel);
    }

 
    if ( write_buffer) g_free(write_buffer);            
}


void gog_generate_object(gint object_type,gchar* output_path ,gchar* _namespace,gchar* _objectname,gchar* _parent_namespace,gchar* _parent_object_name){
    
    GString* header_output_path = g_string_new(output_path);
    g_string_append_printf(header_output_path,"%s_%s.h",_namespace,_objectname);
    
    GString* source_output_path = g_string_new(output_path);
    g_string_append_printf(source_output_path,"%s_%s.c",_namespace,_objectname);
    
    switch(object_type){
        case GOG_OBJECT_FINAL_PRIVATE:
             gog_generate_object_file(_data_object_final_private_c,source_output_path->str,_namespace,_objectname,_parent_namespace,_parent_object_name);
             gog_generate_object_file(_data_object_final_private_h,header_output_path->str,_namespace,_objectname,_parent_namespace,_parent_object_name);
             break;
             
        default:
            break;
    
    }
  
    g_string_free(header_output_path,TRUE);
    g_string_free(source_output_path,TRUE);
}








