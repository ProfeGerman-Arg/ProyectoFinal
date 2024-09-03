#include "proyectogui-config.h"
#include "proyectogui-window.h"

struct _ProyectoguiWindow
{
  GtkApplicationWindow  parent_instance;
  GtkHeaderBar        *header_bar;
  GtkBox              *box;
  
};

G_DEFINE_TYPE (ProyectoguiWindow, proyectogui_window, GTK_TYPE_APPLICATION_WINDOW)

static void
proyectogui_window_class_init (ProyectoguiWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/my/ProyectoGUI/proyectogui-window.ui");
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, ProyectoguiWindow, box);
}
                        

static void
capturar_accion (ProyectoguiWindow *self, gchar *action_name, GCallback handler)
{
  GSimpleAction *action = g_simple_action_new (action_name, NULL);
  g_signal_connect_swapped (action, "activate", handler, self);
  g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (action));
}

static void
proyectogui_window_init (ProyectoguiWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
  
  /*Invocar a la función que registra eventuales acciones en los controles de la ventana (los ojetos, gtkobjetc),
    recordar que luego, de alguna manera debe incluirse un código para ese botón con lo que mostrará
    al ser clickeado, es decir debe llamarse a la función que a continuación se ejemplifica 
  EJEMPLO:
  capturar_accion (self, "mostrar", G_CALLBACK(cargar_clickeado));*/
}
