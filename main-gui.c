/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: drolland
 *
 * Created on 20 novembre 2016, 18:31
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk-3.0/gtk/gtk.h>
#include <glib-2.0/glib/gerror.h>
#include <glib-2.0/glib/gmessages.h>

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
    
  GtkCssProvider* css_provider = GTK_CSS_PROVIDER(gtk_css_provider_new());
  GtkStyleContext* style_context = NULL;
  GError* error = NULL;
  gtk_css_provider_load_from_path(css_provider,"./gtk-3.0/gtk.css",&error);
  
  
  if ( error) {
      g_critical("error %s\n",error->message);
     
  }
  
  GtkWidget *window;
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
  
  GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL,30);
  GtkWidget* calendar = gtk_calendar_new();
  
  GtkWidget* button = gtk_button_new_with_label("click me");
  
 

  
  gtk_container_add(GTK_CONTAINER(window),box);
  
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,FALSE,10);
  gtk_box_pack_start(GTK_BOX(box),calendar,TRUE,FALSE,10);
  
  //style_context = gtk_style_context_new(style_context);
  //gtk_widget_path *path = gtk_widget_path_new ();
  //gtk_widget_path_append_type (path, GTK_TYPE_WINDOW);
  
  //gtk_style_context_add_provider(style_context,GTK_STYLE_PROVIDER(css_provider),1000);
  

  
  
  
  
  
 

  
  gtk_widget_show(GTK_WIDGET(button));
  gtk_widget_show_all (window);

  gtk_style_context_add_provider(gtk_widget_get_style_context(GTK_WIDGET(window)),GTK_STYLE_PROVIDER(css_provider),1000);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),GTK_STYLE_PROVIDER(css_provider),1000);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;

}