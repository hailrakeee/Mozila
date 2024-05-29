#include <e-util/e-module.h>
#include <libedataserver/libedataserver.h>
#include <libebackend/libebackend.h>
#include <libeshell/libeshell.h>
#include <gtk/gtk.h>

typedef struct _EMeetingPlugin EMeetingPlugin;
typedef struct _EMeetingPluginClass EMeetingPluginClass;

struct _EMeetingPlugin {
    EExtension parent;
};

struct _EMeetingPluginClass {
    EExtensionClass parent_class;
};

G_DEFINE_DYNAMIC_TYPE(EMeetingPlugin, e_meeting_plugin, E_TYPE_EXTENSION)

static void
on_button_clicked(GtkWidget *widget, gpointer data)
{
    g_print("Meeting button clicked!\n");
    // Здесь можно добавить логику создания встречи
}

static void
e_meeting_plugin_constructed(GObject *object)
{
    EExtensible *extensible;
    GtkWidget *button;

    extensible = e_extension_get_extensible(E_EXTENSION(object));

    // Создаем кнопку
    button = gtk_button_new_with_label("Create Meeting");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_widget_show(button);

    // Добавляем кнопку в панель инструментов окна Shell
    if (G_TYPE_CHECK_INSTANCE_TYPE(extensible, E_TYPE_SHELL)) {
        EShell *shell = E_SHELL(extensible);
        GtkWidget *toolbar = e_shell_get_toolbar(shell);
        if (toolbar) {
            gtk_toolbar_insert(GTK_TOOLBAR(toolbar), GTK_TOOL_ITEM(button), -1);
            gtk_widget_show(button);
        }
    }

    E_EXTENSION_CLASS(e_meeting_plugin_parent_class)->constructed(object);
}

static void
e_meeting_plugin_finalize(GObject *object)
{
    g_print("EMeetingPlugin finalized\n");

    G_OBJECT_CLASS(e_meeting_plugin_parent_class)->finalize(object);
}

static void
e_meeting_plugin_class_init(EMeetingPluginClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->constructed = e_meeting_plugin_constructed;
    object_class->finalize = e_meeting_plugin_finalize;

    EExtensionClass *extension_class = E_EXTENSION_CLASS(klass);
    extension_class->extensible_type = E_TYPE_SHELL;
}

static void
e_meeting_plugin_class_finalize(EMeetingPluginClass *klass)
{
}

static void
e_meeting_plugin_init(EMeetingPlugin *plugin)
{
}

G_MODULE_EXPORT void
e_module_load(GTypeModule *module)
{
    e_meeting_plugin_register_type(module);
}

G_MODULE_EXPORT void
e_module_unload(GTypeModule *module)
{
}
