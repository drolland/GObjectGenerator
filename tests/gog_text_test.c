/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   gog_text_test.c
 * Author: drolland
 *
 * Created on 17 décembre 2016, 11:48
 */

#include <glib-2.0/glib.h>
#include "../gog_text.h"



void test_append_line(){
    
    GogText* gt = gog_text_new();

    gchar* text1 = NULL;
    gchar* text2 = "";
    gchar* text3 = "Les sanglots longs\n des violons de l'automne\n m'ecoeurent\n\n\n Enfin";
    
    gog_text_append_lines(gt,text3);
    int nb_lines = gog_text_get_nb_lines(gt);
    g_assert_cmpint(6,==,nb_lines);
    
    gog_text_append_lines(gt,text3);
    nb_lines = gog_text_get_nb_lines(gt);
    g_assert_cmpint(12,==,nb_lines);
    
    
    
    
}

int main(int argc, char** argv) {
        
    g_test_init(&argc,&argv,NULL);
    
    g_test_add_func ("/gog_text/append_line",test_append_line);
    
   
    
    
    
    return g_test_run ();

}
