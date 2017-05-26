/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>

#include "gog_object_generator.h"

static char* object_type = NULL;

#define usage_string                                                                            \
"namespace objet_name parent_namespace parent_objectname\n\n"                                     \
"  Create a glib gobject. You need to supply the four parameters described above.\n"             \
"  Exemple: gogen wh text_file g object, creates a WhTextFile Object derived from GObject"        \


#define object_type_help_string                         \
"Type of object to create. Available types are:\n"      \
"\t\t\t\tFINAL_PRIVATE"                                      


static GOptionEntry entries[] =
{
  { "object-type", 'o', 0, G_OPTION_ARG_STRING, &object_type, object_type_help_string, "TYPE" },
  { NULL }
};


int main(int argc,char** argv){
    
    GError *error = NULL;
    GOptionContext *context;

    context = g_option_context_new (usage_string);
    g_option_context_set_help_enabled (context,TRUE);
    g_option_context_add_main_entries (context, entries, NULL);
    if (!g_option_context_parse (context, &argc, &argv, &error))
    {
      g_print ("option parsing failed: %s\n", error->message);
      exit(EXIT_FAILURE);
    }
    
    if ( argc == 5)
    {
        gog_generate_object(GOG_OBJECT_FINAL_PRIVATE,NULL,argv[1],argv[2],argv[3],argv[4]);
    }
    
    
    if ( argc != 5)
    {
        //g_print("%s",g_option_context_get_help(context,FALSE,NULL));
        gog_generate_object(GOG_OBJECT_FINAL_PRIVATE,NULL,"wh","text_file","g","object");
    }
    
    
    
}