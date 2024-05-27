#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#define DIM 105

int MinOfTwo(int a, int b) {
    return a < b ? a : b;
}

int levenshtein_distance(const char *s1, const char *s2) {
    int m = strlen(s1);
    int n = strlen(s2);
    int **dp = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (s1[i] == s2[j]) {
                dp[i + 1][j + 1] = dp[i][j];
            } else {
                int insert_cost = dp[i + 1][j] + 1;
                int delete_cost = dp[i][j + 1] + 1;
                int replace_cost = dp[i][j] + 1;

                if (i > 0 && j > 0 && s1[i - 1] == s2[j] && s1[i] == s2[j - 1]) {
                    int swap_cost = dp[i - 1][j - 1] + 1;
                    replace_cost = MinOfTwo(replace_cost, swap_cost);
                }
                dp[i + 1][j + 1] = MinOfTwo(MinOfTwo(insert_cost, delete_cost), replace_cost);
            }
        }
    }

    int result = dp[m][n];
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

void calculate_distance(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const char *str1 = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const char *str2 = gtk_entry_get_text(GTK_ENTRY(entries[1]));

    int distance = levenshtein_distance(str1, str2);

    char message[256];
    snprintf(message, sizeof(message), "The minimum number of operations to transform '%s' into '%s' is %d", str2, str1, distance);

    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label1, *label2;
    GtkWidget *entry1, *entry2;
    GtkWidget *button;
    GtkWidget *entries[2];

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Edit Distance Calculator");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    label1 = gtk_label_new("Enter the first string:");
    label2 = gtk_label_new("Enter the second string:");
    entry1 = gtk_entry_new();
    entry2 = gtk_entry_new();
    button = gtk_button_new_with_label("Calculate Distance");

    entries[0] = entry1;
    entries[1] = entry2;

    g_signal_connect(button, "clicked", G_CALLBACK(calculate_distance), entries);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_grid_attach(GTK_GRID(grid), label1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry1, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 2, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

