/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   generate.c
 * Author: denis
 *
 * Created on 26 mai 2017, 12:58
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib-2.0/glib.h>
#include <malloc.h>
#include "../gog_object_generator.h"



void test_object_final_private(){

    gog_generate_object(GOG_OBJECT_FINAL_PRIVATE,"","wh","text_file","g","object");
    
}

int main(int argc, char** argv) {
        
    g_print("\e[34m");
    
    g_print("GOG Object Generator tests\n");
     
    g_test_init(&argc,&argv,NULL);
    
    g_test_add_func ("/gog_object_generator/object_final_private",test_object_final_private);
    
    g_printf("\e[0m");
    
    return g_test_run ();

}

