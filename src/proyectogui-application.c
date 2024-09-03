#include <glib/gi18n.h>
#include "proyectogui-application.h"
#include "proyectogui-window.h"

struct _ProyectoguiApplication
{  
  GtkApplication parent_instance;
  GtkWindow *window;
};
 
G_DEFINE_TYPE (ProyectoguiApplication, proyectogui_application, GTK_TYPE_APPLICATION)

static void
proyectogui_application_quit_action (GSimpleAction *action,
                                     GVariant      *parameter,
                                     gpointer      *user_data)
{
 ProyectoguiApplication *proyectogui;
 proyectogui = PROYECTOGUI_APPLICATION (user_data);
 gtk_widget_destroy (GTK_WIDGET (proyectogui -> window)); 
}

static void
proyectogui_application_about_action (GSimpleAction *action,
                                      GVariant      *parameter,
                                      gpointer      *user_data)
{
  ProyectoguiApplication *proyectogui;
  proyectogui = PROYECTOGUI_APPLICATION (user_data);
  GtkWidget *about_dialog;
  const gchar *authors[] = {
    "Datos del estudiante",
    NULL
  };
  const gchar *artists[] = {
    "Datos del estudiante",
    NULL
  };
  about_dialog = g_object_new (GTK_TYPE_ABOUT_DIALOG,
                               "transient-for", GTK_WINDOW (proyectogui -> window),
                               "modal", TRUE,
                               "destroy-with-parent", TRUE,
                               "program-name", "ProyectoFinal",
                               "comments", "DETALLES DEL DESARROLLO",
                               "version", "1.0 - BETA",
                               "website-label", "OPCIONAL LINK",
                               "website", "https://link",
                               "authors", authors,
                               "artists", artists,
                               NULL);
  gtk_widget_show_all (about_dialog);
  
}

static void
proyectogui_application_activate (GtkApplication *application)
{
  ProyectoguiApplication *proyectogui;
  g_assert (GTK_IS_APPLICATION (application));
  proyectogui = PROYECTOGUI_APPLICATION (application);
  proyectogui -> window = gtk_application_get_active_window (application);
  if (proyectogui -> window == NULL)
    proyectogui -> window = g_object_new (PROYECTOGUI_TYPE_WINDOW,
                                 "application",application,
                                 NULL);
  gtk_window_present (proyectogui -> window);
}

static void
proyectogui_application_startup (GtkApplication *application)
{
  ProyectoguiApplication *proyectogui;
  proyectogui = PROYECTOGUI_APPLICATION (application);
  static const GActionEntry app_entry[] = {
      {"quit", proyectogui_application_quit_action, NULL, NULL, NULL},
      {"about_dialog", proyectogui_application_about_action, NULL, NULL, NULL},
  };
  g_action_map_add_action_entries (G_ACTION_MAP (application),
                                   app_entry,
                                   G_N_ELEMENTS (app_entry),
                                   application);
  G_APPLICATION_CLASS (proyectogui_application_parent_class) -> startup (application);
  
}

ProyectoguiApplication *
proyectogui_application_new (void)
{
  return g_object_new (PROYECTOGUI_TYPE_APPLICATION, 
                       "resource_base_path", "Proyectos/Builder/ProyectoFinal",
                       "application-id", "/org/my/ProyectoGUI",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}

static void
proyectogui_application_class_init (ProyectoguiApplicationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  G_APPLICATION_CLASS (klass) ->activate = proyectogui_application_activate;
  G_APPLICATION_CLASS (klass) ->startup = proyectogui_application_startup;
}

static void
proyectogui_application_init (ProyectoguiApplication *self)
{
  /*Inicializa la app, aquí deben implementarse las funciones que capturan las acciones declaradas
    en el control(objeto, un gtkobject) de la UI diseñada.
    EJEMPLO: un botón para mostrar datos.  
  gtk_application_set_accels_for_action (GTK_APPLICATION (self),
                                         "win.MOSTRAR",
                                         (const char *[]) { NULL, NULL});
  */
}
